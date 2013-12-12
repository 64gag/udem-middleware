#ifndef HARDWARE_H
#define HARDWARE_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

using namespace RTC;

class Hardware
  : public RTC::DataFlowComponentBase
{
 public:

  Hardware(RTC::Manager* manager);
  ~Hardware();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onFinalize();
   virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

 protected:
  int m_int_joints;
  int m_int_exec_delay;
  std::string m_str_json_data_format;
  std::string m_str_slopes;
  RTC::TimedString m_p_position;
  InPort<RTC::TimedString> m_p_positionIn;
  RTC::TimedString m_p_feedback;
  InPort<RTC::TimedString> m_p_feedbackIn;
  RTC::TimedULong m_p_status;
  OutPort<RTC::TimedULong> m_p_statusOut;
  RTC::TimedString m_p_data;
  OutPort<RTC::TimedString> m_p_dataOut;

 private:

};


extern "C"
{
  DLL_EXPORT void HardwareInit(RTC::Manager* manager);
};

#endif // HARDWARE_H
