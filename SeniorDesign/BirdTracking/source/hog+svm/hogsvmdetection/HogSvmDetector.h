#ifndef HOG_SVM_Detector_h
#define HOG_SVM_Detector_h




#include "HogSvmDetectorTool.h"

#include "TvSVM.h"

#include "Miscellaneous.h"


class  HogSvmDetector :public HOGDescriptor
{
public:

	HogSvmDetector(Size _winSize = Size(WIN_W,WIN_H) , Size _blockSize = Size(BLK_W,BLK_H), Size _blockStride= Size(BLK_S_W,BLK_S_H),
		        Size _cellSize= Size(CEL_W,CEL_H), int _nbins = BIN_S);	
    
	~HogSvmDetector(void);

	TvSVM svm;

private:
	bool calcFeatureVec(char* filePath, float* buf, bool bNegflag);
	bool calcFeatureMat(char* posFilePath, char*  negFilePath, CvMat** features, CvMat** labels);
	int nNegSampleStep;
	int nTotalNegSampleNum;
	int nUsedNegSampleNum;
	int nTotalPosSampleNum;
	int nNegSampleMemSize;
	int nPosSampleMemSize;
	int nSingleFeatureSize;
	double dbNegtoPosRatio;
	char modelPath[512];


protected:
	bool CheckSampleContext(const char* posFilePath, const char* negFilePath);

public:
	void SetModelPath(const char* path){strcpy(modelPath,path);}
	bool train(const CvMat* train_data, 
		const CvMat* labels, 
		CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON),
		double C = 10.0);

	bool train(char* posFilePath, 
		char* negFileFath, int npr = NEG_POS_R,
		CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON),
		double C = 10.0);

	void loadDetector(const char* filePath);
	void saveDetector(const char* filePath);
	float predict(const Mat& sample);
	void predict(char* imgPath, Label lb, int& nImg, int& nRight, float& accuracy);
	void objectdetect(const Mat& img, vector<Rect>& foundLocations,	
		              double hitThreshold = 0, Size winStride = Size(),
		              Size padding=Size(), double scale=1.05,
		              int groupThreshold = 2);
	void Save(const String& filename);
};

#endif