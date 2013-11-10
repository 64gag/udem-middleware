#include <json/json.h>
#include "Simulation.h"
#include "SimulationBridge.h"
#include "SimulationAux.h"

Json::Value rosbridge_msg, rosbridge_args;
Json::Value arg_setmodes, arg_values, arg_handles;


// Module specification
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
	""
};

Simulation::Simulation(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_p_dataIn("Data", m_p_data),
    m_p_feedbackOut("Feedback", m_p_feedback),
    m_p_cameraOut("Camera", m_p_camera)
{
}

Simulation::~Simulation()
{
}

RTC::ReturnCode_t Simulation::onInitialize()
{
  // Set InPort buffers
  addInPort("Data", m_p_dataIn);

  // Set OutPort buffer
  addOutPort("Feedback", m_p_feedbackOut);
  addOutPort("Camera", m_p_cameraOut);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onActivated(RTC::UniqueId ec_id)
{
	rosbridge_msg["op"] = "call_service";
	rosbridge_msg["service"] = "/vrep/simRosSetJointState";

	arg_handles.resize(1);
	arg_values.resize(1);
	arg_setmodes.resize(1);


	char host[] = "127.0.0.1"; 
	ws_vrep_open(host, 9090);
	return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onDeactivated(RTC::UniqueId ec_id)
{
	ws_vrep_close();
	return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onExecute(RTC::UniqueId ec_id)
{
	if (m_p_dataIn.isNew())
	{
		m_p_dataIn.read();
		{
			std::ostringstream out;
			out << m_p_data.data;
			m_p_feedback.data = out.str().c_str();
			m_p_feedbackOut.write();

			Json::Value root;
			Json::Reader reader;
			bool parsedSuccess = reader.parse(out.str(), root, false);
			if(!parsedSuccess) {
				//panic out
			}
			std::vector<float> extracted = extractFloats(root["data"].asString(), "<WRIST>([ANGLE.1:%][ANGLE.2:%][ANGLE.3:%][ANGLE.4:%][ANGLE.5:%][ANGLE.6:%][ANGLE.7:%][GRIPPER:%])", '%');
			arg_values[0u] = extracted[0];
		}
		arg_handles[0u] = 40;
		arg_setmodes[0u] = 0;

		rosbridge_args["handles"] = arg_handles;
		rosbridge_args["setModes"] = arg_setmodes;
		rosbridge_args["values"] = arg_values;

		rosbridge_msg["args"] = rosbridge_args;

		std::cout << rosbridge_msg.toStyledString() << std::endl;
		ws_vrep_service(rosbridge_msg.toStyledString().c_str());
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


