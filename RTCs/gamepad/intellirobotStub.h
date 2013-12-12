// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file intellirobotStub.h 
 * @brief intellirobot client stub header wrapper code
 * @date Wed Nov 27 08:05:20 2013 
 *
 */

#ifndef _INTELLIROBOTSTUB_H
#define _INTELLIROBOTSTUB_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "intellirobotC.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "intellirobot.hh"
#elif defined ORB_IS_MICO
#  include "intellirobot.h"
#elif defined ORB_IS_ORBIT2
#  include "intellirobot-cpp-stubs.h"
#elif defined ORB_IS_RTORB
#  include "intellirobot.h"
#else
#  error "NO ORB defined"
#endif

#endif // _INTELLIROBOTSTUB_H
