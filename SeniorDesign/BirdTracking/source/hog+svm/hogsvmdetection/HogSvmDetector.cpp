//#define  HOG__DLLEXPORT_API __declspec(dllexport) 
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "HogSvmDetector.h"
#include "Miscellaneous.h"
#include "windows.h"
HogSvmDetector::HogSvmDetector(Size _winSize, Size _blockSize , Size _blockStride,Size _cellSize, int _nbins )
	           :HOGDescriptor(_winSize,_blockSize,_blockStride,_cellSize,_nbins)
{
	this->nTotalNegSampleNum  = 0;
	this->nTotalPosSampleNum = 0;
	this->dbNegtoPosRatio = 1.0;
	this->nNegSampleStep = 1;
	modelPath[0] = 0;


}


HogSvmDetector::~HogSvmDetector(void)
{

}

bool HogSvmDetector::CheckSampleContext(const char* posFilePath, const char* negFilePath)
{
	printf("Checking Sample Context...\n");
	if(posFilePath == NULL)
		return false;
	if(negFilePath ==  NULL)
		return false;
	 _finddata_t file;
	int memsize = 0;
	int nBlock = 0;
	int nCell = 0;
	double mem = 0;
    vector<float> descriptor;

	long lf;	
	if((lf = _findfirst(posFilePath,&file)) == -1)
    {
        printf("no file found\n");
        return false;
    }
	do
	{
		nTotalPosSampleNum ++;
	}
	while(_findnext(lf,&file) ==0);
	_findclose(lf);
	if((lf = _findfirst(negFilePath,&file)) == -1)
    {
        printf("no file found\n");
        return false;
    }
	do
	{
		nTotalNegSampleNum ++;
	}
	while(_findnext(lf,&file) ==0);
	_findclose(lf);
	nTotalPosSampleNum -= 2;
	nTotalNegSampleNum -= 2;
	if((double)nTotalNegSampleNum > (dbNegtoPosRatio * (double)nTotalPosSampleNum))
	{
		this->dbNegtoPosRatio = (double)nTotalNegSampleNum / ((double)nTotalPosSampleNum * dbNegtoPosRatio) ;
	}
	else
	{
		this->dbNegtoPosRatio = 1.0;
	}
	this->nNegSampleStep = cvRound(this->dbNegtoPosRatio ) + 1;

	nBlock =( (winSize.width - blockSize.width) / blockStride.width + 1 ) * ((winSize.height - blockSize.height) / blockStride.height + 1);
	nCell = blockSize.area() / cellSize.area();
	nSingleFeatureSize = nBlock * nbins * nCell;
	nSingleFeatureSize = getDescriptorSize();

	
	memsize = nSingleFeatureSize;//(nBlock * nbins * nCell);
	memsize *= (nTotalPosSampleNum + (int)((double)nTotalNegSampleNum /dbNegtoPosRatio));
	nNegSampleMemSize = (int)((double)nTotalNegSampleNum /dbNegtoPosRatio) * nBlock * nbins * nCell * sizeof(float);
	nPosSampleMemSize = nTotalPosSampleNum * nBlock * nbins * nCell * sizeof(float);
	memsize *= sizeof(float);
	mem = (double)memsize / 1024.0;
	mem /= 1024.0;
#ifdef _DOUBLE_SAMPLE_FIX_
	mem *= 2;
	printf("Double Sample Fix Feature is applied...\n");
#endif
	nUsedNegSampleNum = (int)((double)nTotalNegSampleNum /dbNegtoPosRatio);
	printf("Pos Sample = %d\n",nTotalPosSampleNum);
	printf("Neg Sample = %d\n",(int)( (double)nTotalNegSampleNum /dbNegtoPosRatio));
	printf("memery needed %f Mega Bytes\n",mem);
#ifdef _DEBUG
	if(mem > 0)
#else
	if(mem >= 2048)
#endif
	{
		printf("required memory may outrun the support size of OpenCV\n Press Enter to continue\nPress Space and Enter to reset neg-Sample to pos-Sample ratio\nPress other key to exit...\n");
		int key =0;
		char temp[20];
		key = getchar();
		
		if(key == 32)
		{
			while(1)
			{
				printf("Please enter a double number\n");
				scanf("%s",temp);
				double r = atof(temp);
				if( r < 1.0)
				{
					printf("Invalidate input,Please try again...\n");
					continue;
				}
				else
				{
					this->dbNegtoPosRatio = (double)nTotalNegSampleNum / ((double)nTotalPosSampleNum * r) ;
					if(dbNegtoPosRatio < 1)
						dbNegtoPosRatio = 1.0;
					memsize = nSingleFeatureSize;//(nBlock * nbins * nCell);
					memsize *= (nTotalPosSampleNum + (int)((double)nTotalNegSampleNum /dbNegtoPosRatio));
					nNegSampleMemSize = (int)((double)nTotalNegSampleNum /dbNegtoPosRatio) * nBlock * nbins * nCell * sizeof(float);
					nPosSampleMemSize = nTotalPosSampleNum * nBlock * nbins * nCell * sizeof(float);
					memsize *= sizeof(float);
					mem = (double)memsize / 1024.0;
					mem /= 1024.0;
					nUsedNegSampleNum = (int)((double)nTotalNegSampleNum /dbNegtoPosRatio);
					printf("Pos Sample = %d\n",nTotalPosSampleNum);
					printf("Neg Sample = %d\n",(int)( (double)nTotalNegSampleNum /dbNegtoPosRatio));
					printf("memory needed %f Mega Bytes\n",mem);
					printf("Press Enter to confirm...\n");
					getchar();
					getchar();
					break;
				}
			}
		}
		else if(key != 10)
			return false;

	}
	return true;
	
}

