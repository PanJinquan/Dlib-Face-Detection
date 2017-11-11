#ifndef _DLIBFACE_DETECTION_H_
#define _DLIBFACE_DETECTION_H_


#include <stdint.h>
#include "opencv2/core/core.hpp"
#include "dlib/image_processing/frontal_face_detector.h"
#include "dlib/image_processing.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
using namespace dlib;
namespace smartimage {
	class FaceDetection
	{
	public:
		string modePath;
		int32_t targetWidth;
		std::vector<full_object_detection> g_Shapes;
		dlib::frontal_face_detector* g_pDetector ;
		dlib::shape_predictor* g_pSp;
	public:
		FaceDetection();
		~FaceDetection();
		void initFaceDetection(std::string spFnStr);

		void uninitFaceDetection();

		int32_t detectFaces(std::string imageAddr, cv::Mat &pSrcImage);

		int32_t detectFaces(cv::Mat & pSrcImage);

		std::vector<full_object_detection> getDetectShapes();

		full_object_detection getDetectOneShape();
	private:
		std::vector<full_object_detection> detectFaceLandmark(cv::Mat &pSrcImage);
		full_object_detection getScaleShape(full_object_detection shape, const double scale);
	};
}



#endif
