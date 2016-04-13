#include "HogSvmDetectorTool.h"
#include "HogSvmDetector.h"


#include "windows.h"

HOGSvmDetetorTool::HOGSvmDetetorTool()
{
	hogDetector = NULL;
}

HOGSvmDetetorTool::~HOGSvmDetetorTool()
{
	if(hogDetector != NULL)
	{
		delete hogDetector;
		hogDetector = NULL;
	}
}

bool HOGSvmDetetorTool::create(Size _winSize, Size _blockSize , Size _blockStride,
	                           Size _cellSize, int _nbins)
{
	if(hogDetector == NULL)
	  hogDetector = new HogSvmDetector(_winSize,_blockSize,_blockStride,_cellSize,_nbins);
	return TRUE;
}

bool HOGSvmDetetorTool::train(const CvMat* train_data, 
	                          const CvMat* labels, 
	                          CvTermCriteria criteria,
	                          double C )
{
	
	if(hogDetector == NULL) create();
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	_hogDetector->train(train_data,labels);
	return TRUE;
}

bool HOGSvmDetetorTool::train(char* posFilePath, 
	                          char* negFileFath, int npr,
	                          CvTermCriteria criteria ,
	                          double C )
{
	if(hogDetector == NULL) 
		create();
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	_hogDetector->train(posFilePath,negFileFath,npr);
	return TRUE;
}

void HOGSvmDetetorTool::loadDetector(const char* filePath)
{
	if(hogDetector == NULL) create();
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	_hogDetector->load(filePath);
	_hogDetector->SetModelPath(filePath);

}

void HOGSvmDetetorTool::saveDetector(const char* filePath)
{
	if(hogDetector == NULL) create();
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	_hogDetector->Save(filePath);

}
float HOGSvmDetetorTool::predict(const Mat& sample)
{
	if(hogDetector == NULL) return 0.0;
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	return (_hogDetector->predict(sample));

}
void HOGSvmDetetorTool::predict(char* imgPath, Label lb, int& nImg, int& nRight, float& accuracy)
{
	
	if(hogDetector == NULL) return;
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	_hogDetector->predict(imgPath,lb,nImg,nRight,accuracy);
}

void HOGSvmDetetorTool::objectdetect(const Mat& img, vector<Rect>& foundLocations,	
	                           double hitThreshold , Size winStride ,
	                           Size padding, double scale,
	                           int groupThreshold )
{
	if(hogDetector == NULL) return;
	HogSvmDetector* _hogDetector = (HogSvmDetector*) hogDetector;
	_hogDetector->objectdetect(img,foundLocations,hitThreshold,winStride,padding,scale,groupThreshold);
}

