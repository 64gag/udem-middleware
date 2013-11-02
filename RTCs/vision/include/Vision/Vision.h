#ifndef VISION_H
#define VISION_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>


using namespace RTC;

class Vision
  : public RTC::DataFlowComponentBase
{
 public:
  Vision(RTC::Manager* manager);
  ~Vision();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onFinalize();
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);



 protected:
  int m_int_camera;
  int m_int_img_width;
  int m_int_img_height;
  std::string m_str_files_path;
  std::string m_str_images;
  std::string m_str_img_rostopic;
  std::string m_str_rosbridge_host;
  int m_int_rosbridge_port;
  int m_int_area_min;
  int m_int_area_max;
  int m_int_exec_delay;
  int m_int_drawflag;

  RTC::TimedString m_p_option;
  InPort<RTC::TimedString> m_p_optionIn;
  RTC::TimedString m_p_result;
  OutPort<RTC::TimedString> m_p_resultOut;
  RTC::TimedULong m_p_status;
  OutPort<RTC::TimedULong> m_p_statusOut;
  
 private:

};


extern "C"
{
  DLL_EXPORT void VisionInit(RTC::Manager* manager);
};

#endif // VISION_H
