#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Hardware.h"


void MyModuleInit(RTC::Manager* manager)
{
  HardwareInit(manager);
  RTC::RtcBase* comp;

  // Create a component
  comp = manager->createComponent("Hardware");

  if (comp==NULL)
  {
    std::cerr << "Component create failed." << std::endl;
    abort();
  }
  return;
}

int main (int argc, char** argv)
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);
  manager->init(argc, argv);
  manager->setModuleInitProc(MyModuleInit);
  manager->activateManager();
  manager->runManager();

  return 0;
}
