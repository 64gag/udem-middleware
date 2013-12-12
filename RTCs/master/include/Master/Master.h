#ifndef MASTER_H
#define MASTER_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

using namespace RTC;

class Master
  : public RTC::DataFlowComponentBase
{
 public:
  Master(RTC::Manager* manager);
  ~Master();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onFinalize();
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

 protected:

  int m_int_exec_delay;
  int m_int_fire_kinematics;
  int m_int_fire_hardware;
  std::string m_str_kinematics;
  std::string m_str_hardware;

  RTC::TimedULong m_p_status_vision;
  InPort<RTC::TimedULong> m_p_status_visionIn;
  RTC::TimedString m_p_result_vision;
  InPort<RTC::TimedString> m_p_result_visionIn;
  RTC::TimedLong m_p_status_kinematics;
  InPort<RTC::TimedLong> m_p_status_kinematicsIn;
  RTC::TimedString m_p_result_kinematics;
  InPort<RTC::TimedString> m_p_result_kinematicsIn;
  RTC::TimedULong m_p_status_hardware;
  InPort<RTC::TimedULong> m_p_status_hardwareIn;
  RTC::TimedString m_p_joystick;
  InPort<RTC::TimedString> m_p_joystickIn;  


  RTC::TimedString m_p_option_vision;
  OutPort<RTC::TimedString> m_p_option_visionOut;
  RTC::TimedString m_p_target_kinematics;
  OutPort<RTC::TimedString> m_p_target_kinematicsOut;
  RTC::TimedString m_p_state_hardware;
  OutPort<RTC::TimedString> m_p_state_hardwareOut;

 private:

};


extern "C"
{
  DLL_EXPORT void MasterInit(RTC::Manager* manager);
};

#endif // MASTER_H
