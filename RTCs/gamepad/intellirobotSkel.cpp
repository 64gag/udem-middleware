// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file intellirobotSkel.cpp 
 * @brief intellirobot server skeleton wrapper
 * @date Wed Nov 27 08:05:20 2013 
 *
 */

#include "intellirobotSkel.h"

#if defined ORB_IS_TAO
#  include "intellirobotC.cpp"
#  include "intellirobotS.cpp"
#elif defined ORB_IS_OMNIORB
#  include "intellirobotSK.cc"
#  include "intellirobotDynSK.cc"
#elif defined ORB_IS_MICO
#  include "intellirobot.cc"
#  include "intellirobot_skel.cc"
#elif defined ORB_IS_ORBIT2
#  include "intellirobot-cpp-stubs.cc"
#  include "intellirobot-cpp-skels.cc"
#elif defined ORB_IS_RTORB
#  include "OpenRTM-aist-decls.h"
#  include "intellirobot-common.c"
#  include "intellirobot-stubs.c"
#  include "intellirobot-skels.c"
#  include "intellirobot-skelimpl.c"
#else
#  error "NO ORB defined"
#endif

// end of intellirobotSkel.cpp
