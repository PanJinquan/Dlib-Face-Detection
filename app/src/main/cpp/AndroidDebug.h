#ifndef DETECT_DEBUG_H
#define DETECT_DEBUG_H

#pragma once
#include "opencv2/opencv.hpp"
#include <dlib/image_processing.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
using namespace dlib;
using namespace std;
//debug info ON-OFF
#define __DEBUG__ON
#ifdef  __DEBUG__ON
#define __DEBUG__WIN__ON         //Window debug:print debug info
#define __DEBUG__PRINT__SHAPE__ON  //print Landmark info
#define __DEBUG__IMSHOW__ON        //show debug images
#define __DEBUG__IMWRITE__ON       //write debug images
#define __DEBUG_PRINT_RUN_TIME__ON
#define __DEBUG__TIME__ON          //run times test on/off
#define __DEBUG__ANDROID__ON      //android debug on/off

//#include <assert.h> 
//#define DEBUG_ASSERT(...) assert( __VA_ARGS__)
//#define DEBUG_CV_ASSERT(...) CV_Assert( __VA_ARGS__)

#else
#define __DEBUG__ON(format,...)
#endif

//print debug info
#ifdef  __DEBUG__WIN__ON
//#define DEBUG_PRINT(...) printf("File: %s, Line: %05d: "format"", __FILE__,__LINE__, ##__VA_ARGS__)
#define DEBUG_PRINT(...) printf( __VA_ARGS__)
#else
#define DEBUG_PRINT(format,...)
#endif


//print debug info
#ifdef  __DEBUG_PRINT_RUN_TIME__ON
#define DEBUG_PRINT_RUN_TIME(...) printf( __VA_ARGS__)
#else
#define DEBUG_PRINT_RUN_TIME(format,...)
#endif


//print Landmark info
#ifdef  __DEBUG__PRINT__SHAPE__ON
#define DEBUG_PRINT_SHAPE(...) printfShape(__VA_ARGS__)
#else
#define DEBUG_PRINT_SHAPE(format,...) 
#endif

//show debug images
#ifdef  __DEBUG__IMSHOW__ON
#define DEBUG_IMSHOW(...) showImages(__VA_ARGS__)
#else
#define DEBUG_IMSHOW(format,...) 
#endif

//write debug images
#ifdef  __DEBUG__IMWRITE__ON
#define DEBUG_IMWRITE(...) saveImage(__VA_ARGS__)
#else
#define DEBUG_IMWRITE(format,...) 
#endif

//write debug images
#ifdef  __DEBUG__ANDROID__ON
#include <android/log.h>
// Define the LOGI and others for print debug infomation like the log.i in java
#define LOG_TAG    "Idphoto -- JNILOG"
//#undef LOG
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG, __VA_ARGS__)
#else
#ifdef __DEBUG__WIN__ON
#define LOGI(...)  printf( __VA_ARGS__)
#define LOGD(...)  printf( __VA_ARGS__)
#define LOGW(...)  printf( __VA_ARGS__)
#define LOGE(...)  printf( __VA_ARGS__)
#define LOGF(...)  printf( __VA_ARGS__)
#else
#define LOGI(...)   
#define LOGD(...)   
#define LOGW(...)   
#define LOGE(...)   
#define LOGF(...)  
#endif
#endif

//run times test...
#ifdef  __DEBUG__TIME__ON
#include<time.h>
#define TIME0 TIME0
#define TIME1 TIME1
#define TIME2 TIME2
#define TIME3 TIME3
#define TIME4 TIME4
#define TIME5 TIME5
#define TIME6 TIME6
#define TIME7 TIME7
#define TIME8 TIME8
#define TIME9 TIME9
static clock_t TIME0;
static clock_t TIME1;
static clock_t TIME2;
static clock_t TIME3;
static clock_t TIME4;
static clock_t TIME5;
static clock_t TIME6;
static clock_t TIME7;
static clock_t TIME8;
static clock_t TIME9;
#define DEBUG__TIME0 (TIME0= clock())
#define DEBUG__TIME1 (TIME1= clock())
#define DEBUG__TIME2 (TIME2= clock())
#define DEBUG__TIME3 (TIME3= clock())
#define DEBUG__TIME4 (TIME4= clock())
#define DEBUG__TIME5 (TIME5= clock())
#define DEBUG__TIME6 (TIME6= clock())
#define DEBUG__TIME7 (TIME7= clock())
#define DEBUG__TIME8 (TIME8= clock())
#define DEBUG__TIME9 (TIME9= clock())

