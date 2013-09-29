// -*- C++ -*-
/*!
 * @file  Vision.cpp
 * @brief Computer vision RTC
 * @date $Date$
 *
 * $Id$
 */

#include "Vision.h"

// Module specification
// <rtc-template block="module_spec">
static const char* vision_spec[] =
  {
    "implementation_id", "Vision",
    "type_name",         "Vision",
    "description",       "Computer vision RTC",
    "version",           "0.0.1",
    "vendor",            "UDEM",
    "category",          "Artificial intelligence",
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
Vision::Vision(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_optionIn("Option", m_p_option),
    m_p_resultOut("Result", m_p_result),
    m_p_statusOut("Status", m_p_status)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Vision::~Vision()
{
}



RTC::ReturnCode_t Vision::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Option", m_p_optionIn);
  
  // Set OutPort buffer
  addOutPort("Result", m_p_resultOut);
  addOutPort("Status", m_p_statusOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Vision::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Vision::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Vision::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Vision::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Vision::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Vision::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void VisionInit(RTC::Manager* manager)
  {
    coil::Properties profile(vision_spec);
    manager->registerFactory(profile,
                             RTC::Create<Vision>,
                             RTC::Delete<Vision>);
  }
  
};


