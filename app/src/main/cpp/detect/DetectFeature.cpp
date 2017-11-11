//
// Created by panjq1 on 2017/11/10.
//

#include "DetectFeature.h"
#include <stdlib.h>

DetectFeature::DetectFeature() {
}
DetectFeature::~DetectFeature() {
}

DetectFeature::DetectFeature(full_object_detection shape) {
    this->shape=shape;
}


void DetectFeature::setShape(full_object_detection shape){
    this->shape=shape;
}
full_object_detection DetectFeature::gstShape(){
    return  this->shape;
}
void DetectFeature::faceFeature(cv::Mat &image,full_object_detection shape){
    //do image process...
    this->showLandmark(image,shape, true);
}

void DetectFeature::showLandmark(cv::Mat &image, full_object_detection shape,bool showNum){
    int thickness=image.cols/150;
    thickness=(thickness>2)?thickness:2;
    for (size_t i = 0; i < shape.num_parts(); i++)
    {
        shape.part(0).x();
        int x = shape.part(i).x();
        int y = shape.part(i).y();
        cv::circle(image, cv::Point(x, y), 1, cv::Scalar(0, 0, 255),thickness);
        if(showNum){
            char str[3];
            //itoa(i, str, 10);
            sprintf(str,"%d",i);
            //line(imgDrawFace, cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Point(shape.part(i).x(), shape.part(i).y()), cv::Scalar(0, i * 3, 255), 2);
            putText(image, str, cv::Point(x, y), cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(0, 255, 0,100),thickness);
        }
    }
    cv::Rect rect(shape.get_rect().left(), shape.get_rect().top(), shape.get_rect().right() - shape.get_rect().left(), shape.get_rect().bottom() - shape.get_rect().top());
    cv::rectangle(image, rect, cv::Scalar(255, 0, 0), thickness, 1, 0);
}
