// -*- C++ -*-
/*!
 * @file  Simulation.cpp
 * @brief Simulation wrapper
 * @date $Date$
 *
 * $Id$
 */

#include "Simulation.h"

// Module specification
// <rtc-template block="module_spec">
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
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Simulation::Simulation(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_dataIn("Data", m_p_data),
    m_p_feedbackOut("Feedback", m_p_feedback),
    m_p_cameraOut("Camera", m_p_camera)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Simulation::~Simulation()
{
}



RTC::ReturnCode_t Simulation::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Data", m_p_dataIn);
  
  // Set OutPort buffer
  addOutPort("Feedback", m_p_feedbackOut);
  addOutPort("Camera", m_p_cameraOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Simulation::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Simulation::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Simulation::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


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
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Simulation::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Simulation::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Simulation::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Simulation::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Simulation::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



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


