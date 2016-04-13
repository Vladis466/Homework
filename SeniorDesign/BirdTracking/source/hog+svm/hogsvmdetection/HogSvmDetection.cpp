// HogSvmDetection.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "stdlib.h"
#include <io.h>
#include "string.h"
#include "HogSvmDetectorTool.h"
#include "Windows.h"
#include <fstream>
using namespace cv;
using namespace std;

//to check if a file exisis
bool fexists(const char *filename)
{
	ifstream ifile(filename);
	return ifile.good();
}
//resize the image to specific size
void ResizeImage(char* imgPath,char* resizePath,int Width,int Height)
{
	char path[_MAX_PATH] = "";
	char path2[_MAX_PATH] = "";
	_finddata_t fileFinder;
	long bFind;	
	int filenum = 0;

	IplImage *dstImage = NULL;
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
			for(int j = i - 1; j >= 0 ;j--)
				path[j] = imgPath[j];
			path[i + 1] = '\0';
			break;
		}
	}
    do 
	{
		strcpy(path2,path); 
		strcat(path2,fileFinder.name);
		IplImage* img = cvLoadImage(path2,1);
		if (img && img->imageData)
		{
			if(dstImage == NULL)
				dstImage = cvCreateImage(cvSize(Width, Height), img->depth, img->nChannels);

			cvResize(img, dstImage, 1);

			strcpy(path2,resizePath); 			
			cvSaveImage(strcat(path2,fileFinder.name), dstImage);
			cvReleaseImage(&img);

			filenum++;

			printf("success save image %d\r",filenum);
		}
    }while(_findnext(bFind,&fileFinder) == 0);
	if(dstImage)
		cvReleaseImage(&dstImage);

}
void StatisticImageRatio(char* srcPath,int n)
{
	int* bins = new int[n];
	memset(bins,0,n * sizeof(int));
	double ratio = 2.0 / (double)n;

	char path[_MAX_PATH] = "";
	char path2[_MAX_PATH] = "";
	_finddata_t fileFinder;
	long bFind;	
	int filenum = 0;

	bFind = _findfirst(srcPath, &fileFinder);
	if (bFind == -1)
	{
		printf("no file found\n");
		return;
	}		

	for (int i = strlen(srcPath); i >=1; i--)
	{
		if(    srcPath[i] =='\\'
			&& srcPath[i-1] != '\\' 
			)
		{
			for(int j = i; j >= 0 ;j--)
				path[j] = srcPath[j];
			
			path[i + 1] = '\0';
			break;
		}
	}
    do 
	{
		strcpy(path2,path); 
		strcat(path2,fileFinder.name);
		IplImage* img = cvLoadImage(path2,1);
		if (img && img->imageData)
		{
			double r = (double)img->height/(double)img->width;
			int id = (int)((r - ratio) / ratio);
			if(id <0)
				id = 0;
			if(id >= n)
				id = n - 1;
			
			bins[id] ++;

			cvReleaseImage(&img);
		}
    }while(_findnext(bFind,&fileFinder) == 0);

	int max = bins[0];
	int index = 0;
	for(int i = 1; i < n; i ++)
	{
		if(bins[i] > max)
		{
			max = bins[i];
			index = i;
		}
	}
	printf("Max probability of Image size ratio is : %f\n",(double)(index +1) * ratio);
	delete[] bins;
}
void ShrinkImage(char* srcPath, char* dstPath,int offset,int thr1 = 32, int thr2 = 32)
{
	char path[_MAX_PATH] = "";
	char path2[_MAX_PATH] = "";
	_finddata_t fileFinder;
	long bFind;	
	int filenum = 0;

	bFind = _findfirst(srcPath, &fileFinder);
	if (!bFind)
	{
		printf("no file found\n");
		return;
	}		

	for (int i = strlen(srcPath); i >=1; i--)
	{
		if(    srcPath[i] =='\\'
			&& srcPath[i-1] == '\\' 
			)
		{
			for(int j = i - 1; j >= 0 ;j--)
				path[j] = srcPath[j];
			path[i + 1] = '\0';
			break;
		}
	}
    do 
	{
		strcpy(path2,path); 
		strcat(path2,fileFinder.name);
		IplImage *dstImage = NULL;
		IplImage* img = cvLoadImage(path2,1);
		if (img && img->imageData)
		{
			strcpy(path2,dstPath);
			strcat(path2,fileFinder.name);
			CvSize size;
			
			
			size.width= img->width - 2 * offset;
			size.height = img->height - 2 * offset;
			
			
			if(size.width < thr1 || size.height < thr2)
				continue;

			if(offset > 0)
			{
				CvRect rect;
				size.width= img->width - 2 * offset;
				size.height = img->height - 2 * offset;
				rect.x = offset;
				rect.y = offset;
				rect.width = size.width;
				rect.height = size.height;
				dstImage = cvCreateImage(size,img->depth,img->nChannels);
				//cvResize(img,dstImage);
				cvGetRectSubPix(img,dstImage,cvPoint2D32f(img->width / 2, img->height / 2));
				//cvGetSubRect(img,dstImage,rect);

				cvSaveImage(path2, dstImage);
				cvReleaseImage(&img);
				cvReleaseImage(&dstImage);
				filenum++;

				printf("success shrinked image %d\r",filenum);
			}
			else
			{
				cvSaveImage(path2, img);
				printf("success shrinked image %d\r",filenum);
				filenum ++;
			}
		}
    }while(_findnext(bFind,&fileFinder) == 0);
}
//print the help information
void help()
{
	printf("Usage: \n"
		"HogSvmDetection -h|-help\n"
		"HogSvmDetection -r|-resize <image_width> <image_height> <src_image_path> <dst_image_path>\n"
		"HogSvmDetection -s|-shrink <scr_image_path> <dst_imae_path> <boundary offset><width threshold><height threshold>\n"
		"HogSvmDetection -t|-train  <image_width> <image_height> <pos sample to neg sample ratio><pos_image_path> <neg_image_path> <classifier_path>\n"
		"HogSvmDetection -t|-train  <image_width> <image_height> <pos sample to neg sample ratio><block height><block width><block stride width><block stride hieght><cell width><cell height><bin number><pos_image_path> <neg_image_path> <classifier_path>\n"
		"HogSvmDetection -p|-predict <label> <image_path> <classifier_path>\n"
		"HogSvmDetection -d|-detect  <image_path> <classifier_path>\n");

	return;
}


