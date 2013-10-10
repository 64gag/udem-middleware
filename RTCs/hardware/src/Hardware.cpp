// -*- C++ -*-
/*!
 * @file  Hardware.cpp
 * @brief Interface/filter between master and real/simulated robot
 * @date $Date$
 *
 * $Id$
 */
#include <sstream>
#include <iostream>
#include <json/json.h>
#include "Hardware.h"

#define EXEC_DELAY 500000

enum {
        HW_CURRENT=0,
        HW_TARGET,
        HW_COUNT
};

enum {
	V_SLOPES=0,
	V_CURRENT,
	V_TARGET
};

// Module specification
// <rtc-template block="module_spec">
static const char* hardware_spec[] =
  {
    "implementation_id", "Hardware",
    "type_name",         "Hardware",
    "description",       "Interface/filter between master and real/simulated robot",
    "version",           "0.0.1",
    "vendor",            "UDEM",
    "category",          "Interfac",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "5",
    "language",          "C++",
    "lang_type",         "compile",
    "conf.default.int_joints", "8",
    "conf.default.str_json_data_format", "<WRIST>([ANGLE.1:%][ANGLE.2:%][ANGLE.3:%][ANGLE.4:%][ANGLE.5:%][ANGLE.6:%][ANGLE.7:%][GRIPPER:%])",
    "conf.default.str_slopes", "0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5",
    ""
  };
// </rtc-template>

/* Evan Teran's string-splitting code from: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s); std::string item;
    while (std::getline(ss, item, delim)) { elems.push_back(item); }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems; split(s, delim, elems);
    return elems;
}

/* Split a string of comma-separated floats and stores them in a vector of floats */
void strings2floats(std::string *s, std::vector<float> *f)
{
	std::vector<std::string> str_slopes = split(*s, ',');

	for(std::vector<std::string>::iterator it = str_slopes.begin(); it != str_slopes.end(); ++it) {
		f->push_back(::atof((*it).c_str()));
	}
}

/* Extracts float numbers from 's' using format 'f' (where floats are specified by 'token') */
std::vector<float> getFloats(std::string s, std::string f, char token)
{
	std::vector<float> ret;
	std::vector<std::string> exploded = split(f, token);

	for(unsigned int i=0; i+1 < exploded.size(); i++){
		s = s.substr(exploded[i].length());
		std::size_t notnum = s.find_first_not_of("0123456789.");
		ret.push_back(::atof(s.substr(0, notnum).c_str()));
		s = s.substr(notnum);
	}
 return ret;
}

class HardwareController {
 private:
	int joints_count;
	unsigned int utid;
	std::vector<float> slopes;
	std::vector<float> angles_current;
	std::vector<float> angles_target;
	std::string json_data_format;
 public:
	HardwareController(int, std::vector<float>, std::string);
	~HardwareController(void);
	void setValues(std::vector<float>, unsigned short int);
	void setValues(std::string, unsigned short int);
	void setValues(std::string);
	unsigned int doUpdate(void);
	std::string getJSON(void);
	unsigned int haveCurrent();
	unsigned int haveTarget();
};

unsigned int HardwareController::haveCurrent(void)
{
	return angles_current.size();
}

unsigned int HardwareController::haveTarget(void)
{
	return angles_target.size();
}

void HardwareController::setValues(std::string s)
{
	setValues(getFloats(s, json_data_format, '%'), V_CURRENT);
}

void HardwareController::setValues(std::string s, unsigned short int t)
{
	std::vector<float> f;
	strings2floats(&s, &f);
	setValues(f,t);
}


void HardwareController::setValues(std::vector<float> v, unsigned short int t)
{
	switch(t){
		case V_SLOPES:
			slopes = v;
		break;
		case V_CURRENT:
			angles_current = v;
		break;
		case V_TARGET:
			angles_target = v;
		break;
	}
}


unsigned int HardwareController::doUpdate(void){

 unsigned int ret = 0;
	for(int i=0;i<joints_count;i++)
	{
		if (angles_current[i] != angles_target[i])
		{
			ret |= (1 << i);
			float smaller_current = (((float)(angles_current[i]<angles_target[i]))-0.5f)*2.0f;	//Ugly way to get -1 or 1
			float diff = (angles_target[i]-angles_current[i])*smaller_current;
			angles_current[i] += (diff>slopes[i] ? slopes[i]: diff)*smaller_current;
		}
	}

 return ret;
}

