
#include <string>
#include "opencv2/opencv.hpp"
#include "AndroidDebug.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>
#include "dlibFaceDetection.h"
using namespace dlib;
using namespace std;
using namespace smartimage;

smartimage::FaceDetection *pFaceDetect=nullptr;
#define DLIB_NO_GUI_SUPPORT

int main(int argc, char** argv)
{  
		//string data = argv[1];
		//string imgPath = argv[2];
		//string outPath= argv[3];
		//string data = "data\\shape_predictor_68_face_landmarks.dat";
		string modePath = "data\\new_train_32.dat";
		string imgPath = "..\\images2\\16.jpg";
		//string imgPath = "out3\\L3.jpg";
		//string imgPath = "images2\\502.jpg";
		//string imgPath = "..\\InputImage\\L16.jpg";
		//string imgPath = "images3\\L40.jpg";
		//string imgPath = "..\\bug1\\bug5.jpg";
		//string imgPath = "..\\highlight\\3598.jpg";
		char * outPath = "lightTest\\L1.jpg";
		//**************************************** face detection *******************************************
		cv::Mat pSrcImage;
		int32_t face_num;
		if (nullptr == pFaceDetect)
		{
			pFaceDetect = new FaceDetection();
			pFaceDetect->initFaceDetection(modePath);
			face_num = pFaceDetect->detectFaces(imgPath, pSrcImage);
		}
		else
		{
			face_num = pFaceDetect->detectFaces(imgPath, pSrcImage);
		}
		if (face_num < 1)
		{
			return 0;
		}
		full_object_detection shape = pFaceDetect->getDetectOneShape();
		//delete dlib
		pFaceDetect->uninitFaceDetection();
		delete pFaceDetect;
		pFaceDetect = nullptr;
		//DEBUG_IMSHOW("pSrcImage", pSrcImage);                       
		// //**************************************** detect face features *******************************************
		// DetectParams m_detectParams = getDetectParams(); //设置并获得检测参数阈值
		// DetectFaceFeature m_detectFaceFeature;
		// m_detectFaceFeature.prepareDetect(pSrcImage, shape, m_detectParams); //初始化检测
		// DetectReport  m_detectReport = m_detectFaceFeature.getDetectReport();//获得检测报告

		// DEBUG_PRINT("isValidity=%d\n", m_detectReport.isValidityLandmark);//输出检测Landmark合法性
		// DEBUG_PRINT("isEyeSlope=%d\n", m_detectReport.isEyeSlope);        //检测眼睛是否倾斜
		// DEBUG_PRINT("isCorrect=%d\n", m_detectReport.isCorrect);         //是否进行了矫正
		// DEBUG_PRINT("isShadeFace=%d\n", m_detectReport.isShadeFace);     //是否是阴阳脸
		// DEBUG_PRINT("isSideFace=%d\n", m_detectReport.isSideFace);		 //是否是侧脸
		// DEBUG_PRINT("faceLightIntensity=%d\n", m_detectReport.faceLightIntensity);//脸部光照强度
		// //DEBUG_PRINT_SHAPE("shape:", shape);			                 //矫正后的新Landmark
		// DEBUG_IMSHOW("Correct Image", pSrcImage);                       //矫正后的新图像
		// DEBUG_PRINT_RUN_TIME("Run Times：firstCropping resize=%dms\n", (GTIME9 - GTIME8));

		// //***************************************** rouhg cropping  *******************************************
		// CropImage m_roughCrop;
		// IdPhotoPicParams roughCropping_Params = getIdPhotoPicParams(IDPHOTO_TYPE_US_VISA);
		// IMAGE_CROP_STRUCT rough_crop_image = m_roughCrop.roughCropping(pSrcImage, shape, roughCropping_Params);
		// DEBUG_PRINT_SHAPE("shape:", rough_crop_image.newShape);
		// DEBUG_IMSHOW("rough_crop_image", rough_crop_image.scaleImage, rough_crop_image.newShape);

		// /*****************************************skin Color Correction****************************************************/
		// ColorCorrection m_colorCorr;
		// m_colorCorr.skinColorCorrection(rough_crop_image.scaleImage,rough_crop_image.newShape);
		// DEBUG_IMSHOW("skinColorCorrection", rough_crop_image.scaleImage, rough_crop_image.newShape);

		// //******************************************** Beauty *********************************************************/
		// FaceBeauty m_faceBeauty;
		// m_faceBeauty.initFaceBeauty(rough_crop_image.scaleImage, shape);

		// int value =100;//美肤力度
		// int r_value = value;//磨皮程度
		// int w_value = value*1.5;//美白程度，美肤力度的1.5倍
		// cv::Mat BtyImage = m_faceBeauty.processFaceBeauty(r_value, w_value);
		// DEBUG_IMSHOW("BtyImage", BtyImage);

		// //****************************************hear to  cutout ************************************



		// //***************************************standard cropping**************************************
		// CropImage m_cropImage;
		// IdPhotoPicParams picParams = getIdPhotoPicParams(IDPHOTO_TYPE_CHINA_ID);//裁剪尺寸参数由JNI传递
		// //(1)you can call this function to get a croped image,if don't know the images mask and Head-Top coordinates 
		// //IMAGE_CROP_STRUCT image_crop_data = m_cropImage.getCropedImageByAuto(rough_crop_image.scaleImage, rough_crop_image.newShape, picParams);

		// //(2) recommend call this function,but you should provide the parameters Mask
		// cv::Mat mMask = rough_crop_image.scaleImage.clone();//test_Num example,you can clone source images as a mask
		// bool maskColor = false;//Note:PC:maskColor=false,but Android:maskColor=true
		// IMAGE_CROP_STRUCT image_crop_data = m_cropImage.getCropedImage(rough_crop_image.scaleImage, rough_crop_image.newShape, mMask, maskColor, picParams);

		// DEBUG_PRINT_SHAPE("shape:", image_crop_data.newShape);
		// DEBUG_PRINT("image_crop_data,isPadding=%d\n", image_crop_data.isPadding);
		// DEBUG_IMSHOW("image_crop", image_crop_data.scaleImage, image_crop_data.newShape);
		// DEBUG_IMWRITE("image_crop1.jpg", image_crop_data.scaleImage, image_crop_data.newShape);
		// DEBUG_IMWRITE("image_crop2.jpg", image_crop_data.scaleImage);
		// //****************************************get the standard image*********************************
		// cv::Mat IDphoto;
		// cv::resize(image_crop_data.scaleImage, IDphoto, cv::Size(picParams.picWidth, picParams.picHeight), 0, 0, cv::INTER_LINEAR);
		// DEBUG_IMSHOW("IDphoto", IDphoto);
		// //****************************************save the standard image*********************************
		// std::vector<int> para;
		// para.push_back(CV_IMWRITE_JPEG_QUALITY);
		// para.push_back(80);             //set JPEG images quality（0-100）
		// imwrite(outPath, IDphoto, para);//save the ID photo
		// DEBUG_IMWRITE(outPath, IDphoto, para);
		 cout << "project finished...";
		 cin.get();
}
