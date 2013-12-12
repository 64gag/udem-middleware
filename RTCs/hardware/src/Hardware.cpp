#include <sstream>
#include <iostream>
#include <json/json.h>
#include "Hardware.h"
#include "HardwareController.h"
#include "HardwareAux.h"

#define DEBUG

int waiting_feedback;

static const char* hardware_spec[] =
{
	"implementation_id", "Hardware",
	"type_name",         "Hardware",
	"description",       "Interface/filter between master and real/simulated robot",
	"version",           "0.0.1",
	"vendor",            "UDEM",
	"category",          "Interface",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "5",
	"language",          "C++",
	"lang_type",         "compile",
	"conf.default.int_exec_delay", "100000",
	"conf.default.int_joints", "9",
	"conf.default.str_json_data_format", "<WRIST>([ANGLE.1:%][ANGLE.2:%][ANGLE.3:%][ANGLE.4:%][ANGLE.5:%][ANGLE.6:%][GRIPPER:%][MOTOR_L:%][MOTOR_R:%])",
	"conf.default.str_slopes", "0.05,0.05,0.05,0.05,0.05,0.05,0.05,1000,1000",
	""
};

class HardwareController* HW = NULL;

Hardware::Hardware(RTC::Manager* manager)

  : RTC::DataFlowComponentBase(manager),
    m_p_positionIn("Position", m_p_position),
    m_p_feedbackIn("Feedback", m_p_feedback),
    m_p_statusOut("Status", m_p_status),
    m_p_dataOut("Data", m_p_data)
{
}

Hardware::~Hardware()
{
}

RTC::ReturnCode_t Hardware::onInitialize()
{
	// Set InPort buffers
	addInPort("Position", m_p_positionIn);
	addInPort("Feedback", m_p_feedbackIn);
	  
	// Set OutPort buffer
	addOutPort("Status", m_p_statusOut);
	addOutPort("Data", m_p_dataOut);
	bindParameter("int_joints", m_int_joints, "9");
	bindParameter("str_json_data_format", m_str_json_data_format, "<WRIST>([ANGLE.1:%][ANGLE.2:%][ANGLE.3:%][ANGLE.4:%][ANGLE.5:%][ANGLE.6:%][GRIPPER:%][MOTOR_L:%][MOTOR_R:%])");
	bindParameter("str_slopes", m_str_slopes, "0.05,0.05,0.05,0.05,0.05,0.05,0.05,1000,1000");

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

RTC::ReturnCode_t Hardware::onActivated(RTC::UniqueId ec_id)
{
	/* Load configurations to a new HardwareController object */
	HW = new HardwareController(m_int_joints, string2floats(m_str_slopes));
	HW->setCurrent(string2floats("0,0,0,0,0,0,0,0,0"));
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
	if (m_p_positionIn.isNew()) {
		m_p_positionIn.read();
		std::string port_str = (char *)m_p_position.data;
#ifdef DEBUG
		std::cout << port_str << std::endl;
#endif
		HW->setTarget(string2floats(port_str));
	}

	/* Get the data the real/simulated robot sends back */
	if (m_p_feedbackIn.isNew()) {
		m_p_feedbackIn.read();
		std::string port_str = (char*)m_p_feedback.data;

		/* Parse received data */
		{
			Json::Value root;
			Json::Reader reader;
			bool parsedSuccess = reader.parse(port_str, root, false);
			if(!parsedSuccess) {
				//panic out
			}
			HW->setCurrent(extractFloats(root["data"].asString(), m_str_json_data_format, '%'));
			waiting_feedback = 0;
		}
	}

	if(waiting_feedback) /* Dont run faster than the simulation */
		return RTC::RTC_OK;

	unsigned int unready_joints = HW->doUpdate();
	if(unready_joints) {
#ifdef DEBUG
		std::cout << "Unready joints" << std::endl;
#endif
		m_p_status.data = unready_joints; /* Report the master block we are not done */
		m_p_statusOut.write();
#ifdef DEBUG
		std::cout << HW->getJSON(m_str_json_data_format).c_str() << std::endl;
#endif
		m_p_data.data = HW->getJSON(m_str_json_data_format).c_str();
		m_p_dataOut.write();
		waiting_feedback = 1;
	}else{ /* All joints ready, won't update */
		if(m_p_status.data) { /* Set status to 0 so the Master block knows we are done */
			m_p_status.data = 0;
			m_p_statusOut.write();
		}
	}

	coil::usleep(m_int_exec_delay);

	return RTC::RTC_OK;
}

extern "C" {
void HardwareInit(RTC::Manager* manager)
{
	coil::Properties profile(hardware_spec);
	manager->registerFactory(profile, RTC::Create<Hardware>, RTC::Delete<Hardware>);
} 
};


