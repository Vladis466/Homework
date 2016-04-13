#include "stdafx.h"
#include "math.h"
#include "Hog.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define PI 3.1415926535897932384626433832795
inline int min(int a,int b){return a > b ? b:a;}
inline float min(float a,float b){return a > b ? b : a;}
inline int round(double v)
{
	return (int)(v + 0.5);
}
inline static char GetImagePixel(char* ptr,int w,int h,int x,int y)
{

	return ptr[y * w + x];
}
inline static char GetInterpolateImagePixel(char* ptr, int w, int h,double x,double y)
{

	char* pt = ptr;
#ifdef _CAOSE_PIXEL_
	return GetImagePixel(ptr,w,h,round(x),round(y));
#else

#endif
}
ImageInfo* HOGHelper::LoadCompatibleImage(const char* file)
{
	return 0;
}
void HOGHelper::ScaleImage(ImageInfo* scr,ImageInfo* dst)
{

	double dx = (double)scr->width / (double)dst->width;
	double dy = (double)scr->height / (double)dst->height;
	int cn = dst->colorChannel;
	double xs = 0;
	double ys = 0;
	int x,y;
	if(cn == 1)
	{

		char* srcPtr = scr->dataPtr;
		char* dstPtr = dst->dataPtr;
		for( y = 0; y < dst->height;y ++)
		{
			xs = 0;

			for( x = 0; x < dst->width - 4; x += 4)
			{
				*dstPtr++ = GetInterpolateImagePixel(srcPtr,scr->width,scr->height,xs,ys);
				*dstPtr++ = GetInterpolateImagePixel(srcPtr,scr->width,scr->height,xs + dx,ys);
				*dstPtr++ = GetInterpolateImagePixel(srcPtr,scr->width,scr->height,xs + dx * 2,ys);
				*dstPtr++ = GetInterpolateImagePixel(srcPtr,scr->width,scr->height,xs + dx * 3,ys);
				xs += 4 * dx;
			}
			for(; x < dst->width; x ++)
			{
				*dstPtr++ = GetInterpolateImagePixel(srcPtr,scr->width,scr->height,xs,ys);
				xs += dx;
			}

			ys += dy;
		}
	}
	else
	{

	
		char* _ptr1 = scr->dataPtr;
		char* _ptr2 = _ptr1 + scr->width * scr->height;
		char* _ptr3 = _ptr2 + scr->width * scr->height;

		char* ptr1 = dst->dataPtr;
		char* ptr2 = ptr1 + dst->width * dst->height;
		char* ptr3 = ptr2 + dst->width * dst->height;
		int x,y;
		for(y = 0; y < dst->height;y ++)
		{
			xs = 0;
			

			for (x = 0; x < dst->width;x += 4)
			{
				*ptr1 = GetInterpolateImagePixel(_ptr1,scr->width,scr->height,xs,ys);
				*ptr2 = GetInterpolateImagePixel(_ptr2,scr->width,scr->height,xs,ys);
				*ptr3 = GetInterpolateImagePixel(_ptr3,scr->width,scr->height,xs,ys);

				*(ptr1 + 1) = GetInterpolateImagePixel(_ptr1,scr->width,scr->height,xs + dx,ys);
				*(ptr2 + 1) = GetInterpolateImagePixel(_ptr2,scr->width,scr->height,xs + dx,ys);
				*(ptr3 + 1) = GetInterpolateImagePixel(_ptr3,scr->width,scr->height,xs + dx,ys);

				*(ptr1 + 2) = GetInterpolateImagePixel(_ptr1,scr->width,scr->height,xs + 2 * dx,ys);
				*(ptr2 + 2) = GetInterpolateImagePixel(_ptr2,scr->width,scr->height,xs + 2 * dx,ys);
				*(ptr3 + 2) = GetInterpolateImagePixel(_ptr3,scr->width,scr->height,xs + 2 * dx,ys);

				*(ptr1 + 3) = GetInterpolateImagePixel(_ptr1,scr->width,scr->height,xs + 3 * dx,ys);
				*(ptr2 + 3) = GetInterpolateImagePixel(_ptr2,scr->width,scr->height,xs + 3 * dx,ys);
				*(ptr3 + 3) = GetInterpolateImagePixel(_ptr3,scr->width,scr->height,xs + 3 * dx,ys);


				xs += 4 * dx;
				ptr1 += 4;
				ptr2 += 4;
				ptr3 += 4;
			}
			for (; x < dst->width;x ++)
			{
				*ptr1 = GetInterpolateImagePixel(_ptr1,scr->width,scr->height,xs,ys);
				*ptr2 = GetInterpolateImagePixel(_ptr2,scr->width,scr->height,xs,ys);
				*ptr3 = GetInterpolateImagePixel(_ptr3,scr->width,scr->height,xs,ys);
				xs += dx;
				ptr1 ++;
				ptr2 ++;
				ptr3 ++;
			}

		
			ys += dy;
		}
	}

	
}
#ifdef _CACHE_SCALE_IMAGE_INDEX_
 
	 HOGHelper::HOGHelper()
	 {
		 scaleCacheIndex = 0;
		 scaleNum = 0;
		 scaleOffset = 0;
		 bConfiguredFlag = false;
	 }
	 void HOGHelper::Release()
	 {
		 if(scaleCacheIndex)
		 {
			 delete[] scaleCacheIndex;
			 scaleCacheIndex = 0;
		 }
		 if(scaleOffset)
		 {
			 delete[] scaleOffset;
			 scaleOffset = 0;
		 }
	 }
	 HOGHelper::~HOGHelper()
	 {
		 Release();
	 }
	 void HOGHelper::Configure(int _w,int _h,double scale,int n)
	 {
		 double s = 1.0;
		 int w = 0;
		 int h = 0;
		 scaleOffset = new int[n];
		 int offset = 0;
		 scaleNum = n;
		 for(int i = 0; i < n; i ++)
		 {
			 scaleOffset[i] = offset;
			 w = (int)((double)_w / s);
			 h = (int)((double)_h / s);
			 offset += w * h;
			 s *= scale;
		 }
		 scaleCacheIndex = new int[offset];
		 int index = 0;
		 double xs = 0;
		 double ys = 0;
		 int x,y;
		 double dx;
		 double dy;
		 s = 1.0;
		 for (int i = 0; i < n; i ++)
		 {
			 w = (int)((double)_w / s);
			 h = (int)((double)_h / s);
			 dx = (double)_w / (double)w;
			 dy = (double)_h / (double)h;
			 ys = 0;
			 s *= scale;
			 for(int j = 0; j < h ; j ++)
			 {
				 xs = 0;
				 y = (int)ys;
				 for(int k = 0; k < w; k ++)
				 {
					 x = (int)xs;
					 scaleCacheIndex[index ++] = y * _w + x;
					 xs += dx;
				 }
				 ys += dy;
			 }
			 
		 }
	 }
	 int* HOGHelper::GetIndexOffset(int n)
	 {
		 return scaleCacheIndex + scaleOffset[n];
	 }
	 void HOGHelper::ScaleImage(ImageInfo* scr,ImageInfo* dst,int n)
	 {
		 int len = dst->width * dst->height;
		 int* index =scaleCacheIndex + scaleOffset[n];
		
		 int i;
		 for(i = 0; i < len - 4; i += 4)
		 {
			 dst->dataPtr[i] = scr->dataPtr[index[i]];

			 dst->dataPtr[i + 1] = scr->dataPtr[index[i + 1]];

			 dst->dataPtr[i + 2] = scr->dataPtr[index[i + 2]];

			 dst->dataPtr[i + 3] = scr->dataPtr[index[i + 3]];
		 }
		 for(;i < len;i ++)
			 dst->dataPtr[i] = scr->dataPtr[index[i]];
	 }
	 bool HOGHelper::IsConfigured()
	 {
		 return bConfiguredFlag;
	 }
