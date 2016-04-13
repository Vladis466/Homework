#include "MultiScaleDescriptor.h"


MultiScaleDescriptor::MultiScaleDescriptor(void)
{
	m_pFirstScaleHOG = new HOGDescriptor(Size(24,30),cv::Size(12,12),Size(6,6),Size(6,6),9);
	m_pSecondScaleHOG = new HOGDescriptor(Size(24,30),cv::Size(6,6),Size(6,6),Size(6,6),9);
	m_pThirdScaleHOG = new HOGDescriptor(Size(24,30),cv::Size(12,15),Size(12,15),Size(12,15),9);
}

MultiScaleDescriptor::MultiScaleDescriptor(Size _winSize, Size _blockSize , Size _blockStride,Size _cellSize, int _nbins )
{
	m_pFirstScaleHOG = new HOGDescriptor(_winSize,_blockSize,_blockStride,_cellSize,_nbins);
	int sw = gcd(_winSize.width,_winSize.height);
	if(sw != _winSize.width / 2 && sw != _winSize.height / 2)
		m_pSecondScaleHOG = new HOGDescriptor(_winSize,Size(sw,sw),Size(sw,sw),Size(sw,sw),_nbins);
	m_pThirdScaleHOG = new HOGDescriptor(_winSize,Size(_winSize.width /2,_winSize.height / 2),Size(_winSize.width /2,_winSize.height / 2),Size(_winSize.width /2,_winSize.height / 2),_nbins);
}
MultiScaleDescriptor::~MultiScaleDescriptor(void)
{
	delete m_pFirstScaleHOG;
	if(m_pSecondScaleHOG)
	{
		delete m_pSecondScaleHOG;
	}
	delete m_pThirdScaleHOG;
}
void MultiScaleDescriptor::Compute(const Mat& img, vector<float>& descriptors)
{
	vector<float> descriptor1;
	vector<float> descriptor2;
	vector<float> descriptor3;
	m_pFirstScaleHOG->compute(img,descriptor1,Size(8,8),Size(0,0));
	m_pThirdScaleHOG->compute(img,descriptor2,Size(8,8),Size(0,0));
	
	int s1 = descriptor1.size();
	int s2 = descriptor2.size();
	int s3 = 0;
	if(m_pSecondScaleHOG)
	{
		m_pSecondScaleHOG->compute(img,descriptor3,Size(8,8),Size(0,0));
		s3 = descriptor3.size();
	}
	descriptors.resize(s1 + s2 + s3);
	for(int i = 0; i < s1;i ++)
		descriptors[i] = descriptor1[i];
	for(int i = 0; i < s2;i ++)
	{
		descriptors[i + s1] = descriptor2[i];
	}
	s1 += s2;
	for(int i = 0; i < s3; i ++)
	{
		descriptors[i + s1] = descriptor3[i];
	}
}
int MultiScaleDescriptor::GetDescriptorLength()
{
	int s = 0;
	if(m_pSecondScaleHOG)
		s = m_pSecondScaleHOG->getDescriptorSize();
	return m_pFirstScaleHOG->getDescriptorSize() + m_pThirdScaleHOG->getDescriptorSize() + s;
}
void MultiScaleDescriptor::SetSVMDetector(vector<float>& vec)
{
	CV_Assert(vec.size() == GetDescriptorLength() || vec.size() == GetDescriptorLength() + 1);
	svmDetector = vec;

}
void MultiScaleDescriptor::save(const String& filename, const String& objName) const
{
	FileStorage fs(filename, FileStorage::WRITE);
	fs << (!objName.empty() ? objName : FileStorage::getDefaultObjectName(filename)) << "{";

	fs  << "winSize" << m_pFirstScaleHOG->winSize
		<< "blockSize" << m_pFirstScaleHOG->blockSize
		<< "blockStride" << m_pFirstScaleHOG->blockStride
		<< "cellSize" << m_pFirstScaleHOG->cellSize
		<< "nbins" << m_pFirstScaleHOG->nbins
		<< "derivAperture" << m_pFirstScaleHOG->derivAperture
		<< "winSigma" << m_pFirstScaleHOG->getWinSigma()
		<< "histogramNormType" << m_pFirstScaleHOG->histogramNormType
		<< "L2HysThreshold" << m_pFirstScaleHOG->L2HysThreshold
		<< "gammaCorrection" << m_pFirstScaleHOG->gammaCorrection;
	if( !svmDetector.empty() )
		fs << "SVMDetector" << "[:" << svmDetector << "]";
	fs << "}";
}