#ifndef SIMULATION_H
#define SIMULATION_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>


using namespace RTC;

class Simulation
  : public RTC::DataFlowComponentBase
{
 public:
  Simulation(RTC::Manager* manager);
  ~Simulation();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

 protected:
  int m_int_joints;
  RTC::TimedString m_p_data;
  InPort<RTC::TimedString> m_p_dataIn;
  RTC::TimedString m_p_feedback;
  OutPort<RTC::TimedString> m_p_feedbackOut;

 private:
};


extern "C"
{
  DLL_EXPORT void SimulationInit(RTC::Manager* manager);
};

#endif // SIMULATION_H