HardwareController::HardwareController(int j, std::vector<float> s, std::string f){
	utid = 1;
	joints_count = j;
	slopes = s;
	json_data_format = f;
	setValues("14,34,-1,-2,3,1,50,20", V_TARGET);
}


HardwareController::~HardwareController(void)
{
}

std::string HardwareController::getJSON(void){

	std::ostringstream out;
	std::vector<std::string> format_pieces = split(json_data_format, '%');

	unsigned int i;
	for(i=0; i<format_pieces.size(); i++){
		out << format_pieces[i];
		if(i+1 < format_pieces.size())
		{
			out << angles_current[i];
		}
	}
	Json::Value toRobot;
	toRobot["ns"] = "org.jwebsocket.plugins.system";
	toRobot["type"] = "broadcast";
	toRobot["data"] = out.str();
	toRobot["responseRequested"] = true;
	toRobot["utid"] = utid++;

 return toRobot.toStyledString();
}


class HardwareController* HW = NULL;


/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Hardware::Hardware(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_positionIn("Position", m_p_position),
    m_p_feedbackIn("Feedback", m_p_feedback),
    m_p_statusOut("Status", m_p_status),
    m_p_dataOut("Data", m_p_data)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Hardware::~Hardware()
{
}

RTC::ReturnCode_t Hardware::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Position", m_p_positionIn);
  addInPort("Feedback", m_p_feedbackIn);
  
  // Set OutPort buffer
  addOutPort("Status", m_p_statusOut);
  addOutPort("Data", m_p_dataOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  bindParameter("int_joints", m_int_joints, "8");
  bindParameter("str_json_data_format", m_str_json_data_format, "<WRIST>([ANGLE.1:%][ANGLE.2:%][ANGLE.3:%][ANGLE.4:%][ANGLE.5:%][ANGLE.6:%][ANGLE.7:%][GRIPPER:%])");
  bindParameter("str_slopes", m_str_slopes, "0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5");
  // </rtc-template>

 return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onFinalize()
{
 return RTC::RTC_OK;
}

RTC::ReturnCode_t Hardware::onStartup(RTC::UniqueId ec_id)
{
 return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t Hardware::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Hardware::onActivated(RTC::UniqueId ec_id)
{
	/* Load configurations to a new HardwareController object */
	std::vector<float> slopes;
	strings2floats(&m_str_slopes, &slopes);
	HW = new HardwareController(m_int_joints, slopes, m_str_json_data_format);

 return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onDeactivated(RTC::UniqueId ec_id)
{
	delete HW;

 return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onExecute(RTC::UniqueId ec_id)
{
	/* Listen to the master */
	if (m_p_positionIn.isNew())
	{
		m_p_positionIn.read();
		std::ostringstream out;
		out << m_p_position.data; /* Is there a better way to do this? */
		HW->setValues(out.str(), V_TARGET);
	}

	/* Get the data the real/simulated robot sends back */
	if (m_p_feedbackIn.isNew())
	{
		m_p_feedbackIn.read();
		std::ostringstream out;
		out << m_p_feedback.data; /* Is there a better way to do this? */

		/* Parse received data */
		{
			Json::Value root;
			Json::Reader reader;
			bool parsedSuccess = reader.parse(out.str(), root, false);
			if(!parsedSuccess)
			{
				//panic out
			}
			HW->setValues(root["data"].asString());
		}
	}

	if(HW->haveCurrent() && HW->haveTarget()){ /* Check if we know the current and desired status, otherwise don't do anything */
		unsigned int unready_joints = HW->doUpdate();
		if(unready_joints)
		{
			m_p_status.data = unready_joints;
			m_p_statusOut.write();
			m_p_data.data = HW->getJSON().c_str();
			m_p_dataOut.write();
		}else{ /* All joints ready, won't update */
			if(m_p_status.data) /* Set status to 0 so the Master block knows we are done */
			{
				m_p_status.data = 0;
				m_p_statusOut.write();
			}
		}
	}

	coil::usleep(EXEC_DELAY);

 return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Hardware::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Hardware::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Hardware::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Hardware::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Hardware::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

extern "C"
{
 
  void HardwareInit(RTC::Manager* manager)
  {
    coil::Properties profile(hardware_spec);
    manager->registerFactory(profile,
                             RTC::Create<Hardware>,
                             RTC::Delete<Hardware>);
  }
  
};


