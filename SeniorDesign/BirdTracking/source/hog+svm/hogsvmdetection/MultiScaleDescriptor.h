pragma once
#include "HogSvmDetectorTool.h"
class MultiScaleDescriptor
{
public:
	MultiScaleDescriptor(void);
	MultiScaleDescriptor(Size _winSize, Size _blockSize , Size _blockStride,Size _cellSize, int _nbins );
	~MultiScaleDescriptor(void);
private:
	HOGDescriptor* m_pFirstScaleHOG;
	HOGDescriptor* m_pSecondScaleHOG;
	HOGDescriptor* m_pThirdScaleHOG;

	 
public:

	vector<float> svmDetector;
	void Compute(const Mat& img, vector<float>& descriptors);
	int GetDescriptorLength();
	void SetSVMDetector(vector<float>& vec);
	void save(const String& filename,const String& objname=String()) const;
};

