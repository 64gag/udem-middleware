#include <json/json.h>
#include "Simulation.h"

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
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Simulation::onExecute(RTC::UniqueId ec_id)
{

	if (m_p_dataIn.isNew())
	{
		m_p_dataIn.read();
		std::cout << "Received: " << std::endl << m_p_data.data << std::endl;
		{
			std::ostringstream out;
			out << m_p_data.data;
			m_p_feedback.data = out.str().c_str();
			m_p_feedbackOut.write();
		}
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


