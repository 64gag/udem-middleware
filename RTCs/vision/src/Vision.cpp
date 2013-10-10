// -*- C++ -*-
/*!
 * @file  Vision.cpp
 * @brief Computer vision RTC
 * @date $Date$
 *
 * $Id$
 */

#include "Vision.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#define FLAG_DRAW 1

enum {
        TARGET_FAST=0,
        TARGET_SLOW,
        TARGET_LEFT,
        TARGET_RIGHT,
        TARGET_STAIRS,
        TARGET_ELEVATOR,
        TARGET_STOP,
	TARGET_COUNT /* Leave this alone! */
};

using namespace cv;

std::string path = "/home/paguiar/Dropbox/UDEM/PPD - Middleware/Vision/src/";
std::string file[TARGET_COUNT] = { "fast.jpg", "slow.jpg", "left.jpg", "right.jpg", "stairs.jpg", "elevator.jpg", "stop.jpg" };


/* Globals are ugly... but fast for prototyping. Change later */
Mat *t_images = NULL;
Mat *t_descriptors = NULL;
std::vector<KeyPoint> * t_kp = NULL;
std::vector<Point2f> * t_ob_corners = NULL;
SurfFeatureDetector * detector = NULL;
SurfDescriptorExtractor * extractor = NULL;
FlannBasedMatcher * matcher = NULL;
unsigned int gFlags = 0;