bool HogSvmDetector::train(const CvMat* train_data, const CvMat* labels, CvTermCriteria criteria, double C)
{
    CvSVMParams param;
    param = CvSVMParams(CvSVM::C_SVC, CvSVM::LINEAR,
                        10.0, 8.0, 1.0, C, 0.5, 0.1, NULL, criteria);

    if (svm.train(train_data, labels, NULL, NULL, param))
    {
        setSVMDetector(svm.get_linear_weight());
        return true;
    }

	    
    return false;
}


bool HogSvmDetector::train(char*  posFilePath, char* negFileFath,int npr, CvTermCriteria criteria, double C)
{
    CvMat *train_data =NULL;
    CvMat *labels = NULL;
	this->dbNegtoPosRatio = (double)npr;
    CvSVMParams param = CvSVMParams(CvSVM::C_SVC, CvSVM::LINEAR,
        10.0, 8.0, 1.0, C, 0.5, 0.1, NULL, criteria);
	if(!CheckSampleContext(posFilePath,negFileFath))//to accelerate loading efficience, where merely use opencv would be really slow when sample set is very large
		return false;
    calcFeatureMat(posFilePath, negFileFath, &train_data, &labels);
    if (svm.train(train_data, labels, NULL, NULL, param))
    {

		setSVMDetector(svm.get_linear_weight());

        
        return true;
    }

    return false;
}


void HogSvmDetector::loadDetector(const char * filename)
{
    svm.load(filename);
    setSVMDetector(svm.get_linear_weight());
}


