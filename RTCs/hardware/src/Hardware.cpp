// -*- C++ -*-
/*!
 * @file  Hardware.cpp
 * @brief Interface/filter between master and real/simulated robot
 * @date $Date$
 *
 * $Id$
 */

#include "Hardware.h"

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
    "activity_type",     "EVENTDRIVEN",
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

/*
RTC::ReturnCode_t Hardware::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Hardware::onExecute(RTC::UniqueId ec_id)
{
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


