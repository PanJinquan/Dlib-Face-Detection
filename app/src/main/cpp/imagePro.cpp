//
// Created by panjq1 on 2017/10/22.
//
#include <string>
#include <android/log.h>
#include "opencv2/opencv.hpp"
#include "AndroidDebug.h"
#include "com_panjq_opencv_alg_ImagePro.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>
#include <src/main/cpp/detect/DetectFeature.h>
#include "dlibFaceDetection.h"
using namespace dlib;
using namespace std;
using namespace smartimage;

smartimage::FaceDetection *pFaceDetect=nullptr;
String g_modelPath;

extern "C"
JNIEXPORT jboolean JNICALL Java_com_panjq_opencv_alg_FaceDetection_initFaceDetection
        (JNIEnv *env, jobject obj, jstring mDlibModel){
    pFaceDetect = new FaceDetection();
    string path=env->GetStringUTFChars(mDlibModel,NULL);
    g_modelPath=path;
    LOGE("正在初始化Dlib...");
    pFaceDetect->initFaceDetection(g_modelPath);
    LOGE("DlibModelPath=%s",g_modelPath.c_str());
    //env->ReleaseStringUTFChars(mDlibModel,path.c_str());
    LOGE("初始化完毕...");
    return (jboolean)true;
}

extern "C"
JNIEXPORT jint JNICALL Java_com_panjq_opencv_alg_FaceDetection_faceDetection
        (JNIEnv *, jobject, jlong matAddrSrcImage, jlong matAddrDestImage){
    DEBUG__TIME0;
    cv::Mat& pSrcImage  = *(Mat*)matAddrSrcImage;
    cv::Mat& destImage = *(Mat*)matAddrDestImage;
    cv::cvtColor(pSrcImage,pSrcImage,CV_BGRA2BGR);
//    string imgPath = "/storage/emulated/0/ID_Photo/colorCorrection.jpg";
//    cv::Mat pSrcImage=cv::imread(imgPath);
//    string modePath = "/storage/emulated/0/ID_Photo/landmark_model.dat";
    //**************************************** face detection *******************************************
    destImage=pSrcImage.clone();
    int32_t face_num;
    if (nullptr == pFaceDetect)
    {
        LOGE("正在初始化Dlib...");
        LOGE("DlibModelPath=%s",g_modelPath.c_str());
        pFaceDetect = new FaceDetection();
        pFaceDetect->initFaceDetection(g_modelPath);
        LOGE("初始化完毕...");
        //face_num = pFaceDetect->detectFaces(imgPath, pSrcImage);
        face_num = pFaceDetect->detectFaces(destImage);
    }
    else
    {
        LOGE("Dlib已经初始化了...");
        face_num = pFaceDetect->detectFaces(destImage);
    }
    LOGE("detect face num=%d",face_num);
    if (face_num < 1)
    {
        return (jint)face_num;
    }
    full_object_detection shape = pFaceDetect->getDetectOneShape();
    DetectFeature *detectFeature =new DetectFeature();
    detectFeature->faceFeature(destImage,shape);
    delete  detectFeature;
    detectFeature= nullptr;
    //**************************************** end*******************************************
    cv::cvtColor(destImage,destImage,CV_BGRA2BGR);
    DEBUG__TIME1;
    LOGE("Run time:faceDetection=%dms\n",(TIME1-TIME0)/1000);
    LOGE("faceDetection: ouput image size=[%d,%d],channels=%d\n",destImage.rows,destImage.cols,destImage.channels());
//    delete dlib
//    pFaceDetect->uninitFaceDetection();
//    delete pFaceDetect;
//    pFaceDetect = nullptr;
    return (jint)face_num;
}