bool HogSvmDetector::calcFeatureVec(char* filePath,float* buf,bool bNegFlag)
{
#define MAX_NEG_NUM 
    char imgFilePath[500] = "";
	char imgFilePath2[500] = "";
    _finddata_t file;
    vector<float> descriptor;
	int negCounter = 0;
	double negIndex = 0.0;
	int desiredIdx = 0;
	long lf;	
	int index = 0;
	int counter = 0;
	IplImage *dstImage = NULL;
	if((lf = _findfirst(filePath,&file)) == -1)
    {
        printf("no file found\n");
        return false;
    }
	
	for (int i = strlen(filePath); i >=1; i--)
	{
		if(    filePath[i] =='\\'
			&& filePath[i-1] == '\\' 
			)
		{
			for(int j = i; j >= 0 ;j--)
		        imgFilePath[j] = filePath[j];
			imgFilePath[i + 1] = '\0';
			break;
		}
	}


	IplImage* grayImage = cvCreateImage(winSize,8,1);

	float* buffer = new float[nSingleFeatureSize];
    do
    {
		// negative  step-counter used to perform serial re-sample, not randomly~
		if(bNegFlag)
		{
			if((negCounter++) == desiredIdx)
			{
				negIndex += this->dbNegtoPosRatio;
				desiredIdx = cvRound(negIndex);
			}
			else
			{
				continue;
			}

		}
		if(bNegFlag)
		{
			if(counter == nUsedNegSampleNum)
				break;
		}
		else
		{
			if(counter == nTotalPosSampleNum)
				break;
		}
		strcpy(imgFilePath2,imgFilePath);
       IplImage* img = cvLoadImage(strcat(imgFilePath2,file.name));

       if (img)
       {
		   counter ++;
           if(img->height != winSize.height  || img->width != winSize.width)
		   {
			   if(dstImage == NULL)
				   dstImage = cvCreateImage(cvSize(winSize.width,winSize.height), img->depth, img->nChannels);
			   cvResize(img,dstImage,1);
			  // cvShowImage("test show", dstImage);
			 //  cvWaitKey(10);

		   }
		   else
		   {
			   if(dstImage == NULL)
				   dstImage = cvCreateImage(cvSize(winSize.width,winSize.height), img->depth, img->nChannels);
			   cvCopy(img,dstImage,0);
			 //  cvShowImage("test show", dstImage);
			  // cvWaitKey(10);
		   }
		 // printf("start compute...\n");

		   cvConvertImage(dstImage, grayImage);
		  // cvShowImage("test show", grayImage);
		   //cvWaitKey(10);
		   compute(grayImage, descriptor, Size(8, 8), Size(0, 0));


	if(descriptor.size() != nSingleFeatureSize)
		return false;

    for (unsigned int i=0; i<descriptor.size(); i++)
    { 
        buf[index ++] = descriptor[i];
    }


    printf("Feature of image %d has been extracted\r", counter);
         
	   cvReleaseImage(&img);
      }
    }
	while(_findnext(lf,&file) ==0);
	delete[] buffer;
	cvReleaseImage(&grayImage);

    _findclose(lf);
	printf("\n");
	if(dstImage)
	{
		cvReleaseImage(&dstImage);
	}
    return true;
}


bool HogSvmDetector::calcFeatureMat(char* posFilePath, char* negFilePath, CvMat** features, CvMat** labels)
{
    vector<float> posFeatures, negFeatures;

	*features = cvCreateMat(nTotalPosSampleNum +nUsedNegSampleNum, nSingleFeatureSize, CV_32FC1);
    *labels = cvCreateMat(nTotalPosSampleNum +nUsedNegSampleNum, 1, CV_32SC1);


	float* bufferPtr = (float*)(*features)->data.ptr;
	float *l = (float *)(*labels)->data.ptr;

	int index = 0;

	for(int i =  0; i < nTotalPosSampleNum; i ++)
	{
		l[index ++] = POS_LABEL;
	}
	for(int i = 0; i < nUsedNegSampleNum;i ++)
	{
		l[index ++] = NEG_LABEL;
	}

    calcFeatureVec(posFilePath,bufferPtr ,false);

	calcFeatureVec(negFilePath,bufferPtr +  nTotalPosSampleNum * this->nSingleFeatureSize,true);

    
	printf("Extracted Positive Sample Num = %d(total = %d)\n", nTotalPosSampleNum,this->nTotalPosSampleNum);
	printf("Extracted Negative Sample Num = %d(total = %d)\n", nUsedNegSampleNum,this->nTotalNegSampleNum);
	//printf("\n\n\n");
   /* for (i = posNum; i < (*features)->height; i++, offset+=fSize)
    {
        float *f = (float *)((*features)->data.ptr + (*features)->step * i);
        float *l = (float *)((*labels)->data.ptr + (*labels)->step * i);

        l[0] = NEG_LABEL;
        for (j = 0; j < fSize; j++)
        {
            f[j] = negFeatures[offset + j];
        }
    }*/

    return true;
}


void HogSvmDetector::saveDetector(const char *filePath)
{

    svm.save(filePath);
}
void HogSvmDetector::Save(const String& filename)
{

	save(filename);

}

float HogSvmDetector::predict(const Mat& sample)
{
    vector<float> descriptors;
    float s;
    unsigned int i;

    assert(sample.rows == winSize.height &&
           sample.cols == winSize.width);

	 compute(sample, descriptors, Size(8, 8), Size(0, 0));

   
    assert(svmDetector.size() == descriptors.size() ||
           svmDetector.size() == descriptors.size()+1);

    if (svmDetector.size() > descriptors.size())
        s = svmDetector[descriptors.size()];
    else
        s = 0;
    
    for (i=0; i<descriptors.size(); i++)
    {
        assert(i<svmDetector.size());
        s += descriptors[i] * svmDetector[i];
    }
    
    return s;
}


