#include <json/json.h>
#include "Simulation.h"
#include "SimulationBridge.h"
#include "FloatsAux.h"

static const char* simulation_spec[] =
{
	"implementation_id", "Simulation",
	"type_name",         "Simulation",
	"description",       "Simulation wrapper",
	"version",           "0.0.1",
	"vendor",            "VenderName",
	"category",          "Category",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	"conf.default.int_joints", "9",
	""
};

Simulation::Simulation(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_p_dataIn("Data", m_p_data),
    m_p_feedbackOut("Feedback", m_p_feedback)
{
}

Simulation::~Simulation()
{
}

RTC::ReturnCode_t Simulation::onInitialize()
{
  addInPort("Data", m_p_dataIn);
  addOutPort("Feedback", m_p_feedbackOut);
  bindParameter("int_joints", m_int_joints, "9");

  return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onActivated(RTC::UniqueId ec_id)
{
	std::cout << "SimulationComp activated" << std::endl;
	char host[] = "127.0.0.1"; 
	ws_rosbridge_open(host, 9090);
	return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onDeactivated(RTC::UniqueId ec_id)
{
	ws_rosbridge_close();
	return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onExecute(RTC::UniqueId ec_id)
{
	if (m_p_dataIn.isNew())
	{
		std::cout << "DataIn New" << std::endl;
		std::vector<float> extracted;
		m_p_dataIn.read();
		{
			std::string port_str = (char*)m_p_data.data;
			m_p_feedback.data = port_str.c_str();
			m_p_feedbackOut.write();

			Json::Value root;
			Json::Reader reader;
			bool parsedSuccess = reader.parse(port_str, root, false);
			if(!parsedSuccess) {
				//panic out
			}
			extracted = extractFloats(root["data"].asString(), "<WRIST>([ANGLE.1:%][ANGLE.2:%][ANGLE.3:%][ANGLE.4:%][ANGLE.5:%][ANGLE.6:%][GRIPPER:%][MOTOR_L:%][MOTOR_R:%])", '%');

			int joint_handles[6] = {58, 60, 62, 64, 66, 68};
			int joint_setModes[6] = {0, 0, 0, 0, 0, 0};
			float joint_values[6];
			for(int i = 0; i < 6; i++)
				joint_values[i] = extracted[i];

			simRosSetJointState(6, joint_handles, joint_setModes, joint_values);
		}
#ifdef DEBUG
//		std::cout << rosbridge_msg.toStyledString() << std::endl;
#endif

		{
			int joint_handles[2] = {50, 52};
			int joint_setModes[2] = {2, 2};
			float joint_values[2] = {extracted[7], extracted[8]};
			simRosSetJointState(2, joint_handles, joint_setModes, joint_values);
		}
#ifdef DEBUG
//		std::cout << rosbridge_msg.toStyledString() << std::endl;
#endif

#ifdef DEBUG
//		std::cout << rosbridge_msg.toStyledString() << std::endl;
#endif

	}

	coil::usleep(1000);

	return RTC::RTC_OK;
}

extern "C"
{
  void SimulationInit(RTC::Manager* manager)
  {
    coil::Properties profile(simulation_spec);
    manager->registerFactory(profile,
                             RTC::Create<Simulation>,
                             RTC::Delete<Simulation>);
  }
};


