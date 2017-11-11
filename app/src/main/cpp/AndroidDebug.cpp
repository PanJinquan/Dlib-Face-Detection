#include "opencv2/opencv.hpp"
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
using namespace dlib;
using namespace std;

void showImages(const char *imageName, cv::Mat srcImage, full_object_detection shape) {
	cv::Mat imgDrawFace = srcImage.clone();
	for (size_t i = 0; i < shape.num_parts(); i++)
	{
		shape.part(0).x();
		//point pt = shape.part(i);
		int x = shape.part(i).x();
		int y = shape.part(i).y();
//		char str[3];
//		itoa(i, str, 10);
//		//line(imgDrawFace, cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Scalar(0, i * 3, 255), 2);
//		putText(imgDrawFace, str, cv::Point(shape.part(i).x(), shape.part(i).y()), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 0, 0));
		cv::circle(imgDrawFace, cv::Point(x, y), 1, cv::Scalar(0, 0, 255));  
	}
	cv::rectangle(imgDrawFace, cv::Rect(shape.get_rect().left(), shape.get_rect().top(), shape.get_rect().right() - shape.get_rect().left(), shape.get_rect().bottom() - shape.get_rect().top()), cv::Scalar(0, 0, 255), 1, 1, 0);
//	char str[200];
	char str1[200];
	strcpy(str1, imageName);
	//sprintf(str, ",Size:%dx%d", imgDrawFace.rows, imgDrawFace.cols);
	//strcat(str1, str);
	int col = 358;
	cv::resize(imgDrawFace, imgDrawFace, cv::Size(col, imgDrawFace.rows*col / imgDrawFace.cols));
	cv::imshow(str1, imgDrawFace);
	cv::waitKey(100);
}
void showImages(const char *imageName, cv::Mat image) {
	cv::Mat imgDrawFace = image.clone();
	//char str[200];
	char str1[200];
	strcpy(str1, imageName);
	//sprintf(str, ",Size:%dx%d", image.rows, image.cols);
	//strcat(str1, str);
	int col = 358;
	cv::resize(imgDrawFace, imgDrawFace, cv::Size(col, imgDrawFace.rows*col / imgDrawFace.cols));
	cv::imshow(str1, imgDrawFace);	
	cv::waitKey(100);
}


void showImages(const char *imageName, cv::Mat img, cv::Rect face, std::vector<cv::Point> pts)
{
	cv::Mat img_show;
	if (img.channels() == 1)
	{
		img_show = gray2BGR(img);
	}
	else {
		img_show = img.clone();
	}
	for (int i = 0; i < pts.size(); ++i) {
		//std::cout << "index: " << i << std::endl;
		cv::circle(img_show, pts.at(i), 2.f, cv::Scalar(0, 0, 255), -1, CV_AA);
		//		char str[3];
		//		itoa(i, str, 10);
		//		//line(imgDrawFace, cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Scalar(0, i * 3, 255), 2);
		//		putText(img_show, str, pts.at(i), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 0, 0));

	}
	cv::rectangle(img_show, face, { 255, 0, 0 }, 2);
	char str[200];
	char str1[200];
	strcpy(str1, imageName);
	//sprintf(str, ",Size:%dx%d", img.rows, img.cols);
	//strcat(str1, str);
	int col = 358;
	cv::resize(img_show, img_show, cv::Size(col, img_show.rows*col / img_show.cols));
	cv::imshow(str1, img_show);
	cv::waitKey(100);
}


void showImages(const char *imageName, cv::Mat img, std::vector<cv::Point> pts)
{
	cv::Mat img_show;
	if (img.channels() == 1)
	{
		img_show = gray2BGR(img);
	}
	else {
		img_show = img.clone();
	}
	for (int i = 0; i < pts.size(); ++i) {
		//std::cout << "index: " << i << std::endl;
		cv::circle(img_show, pts.at(i), 2.f, cv::Scalar(0, 0, 255), -1, CV_AA);
		//		char str[3];
		//		itoa(i, str, 10);
		//		//line(imgDrawFace, cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Scalar(0, i * 3, 255), 2);
		//		putText(img_show, str, pts.at(i), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 0, 0));
	}
	char str[200];
	char str1[200];
	strcpy(str1, imageName);
	//sprintf(str, ",Size:%dx%d", img.rows, img.cols);
	//strcat(str1, str);
	int col = 358;
	cv::resize(img_show, img_show, cv::Size(col, img_show.rows*col / img_show.cols));
	cv::imshow(str1, img_show);
	cv::waitKey(100);
}

void showImages(const char *imageName, cv::Mat img, cv::Rect face)
{
	cv::Mat img_show;
	if (img.channels() == 1)
	{
		img_show = gray2BGR(img);
	}
	else {
		img_show = img.clone();
	}
	cv::rectangle(img_show, face, { 255, 0, 0 }, 2);
	char str[200];
	char str1[200];
	strcpy(str1, imageName);
	//sprintf(str, ",Size:%dx%d", img.rows, img.cols);
	//strcat(str1, str);
	int col = 358;
	cv::resize(img_show, img_show, cv::Size(col, img_show.rows*col / img_show.cols));
	cv::imshow(str1, img_show);
	cv::waitKey(100);
}

void printfShape(const char *str, full_object_detection shape) {
	DEBUG_PRINT("%s", str);
	for (size_t i = 0; i < shape.num_parts(); i++)
	{
		shape.part(0).x();
		int x = shape.part(i).x();
		int y = shape.part(i).y();
		DEBUG_PRINT("%d,%d;", x, y);
	}
	DEBUG_PRINT("\n");
}


void saveImage(const char *imageName, cv::Mat image, full_object_detection shape) {
	cv::Mat imgDrawFace = image.clone();
	for (size_t i = 0; i < shape.num_parts(); i++)
	{
		shape.part(0).x();
		//point pt = shape.part(i);
		int x = shape.part(i).x();
		int y = shape.part(i).y();
		cv::circle(imgDrawFace, cv::Point(x, y), 1, cv::Scalar(0, 0, 255));
	}
	cv::rectangle(imgDrawFace, cv::Rect(shape.get_rect().left(), 
				shape.get_rect().top(), shape.get_rect().right() - shape.get_rect().left(),
				shape.get_rect().bottom() - shape.get_rect().top()), cv::Scalar(0, 0, 255), 1, 1, 0);
	cv::imwrite(imageName, imgDrawFace);
}
void saveImage(const char *imageName, cv::Mat image) {
	cv::imwrite(imageName, image);
}

void saveImage(const char *imageName, cv::Mat image, std::vector<int> para) {
	cv::imwrite(imageName, image, para);
}

void saveImage(const char *imageName, cv::Mat image, cv::Rect face, std::vector<cv::Point> pts) {
	cv::Mat img = image.clone();
	for (int i = 0; i < pts.size(); ++i) {
		//std::cout << "index: " << i << std::endl;
		cv::circle(img, pts.at(i), 2.f, cv::Scalar(0, 0, 255), -1, CV_AA);
	}
	cv::rectangle(img, face, { 255, 0, 0 }, 2);
	cv::imwrite(imageName, img);
}


cv::Mat gray2BGR(cv::Mat grayImg) {
	cv::Mat bgrImg = cv::Mat::zeros(grayImg.size(), CV_8UC3);
	std::vector<cv::Mat> bgr_channels;
	cv::split(bgrImg, bgr_channels);
	bgr_channels.at(0) = grayImg;
	bgr_channels.at(1) = grayImg;
	bgr_channels.at(2) = grayImg;
	cv::merge(bgr_channels, bgrImg);
	return bgrImg;
}