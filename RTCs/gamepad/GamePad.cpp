/************************************************************************************
GamePad RT-Component
Copyright (c) 2010, Segway-Japan, Ltd.
All rights reserved.

Contact us if you use this software for sell.
If you use this software not for sell, you can use this software under BSD lisence.
See the files LICENSE.TXT and LICENSE-BSD.TXT for more details.                     
************************************************************************************/
#include <json/json.h>
#include "GamePad.h"
#include "pad_linux.h"


// Module specification
// <rtc-template block="module_spec">
static const char* gamepad_spec[] =
  {
    "implementation_id", "GamePad",
    "type_name",         "GamePad",
    "description",       "GamePad Component",
    "version",           "0.1.0",
    "vendor",            "SegwayJapan",
    "category",          "Generic",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    //"exec_cxt.periodic.rate", "30.0",
    // Configuration variables
    "conf.default.Klx", "1.0",
    "conf.default.Kly", "1.0",
    "conf.default.Krx", "1.0",
    "conf.default.Kry", "1.0",
    "conf.default.str_port", "/dev/input/js0",

    ""
  };
// </rtc-template>

GamePad::GamePad(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_statusOut("Status", m_p_status),
    // </rtc-template>
	dummy(0)
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  registerOutPort("Status", m_p_statusOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>





}

GamePad::~GamePad()
{
}


RTC::ReturnCode_t GamePad::onInitialize()
{
  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Klx", m_Klx, "1.0");
  bindParameter("Kly", m_Kly, "1.0");
  bindParameter("Krx", m_Krx, "1.0");
  bindParameter("Kry", m_Kry, "1.0");
  bindParameter("str_port", m_str_port, "/dev/input/js0");

  
  // </rtc-template>
  return RTC::RTC_OK;
}

RTC::ReturnCode_t GamePad::onActivated(RTC::UniqueId ec_id)
{

  pad_sdl_js_open(m_str_port.c_str());

  return RTC::RTC_OK;
}



RTC::ReturnCode_t GamePad::onDeactivated(RTC::UniqueId ec_id)
{
  pad_sdl_js_close();

  return RTC::RTC_OK;
}


/*!
  @brief polling gamepad status
  @param[in]
  @return
*/
RTC::ReturnCode_t GamePad::onExecute(RTC::UniqueId ec_id)
{
  Json::Value js_status;
  pad_sdl_js_update();
 

  unsigned int btns = 0;
  for (int i = 0; i < 12; i++) {
    if (pad_sdl_js_button(i)) {
      btns |= (1<<i);
    }
  }

  //printf("button %x \n", (unsigned int)m_Button.data);

  float lx, ly, rx, ry;
  lx = (float)pad_sdl_js_axis(0) / (float)PAD_SDL_JS_AXIS_MAX;
  ly = (float)pad_sdl_js_axis(1) / (float)PAD_SDL_JS_AXIS_MAX;
  rx = (float)pad_sdl_js_axis(2) / (float)PAD_SDL_JS_AXIS_MAX;
  ry = (float)pad_sdl_js_axis(3) / (float)PAD_SDL_JS_AXIS_MAX;

  js_status["Button"] = btns;
  js_status["StickLX"] = (double)(m_Klx * lx);
  js_status["StickLY"] = (double)(m_Kly * ly);
  js_status["StickRX"] = (double)(m_Krx * rx);
  js_status["StickRY"] = (double)(m_Kry * ry);
/*
  js_status["StickLXd"] = (double)m_StickLX.data;
  js_status["StickLYd"] = (double)m_StickLY.data;
  js_status["StickRXd"] = (double)m_StickRX.data;
  js_status["StickRYd"] = (double)m_StickRY.data;
*/
  js_status["Velocity"]["v"] = -m_Kly * (double)ly;
  js_status["Velocity"]["w"] = -m_Klx * (double)rx;

  js_status["VelocityIIS"]["vx"] = -m_Kly * (double)ly;
  js_status["VelocityIIS"]["vy"] = -m_Klx * (double)lx;
  js_status["VelocityIIS"]["w"] = -m_Krx * (double)rx;


  m_p_status.data = js_status.toStyledString().c_str();

  m_p_statusOut.write();
  coil::usleep(15000);

  return RTC::RTC_OK;
}


extern "C"
{

  void GamePadInit(RTC::Manager* manager)
  {
    RTC::Properties profile(gamepad_spec);
    manager->registerFactory(profile,
                             RTC::Create<GamePad>,
                             RTC::Delete<GamePad>);
  }

};


