// "VIBE: A POWERFUL RANDOM TECHNIQUE TO ESTIMATE THE BACKGROUND IN VIDEO SEQUENCES"

#include "opencv2/opencv.hpp"
#include "ViBe.h"
#include <iostream>
#include <cstdio>
#include <chrono>

#define _FROM_FILE_// comment out this macro if you want to capture video from ccd
using namespace cv;
using namespace std;
using namespace std::chrono;

#define BLUR_SIZE 5
int main(int argc, char* argv[])
{
	char filename[512];
	Mat frame, color_frame;
	// mask;
	milliseconds LastTimeStamp = milliseconds();
	float start_time = 0;
	float last_time = 0;
#ifdef _FROM_FILE_
	VideoCapture capture;
	cout << "Please enter the file name" << endl;
	cin >> filename;
	capture.open(filename);
	if (!capture.isOpened())
#else
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);
	if (!capture)
#endif
	{
		cout << "No camera or video input!\n" << endl;
		return -1;
	}

	ViBeBackgroundModel ViBeBackgroundModel;
	int FrameIndex = 0;

	while (1)
	{
		FrameIndex++;
#ifdef _FROM_FILE_
		capture.read(frame);
#else
		frame = cvQueryFrame(capture);
#endif
		if (frame.empty())
			break;
		LastTimeStamp = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
		cvtColor(frame, color_frame, CV_RGB2RGBA);
		//cv::blur(frame, frame, cv::Size(BLUR_SIZE, BLUR_SIZE));
		if (FrameIndex == 1)
		{
			ViBeBackgroundModel.Init(color_frame);
		}
		else
		{
			ViBeBackgroundModel.Update(color_frame);
			Mat& mask = ViBeBackgroundModel.GetMask();
			ViBeBackgroundModel.RemoveSinglePoint();
			imshow("Original Output", mask);
			//morphologyEx(mask, mask, MORPH_OPEN, Mat());
			//imshow("Processed output", mask);
		}

		imshow("input", color_frame);
		milliseconds CurrentTimeStamp = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
		std::cout << "Current Frame: " << FrameIndex << " Processing Time:" << (CurrentTimeStamp - LastTimeStamp).count() << endl;
		if (cvWaitKey(10) == 'q')
			break;

	}

	return 0;
}