// Module specification
// <rtc-template block="module_spec">
static const char* vision_spec[] =
  {
    "implementation_id", "Vision",
    "type_name",         "Vision",
    "description",       "Computer vision RTC",
    "version",           "0.0.1",
    "vendor",            "UDEM",
    "category",          "Artificial intelligence",
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
Vision::Vision(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_p_optionIn("Option", m_p_option),
    m_p_cameraIn("Camera", m_p_camera),
    m_p_resultOut("Result", m_p_result),
    m_p_statusOut("Status", m_p_status)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Vision::~Vision()
{
}



RTC::ReturnCode_t Vision::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Option", m_p_optionIn);
  addInPort("Camera", m_p_cameraIn);
  
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


RTC::ReturnCode_t Vision::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Vision::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Vision::onActivated(RTC::UniqueId ec_id)
{
	gFlags |= FLAG_DRAW;

	t_images = new Mat[TARGET_COUNT];
	t_descriptors = new Mat[TARGET_COUNT];
	t_kp = new std::vector<KeyPoint>[TARGET_COUNT];
	t_ob_corners = new std::vector<Point2f>[TARGET_COUNT];
	detector = new SurfFeatureDetector(300);
	extractor = new SurfDescriptorExtractor();
	matcher = new FlannBasedMatcher();

	for (int i=0; i<TARGET_COUNT; i++){
		t_images[i] = imread( path+file[i], CV_LOAD_IMAGE_GRAYSCALE );
		detector->detect( t_images[i], t_kp[i]);
		extractor->compute( t_images[i], t_kp[i], t_descriptors[i] );
		t_ob_corners[i].push_back(cvPoint(0,0));
		t_ob_corners[i].push_back(cvPoint( t_images[i].cols, 0 ));
		t_ob_corners[i].push_back(cvPoint( t_images[i].cols, t_images[i].rows ));
		t_ob_corners[i].push_back(cvPoint( 0, t_images[i].rows ));
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Vision::onDeactivated(RTC::UniqueId ec_id)
{
	delete[] t_images;
	delete[] t_descriptors;
	delete[] t_kp;
	delete[] t_ob_corners;
	delete detector;
	delete extractor;
	delete matcher;

 return RTC::RTC_OK;
}


RTC::ReturnCode_t Vision::onExecute(RTC::UniqueId ec_id)
{
	double *large = new double[TARGET_COUNT];
	double *width = new double[TARGET_COUNT];
	double *area = new double[TARGET_COUNT];

	gFlags |= FLAG_DRAW;

	Mat frame;
	VideoCapture cap(0);
	cap >> frame;

	std::vector<vector<DMatch > > *t_matches = new std::vector<vector<DMatch > >[TARGET_COUNT];
	std::vector<DMatch > *t_good_matches = new std::vector<DMatch >[TARGET_COUNT];
	std::vector<Point2f> *t_ob = new std::vector<Point2f>[TARGET_COUNT];
	std::vector<Point2f> *t_ob_center = new std::vector<Point2f>[TARGET_COUNT];
	std::vector<Point2f> *t_scene = new std::vector<Point2f>[TARGET_COUNT];
	std::vector<Point2f> *t_scene_corners = new std::vector<Point2f>[TARGET_COUNT];

	Mat des_image, img_matches;
	std::vector<KeyPoint> kp_image;

	Mat H;
	Mat image;

	cvtColor(frame, image, CV_RGB2GRAY);

	detector->detect( image, kp_image );
	extractor->compute( image, kp_image, des_image );

	for(int t=0; t<TARGET_COUNT; t++){
		t_scene_corners[t].resize(4);
		matcher->knnMatch(t_descriptors[t], des_image, t_matches[t], 2);
		for(int i = 0; i < min(des_image.rows-1,(int) t_matches[t].size()); i++) //THIS LOOP IS SENSITIVE TO SEGFAULTS
		{
		    if((t_matches[t][i][0].distance < 0.6*(t_matches[t][i][1].distance)) && ((int) t_matches[t][i].size()<=2 && (int) t_matches[t][i].size()>0))
		    {
			t_good_matches[t].push_back(t_matches[t][i][0]);
		    }
		}
		//Draw only "good" matches
		drawMatches( t_images[t], t_kp[t], image, kp_image, t_good_matches[t], img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

		if (t_good_matches[t].size() >= 4)
		{
			if(gFlags & FLAG_DRAW)
			{
				for(unsigned int i = 0; i < t_good_matches[t].size(); i++ )
				{
					t_ob[t].push_back( t_kp[t][ t_good_matches[t][i].queryIdx ].pt );
					t_scene[t].push_back( kp_image[ t_good_matches[t][i].trainIdx ].pt );
				}

				H = findHomography( t_ob[t], t_scene[t], CV_RANSAC );
				perspectiveTransform( t_ob_corners[t], t_scene_corners[t], H);

				line( image, t_scene_corners[t][0], t_scene_corners[t][1], Scalar(0, 255, 0), 4 );
				line( image, t_scene_corners[t][1], t_scene_corners[t][2], Scalar( 0, 255, 0), 4 );
				line( image, t_scene_corners[t][2], t_scene_corners[t][3], Scalar( 0, 255, 0), 4 );
				line( image, t_scene_corners[t][3], t_scene_corners[t][0], Scalar( 0, 255, 0), 4 );

				large[t]=cv::norm(t_scene_corners[t][1]-t_scene_corners[t][0]);
				width[t]=cv::norm(t_scene_corners[t][2]-t_scene_corners[t][1]);
				area[t]=large[t]*width[t];
				if(area[t]>15000 && area[t]<300000)
				{
					t_ob_center[t].push_back((t_scene_corners[t][0]+t_scene_corners[t][1])*.5);
					std::cout<< "Area "+ file[t] + ": " << area[t] << + " and coord " << t_ob_center[t] << std::endl;
				}
			}
		}
	}

	//Show detected matches
	if(gFlags & FLAG_DRAW){
		imshow( "Result", image );
	}

	delete[] t_matches;
	delete[] t_good_matches;
	delete[] t_ob;
	delete[] t_ob_center;
	delete[] t_scene;
	delete[] t_scene_corners;
	delete[] large;
	delete[] width;
	delete[] area;
	coil::usleep(100000);
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Vision::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Vision::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void VisionInit(RTC::Manager* manager)
  {
    coil::Properties profile(vision_spec);
    manager->registerFactory(profile,
                             RTC::Create<Vision>,
                             RTC::Delete<Vision>);
  }
  
};


