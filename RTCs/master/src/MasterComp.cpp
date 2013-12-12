#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Master.h"


void MyModuleInit(RTC::Manager* manager)
{
  MasterInit(manager);
  RTC::RtcBase* comp;

  comp = manager->createComponent("Master");

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
