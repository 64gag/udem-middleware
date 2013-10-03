// -*- C++ -*-
/*!
 * @file  Kinematics.cpp
 * @brief Calculates links positions needed to reach a target
 * @date $Date$
 *
 * $Id$
 */

#include "Kinematics.h"

// Module specification
// <rtc-template block="module_spec">
static const char* kinematics_spec[] =
  {
    "implementation_id", "Kinematics",
    "type_name",         "Kinematics",
    "description",       "Calculates links positions needed to reach a target",
    "version",           "0.0.1",
    "vendor",            "UDEM",
    "category",          "Mechanical",
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
Kinematics::Kinematics(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_targetIn("Target", m_p_target),
    m_p_resultOut("Result", m_p_result),
    m_p_statusOut("Status", m_p_status)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Kinematics::~Kinematics()
{
}



RTC::ReturnCode_t Kinematics::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Target", m_p_targetIn);
  
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


RTC::ReturnCode_t Kinematics::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Kinematics::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Kinematics::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Kinematics::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Kinematics::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Kinematics::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Kinematics::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Kinematics::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Kinematics::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Kinematics::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Kinematics::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void KinematicsInit(RTC::Manager* manager)
  {
    coil::Properties profile(kinematics_spec);
    manager->registerFactory(profile,
                             RTC::Create<Kinematics>,
                             RTC::Delete<Kinematics>);
  }
  
};


