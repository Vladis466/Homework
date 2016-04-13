#pragma once
	//////////////////////////////////////////////////////////////////////////
	//Class HOGHelper is used for auxiliary functions

#include "stdio.h"
#include "string.h"
#define _CAOSE_PIXEL_
#define _SIMD_
#define _LUT_
#define _FAST_LUT_
//#define _USE_FIX_POINT_



#define _INTRINSIC_
class HGDescriptor;
struct ImageInfo
{
	char* dataPtr;
	int colorChannel;
	int width;
	int height;
	int widthStep;
	ImageInfo()
	{
		memset(this,0,sizeof(ImageInfo));
	}
};
 struct Vector2D
 {
	 int x;
	 int y;
	 Vector2D()
	 {
		 x = 0;
		 y = 0;
	 }
	 Vector2D(int _x,int _y)
	 {
		 x = _x;
		 y = _y;
	 }
	 int Area()
	 {
		 return x * y;
	 }

 };
 struct RegionList 
 {
	 Vector2D location;
	 Vector2D size;
	 RegionList* next;
	 RegionList()
	 {
		 next = 0;
	 }
	 void Release()
	 {
		 ReleaseVector2DList(this);
	 }
	 static void ReleaseVector2DList(RegionList* list)
	 {
		 RegionList* pNext;
		 while(list)
		 {
			 pNext = list->next;
			 delete list;
			 list = pNext;
		 }
	 }
	 void AppendItemToVector2D(Vector2D pt,Vector2D _s = Vector2D())
	 {
		 RegionList* item = new RegionList();
		 item->location = pt;
		 item->size = _s;
		 RegionList* p = this;
		 while(p->next)
		 {
			 p = p->next;
		 }
		 p->next = item;
	 }
	 static void AppendItemToVector2DList(RegionList*& list,RegionList* item)
	 {
		 if(list == NULL)
		 {
			 list = item;
			 return;
		 }
		 RegionList* p = list;
		 while(p->next)
		 {
			 p = p->next;
		 }
		 p->next = item;

	 }
 };
 struct PixLutData
 {
#ifdef _USE_FIX_POINT_
	 int weight;
	 int histWeight[4];
#else
	 float weight;
	 float histWeight[4];
#endif
	 int offset;
	 int histOffset[4];
	 PixLutData()
	 {
		 memset(this,0,sizeof(PixLutData));
	 }
 };
	
 class HOGHelper
 {
#ifdef _CACHE_SCALE_IMAGE_INDEX_
 private:
	 int* scaleCacheIndex;
	 int scaleNum;
	 int* scaleOffset;
	 bool bConfiguredFlag;
 protected:
	 
 public:
	 HOGHelper();
	 void Release();
	 ~HOGHelper();
	 void Configure(int _w,int _h,double scale,int n);
	 int* GetIndexOffset(int n);
	 void ScaleImage(ImageInfo* scr,ImageInfo* dst,int n);
	 bool IsConfigured();
#endif
	
 public:
	 static ImageInfo* LoadCompatibleImage(const char* file);
	 static void ScaleImage(ImageInfo* scr,ImageInfo* dst);
 };
 class CacheHelper
 {
 public:
	 Vector2D nBlocks;
	 Vector2D nCaches;
	 int blockHistSize;
 private:
	 Vector2D winSize;
	 float* blockHistCache;//used for caching all possible block hog histogram of an image.
	 int cachecharSize;
	 HGDescriptor* m_pHogDescriptor;
	 PixLutData* pixelData;

	 int count1,count2,count4;

	 Vector2D cacheMaxImageSize;
#ifdef _PADDING_
	 Vector2D paddingSize;
#endif
	 Vector2D blockSize;
	 Vector2D cellSize;
	 Vector2D cacheStride;
	 int nBins;
 protected:

 public:
	 CacheHelper();
	 void Release();
	 virtual ~CacheHelper();
	 void Configure(HGDescriptor* _hog);
	 void GeneratePinxelInterpolateData();
	 //according to the original HOG in OpenCV, the init method is coupled with some redundant code that can be execute only once.
	 void UpdatePixelLutOffset(int w,int h);
	 void CacheImage(ImageInfo* imagePtr);
	 void CacheFullFeature(int w,int h);
	 void ComputeBlockHist(Vector2D pt,float* buf,int width,int h);
#ifdef _USE_FIX_POINT_
	void NormalizeBlockHistogram(int* hist);
#else
	 void NormalizeBlockHistogram(float* hist);
#endif
	 float* GetBlockHist(Vector2D pt);
	 Vector2D GetWindow(Vector2D imageSize,Vector2D _winStride,int index);
 };
	//////////////////////////////////////////////////////////////////////////
 class HGDescriptor
	{
		//Insert structure for cache utility
		friend class CacheHelper;
		
	public:
		
		//Basic class members
		Vector2D maxImageSize;
		Vector2D windowSize;
		Vector2D windowStride;
		Vector2D blockSize;
		Vector2D blockStride;
		Vector2D cellSize;
		Vector2D cacheStride;
		char* binLookUpTable;
		float* magnitudeLookUpTable;
		inline void LookUp(int dx,int dy,int& bin1,int& bin2,float& mag1,float& mag2);
		void GenerateLookUpTable();

		int binCount;
		double winSigma;
		//Buffer members

	private:
		//cache members
		CacheHelper cacheHelper;
		HOGHelper hogHelper;
		float lookUpTable[256];

		float* hyperPanelVector;

		float* magnitudePtr;

		char* anglePtr;
	protected:
		bool CheckConfigure();

		void GenerateGradientWorkCache();
		inline int BorderInterpolate(int index,int scale);
		inline void CartToPolar(float x,float y, float& m,float& a);
		inline void CartToPolar(float* x, float* y, float* m,float* a,int len);
	public:
		HGDescriptor();
		~HGDescriptor();
		bool Configure(Vector2D _imageSize,Vector2D _windowSize,Vector2D _windowsStride,Vector2D _blockSize,Vector2D _blockStride,Vector2D _cellSize,int _binCount);
		int GetDescriptorSize();
		Vector2D WindowsInImage(int,int);
		double GetWinSigma();
		void ComputerGradient(ImageInfo* imagePtr);
		void Compute(ImageInfo* imagePtr,float* descriptor);
		void Detect(ImageInfo* imagePtr,RegionList*& pList);
		void DetectMultiScale(ImageInfo* image, RegionList*& pList);
		void LoadHyperPanelVector();
	};
