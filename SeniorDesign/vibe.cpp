#include <opencv2/opencv.hpp>
#include <iostream>
#include "vibe.h"
 
using namespace std;
using namespace cv;
 
 
ViBeBackgroundModel::ViBeBackgroundModel(void)
{
    int _OffsetX[] = { -1,  1, -1, 1, 0, 0, 1, -1 };
    int _OffsetY[] = { -1,  1, 1, -1, -1, 1, 0, 0 };
    for (int i = 0; i < NEIGHBOR_POINT_NUM; i++)
    {
        OffsetX[i] = _OffsetX[i];
        OffsetY[i] = _OffsetY[i];
    }
}
ViBeBackgroundModel::~ViBeBackgroundModel(void)
{
 
}
//Init the background sample images.
void ViBeBackgroundModel::Init(const Mat _image)
{
    for (int i = 0; i < SampleImageStackSize; i++)
    {
        SampleImageStack[i] = Mat::zeros(_image.size(), CV_8UC4);
    }
    ForegroundImageHitCount = Mat::zeros(_image.size(), CV_8UC1);
    ForegroundImage = Mat::zeros(_image.size(), CV_8UC1);
    RNG rng;
    int row, col;
    int* src = (int*)_image.data;
    int* dst = 0;
 
    for (int i = 0; i < _image.rows; i++)
    {
        for (int j = 0; j < _image.cols; j++)
        {
            for (int k = 0; k < SampleImageStackSize; k++)
            {
                dst = (int*)SampleImageStack[k].data;
                //Random pick up SampleImageStackSize pixel in neighbourhood to construct the model
                int random = rng.uniform(0, 9);
 
                row = i + OffsetY[random];
                if (row < 0)
                    row = 0;
                if (row >= _image.rows)
                    row = _image.rows - 1;
 
                col = j + OffsetX[random];
                if (col < 0)
                    col = 0;
                if (col >= _image.cols)
                    col = _image.cols - 1;
                dst[i * _image.cols + j] = src[row * _image.cols + col];
            }
        }
    }
}
inline int regulateIndex(int x, int y, int w, int h)
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= w)
        x = w - 1;
    if (y >= h)
        y = h - 1;
    return y * w + x;
}
void  ViBeBackgroundModel::RemoveSinglePoint()
{
    uchar* fore_ptr = ForegroundImage.data;
    int w = ForegroundImage.cols;
    int h = ForegroundImage.rows;
    int r = w*h;
    int index = 0;
    int index1 = 0;
    int x, y;
    int n = 0;
    for (int i = 0; i < h; i++)
    {
         
        for (int j = 0; j < w; j++)
        {
            n = 0;
            if (fore_ptr[index] == 0)
            {
                index++;
                continue;
            }
            if (fore_ptr[index] == 254)
            {
                index++;
                continue;
            }
            for (int k = 0; k < NEIGHBOR_POINT_NUM; k++)
            {
                x = j + OffsetX[k];
                y = i + OffsetY[k];
                index1 = regulateIndex(x, y, w, h);
                if (fore_ptr[index1] != 0)
                {
                    fore_ptr[index1] = 254;
                    fore_ptr[index] = 254;
                    n++;
                    break;
                }
            }
            if (n == 0)
                fore_ptr[index] = 0;
            index++;
        }
    }
}
///Update the model using randam scheme
void ViBeBackgroundModel::Update(const Mat& _image)
{
    RNG rng;
    uchar* fore_ptr = ForegroundImageHitCount.data; //I prefer to use points, OpenCV's interfaces sometime are very slow.
    int* img_ptr = (int*)_image.data;
    int* src_ptr = 0;
    int offset1;// using memory offset index can improve the performance, you do not have to re-calculate the point from time to time.
    int offset2;
    int v1, v2;// 32 bits integers for extracting each RGB channels.
    int r, g, b;
    for (int i = 0; i < _image.rows; i++)
    {
        offset1 = i * _image.cols;
        for (int j = 0; j < _image.cols; j++)
        {
            offset2 = offset1 + j;
            int matches(0), count(0);
            int dist = 0;
 
            while (matches < MIN_MATCHES && count < SampleImageStackSize)
            {
                v1 = ((int*)SampleImageStack[count].data)[offset2];
                v2 = img_ptr[offset2];
                r = (v1 & 0xff) - (v2 & 0xff);
                g = ((v1 >> 8) & 0xff) - ((v2 >> 8) & 0xff);
                b = ((v1 >> 16) & 0xff) - ((v2 >> 16) & 0xff);
                dist = r*r + b*b + g*g;
                if (dist < RADIUS)
                    matches++;
                count++;
            }
 
            if (matches >= MIN_MATCHES)
            {
                // It is a background pixel
                fore_ptr[offset2] = 0;
 
                // Set background pixel to 0
                ForegroundImage.data[offset2] = 0;
 
                int random = rng.uniform(0, SUBSAMPLE_FACTOR);
                if (random == 0)
                {
                    random = rng.uniform(0, SampleImageStackSize);
                    ((int*)SampleImageStack[random].data)[offset2] = img_ptr[offset2];
                }
 
                random = rng.uniform(0, SUBSAMPLE_FACTOR);
                if (random == 0)
                {
                    int row, col;
                    random = rng.uniform(0, 9);
                    row = i + OffsetY[random];
                    if (row < 0)
                        row = 0;
                    if (row >= _image.rows)
                        row = _image.rows - 1;
 
                    random = rng.uniform(0, 9);
                    col = j + OffsetX[random];
                    if (col < 0)
                        col = 0;
                    if (col >= _image.cols)
                        col = _image.cols - 1;
 
                    random = rng.uniform(0, SampleImageStackSize);
                    ((int*)SampleImageStack[random].data)[offset2] = img_ptr[offset2];
                }
            }
            else
            {
                // It is a foreground pixel
                fore_ptr[offset2] ++;
 
                // Set background pixel to 255 (white)
                ForegroundImage.data[offset2] = 255;
 
                //if any point being forground for over 50 time, we think it should be background pixel
                if (fore_ptr[offset2] > 50)
                {
                    int random = rng.uniform(0, SampleImageStackSize);
                    if (random == 0)
                    {
                        random = rng.uniform(0, SampleImageStackSize);
                        ((int*)SampleImageStack[random].data)[offset2] = img_ptr[offset2];
                    }
                }/**/
            }
        }
    }
    //RemoveSinglePoint();
}