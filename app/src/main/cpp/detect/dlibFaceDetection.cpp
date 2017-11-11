#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <vector>
#include "dlibFaceDetection.h"
#include "AndroidDebug.h"
#include "dlib/opencv/cv_image.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace dlib;

namespace smartimage {


	FaceDetection::FaceDetection()
	{

	}
	FaceDetection::~FaceDetection()
	{
	}
	void FaceDetection::initFaceDetection(std::string modePath) {
		this->targetWidth = 300;
        this->modePath=modePath;
		g_pDetector = new dlib::frontal_face_detector;
		*g_pDetector = dlib::get_frontal_face_detector();
		g_pSp = new dlib::shape_predictor;
		dlib::deserialize(modePath) >> *g_pSp;
		return;
	}

	void FaceDetection::uninitFaceDetection() {
		delete g_pDetector;
		g_pDetector = nullptr;
		delete g_pSp;
		g_pSp = nullptr;
	}


	std::vector<full_object_detection> FaceDetection::detectFaceLandmark(cv::Mat &pSrcImage) {
		cv::Mat tmpImage;
		int channels = pSrcImage.channels();
		if (channels == 4) {
			cvtColor(pSrcImage, tmpImage, CV_BGRA2GRAY);
		}
		else if (channels == 3) {
			cvtColor(pSrcImage, tmpImage, CV_BGR2GRAY);
		}
		else if (channels == 1) {
			tmpImage = pSrcImage.clone();
		}else{
			LOGD("Error: Unsupported image format for face detection.");
		}
		double scale = (double)targetWidth / pSrcImage.rows;
		cv::resize(tmpImage, tmpImage, cv::Size(), scale, scale, cv::INTER_LINEAR);
		dlib::cv_image<unsigned char> dlib_img(tmpImage);
		//std::vector<dlib::rectangle> dets = detector(dlib_img);
		std::vector<dlib::rectangle> dets = g_pDetector->operator()(dlib_img);
		std::vector<full_object_detection> shapes;
		for (size_t i = 0; i < dets.size(); i++)
		{
			full_object_detection shape;
			shape = g_pSp->operator()(dlib_img, dets[i]);
			shape = getScaleShape(shape, 1 / scale);
			cv::Rect rect(shape.get_rect().left(),
				shape.get_rect().top(),
				shape.get_rect().right() - shape.get_rect().left(),
				shape.get_rect().bottom() - shape.get_rect().top());
			shapes.push_back(shape);
		}
		return shapes;
	}

	int32_t FaceDetection::detectFaces(std::string imageAddr, cv::Mat & pSrcImage) {
		pSrcImage = cv::imread(imageAddr);
		if (!pSrcImage.data)
		{
			LOGD("Error: Please verify that you entered the correct path.");
			return -1;
		}
		int channels = pSrcImage.channels();
		if (channels == 4 || channels == 3 || channels == 1)
			g_Shapes = detectFaceLandmark(pSrcImage);
		else {
			LOGD("Error: Unsupported image format for face detection.");
			return -1;
		}
		int num = g_Shapes.size();
		if (num == 0)
		{
			LOGD("Error: No face was detected.");
		}
		else if (num >= 1)
		{
			LOGD("Successfully: %d faces were detected\n", num);
		}
		return num;
	}

	int32_t FaceDetection::detectFaces(cv::Mat & pSrcImage) {
		if (!pSrcImage.data)
		{
			LOGD("Error: Please verify that you entered the correct path.");
			return -1;
		}
		int channels = pSrcImage.channels();
		if (channels == 4 || channels == 3 || channels == 1)
			g_Shapes = detectFaceLandmark(pSrcImage);
		else {
			LOGD("Error: Unsupported image format for face detection.");
			return -1;
		}
		int num = g_Shapes.size();
		if (num == 0)
		{
			LOGD("Error: No face was detected.");
		}
		else if (num >= 1)
		{
			LOGD("Successfully: %d faces were detected\n", num);
		}
		return num;
	}
	
	    full_object_detection FaceDetection::getScaleShape(full_object_detection shape, const double scale) {
        full_object_detection reShape = shape;
        dlib::rectangle &mRect = reShape.get_rect();
        mRect.set_left(mRect.left()*scale);
        mRect.set_right(mRect.right() *scale);
        mRect.set_top(mRect.top()*scale);
        mRect.set_bottom(mRect.bottom() *scale);
        for (size_t i = 0; i < shape.num_parts(); i++)
        {
            reShape.part(i).x() = cvRound(shape.part(i).x()*scale);
            reShape.part(i).y() = cvRound(shape.part(i).y()*scale);
        }
        return reShape;
    }

	std::vector<full_object_detection> FaceDetection::getDetectShapes() {
		return g_Shapes;
	}

	full_object_detection FaceDetection::getDetectOneShape() {
		return g_Shapes.at(0);
	}
}
