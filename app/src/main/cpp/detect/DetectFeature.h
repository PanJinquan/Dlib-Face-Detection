//
// Created by panjq1 on 2017/11/10.
//

#ifndef DLIB_FACE_DETECTION_DETECTFEATURE_H
#define DLIB_FACE_DETECTION_DETECTFEATURE_H

#include "opencv2/opencv.hpp"
#include <dlib/image_processing.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
using namespace dlib;
using namespace std;

class DetectFeature {

private:
    full_object_detection shape;

public:
    DetectFeature();
    DetectFeature(full_object_detection shape);
    ~DetectFeature();
public:
    void showLandmark(cv::Mat &image, full_object_detection shape,bool showNum);
    void setShape(full_object_detection shape);
    full_object_detection gstShape();
    void faceFeature(cv::Mat &image,full_object_detection shape);

private:

};


#endif //DLIB_FACE_DETECTION_DETECTFEATURE_H
