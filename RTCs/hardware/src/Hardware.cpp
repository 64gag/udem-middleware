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

#define EXEC_DELAY 1000

enum {
        HW_CURRENT=0,
        HW_TARGET,
        HW_COUNT
};

enum {
        ANGLE_1=0,
        ANGLE_2,
        ANGLE_3,
	ANGLE_GRIPPER,
	ANGLE_COUNT
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
    ""
  };
// </rtc-template>

class H9_Hardware {
 private:
	float slopes[ANGLE_COUNT];
	float angles[HW_COUNT][ANGLE_COUNT];
	int updated;
 public:
	H9_Hardware();
	int setValues(float*, float*, unsigned short int);
	std::string getJSON(unsigned short int t);
	void setSlopes(float*);
	void doUpdate(void);
} HW;

void H9_Hardware::setSlopes(float *s){
	setValues(NULL, s, 0);
}

void H9_Hardware::doUpdate(void){
	for(int i=0;i<ANGLE_COUNT;i++){
		if (angles[HW_CURRENT][i] != angles[HW_TARGET][i])
		{
			updated = 1;
			float smaller_current = (((float)(angles[HW_CURRENT][i]<angles[HW_TARGET][i]))-0.5f)*2.0f;	//Ugly way to get -1 or 1
			float diff = (angles[HW_TARGET][i]-angles[HW_CURRENT][i])*smaller_current;
			angles[HW_CURRENT][i] += (diff>slopes[i] ? slopes[i]: diff)*smaller_current;			//Should I use setValues()? :P
		}
	}
}

H9_Hardware::H9_Hardware(){
// Read these from the robot
	float slopes[4] = {0.5f, 0.5f, 0.5f, 0.5f};
	this->setSlopes(slopes);
	float initial_angles[4] = {0.0f, 45.0f, -10.0f, 0.0f};
	this->setValues(initial_angles, NULL, HW_CURRENT);
// These will be received from the master block
	float t_angles[4] = {1.1f, 0.0f, 10.0f, 1.0f};
	this->setValues(t_angles, NULL, HW_TARGET);
}

int H9_Hardware::setValues(float* a, float* s, unsigned short int t = 0){
	if(a){
		for(int i=0;i<ANGLE_COUNT;i++){
			angles[t][i]=a[i];
		}
	}

	if(s){
		for(int i=0;i<ANGLE_COUNT;i++){
			slopes[i]=s[i];
		}
	}
	return 0;
}

std::string H9_Hardware::getJSON(unsigned short int t = 0){

	std::ostringstream out;
	out << "<WRIST>([ANGLE.1:" << angles[t][ANGLE_1] << "][ANGLE.2:" << angles[t][ANGLE_2] << "][ANGLE.3:" << angles[t][ANGLE_3] << "][GRIPPER:" << angles[t][ANGLE_GRIPPER] << "])";
	Json::Value toRobot;
	toRobot["ns"] = "org.jwebsocket.plugins.system";
	toRobot["type"] = "broadcast";
	toRobot["data"] = out.str();
	toRobot["responseRequested"] = true;
	toRobot["utid"] = 1;

 return toRobot.toStyledString();
}

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
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onStartup(RTC::UniqueId ec_id)
{

	for(int xx=0;xx<10;xx++)
	{
		std::cout << HW.getJSON(HW_CURRENT) << std::endl;
		HW.doUpdate();
		coil::usleep(EXEC_DELAY);
	}

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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onDeactivated(RTC::UniqueId ec_id)
{


std::cout << "Ran onDeactivated" << std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onExecute(RTC::UniqueId ec_id)
{



// Creation//





  coil::usleep(1000000);
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