void HogSvmDetector::predict(char* imgPath, Label lb, int& nImg, int& nRight, float& accuracy)
{
    char path[_MAX_PATH] = "";
	char path2[_MAX_PATH] = "";
	char path3[_MAX_PATH] = "";
    _finddata_t fileFinder;
    long bFind;
    float result;
	int neg = 0;
	int pos = 0;
    assert(lb == POS || lb == NEG);

    bFind = _findfirst(imgPath, &fileFinder);
    if (!bFind)
    {
        printf("no file found\n");
        return;
    }

	for (int i = strlen(imgPath); i >=1; i--)
	{
		if(    imgPath[i] =='\\'
			&& imgPath[i-1] == '\\' 
			)
		{
			for(int j = i; j >= 0 ;j--)
				path[j] = imgPath[j];
			path[i + 1] = '\0';
			break;
		}
	}


    nImg = 0;
    nRight = 0;
		IplImage* dstImage = NULL;
		strcpy(path3,"c:\\");
		strcat(path3,"SVM Predict-Report-");
		if(lb)
			strcat(path3,"1-");
		else
			strcat(path,"0-");
		int time = ::timeGetTime();
		char temp[32];
		_itoa(time,temp,16);
		strcat(path3,temp);
		strcat(path3,".txt");
		FILE* pfile = ::fopen(path3,"w");
		if(pfile)
		{
			fprintf(pfile,"This file is report genereated for OpenCV SVM classifier prediction.\nVersion 1.0.0.2011.05.12\n");
			fprintf(pfile,"--------------------------------------------------------\n");
			fprintf(pfile,"--------------------------------------------------------\n");
			fprintf(pfile,"\n");
			fprintf(pfile,"image path: ");
			fwrite(imgPath,strlen(imgPath),1,pfile);
			fwrite("\n",1,1,pfile);
			if(strlen(modelPath) > 0)
			{
				fprintf(pfile,"SVM model path:");
				fwrite(modelPath,strlen(modelPath),1,pfile);
				fwrite("\n",1,1,pfile);
			}
			fprintf(pfile,"--------------------------------------------------------\n");
			fprintf(pfile,"Incorrectly classified Images:\n");

		}
    do 
    {
        strcpy(path2,path); 
		
		IplImage* img = cvLoadImage(strcat(path2,fileFinder.name));
         if (img)
         {
             nImg++;
			 if(img->height != winSize.height || img->width != winSize.width)
			 {
				 if(dstImage == NULL)
					 dstImage = cvCreateImage(winSize,img->depth,img->nChannels);
				 cvResize(img,dstImage,1);
			 }
			 else
			 {
				 if(dstImage == NULL)
					 dstImage = cvCreateImage(winSize,img->depth,img->nChannels);
				 cvCopy(img,dstImage);
			 }
             result = predict(dstImage);
                
             if ((lb == POS && result > 0) ||
                 (lb == NEG && result <= 0))
			 {
				 nRight++;
				 //printf("image %d 
			 }
			 else
			 {
				 if(pfile){
				 fwrite(fileFinder.name,strlen(fileFinder.name),1,pfile);
				 fwrite("\n",1,1,pfile);}
			 }
			 if(result > 0)
				 pos ++;
			 else
				 neg ++;
			 printf("Pos = %d ; Neg = %d \r",pos,neg);
				 
			 cvReleaseImage(&img);
            
        }
        
    }while(_findnext(bFind,&fileFinder) == 0);
	if(dstImage)
		cvReleaseImage(&dstImage);
	printf("\n");
    accuracy = nRight * 1.0f / nImg;
	if(pfile)
	{
		fprintf(pfile,"--------------------------------------------------------\n");
		fprintf(pfile,"Pos = %d ; Neg = %d \n",pos,neg);
		fprintf(pfile,"Accuracy = %f\n",accuracy);
		fclose(pfile);
		printf("Predicting Recorder saved in %s\n",path3);
//		::ShellExecuteA(NULL,"open",path3,NULL,NULL,SW_SHOWNORMAL);
	}
   _findclose(bFind);
 
    return;
}

void HogSvmDetector::objectdetect(const Mat& img, vector<Rect>& foundLocations,	
	                        double hitThreshold , Size winStride ,
	                        Size padding, double scale,
	                        int groupThreshold )
{
    detectMultiScale(img,foundLocations,hitThreshold,winStride,padding,scale,groupThreshold);
}
