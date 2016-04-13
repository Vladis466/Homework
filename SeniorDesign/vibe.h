#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"
 
using namespace cv;
using namespace std;
 
#define SampleImageStackSize 20     //Sample Image stack for background model
#define MIN_MATCHES 2       //Min match count
#define RADIUS 500      //space radius
#define SUBSAMPLE_FACTOR 16 //sample factor
#define NEIGHBOR_POINT_NUM 8    
#define MAX_FOREGROUND_HIT_COUNT 32
#define IMAGE_STACK_SIZE 20     
 
class ViBeBackgroundModel
{
public:
    ViBeBackgroundModel(void);
    ~ViBeBackgroundModel(void);
 
    void Init(const Mat _image);   //???
    void Update(const Mat& _image);  //??
    Mat& GetMask(void){ return ForegroundImage; };
    void RemoveSinglePoint();
private:
    Mat SampleImageStack[IMAGE_STACK_SIZE];
    Mat ForegroundImageHitCount;
    Mat ForegroundImage;
    int OffsetX[NEIGHBOR_POINT_NUM];
    int OffsetY[NEIGHBOR_POINT_NUM];
};