#define GTIME0 GTIME0
#define GTIME1 GTIME1
#define GTIME2 GTIME2
#define GTIME3 GTIME3
#define GTIME4 GTIME4
#define GTIME5 GTIME5
#define GTIME6 GTIME6
#define GTIME7 GTIME7
#define GTIME8 GTIME8
#define GTIME9 GTIME9
extern clock_t GTIME0;
extern clock_t GTIME1;
extern clock_t GTIME2;
extern clock_t GTIME3;
extern clock_t GTIME4;
extern clock_t GTIME5;
extern clock_t GTIME6;
extern clock_t GTIME7;
extern clock_t GTIME8;
extern clock_t GTIME9;
#define DEBUG__GTIME0 (GTIME0= clock())
#define DEBUG__GTIME1 (GTIME1= clock())
#define DEBUG__GTIME2 (GTIME2= clock())
#define DEBUG__GTIME3 (GTIME3= clock())
#define DEBUG__GTIME4 (GTIME4= clock())
#define DEBUG__GTIME5 (GTIME5= clock())
#define DEBUG__GTIME6 (GTIME6= clock())
#define DEBUG__GTIME7 (GTIME7= clock())
#define DEBUG__GTIME8 (GTIME8= clock())
#define DEBUG__GTIME9 (GTIME9= clock())
#else
#define TIME0 0
#define TIME1 0
#define TIME2 0
#define TIME3 0
#define TIME4 0
#define TIME5 0
#define TIME6 0
#define TIME7 0
#define TIME8 0
#define TIME9 0
#define DEBUG__TIME0 
#define DEBUG__TIME1
#define DEBUG__TIME2
#define DEBUG__TIME3
#define DEBUG__TIME4
#define DEBUG__TIME5
#define DEBUG__TIME6
#define DEBUG__TIME7
#define DEBUG__TIME8
#define DEBUG__TIME9

#define GTIME0 0
#define GTIME1 0
#define GTIME2 0
#define GTIME3 0
#define GTIME4 0
#define GTIME5 0
#define GTIME6 0
#define GTIME7 0
#define GTIME8 0
#define GTIME9 0
#define DEBUG__GTIME0 
#define DEBUG__GTIME1 
#define DEBUG__GTIME2 
#define DEBUG__GTIME3 
#define DEBUG__GTIME4 
#define DEBUG__GTIME5 
#define DEBUG__GTIME6 
#define DEBUG__GTIME7 
#define DEBUG__GTIME8 
#define DEBUG__GTIME9 
#endif


void showImages(const char *imageName,cv::Mat image, full_object_detection shape);
void showImages(const char *imageName, cv::Mat image);
void showImages(const char *imageName, cv::Mat img, cv::Rect face);
void showImages(const char *imageName, cv::Mat img, cv::Rect face, std::vector<cv::Point> pts);
void showImages(const char *imageName, cv::Mat img, std::vector<cv::Point> pts);


void printfShape(const char *str,full_object_detection shape);

void saveImage(const char *imageName, cv::Mat image, full_object_detection shape);
void saveImage(const char *imageName, cv::Mat image);
void saveImage(const char *imageName, cv::Mat image, std::vector<int> para);
void saveImage(const char *imageName, cv::Mat image, cv::Rect face, std::vector<cv::Point> pts);

cv::Mat gray2BGR(cv::Mat grayImg);


#endif