extern "C"
JNIEXPORT jobject JNICALL Java_com_panjq_opencv_alg_FaceDetection_jniImagePro2
        (JNIEnv *env, jobject obj, jobject image_obj){
    DEBUG__TIME0;
    //获取Java中的实例类
    // jclass jcInfo = env->FindClass("com/panjq/opencv/alg/ImageData");
    jclass jcInfo = env->GetObjectClass(image_obj);

    //获得类属性
    jfieldID jf_w = env->GetFieldID(jcInfo, "w", "I");//ImageData类中属性w
    int w = env->GetIntField(image_obj, jf_w);
    jfieldID jf_h = env->GetFieldID(jcInfo, "h", "I");//ImageData类中属性h
    int h = env->GetIntField(image_obj, jf_h);

    //ImageData类中属性pixels
    jfieldID jf_pixels = env->GetFieldID(jcInfo, "pixels", "[I");
    //获得对象的pixels数据，并保存在pixels数组中
    jintArray pixels = (jintArray)env->GetObjectField(image_obj, jf_pixels);
    jint *ptr_pixels = env->GetIntArrayElements(pixels, 0);//获得pixels数组的首地址
    Mat imgData(h,w,CV_8UC4,(unsigned char*) ptr_pixels);
    cv::cvtColor(imgData,imgData,CV_BGRA2BGR);
    LOGE("jniImagePro2: input image size=[%d,%d]",imgData.cols,imgData.rows);
    //释放内存空间
    env->ReleaseIntArrayElements(pixels, ptr_pixels, 0);
    //imwrite("/storage/emulated/0/OpencvDemo/input_imgData.jpg",imgData);
    //****************** here to Opencv image relevant processing*****************
    /**
     *
     * 进行OpenCV的图像处理....
     *
     */
    blur(imgData,imgData,Size(20,20));//图像模糊
    //resize(imgData,imgData,Size(imgData.cols/4,imgData.rows/4),INTER_LINEAR);//图像缩小4倍
    /**
     *
     *
     */
    //*********************************** end ************************************
    jobject obj_result = env->AllocObject(jcInfo);
    cv::cvtColor(imgData,imgData,CV_BGR2BGRA);
    //imwrite("/storage/emulated/0/OpencvDemo/out_imgData.jpg",imgData);
    uchar *ptr = imgData.data;
    int size = imgData.rows* imgData.cols;
    jintArray resultPixel = env->NewIntArray(size);
    jint *ptr_resultPixel = env->GetIntArrayElements(resultPixel, 0);//获得数组的首地址
    env->SetIntArrayRegion(resultPixel, 0, size, (const jint *) ptr);
    env->SetObjectField(obj_result, jf_pixels, resultPixel);
    h=imgData.rows;
    w=imgData.cols;
    LOGE("jniImagePro2: ouput image size=[%d,%d]",w,h);
    env->SetIntField(obj_result, jf_w, w);
    env->SetIntField(obj_result, jf_h, h);
    env->ReleaseIntArrayElements(resultPixel, ptr_resultPixel, 0);
    DEBUG__TIME1;
    LOGE("Run time:jniImagePro2=%dms\n",(TIME1-TIME0)/1000);
    return  obj_result;
}

extern "C"
JNIEXPORT jintArray  JNICALL Java_com_panjq_opencv_alg_FaceDetection_jniImagePro1
        (JNIEnv *env, jobject obj, jintArray buf, jint w , jint h){
    DEBUG__TIME0;
    //读取int数组并转为Mat类型
    jint *cbuf = env->GetIntArrayElements(buf,JNI_FALSE);
    if (NULL == cbuf)
    {
        return 0;
    }
    Mat imgData(h,w,CV_8UC4,(unsigned char*) cbuf);
    cv::cvtColor(imgData,imgData,CV_BGRA2BGR);
    LOGE("jniImagePro1: called JNI start...image size=[%d,%d]",imgData.cols,imgData.rows);
    //这里进行图像相关操作
    blur(imgData,imgData,Size(20,20));


    //对图像相关操作完毕
    cv::cvtColor(imgData,imgData,CV_BGR2BGRA);
    //这里传回int数组。
    uchar *ptr = imgData.data;
    //int size = imgData.rows * imgData.cols;
    int size = w * h;
    jintArray result = env->NewIntArray(size);
//    env->SetIntArrayRegion(result, 0, size, cbuf);
    env->SetIntArrayRegion(result, 0, size, (const jint *) ptr);
    env->ReleaseIntArrayElements(buf, cbuf, 0);
    LOGE("jniImagePro1: called JNI end...image size=[%d,%d]",imgData.cols,imgData.rows);
    DEBUG__TIME1;
    LOGE("Run time:jniImagePro1=%dms\n",(TIME1-TIME0)/1000);
    return result;
}


