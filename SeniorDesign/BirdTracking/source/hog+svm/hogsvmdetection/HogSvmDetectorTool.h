#ifndef  HOG_SVM_DETECTOR_H
#define  HOG_SVM_DETECTOR_H


#include "opencv2/opencv.hpp"

#include "stdio.h"
#include "Miscellaneous.h"
using namespace cv;

#define POS_LABEL  1
#define NEG_LABEL -1

typedef enum { NEG = -1, POS = 1 } Label;

class   HOGSvmDetetorTool
{
public:

	HOGSvmDetetorTool(void);
	~HOGSvmDetetorTool(void);

public:
	bool create(Size _winSize = Size(WIN_W,WIN_H) ,Size _blockSize = Size(BLK_W,BLK_H), Size _blockStride= Size(BLK_S_W,BLK_S_H),
		        Size _cellSize= Size(CEL_W,CEL_H), int _nbins = BIN_S);
	
	bool train(const CvMat* train_data, 
		const CvMat* labels, 
		CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON),
		double C = 10.0);

	bool train(char* posFilePath, 
		char* negFileFath, int npo = NEG_POS_R,
		CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON),
		double C = 10.0);

	void loadDetector(const char* filePath);
	void saveDetector(const char* filePath);
	float predict(const Mat& sample);
	void  predict(char* imgPath, Label lb, int& nImg, int& nRight, float& accuracy);

	void objectdetect(const Mat& img, vector<Rect>& foundLocations,	
		              double hitThreshold = 0, Size winStride = Size(),
		              Size padding=Size(), double scale=1.05,
		              int groupThreshold = 2);

private:
	void* hogDetector; 

};

#endif