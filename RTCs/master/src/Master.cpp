#include <json/json.h>
#include "Master.h"

#define DEBUG

#define WF_VISION 0x01
#define WF_KINEMATICS 0x02
#define WF_HARDWARE 0x04
static const char* master_spec[] =
  {
    "implementation_id", "Master",
    "type_name",         "Master",
    "description",       "Mind and commander",
    "version",           "0.0.1",
    "vendor",            "UDEM",
    "category",          "Administrative",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    "conf.default.int_exec_delay", "50000",
    "conf.default.int_fire_kinematics", "1",
    "conf.default.int_fire_hardware", "1",
    "conf.default.str_hardware", "0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5",
    "conf.default.str_kinematics", "{ \"tip_config\" : [[0, 90, -180],[1, 1, 1]] }",
    ""
  };

Master::Master(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_status_visionIn("Status_vision", m_p_status_vision),
    m_p_result_visionIn("Result_vision", m_p_result_vision),
    m_p_status_kinematicsIn("Status_kinematics", m_p_status_kinematics),
    m_p_result_kinematicsIn("Result_kinematics", m_p_result_kinematics),
    m_p_status_hardwareIn("Status_hardware", m_p_status_hardware),
    m_p_joystickIn("Joystick", m_p_joystick),
    m_p_option_visionOut("Option_vision", m_p_option_vision),
    m_p_target_kinematicsOut("Target_kinematics", m_p_target_kinematics),
    m_p_state_hardwareOut("Position_hardware", m_p_state_hardware)

{
}

Master::~Master()
{
}



RTC::ReturnCode_t Master::onInitialize()
{
  addInPort("Status_vision", m_p_status_visionIn);
  addInPort("Result_vision", m_p_result_visionIn);
  addInPort("Status_kinematics", m_p_status_kinematicsIn);
  addInPort("Result_kinematics", m_p_result_kinematicsIn);
  addInPort("Status_hardware", m_p_status_hardwareIn);
  addInPort("Joystick", m_p_joystickIn);
  
  addOutPort("Option_vision", m_p_option_visionOut);
  addOutPort("Target_kinematics", m_p_target_kinematicsOut);
  addOutPort("Position_hardware", m_p_state_hardwareOut);
  
  bindParameter("int_exec_delay", m_int_exec_delay, "50000");
  bindParameter("int_fire_hardware", m_int_fire_hardware, "1");
  bindParameter("int_fire_kinematics", m_int_fire_kinematics, "1");
  bindParameter("str_kinematics", m_str_kinematics, "{ \"tip_config\" : [[0, 90, -180],[1, 1, 1]] }");
  bindParameter("str_hardware", m_str_hardware, "0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5");
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Master::onFinalize()
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Master::onActivated(RTC::UniqueId ec_id)
{
  m_p_state_hardware.data = "0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0";
  m_p_state_hardwareOut.write();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Master::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Master::onExecute(RTC::UniqueId ec_id)
{

 unsigned char write_flags=0;

	if (m_p_status_hardwareIn.isNew())
	{
		m_p_status_hardwareIn.read();
#ifdef DEBUG
		std::cout << "Received hardwareIn: " << std::endl << m_p_status_hardware.data << std::endl;
#endif
	}

	if (m_p_result_visionIn.isNew())
	{
		m_p_result_visionIn.read();
		Json::Value in_json;
		Json::Reader in_reader;
		std::string port_str = (char*)m_p_result_vision.data;

		bool parsedSuccess = in_reader.parse(port_str, in_json, false);

		if(!parsedSuccess)
		{

		}

		if(in_json.isMember("fast.jpg")){
			std::cout << "fast.jpg detected!" << std::endl;
			m_p_state_hardware.data = "0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.0,2.0";

			write_flags |= WF_HARDWARE;
		}

		if(in_json.isMember("slow.jpg")){
			std::cout << "slow.jpg detected!" << std::endl;
			m_p_state_hardware.data = "0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,0.5";

			write_flags |= WF_HARDWARE;
		}

		if(in_json.isMember("left.jpg")){
			std::cout << "left.jpg detected!" << std::endl;
			m_p_state_hardware.data = "0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,-0.5";

			write_flags |= WF_HARDWARE;
		}

		if(in_json.isMember("right.jpg")){
			std::cout << "right.jpg detected!" << std::endl;
			m_p_state_hardware.data = "0.0,0.0,0.0,0.0,0.0,0.0,0.0,-0.5,0.5";

			write_flags |= WF_HARDWARE;
		}
		if(in_json.isMember("stop.jpg")){
			std::cout << "stop.jpg detected!" << std::endl;
			m_p_state_hardware.data = "0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0";

			write_flags |= WF_HARDWARE;
		}
#ifdef DEBUG
		std::cout << "Received visionIn: " << std::endl << m_p_result_vision.data << std::endl;
#endif
	}
	if (m_p_joystickIn.isNew())
	{
		m_p_joystickIn.read();
#ifdef DEBUG
		std::cout << "Received joystickIn: " << std::endl << m_p_joystick.data << std::endl;
#endif
	}
	if (m_p_result_kinematicsIn.isNew() || m_p_joystickIn.isNew())
	{
		Json::Value in_json;
		Json::Reader in_reader;
		std::ostringstream out_stream;

		m_p_result_kinematicsIn.read();
#ifdef DEBUG
		std::cout << "Received kinematicsIn: " << std::endl << m_p_result_kinematics.data << std::endl;
#endif

		std::string port_str = (char*)m_p_result_kinematics.data;
		bool parsedSuccess = in_reader.parse(port_str, in_json, false);

		if(!parsedSuccess)
		{

		}

		for(unsigned int i = 0; i<in_json["joints"].size(); i++){
			out_stream << in_json["joints"][i] << ",";
		}

		out_stream << "0"; //Gripper-dummy
		if(m_p_joystick.data) {

			Json::Value jin_json;
			Json::Reader jin_reader;
			std::string js_port_str = (char*)m_p_joystick.data;

			bool parsedSuccess = in_reader.parse(js_port_str, jin_json, false);

			if(parsedSuccess)
			{
				double VL, VR;
				VL = jin_json["StickLY"].asDouble()*150.0f;
				VR = jin_json["StickRX"].asDouble()*150.0f;
				out_stream << "," << VL << "," << VR;
			}else{
				out_stream << ",0,0";
			}

		}else{
			out_stream << ",0,0";
		}
#ifdef DEBUG
		std::cout << out_stream.str() << std::endl;
#endif
		m_p_state_hardware.data = out_stream.str().c_str();
		m_p_state_hardwareOut.write();
	}

	if(m_int_fire_kinematics) {
		m_int_fire_kinematics = 0;
		m_p_target_kinematics.data = m_str_kinematics.c_str();
		m_p_target_kinematicsOut.write();
#ifdef DEBUG
		std::cout << m_str_kinematics << std::endl;
#endif
	}

	if(write_flags & WF_HARDWARE) {
		m_p_state_hardware.data = ""; //TODO change this
		m_p_state_hardwareOut.write();
	}

  coil::usleep(m_int_exec_delay);

  return RTC::RTC_OK;
}

extern "C"
{
 
  void MasterInit(RTC::Manager* manager)
  {
    coil::Properties profile(master_spec);
    manager->registerFactory(profile,
                             RTC::Create<Master>,
                             RTC::Delete<Master>);
  }
  
};