int main(int argc, char* argv[])
{
  

#if 1
    HOGSvmDetetorTool hs;
    char operation[MAX_PATH] = "";
    char path1[MAX_PATH] = "";
    char path2[MAX_PATH] = "";
    char path3[MAX_PATH] = "";

    int nImg, nPos;
    float posRate;
    vector<Rect> found;

    if (argc == 1)
    {
        printf("No input argument specified aborting.\n\n");
        help();
        return 0;
    }

	strcpy(operation,argv[1]);

    if (!strcmp(operation, "-h") || !strcmp(operation, "-help"))
    {
        help();
        return 0;
    }
	else if (!strcmp(operation, "-r") || !strcmp(operation, "-resize"))
	{
		if(argc != 6)
		{
			printf("Incorrect number of input arguments.\n");
			printf("Please try -help for more information.\n");
			return 0;
		}
		int win_width = atoi(argv[2]);
		int win_height = atoi(argv[3]);
		ResizeImage(argv[4],argv[5],win_width,win_height);

	}
	else if (!strcmp(operation, "-s") || !strcmp(operation, "-shrink"))//
	{
		if(argc != 7)
		{
			printf("Incorrect number of input arguments.\n");
			printf("Please try -help for more information.\n");
			return 0;
		}
		int offset = atoi(argv[4]);
		int thr1 = atoi(argv[5]);
		int thr2 = atoi(argv[6]);
		ShrinkImage(argv[2],argv[3],offset,thr1,thr2);

	}
	else if (!strcmp(operation, "-m") || !strcmp(operation, "-measure"))//
	{
		if(argc != 4)
		{
			printf("Incorrect number of input arguments.\n");
			printf("Please try -help for more information.\n");
			return 0;
		}
		
		StatisticImageRatio(argv[2],atoi(argv[3]));

	}
    else if (!strcmp(operation, "-t") || !strcmp(operation, "-train"))// to train a svm model
    {

        if (argc == 8)
        {
            int win_width = atoi(argv[2]);
			int win_height = atoi(argv[3]);
			int npr = atoi(argv[4]);
			Size winsize;
			winsize.height = win_height;
			winsize.width = win_width;
			hs.create(winsize);
			hs.train(argv[5], argv[6],npr); 
			hs.saveDetector(argv[6]);
        }
		else if(argc == 15)
		{
			int win_width = atoi(argv[2]);
			int win_height = atoi(argv[3]);
			int npr = atoi(argv[4]);
			Size winsize,blocksize,blockstride,cellsize;
			int bin = 9;
			winsize.height = win_height;
			winsize.width = win_width;
			blocksize.width = atoi(argv[5]);
			blocksize.height = atoi(argv[6]);
			blockstride.width = atoi(argv[7]);
			blockstride.height = atoi(argv[8]);
			cellsize.width = atoi(argv[9]);
			cellsize.height = atoi(argv[10]);
			bin = atoi(argv[11]);
			if(winsize.area() <= 0 || blocksize.area() <= 0 || blockstride.area() <= 0 || cellsize.area() <= 0 || bin <= 0)
			{
				printf("Paraments error, Please check your input\n");
				return 0;
			}
			hs.create(winsize,blocksize,blockstride,cellsize,bin);
			hs.train(argv[12], argv[13],npr); 
			hs.saveDetector(argv[14]);
		}
		else
		{
			printf("Incorrect number of input arguments.\n");
            printf("Please try -help for more information.\n");
            return 0;

		}
		
    }
    else if (!strcmp(operation, "-p") || !strcmp(operation, "-predict"))//prediction task
    {
        if (argc != 5)
        {
            printf("Incorrect number of input arguments.\n");
            printf("Please try -help for more information.\n");
            return 0;
        }
		int	label =  atoi(argv[2]);
		Label lb;
		if(label == 1)
			 lb = POS;
		else
			 lb = NEG;

		hs.loadDetector(argv[4]);
		hs.predict(argv[3], lb, nImg, nPos, posRate);

        printf("Predict result: \n"
               "Image num: %d\n"
               "Correctly classified image num: %d;  percentage: %f%\n"
               "InCorrectly classified image num: %d;  percentage: %f%\n",
               nImg, nPos, 100*posRate, nImg-nPos, 100*(1-posRate));
    }
    else if (!strcmp(operation, "-d") || !strcmp(operation, "-detect"))//detection task
    {
        if (argc != 4)
        {
            printf("Incorrect number of input arguments.\n");
            printf("Please try -help for more information.\n");
            return 0;
        }
		LARGE_INTEGER ltime0, ltime1, ltimef; //Used for timing
		double inttime;
		QueryPerformanceFrequency(&ltimef);  

		Mat img = imread(argv[2]);
		if (!img.data)
		{
			printf("load image failed!\n");
			return 0;
		}

		hs.loadDetector(argv[3]);
		QueryPerformanceCounter(&ltime0);
        hs.objectdetect(img, found, 2.0, Size(8, 8), Size(0, 0), 1.05, 2);
		QueryPerformanceCounter(&ltime1); 
		inttime=(double)(ltime1.QuadPart - ltime0.QuadPart) / ltimef.QuadPart*1000;	
		printf("run time %lf s",inttime);
        for(unsigned int i = 0; i < found.size(); i++ )
        {
            Rect r = found[i];
            // the HOG detector returns slightly larger rectangles than the real objects.
            // so we slightly shrink the rectangles to get a nicer output.
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.07);
            r.height = cvRound(r.height*0.8);
            rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
        }

		for (int i = 0;;i ++)
		{ 
			sprintf(path3, "result%d.jpg", i);
			if (fexists(path3))
			{
				continue;
			}
			imwrite(path3, img);
			break;
		}
        cvWaitKey(0);
    }
    else
    {
        printf("Unkown input arguments. Please try -h|-help for more information.\n");
        return 0;
    }

#endif    

    
	return 0;
}