#endif
inline bool IsSimilarRegion(RegionList* r1,RegionList* r2)
{
	static float eps = 0.1f;
	
	int delta = 0;//eps * (min(r1->size.x,r2->size.x)) + (min(r1->size.y,r2->size.y));
	delta += min(r1->size.x,r2->size.x);
	delta += min(r1->size.y,r2->size.y);
	delta /= 10;
	delta +=2;

	return ((abs(r1->location.x - r2->location.x) < delta) && (abs(r1->location.y - r2->location.y) < delta) && (abs(r1->size.x - r2->size.x)< delta ) && (abs(r1->size.y - r2->size.y) < delta));

}
inline bool IsReg1InReg2(RegionList* r1,RegionList* r2)
{
	if(r1->location.x < r2->location.x)
		return false;
	if(r1->location.y < r2->location.y)
		return false;
	if(r1->location.x + r1->size.x > r2->location.x + r2->size.x)
		return false;
	if(r1->location.y + r1->size.y > r2->location.y + r2->size.y)
		return false;
	return true;
}
int LabeRegion(RegionList* list,int* label,int n)
{
	int i, j, N = n;
	RegionList* p1 = list;
	RegionList* p2 = list;

	const int PARENT=0;
	const int RANK=1;

	int* _nodes = new int[2 * n];
	int (*nodes)[2] = (int(*)[2])&_nodes[0];

	// The first O(N) pass: create N single-vertex trees
	for(i = 0; i < N; i++)
	{
		nodes[i][PARENT]=-1;
		nodes[i][RANK] = 0;
	}

	// The main O(N^2) pass: merge connected components
	for( i = 0; i < N; i++ )
	{
		int root = i;

		// find root
		while( nodes[root][PARENT] >= 0 )
			root = nodes[root][PARENT];
		p2 = list;
		for( j = 0; j < N; j++ )
		{
			if( i == j || !IsSimilarRegion(p1,p2))
			{
				p2 = p2->next;
				continue;
			}
			int root2 = j;

			while( nodes[root2][PARENT] >= 0 )
				root2 = nodes[root2][PARENT];

			if( root2 != root )
			{
				// unite both trees
				int rank = nodes[root][RANK], rank2 = nodes[root2][RANK];
				if( rank > rank2 )
					nodes[root2][PARENT] = root;
				else
				{
					nodes[root][PARENT] = root2;
					nodes[root2][RANK] += rank == rank2;
					root = root2;
				}
				//assert( nodes[root][PARENT] < 0 );

				int k = j, parent;

				// compress the path from node2 to root
				while( (parent = nodes[k][PARENT]) >= 0 )
				{
					nodes[k][PARENT] = root;
					k = parent;
				}

				// compress the path from node to root
				k = i;
				while( (parent = nodes[k][PARENT]) >= 0 )
				{
					nodes[k][PARENT] = root;
					k = parent;
				}
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	int nclasses = 0;

	for( i = 0; i < N; i++ )
	{
		int root = i;
		while( nodes[root][PARENT] >= 0 )
			root = nodes[root][PARENT];
		if( nodes[root][RANK] >= 0 )
			nodes[root][RANK] = ~nclasses++;
		label[i] = ~nodes[root][RANK];
	}
	delete[] _nodes;
	return nclasses;
	
}
void GroupRectangles(RegionList*& list)
{
	if(list == 0)
		return;
	int n = 0;
	RegionList* p = list;
	while(p)
	{
		n ++;
		p = p->next;
	}
	int* label  = new int[n];
	int m = LabeRegion(list,label,n);
	RegionList* regs = new RegionList[m];
	int* weight = new int[m];
	for(int i = 0; i < m ; i ++)
		weight[i] = 0;
	p = list;
	int id = 0;
	for(int i = 0; i < n; i ++)
	{
		id = label[i];
		regs[id].location.x += p->location.x;
		regs[id].location.y += p->location.y;
		regs[id].size.x += p->size.x;
		regs[id].size.y += p->size.y;
		weight[id] ++;
		p = p->next;
	}
	p = list;
	for(int i = 0; i < m ; i ++)
	{
		regs[i].location.x /= weight[i];
		regs[i].location.y /= weight[i];
		regs[i].size.x /= weight[i];
		regs[i].size.y /=weight[i];
		regs[i].next =p->next;
		*p = regs[i];
		if(i < m - 1)
			p = p->next;
		else
		{
			p->next->Release();
			p->next = 0;
		}
	}
	p = list;
	RegionList* p1 = list;
	for(int i = 0; i < m; i ++)
	{
		p1 = list;
		weight[i] = 1;
		for(int j = 0; j < m ; j ++)
		{
			if(i != j)
			{
				if(IsReg1InReg2(p,p1))
				{
					weight[i] = 0;
					break;
				}
			}
			p1 = p1->next;
		}
		p = p->next;
	}
	p = list;
	p1 = list;
	for(int i = 0; i < m ; i ++)
	{
		if(weight[i] == 0)
		{
			if(p == list)
			{
				list = p->next;
				p->next = 0;
				p->Release();
				p = list;
				p1 = p;
			}
			else
			{
				p1->next = p->next;
				p->next = 0;
				p->Release();
				p = p1->next;
			}
			continue;;
		}
		p1 = p;
		p = p->next;
	}
	p = list;
	
	delete[]regs;
	delete[] weight;
}
inline int AlignSize(int sz,int n)
{
	for(int i = 0; i < n; i ++)
	{
		if(sz % n == 0)
			break;
		sz ++;
	}
	return sz;
}
inline int GreatCommonDivisor(int a,int b)
{
	int c = 0;
	if(a < b)
	{
		c = a;
		a = b;
		b = c;
	}
	while(b > 0)
	{
		c  = a % b;
		a = b;
		b = c;
	}
	return a;
}
	//////////////////////////////////////////////////////////////////////////
	CacheHelper::CacheHelper()
	{
		m_pHogDescriptor = 0;
		blockHistCache = 0;
		blockHistSize = 0;
		pixelData = 0;
		count1 = count2 = count4 = 0;
		cachecharSize = 0;
	}
	void CacheHelper::Release()
	{
		if(blockHistCache)
		{
			delete[] blockHistCache;
			blockHistCache = 0;
		}
				
		if(pixelData)
		{
			delete[] pixelData;
			pixelData = 0;
		}
	}
	CacheHelper::~CacheHelper()
	{
		Release();
	}
	void CacheHelper::Configure(HGDescriptor* _hog)
	{
		m_pHogDescriptor = _hog;
		winSize = _hog->windowSize;

		blockSize = _hog->blockSize;
		cacheStride = _hog->cacheStride;
		cellSize = _hog->cellSize;
		nBins = _hog->binCount;
		blockHistSize = ((blockSize.x /cellSize.x) * (blockSize.y / cellSize.y)) * nBins;
		nBlocks.x = (winSize.x - blockSize.x) / _hog->blockStride.x + 1;
		nBlocks.y = (winSize.y - blockSize.y) / _hog->blockStride.y + 1;
				
		count1 = cellSize.Area();
		count2 = cellSize.x * (blockSize.y - cellSize.y)  + cellSize.y * (blockSize.x - cellSize.x);
		count4 = blockSize.Area() - count2 - count1;
		GeneratePinxelInterpolateData();
	}
	void CacheHelper::GeneratePinxelInterpolateData()
	{
		if(pixelData == 0)
		{
			pixelData = new PixLutData[blockSize.Area()];
		}
				
		float sigma = (float)m_pHogDescriptor->GetWinSigma();
		float scale = 1.f / (sigma * sigma * 2);
		Vector2D ncells = Vector2D(blockSize.x / cellSize.x,blockSize.y / cellSize.y);
		float cellX = 0;
		float cellY = 0;
		int icellX0 = 0;
		int icellY0 = 0;
		int icellX1 = 0;
		int icellY1 = 0;

		float t0 = 0;
		float t1 = 0;
		float t2 = 0;

		int c1 = 0;
		int c2 = 0;
		int c4 = 0;

		PixLutData* pData1 = pixelData;
		PixLutData* pData2 = pixelData + count1;
		PixLutData* pData4 = pData2 + count2;
		PixLutData pDtata;


		for(int j = 0; j < blockSize.x; j ++)
		{
			for(int i = 0; i < blockSize.y;i ++)
			{
				cellY = (i + 0.5f) / cellSize.y - 0.5f;
				icellY0 = floor(cellY);
				icellY1 = icellY0 + 1;
				cellY -= icellY0;

				cellX = (j + 0.5f) / cellSize.x - 0.5f;
				icellX0 = floor(cellX);
				icellX1 = icellX0 + 1;
				cellX -= icellX0;

				//pDtata.offset = (paddingSize.x * i + j ) * 2;--this should be update according to new image size;
				float di = i - blockSize.y * 0.5f;
				float dj = j - blockSize.x * 0.5f;

				pDtata.weight = exp(-(di * di + dj * dj) * scale);
				if( (unsigned)icellX0 < (unsigned)ncells.x &&
					(unsigned)icellX1 < (unsigned)ncells.x )
				{
					if ((unsigned)icellY0 < (unsigned)ncells.y &&
						(unsigned)icellY1 < (unsigned)ncells.y)
					{

						//??????????????????Data arrange in vertical type?????????????
						pDtata.histOffset[3] = (icellX1 * ncells.y + icellY1) * nBins;
						t0 = cellX * cellY;
						pDtata.histWeight[3] = t0;

						pDtata.histOffset[2] = (icellX0 * ncells.y + icellY1) * nBins;
						pDtata.histWeight[2] = cellY - t0;

						pDtata.histOffset[1] = (icellX1 * ncells.y + icellY0) * nBins;
						t1 = cellX - t0;
						pDtata.histWeight[1] = t1;

						pDtata.histOffset[0] = (icellX0 * ncells.y + icellY0) * nBins;
						pDtata.histWeight[0] = 1.f - cellY - t1;

						pData4[c4 ++] = pDtata;
					}
					else
					{
						if((unsigned) icellY0 < (unsigned)ncells.y)
						{
							icellY1 = icellY0;
							cellY = 1.f - cellY;
						}
						pDtata.histOffset[1] = (icellX1 * ncells.y + icellY1) * nBins;
						t0 = cellX * cellY;
						pDtata.histWeight[1] = t0;

						pDtata.histOffset[0] = (icellX0 * ncells.y + icellY1) * nBins;
						pDtata.histWeight[0] = cellY - t0;
						pData2[c2 ++] = pDtata;
					}
				}
				else
				{
					if ((unsigned)icellX0 < (unsigned)ncells.x)
					{
						icellX1 = icellX0;
						cellX = 1.f - cellX;
					}
					if ((unsigned)icellY0 < (unsigned)ncells.y &&
						(unsigned)icellY1 < (unsigned)ncells.y)
					{
						pDtata.histOffset[1] = (icellX1 * ncells.y + icellY1) * nBins;
						t0 = cellX * cellY;
						pDtata.histWeight[1] = t0;

						pDtata.histOffset[0] = (icellX1 * ncells.y + icellY0) * nBins;
						pDtata.histWeight[0] = cellX - t0;
						pData2[c2 ++] = pDtata;
					}
					else
					{
						if ((unsigned)icellY0 < (unsigned)ncells.y)
						{
							icellY1 = icellY0;
							cellY = 1.f - cellY;
						}
						pDtata.histOffset[0] = (icellX1 * ncells.y + icellY1) * nBins;
						pDtata.histWeight[0] = cellX * cellY;
						pData1[c1 ++] = pDtata;
					}

				}

			}
		}

	}
	//according to the original HOG in OpenCV, the init method is coupled with some redundant code that can be execute only once.
	void CacheHelper::UpdatePixelLutOffset(int w,int h)
	{


		int index = 0;
		int index2 = 0;
		int index4 = 0;
		int i,j;
		int cx = cellSize.x / 2;
		int cy = cellSize.y / 2;
		//for count1 type pixels
		PixLutData* pData2 = pixelData + count1;
		PixLutData* pData4 = pData2 + count2;
		for( j = 0; j < cx ; j ++)
		{
			for ( i = 0; i < cy; i ++)
			{
				pixelData[index ++].offset = (i * w + j) * 2;
			}
			for( i = blockSize.y - cy; i < blockSize.y; i ++)
			{
				pixelData[index ++].offset = (i * w + j) * 2;
			}
			for( i = cy; i < blockSize.y - cy; i ++)
			{
				pData2[index2 ++].offset = (i * w + j) * 2;
			}
		}
		for( j = cx; j < blockSize.x - cx; j ++)
		{
			for ( i = 0; i < cy; i ++)
			{
				pData2[index2 ++].offset = (i * w + j) * 2;
			}
			for( i = blockSize.y - cy; i < blockSize.y; i ++)
			{
				pData2[index2 ++].offset = (i * w + j) * 2;
			}
			for( i = cy; i < blockSize.y - cy; i ++)
			{
				pData4[index4 ++].offset = (i * w + j) * 2;
			}
		}
		for ( j = blockSize.x - cx; j < blockSize.x; j ++)
		{
			for ( i = 0; i < cy; i ++)
			{
				pixelData[index ++].offset = (i * w + j) * 2;
			}
			for( i = blockSize.y - cy; i < blockSize.y; i ++)
			{
				pixelData[index ++].offset = (i * w + j) * 2;
			}
			for( i = cy; i < blockSize.y - cy; i ++)
			{
				pData2[index2 ++].offset = (i * w + j) * 2;
			}
		}


		
	}
	void CacheHelper::CacheImage(ImageInfo* imagePtr)
	{

		int paddedWidth = imagePtr->width;
		int paddedHeight = imagePtr->height;

		int cachedWidth = (paddedWidth - blockSize.x) / cacheStride.x + 1;
		int cachedHeight = (paddedHeight - blockSize.y) / cacheStride.y + 1;
		if(blockHistCache == 0)
		{
			blockHistCache = new float[cachedHeight * cachedWidth * blockHistSize];
			//pixelData = new PixLutData[blockSize.Area()];
			cacheMaxImageSize.x = paddedWidth;
			cacheMaxImageSize.y = paddedHeight;
		}
		else
		{
			if(paddedWidth > cacheMaxImageSize.x || paddedHeight > cacheMaxImageSize.y)
			{
				cacheMaxImageSize.x = paddedWidth;
				cacheMaxImageSize.y = paddedHeight;
				Release();
				blockHistCache = new float[cachedHeight * cachedWidth * blockHistSize];
				//pixelData = new PixLutData[blockSize.Area()];
			}

		}
		UpdatePixelLutOffset(paddedWidth,paddedHeight);
		//m_pHogDescriptor->UpdateInterpolateIndexCache(Vector2D(paddedWidth,paddedHeight));
		m_pHogDescriptor->ComputerGradient(imagePtr);

		CacheFullFeature(paddedWidth,paddedHeight);
	}
	void CacheHelper::CacheFullFeature(int w,int h)
	{
		float* cache = blockHistCache;
		nCaches = Vector2D((w - blockSize.x) / cacheStride.x + 1,(h - blockSize.y)/ cacheStride.y + 1);
		Vector2D pt;
		for(int i = 0; i < nCaches.y; i ++)
		{
			
			pt.x = 0;
			for(int j = 0; j < nCaches.x; j ++)
			{
				ComputeBlockHist(pt,cache,w,h);
				pt.x += cacheStride.x;
				cache += blockHistSize;
			}
			pt.y += cacheStride.y;
		}
	}
	void CacheHelper::ComputeBlockHist(Vector2D pt,float* buf,int width,int h)
	{

		float* gradPtr = m_pHogDescriptor->magnitudePtr + (width * pt.y + pt.x) * 2;
		char* angPtr = m_pHogDescriptor->anglePtr + (width * pt.y + pt.x) * 2;
		int i;
		for(i = 0; i < blockHistSize - 4;i ++)
		{
			buf[i] = 0.f;
			buf[i + 1] = 0;
			buf[i + 2] = 0;
			buf[i + 3] = 0;
		}
		for(;i < blockHistSize;i ++)
			buf[i] = 0;


		float* grad;
		float g0,g1;
		int k = 0;
		char* ang;
		int a0,a1;
		float* hist;
		PixLutData pData;
		float w;

		for(k = 0; k < count1; k ++)
		{
			pData = pixelData[k];
			grad = gradPtr + pData.offset;
			g0 = grad[0];
			g1 = grad[1];
			ang = angPtr + pData.offset;
			a0 = ang[0];
			a1 = ang[1];
			hist = buf + pData.histOffset[0];
			w = pData.histWeight[0];
			hist[a0] = hist[a0] +g0 ;//* w;
			hist[a1] = hist[a1] +g1;// * w;
		}
		int c = count1 + count2;
		for(;k < c; k ++)
		{
			pData = pixelData[k];
			grad = gradPtr + pData.offset;
			g0 = grad[0];
			g1 = grad[1];
			ang = angPtr + pData.offset;
			a0 = ang[0];
			a1 = ang[1];

			hist = buf + pData.histOffset[0];
			w =pData.histWeight[0];
			hist[a0] += g0;// * w;
			hist[a1] += g1;// * w;

			hist = buf + pData.histOffset[1];
			w =pData.histWeight[1];
			hist[a0] += g0;// * w;
			hist[a1] += g1;// * w;


		}

		c += count4;

		for (; k < c; k ++)
		{
			pData = pixelData[k];
			grad = gradPtr + pData.offset;
			g0 = grad[0];
			g1 = grad[1];
			ang = angPtr + pData.offset;
			a0 = ang[0];
			a1 = ang[1];

			hist = buf + pData.histOffset[0];
			//w = pData.histWeight[0];
			hist[a0] += g0;// * w;
			hist[a1] += g1;// * w;

			hist = buf + pData.histOffset[1];
			w = pData.histWeight[1];
			hist[a0] += g0;// * w;
			hist[a1] += g1;// * w;

			hist = buf + pData.histOffset[2];
			w =pData.histWeight[2];
			hist[a0] += g0;// * w;
			hist[a1] += g1;// * w;

			hist = buf + pData.histOffset[3];
			w = pData.histWeight[3];
			hist[a0] += g0;// * w;
			hist[a1] += g1;// * w;
		}

		NormalizeBlockHistogram(buf);

		
	}

	void CacheHelper::NormalizeBlockHistogram(float* hist)
	{

		float sum = 0;
		float t;
		float t0,t1,t2,t3;
		int i;
		for(i = 0; i < blockHistSize - 4;i += 4)
		{
			t0 = hist[i];
			t1 = hist[i +1];
			t2 = hist[i +2];
			t3 = hist[i +3];
			sum += t0 * t0 + t1 * t1 + t2 * t2 + t3 * t3;
		}
		for(;i < blockHistSize; i ++)
		{
			t = hist[i];
			sum += t * t;
		}
		float scale = 1.f / (sqrt(sum + blockHistSize * 0.1f));
		static float thresh = 0.2;
		sum = 0;
		for(i = 0; i < blockHistSize - 4;i += 4)
		{
			hist[i] = min(hist[i] * scale,thresh);
			hist[i + 1] = min(hist[i + 1] * scale,thresh);
			hist[i + 2] = min(hist[i + 2] * scale,thresh);
			hist[i + 3] = min(hist[i + 3] * scale,thresh);
			
			sum += hist[i] * hist[i] + hist[i + 1] * hist[i + 1] +hist[i + 2] * hist[i + 2] +hist[i + 3] * hist[i + 3];
		}
		for(; i < blockHistSize; i ++)
		{
			hist[i] = min(hist[i] * scale,thresh);
			sum += hist[i] * hist[i];
		}


		scale = 1.f / (sqrt(sum) + 1e-3f);

		for(i = 0; i < blockHistSize - 4; i += 4)
		{
			hist[i] *= scale;
			hist[i + 1] *= scale;
			hist[i + 2] *= scale;
			hist[i + 3] *= scale;
		}
		for(; i < blockHistSize; i ++)
		{
			hist[i] *= scale;
		}

		
	}

	float* CacheHelper::GetBlockHist(Vector2D pt)// Cache offset should be consistent with the caching arrangement of feature response
	{
		if(pt.x % cacheStride.x != 0 || pt.y % cacheStride.y != 0)
			return 0;
		int x = pt.x / cacheStride.x;
		int y = pt.y / cacheStride.y;

		return blockHistCache + (y * nCaches.x + x) * blockHistSize;
	}
	Vector2D CacheHelper::GetWindow(Vector2D imageSize,Vector2D _winStride,int index)
	{
		int winX = (imageSize.x - winSize.x) / _winStride.x + 1;
		int y = index / winX;
		int x = index - y * winX;
		return Vector2D(x * _winStride.x,y * _winStride.y);
	}
	bool  HGDescriptor::CheckConfigure()
	{

		return true;
	}

	void HGDescriptor::GenerateGradientWorkCache()
	{
		
		if(magnitudePtr)
		{
			delete[] magnitudePtr;
			magnitudePtr = 0;
		}
		if(anglePtr)
		{
			delete[] anglePtr;
			anglePtr = 0;

		}

		int len = maxImageSize.x  * maxImageSize.y  * 2;


		magnitudePtr = new float[len];

		anglePtr = new char[len];
	}
	int HGDescriptor::BorderInterpolate(int index,int scale)
	{
		if(index < 0)
			return -(index );
		if(index >= scale)
			return scale - 2 - (index - scale  );
		return index;
	}
	void HGDescriptor::CartToPolar(float x,float y, float& m,float& a)
	{
		static float PI2 = 6.283185307179586476925286766559;
		static double scale = 0.01745329251994329576923690768489;
		static float maxM = 0;
		static float minM = 99999999.0f;
		m = (x * x + y * y);
		m = sqrt(m);
		a = atan2l((long double)y,(long double)x);//fastAtan2(y,x);//
		if(a < 0)
			a += PI2;
	}
	void HGDescriptor::CartToPolar(float* x, float* y, float* m,float* a,int len)
	{
		for(int i = 0; i < len; i ++)
		{
			CartToPolar(x[i],y[i],m[i],a[i]);
		}
	}
	HGDescriptor::HGDescriptor()
	{
		for(int i = 0; i < 256; i ++)
			lookUpTable[i] = (float)i;//lookUpTable[i] = sqrt((float)i);


		binLookUpTable = 0;
		magnitudeLookUpTable = 0;

		magnitudePtr = 0;
		anglePtr = 0;
		hyperPanelVector = 0;
	}
	HGDescriptor::~HGDescriptor()
	{

		if(hyperPanelVector)
		{
			delete[] hyperPanelVector;
			hyperPanelVector = 0;
		}
		
		if(magnitudePtr)
		{
			delete[] magnitudePtr;
			magnitudePtr = 0;
		}
		if(anglePtr)
		{
			delete[] anglePtr;
			anglePtr = 0;
		}

		if(binLookUpTable)
		{
			delete[] binLookUpTable;
			binLookUpTable = 0;
		}
		if(magnitudeLookUpTable)
		{
			delete[] magnitudeLookUpTable;
			magnitudeLookUpTable = 0;
		}

	}

	void HGDescriptor::GenerateLookUpTable()
	{
#ifdef _FAST_LUT_
		binLookUpTable = new char[511 * 512 * 2];
		magnitudeLookUpTable = new float[511 * 512 * 2];
		int index = 0;
		float Mag,Ang;
		int hidx;
		float t0;
		float angleScale = (float)(binCount / PI);
		for (int y = -255; y < 256; y ++)
		{
			for(int x = -255; x < 256; x ++)
			{
				CartToPolar(x,y,Mag,Ang);

				Ang *= angleScale;
				Ang -= 0.5f;
				hidx = floor(Ang);
				Ang -= hidx;
				if(hidx < 0)
					hidx += binCount;
				else if(hidx >= binCount)
					hidx -= binCount;

				index = (((y + 255) << 9) | (x + 255)) << 1;
				
				binLookUpTable[index] = hidx;
				t0 = Mag * Ang;
				magnitudeLookUpTable[index] = Mag - t0;

				hidx ++;
				if(hidx >= binCount)
					hidx = 0;
				binLookUpTable[index + 1] = hidx;
				magnitudeLookUpTable[index + 1] = t0;
			}
		}
#else
		binLookUpTable = new char[511 * 511 * 2];
		magnitudeLookUpTable = new float[511 * 511 * 2];
		int index = 0;
		float Mag,Ang;
		int hidx;
		float t0;
		float angleScale = (float)(binCount / PI);
		for (int y = -255; y < 256; y ++)
		{
			for(int x = -255; x < 256; x ++)
			{
				CartToPolar(x,y,Mag,Ang);

				Ang *= angleScale;
				Ang -= 0.5f;
				hidx = floor(Ang);
				Ang -= hidx;
				if(hidx < 0)
					hidx += binCount;
				else if(hidx >= binCount)
					hidx -= binCount;



				binLookUpTable[index] = hidx;
				t0 = Mag * Ang;
				magnitudeLookUpTable[index] = Mag - t0;

				hidx ++;
				if(hidx >= binCount)
					hidx = 0;
				binLookUpTable[index + 1] = hidx;
				magnitudeLookUpTable[index + 1] = t0;
				index += 2;
			}
		}
#endif
	}
	void HGDescriptor::LookUp(int dx,int dy,int& bin1,int& bin2,float& mag1,float& mag2)
	{
#ifdef _FAST_LUT_
		int index = (((dy + 255) << 9) | (dx + 255)) << 1;
		bin1 = binLookUpTable[index];
		bin2 = binLookUpTable[index + 1];
		mag1 = magnitudeLookUpTable[index];
		mag2 = magnitudeLookUpTable[index + 1];
#else
		int index = ((dy + 255) * 511 + (dx + 255)) * 2;
		bin1 = binLookUpTable[index];
		bin2 = binLookUpTable[index + 1];
		mag1 = magnitudeLookUpTable[index];
		mag2 = magnitudeLookUpTable[index + 1];
#endif
	}

	bool HGDescriptor::Configure(Vector2D _imageSize,Vector2D _windowSize,Vector2D _windowsStride,Vector2D _blockSize,Vector2D _blockStride,Vector2D _cellSize,int _binCount)
	{
		maxImageSize = _imageSize;
		windowSize = _windowSize;
		windowStride = _windowsStride;
		blockSize = _blockSize;
		blockStride = _blockStride;
		cellSize = _cellSize;
		binCount = _binCount;

		cacheStride.x = GreatCommonDivisor(windowStride.x,blockStride.x);
		cacheStride.y = GreatCommonDivisor(windowStride.y,blockStride.y);

		if(!CheckConfigure())
			return false;
		//GenerateInterpolateIndexCache(); //----this function should be call for each scale of image;
		GenerateGradientWorkCache();
		GenerateLookUpTable();
		cacheHelper.Configure(this);//init the cacheHelper for cache context index generation
#ifdef _CACHE_SCALE_IMAGE_INDEX_
		hogHelper.Configure(320,240,1.05,38);
#endif
		return true;
	}
	int HGDescriptor::GetDescriptorSize()
	{
		int size = (blockSize.x / cellSize.x) * (blockSize.y / cellSize.y) * ((windowSize.x - blockSize.x)/ blockStride.x + 1) * ((windowSize.y - blockSize.y) / blockStride.y + 1) * binCount;
		return size;
	}
	Vector2D HGDescriptor::WindowsInImage(int w, int h)
	{

		return Vector2D((w  - windowSize.x) / windowStride.x + 1,(h  - windowSize.y) / windowStride.y + 1);

	}
	double HGDescriptor::GetWinSigma()
	{
		return winSigma >= 0 ? winSigma : (blockSize.x + blockSize.y)/8.;
	}
	void HGDescriptor::ComputerGradient(ImageInfo* imagePtr)
	{

		int _paddedImageWidth = imagePtr->width ;
		int _paddedImageHeight = imagePtr->height;
		int x2,x3,y1,y2;

		int cn = imagePtr->colorChannel;
		int step = imagePtr->width;

		int index = 0;
		int x1 = 0;
		int dX,dY;
		float angleScale = (float)(binCount / PI);
		int hidx;
		float t0;
		short* binPtr = (short*)anglePtr;
		double* magPtr = (double*)magnitudePtr;
		if(cn == 1)
		{
			char* prevPtr = 0;
			char* nextPtr = 0;
			char* currPtr = 0;
			for (int y = 0; y < _paddedImageHeight;y ++)
			{
				y1 = y - 1;
				y2 = y + 1; 
				y1 = y1 - y1 * ( y1 < 0);
				//y2 = y2 * (y2 < _paddedImageHeight) + (_paddedImageHeight - 2) * (y2 >= _paddedImageHeight);//y2 - ((y2 >= _paddedImageHeight) * 2);//
				y2 = y2 - ((y2 >= _paddedImageHeight) * 2);//

				currPtr = imagePtr->dataPtr + step * y;
				prevPtr = imagePtr->dataPtr + step * y1;
				nextPtr = imagePtr->dataPtr + step * y2;


				for(int x = 0; x < _paddedImageWidth; x ++)
				{

					x1 = x;
					x2 = x + 1; 
					x3 = x - 1; 
					x2 =x2 - ((x2 >= _paddedImageWidth) * 2);// x2 * (x2 < _paddedImageWidth) + (_paddedImageWidth - 2) * (x2 >= _paddedImageWidth);// 
					x3 = x3 - x3 * (x3 < 0);
					dX = currPtr[x2] - currPtr[x3];
					dY = nextPtr[x1] - prevPtr[x1];
#ifdef _INTRINSIC_
					index = (((dY + 255) << 9) | (dX + 255)) << 1;
					*binPtr = *((short*)(binLookUpTable + index));
					*magPtr = *((double*)(magnitudeLookUpTable + index));
					binPtr++;
					magPtr++;
#else
					int b1,b2;
					float m1,m2;
					LookUp(dX,dY,b1,b2,m1,m2);
					anglePtr[index] = b1;
					anglePtr[index + 1] = b2;
					magnitudePtr[index] = m1;
					magnitudePtr[index + 1] = m2;
					index += 2;
#endif

				}

			}
		}
		else
		{
			char* dataPtr1 = imagePtr->dataPtr;
			char* dataPtr2 = dataPtr1 + imagePtr->width * imagePtr->height;
			char* dataPtr3 = dataPtr2 + imagePtr->width * imagePtr->height;

			char* currPtr1,*currPtr2,*currPtr3;
			char* prevPtr1,*prevPtr2,*prevPtr3;
			char* nextPtr1,*nextPtr2,*nextPtr3;

			int index = 0;
			int x1 = 0;

			float dX,dY,Mag,Ang;
			float angleScale = (float)(binCount / PI);
			int hidx;
			float t0;
			for (int y = 0; y < _paddedImageHeight;y ++)
			{




				y1 = y - 1;
				y2 = y + 1;
				y1 = y1 - y1 * (y1 < 0);
				y2 = y2 * (y2 < _paddedImageHeight) - (_paddedImageHeight - 2) * (y2 >= _paddedImageHeight);

				currPtr1 = dataPtr1 + step * y;
				prevPtr1 = dataPtr1 + step * y1;
				nextPtr1 = dataPtr1 + step * y2;

				currPtr2 = dataPtr2 + step * y;
				prevPtr2 = dataPtr2 + step * y1;
				nextPtr2 = dataPtr2 + step * y2;

				currPtr3 = dataPtr3 + step * y;
				prevPtr3 = dataPtr3 + step * y1;
				nextPtr3 = dataPtr3 + step * y2;


				int dx0,dy0,dx,dy,mg0,mg;

				for (int x = 0; x < _paddedImageWidth; x ++)
				{
				x1 = x ;
					x2 = x + 1;
					x3 = x - 1;
					if(x2 >= _paddedImageWidth)
						x2 = _paddedImageWidth - 2;
					if(x3 < 0)
						x3 = 1;
					char* p2 = currPtr3 + x2;
					char* p0 = currPtr3 + x3;


					dx0 = *p2 - *p0;
					dy0 = nextPtr3[x1] - prevPtr3[x1];
					mg0 = dx0 * dx0 + dy0 * dy0;

					p2 = currPtr2 + x2;
					p0 = currPtr2 + x3;

					dx = *p2 - *p0;
					dy = nextPtr2[x1] - prevPtr2[x1];
					mg = dx * dx + dy * dy;

					if(mg0 < mg)
					{
						dx0 = dx;
						dy0 = dy;
						mg0 = mg;
					}

					p2 = currPtr1 + x2;
					p0 = currPtr1 + x3;

					dx = *p2 - *p0;
					dy = nextPtr1[x1] - prevPtr1[x1];
					mg = dx* dx + dy * dy;
					if(mg0 < mg)
					{
						dx0 = dx;
						dy0 = dy;
					}

					dX = dx0;
					dY = dy0;

					int b1,b2;
					float m1,m2;
					LookUp(dX,dY,b1,b2,m1,m2);
					anglePtr[index] = b1;
					anglePtr[index + 1] = b2;
					magnitudePtr[index] = m1;
					magnitudePtr[index + 1] = m2;

					index += 2;

				}

			}
		}


	}
	void HGDescriptor::Compute(ImageInfo* imagePtr,float* descriptor)
	{
		
		if(descriptor == 0)
			return;
		cacheHelper.CacheImage(imagePtr);
		Vector2D nWindows = WindowsInImage(imagePtr->width,imagePtr->height);
		Vector2D nBlocks = cacheHelper.nBlocks;
		float s = 0;
		Vector2D pt0;
		Vector2D offset;
		float* hist = 0;
		int histLen = cacheHelper.blockHistSize;
		int index = 0;
		for(int y = 0; y < nWindows.y; y ++)//window sliding in vertical direction.
		{

			pt0.x = 0;
			for (int x = 0; x < nWindows.x; x ++)//window sliding in horizontal direction.
			{
				offset = pt0;
				for (int x0 = 0; x0 < nBlocks.x; x0++)//block sliding in horizontal direction.
				{
					offset.y = pt0.y;
					for(int y0 = 0; y0 < nBlocks.y; y0 ++)//block sliding in vertical direction.
					{

						hist = cacheHelper.GetBlockHist(offset);
						if(hist)
						{
							for(int k = 0; k < histLen; k ++)
							{
								descriptor[index ++] = hist[k];
							}
						}
						offset.y += blockStride.y;
					}//block in x
					offset.x += blockStride.x;
				}//block in y
				pt0.x += windowStride.x;
			}//window in x
			pt0.y += windowStride.y;

		}//window in y
	}
	void HGDescriptor::Detect(ImageInfo* imagePtr,RegionList*& pList)
	{
		if(hyperPanelVector == 0)
			return;
		cacheHelper.CacheImage(imagePtr);
		Vector2D nWindows = WindowsInImage(imagePtr->width,imagePtr->height);
		Vector2D nBlocks = cacheHelper.nBlocks;
		float s = 0;
		Vector2D pt0;
		Vector2D offset;
		float* hist = 0;
		int histLen = cacheHelper.blockHistSize;
		int index = 0;
		float rho = hyperPanelVector[GetDescriptorSize()];
		int k;
		for(int y = 0; y < nWindows.y; y ++)//window sliding in vertical direction.
		{
			
			pt0.x = 0;
			for (int x = 0; x < nWindows.x; x ++)//window sliding in horizontal direction.
			{
				offset = pt0;
				index = 0;
				s = rho;
				for (int x0 = 0; x0 < nBlocks.x; x0++)//block sliding in horizontal direction.
				{
					offset.y = pt0.y;
						for(int y0 = 0; y0 < nBlocks.y; y0 ++)//block sliding in vertical direction.
						{

						hist = cacheHelper.GetBlockHist(offset);
						if(hist)
						{
							for(k = 0; k < histLen - 4; k += 4)
							{
								s += hyperPanelVector[index] * hist[k ] +  hyperPanelVector[index + 1] * hist[k+ 1] +  hyperPanelVector[index + 2] * hist[k + 2] +  hyperPanelVector[index + 3] * hist[k + 3];
								index += 4;
								
							}
							for(;k < histLen;k ++)
							{
								s += hyperPanelVector[index ++] * hist[k];
							}
						}
						offset.y += blockStride.y;
					}//block in x
					offset.x += blockStride.x;
				}//block in y
				
				if(s > 0.1f)
				{
					offset = pt0;

					if (pList == 0)
					{
						pList = new RegionList();
						pList->location = offset;
					}
					else
						pList->AppendItemToVector2D(offset);
				}
				pt0.x += windowStride.x;
			}//window in x
			pt0.y += windowStride.y;

		}//window in y
	}
	void HGDescriptor::DetectMultiScale(ImageInfo* image, RegionList*& pList)
	{
#define Max_Level 64
		char* workBuffer = new char[image->widthStep * image->height];
		float levelScale[Max_Level];
		float scale = 1.f;
		int nScale = 0;
		for(int i = 0;  i < Max_Level; i ++)
		{
			levelScale[i] = scale;
			nScale ++;
			if((int)(image->width / scale) < windowSize.x || (int)(image->height / scale) < windowSize.y)
				break;
			scale *= 1.05;
		}
		if(pList)
		{
			pList->Release();
			pList = 0;
		}
		ImageInfo info;
		info.dataPtr = workBuffer;
		info.colorChannel = image->colorChannel;

		for(int i = 0; i < nScale; i ++)
		{
			RegionList* hitList = 0;
			
			info.width = (int)(image->width / levelScale[i]);
			info.height = (int)(image->height / levelScale[i]);
			info.widthStep = info.colorChannel * info.width;
#ifdef _CACHE_SCALE_IMAGE_INDEX_
			hogHelper.ScaleImage(image,&info,i);
#else
			hogHelper.ScaleImage(image,&info);
#endif
			Detect(&info,hitList);
			if(hitList)
			{
				RegionList* p = hitList;
				while(p)
				{
					p->location.x = (int)((double)p->location.x * levelScale[i]);
					p->location.y = (int)((double)p->location.y * levelScale[i]);
					p->size.x = (int)((double)windowSize.x * levelScale[i]);
					p->size.y = (int)((double)windowSize.y * levelScale[i]);
					p = p->next;
				}
				if(pList == 0)
					pList = hitList;
				else
				{
					p = pList;
					while(p->next)
						p = p->next;
					p->next = hitList;

				}
			}
		}
		GroupRectangles(pList);
	}
	void HGDescriptor::LoadHyperPanelVector()
	{
		static float svm[] = {1.63548902e-001,7.72843556e-003,-6.34394109e-001,7.02546000e-001,3.87584984e-001,-1.31931353e+000,-8.40644598e-001,8.86599064e-001,
			-1.45422888e+000,1.63943887e+000,4.08582211e-001,-7.01271370e-002,-6.42566860e-001,3.24171543e-001,2.44025916e-001,6.80612922e-001,1.49902165e+000,
			2.97460686e-002,3.43057930e-001,1.26274824e+000,1.27738714e+000,-2.79087991e-001,1.07702923e+000,-8.26294363e-001,-1.30671155e+000,4.04851548e-002,
			1.71147123e-001,2.29916334e+000,1.23705769e+000,-8.85775592e-003,1.04639575e-001,5.75151443e-001,1.73506141e+000,5.70053399e-001,8.86661232e-001,
			1.32830456e-001,8.19004774e-001,1.54008687e+000,8.43001381e-002,7.31232047e-001,-1.47458339e+000,9.27324742e-002,-3.67055833e-001,8.48027229e-001,
			3.32028210e-001,1.64557135e+000,1.28111437e-001,3.28415841e-001,-7.62582123e-001,-4.90138531e-001,1.25967875e-001,5.85575402e-001,5.10535538e-001,
			4.87704188e-001,1.35491717e+000,1.01917422e+000,2.03481030e+000,1.89837170e+000,-1.03403144e-001,4.15780008e-001,-1.55884959e-002,3.90262157e-001,
			-6.24432802e-001,-5.47818720e-001,1.33350968e+000,2.30646625e-001,2.54159588e-002,-4.53409106e-001,1.07072890e+000,3.71945769e-001,-6.22843504e-001,
			-1.41997242e+000,2.23122928e-002,1.22254479e+000,4.41489279e-001,-3.81788194e-001,2.00440347e-001,9.66406584e-001,2.16159582e-001,1.18114859e-001,
			-2.11041681e-002,1.43336785e+000,3.39215964e-001,3.32445979e-001,-6.01023674e-001,-5.57628334e-001,6.88531697e-001,8.15963805e-001,1.48902714e+000,
			2.66668439e+000,-1.02698970e+000,3.46751213e-001,-4.37837034e-001,2.69537091e-001,5.48955202e-001,1.15218997e+000,4.19044226e-001,7.07569793e-002,
			-1.14140308e+000,-1.28942704e+000,3.17754596e-001,7.76658952e-002,2.59934902e-001,8.33553851e-001,1.55445492e+000,2.91422486e-001,4.54524159e-001,
			-4.85568434e-001,1.76970029e+000,-3.32036406e-001,-4.09191459e-001,2.10815780e-002,4.26882416e-001,1.19168088e-001,-8.94024134e-001,-4.94462907e-001,
			1.13681293e+000,-1.00737464e+000,-1.63001442e+000,-1.65387225e+000,5.12938835e-002,-8.72397721e-001,1.12233222e+000,9.50969338e-001,2.13275814e+000,
			1.55309379e+000,4.81643379e-001,1.33272529e+000,1.00630021e+000,4.03895706e-001,1.09589851e+000,5.18414617e-001,2.77012795e-001,2.22069725e-001,
			9.85985935e-001,-1.25085795e+000,-6.74313426e-001,1.20268691e+000,8.61951351e-001,7.85250485e-001,2.13868046e+000,5.93881309e-001,1.21688080e+000,
			-1.62335563e+000,-2.11855158e-001,6.00183569e-002,7.21975625e-001,-2.81525135e-001,2.31495190e+000,-2.36348599e-001,-8.05323243e-001,-1.13484597e+000,
			-5.82053542e-001,-4.16891694e-001,-9.44575608e-001,-4.85903174e-001,-2.32578802e+000,-3.48131359e-001,-7.85113335e-001,-8.95153821e-001,-6.20131314e-001,
			8.73837829e-001,-6.52689815e-001,-1.35980248e+000,1.62691884e-002,5.08458972e-001,3.24505150e-001,8.28911126e-001,6.82835758e-001,7.39475906e-001,
			-5.61804116e-001,8.14043209e-002,-3.95793527e-001,-5.12988329e-001,-6.83576584e-001,-5.04323661e-001,1.89955384e-001,9.99675170e-002,-1.34730959e+000,
			-5.58875859e-001,-6.19008243e-001,-1.46195579e+000,-1.77663827e+000,-1.29811001e+000,7.89181709e-001,1.59185976e-002,-8.61074805e-001,5.65910995e-001,
			6.80679798e-001,1.17413819e+000,4.43185747e-001,-5.49629927e-001,-1.06460226e+000,1.98415744e+000,7.79358029e-001,-9.81411219e-001,-5.98786138e-002,
			1.53105581e+000,-1.46102756e-001,-4.22906950e-002,-6.27086580e-001,8.38925183e-001,3.47932279e-001,-1.55593470e-001,-1.29866982e+000,-1.60455954e+000,
			-1.01034975e+000,1.47072405e-001,-5.68620205e-001,2.84170657e-001,8.72180045e-001,9.07565951e-001,7.55403697e-001,2.73194253e-001,-7.01423526e-001,
			5.99082232e-001,9.39553320e-001,-3.32112253e-001,1.36174291e-001,-3.90876144e-001,2.84012586e-001,1.34629279e-001,-8.42408955e-001,1.13278823e-002,
			2.01579601e-001,8.42534125e-001,7.79866993e-001,4.84167784e-001,1.65170759e-001,1.95605576e+000,1.49396205e+000,3.99481356e-001,-7.16117024e-001,
			-2.82099545e-002,-4.73233275e-002,-5.25296807e-001,1.71384484e-001,2.55782753e-001,5.70856392e-001,9.67422947e-002,1.09064795e-001,3.68041962e-001,
			5.35551190e-001,-5.31320512e-001,-3.26477110e-001,-2.60662556e-001,4.58132863e-001,5.96510351e-001,9.81617421e-002,8.65905344e-001,5.22053353e-002,
			1.19543242e+000,9.17464912e-001,9.31706905e-001,-3.82946074e-001,-1.47890699e+000,8.09361875e-001,-3.74914855e-002,6.33144677e-001,3.82896036e-001,
			-7.25833535e-001,-2.22276852e-001,2.59975661e-002,-3.74904305e-001,-4.05372351e-001,1.55490100e+000,2.41789579e+000,-9.14923176e-002,2.26286769e-001,
			-6.76923752e-001,9.64280963e-001,1.82052329e-001,1.46743262e+000,-1.98630318e-001,4.96192843e-001,-8.70725811e-001,-2.89464593e-001,1.98854089e-001,
			1.05138683e+000,4.41000573e-002,1.82819918e-001,6.17333174e-001,1.80767983e-001,1.62395298e+000,1.29689395e-001,-1.94508687e-001,-2.47817397e-001,
			-3.53273362e-001,-7.25425065e-001,6.50156200e-001,-6.55355752e-001,-1.67941213e+000,1.08100104e+000,3.31791252e-001,-1.14812113e-001,1.07366955e+000,
			-8.34896713e-002,1.00144517e+000,1.46889281e+000,4.58951354e-001,5.04252076e-001,4.59112883e-001,3.34164798e-001,7.60228515e-001,1.33884144e+000,
			7.27180600e-001,-1.94532776e+000,3.03994957e-002,-1.46982923e-001,-1.17871666e+000,-6.13279402e-001,9.04345036e-001,1.21193282e-001,1.29873288e+000,
			7.87341237e-001,7.81241238e-001,-4.05002415e-001,1.21850991e+000,-7.23632053e-002,1.31028271e+000,5.00214994e-001,1.32103227e-002,2.40794301e-001,
			1.28569281e+000,3.68066281e-001,1.52047026e+000,-4.64559570e-002,7.83276260e-001,3.44313622e-001,8.21015179e-001,-1.65544137e-001,1.07670176e+000,
			8.35829377e-001,-1.98208690e+000,8.14752519e-001,-1.06623638e+000,-1.12665904e+000,6.61113799e-001,4.55502659e-001,1.44510835e-001,-3.14201564e-001,
			1.89143047e-001,-4.16393608e-001,6.47515833e-001,1.18880916e+000,5.13265967e-001,-9.44132090e-001,6.86144382e-002,-4.26081181e-001,1.04428709e+000,
			1.80969024e+000,7.05287755e-001,9.22894895e-001,-6.78027719e-002,1.24394929e+000,-3.77936244e-001,-5.76744139e-001,4.45760846e-001,6.28573716e-001,
			1.11651886e+000,-6.16994500e-001,1.08160806e+000,8.33490610e-001,8.67341459e-001,3.65021288e-001,2.40559690e-002,-4.44435060e-001,5.37973106e-001,
			6.69782400e-001,-1.59732252e-001,3.10872078e-001,-2.43232518e-001,-5.53220987e-001,7.59951949e-001,2.66008168e-001,-1.06799982e-001,1.31581232e-001,
			-1.67659402e+000,8.45929086e-001,1.17241696e-001,-5.96425533e-001,5.85701823e-001,-3.66511226e-001,3.89370680e-001,-1.41355348e+000,9.12035167e-001,
			4.34395850e-001,1.58103615e-001,1.77448368e+000,4.80610400e-001,1.26134181e+000,-8.87439966e-001,4.71207388e-002,5.14700055e-001,5.15153632e-003,
			1.08084112e-001,8.72076392e-001,1.29042566e+000,8.37188244e-001,1.03481758e+000,3.02823281e+000,1.21720350e+000,5.18991314e-002,1.07655811e+000,
			1.10837424e+000,-1.45941257e+000,2.71854281e-001,4.39062536e-001,1.82249784e+000,9.74588454e-001,2.61211658e+000,-6.62577525e-002,6.38587773e-001,
			-1.58291662e+000,4.44385856e-001,4.97545719e-001,-8.26942027e-001,8.43312085e-001,1.05678461e-001,5.87189868e-002,-1.84793368e-001,-6.10727549e-001,
			6.52873993e-001,3.67347312e+000,2.14943886e+000,3.58315021e-001,1.23022266e-001,-2.04932475e+000,-1.38063967e+000,-2.25070429e+000,-2.15258861e+000,
			-3.61237228e-001,-2.03568058e+001};
		if(hyperPanelVector)
		{
			delete[] hyperPanelVector;
			hyperPanelVector = 0;

		}
		int len = sizeof(svm) / sizeof(float);
		hyperPanelVector = new float[len];
		for(int i = 0; i < len; i ++)
		{
			hyperPanelVector[i] = svm[i];
		}
	}