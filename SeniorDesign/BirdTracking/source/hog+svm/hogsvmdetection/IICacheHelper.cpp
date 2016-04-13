#include "hog.h"
#include "math.h"

IICacheHelper::IICacheHelper()
{
	ppIICacheData = 0;
	pFullHisCacheData = 0;
	iiWidth = 0;
	iiHeight = 0;
}
IICacheHelper::~IICacheHelper()
{
	Release();
}
void IICacheHelper::Release()
{
#ifdef _COMPACT_DATA_
	if(ppIICacheData)
	{
		delete[] ppIICacheData;
		ppIICacheData = 0;
	}
#else
	if(ppIICacheData)
	{
		for(int i = 0; i < nBins; i ++)
		{
			if(ppIICacheData[i])
			{
				delete[] ppIICacheData[i];
			}
		}
		delete[] ppIICacheData;
		ppIICacheData = 0;
	}
#endif
	if(pFullHisCacheData)
	{
		delete[] pFullHisCacheData;
		pFullHisCacheData = 0;
	}
}
void IICacheHelper::Configure(HGDescriptor* _hog)
{
	Release();
	m_pHogDescriptor = _hog;
	cacheMaxImageSize = _hog->maxImageSize;
	nBins = _hog->binCount;
#ifdef _COMPACT_DATA_
	ppIICacheData = new GT[cacheMaxImageSize.Area() * nBins];
#else
	ppIICacheData = new GT*[nBins];
	for(int i = 0; i < nBins; i ++)
	{
		ppIICacheData[i] = new GT[cacheMaxImageSize.Area()];
	}
#endif
	blockHistSize = (_hog->blockSize / _hog->cellSize).Area() * nBins;

	//generate static reference geometry table for control
	const float scale = 1.05f ;
	float s = 1.f;
	scaleCount = 0;
	GeometryInfo gi;
	int offset = 0;
	cellGrid = (m_pHogDescriptor->blockSize/m_pHogDescriptor->cellSize);
	for(int i = 0; i < 64; i ++)
	{
		gi.winSize = m_pHogDescriptor->windowSize * s;
		gi.blockSize = m_pHogDescriptor->blockSize * s;
		gi.winStride = m_pHogDescriptor->windowStride * s;
		gi.blockStride = m_pHogDescriptor->blockStride * s;
		gi.cellSize = m_pHogDescriptor->cellSize * s;
		gi.cacheStride = Vector2D(GreatCommonDivisor(gi.winStride.x,gi.blockStride.x),GreatCommonDivisor(gi.winStride.y,gi.blockStride.y));
		gi.histCacheOffset = offset;
		int cx = (iiWidth - gi.blockSize.x) / gi.cacheStride.x + 1;
		int cy = (iiHeight - gi.blockSize.y) / gi.cacheStride.y + 1;
		gi.cacheGrid = Vector2D(cx,cy);
		offset += cx * cy * blockHistSize;
		{
			geometryRefTable[i] = gi;
		}
		s *= scale;

	}
	
}
void IICacheHelper::GenerateGeometryInfo()
{
	const float scale = 1.05f;
	float s = 1.f;
	scaleCount = 0;
	GeometryInfo gi;
	int offset = 0;
	cellGrid = (m_pHogDescriptor->blockSize/m_pHogDescriptor->cellSize);
	do 
	{
		gi.winSize = m_pHogDescriptor->windowSize * s;
		gi.blockSize = m_pHogDescriptor->blockSize * s;
		gi.winStride = m_pHogDescriptor->windowStride * s;
		gi.blockStride = m_pHogDescriptor->blockStride * s;
		gi.cellSize = m_pHogDescriptor->cellSize * s;
		gi.cacheStride = Vector2D(GreatCommonDivisor(gi.winStride.x,gi.blockStride.x),GreatCommonDivisor(gi.winStride.y,gi.blockStride.y));
		gi.histCacheOffset = offset;
		int cx = (iiWidth - gi.blockSize.x) / gi.cacheStride.x + 1;
		int cy = (iiHeight - gi.blockSize.y) / gi.cacheStride.y + 1;
		gi.cacheGrid = Vector2D(cx,cy);
		offset += cx * cy * blockHistSize;
		{
			geometryData[scaleCount ++] = gi;
		}
		s *= scale;

	} while (gi.winSize.x < iiWidth && gi.winSize.y < iiHeight && scaleCount < 63);
	if(iiWidth > histCacheSize.x || iiHeight > histCacheSize.y)
	{
		delete[] pFullHisCacheData;
		pFullHisCacheData = 0;
	}
	if(pFullHisCacheData == 0)
	{
		pFullHisCacheData = new float[offset];
		histCacheSize.x = iiWidth;
		histCacheSize.y = iiHeight;
	}
}
void IICacheHelper::ClearIntegralImages()
{
	int len = iiWidth * iiHeight;
#ifdef _COMPACT_DATA_
	len *= nBins;
	for(int i = 0; i < len;i ++)
	{
		ppIICacheData[i] = 0;
	}
#else
	GT* p = 0;
	for(int i = 0; i < nBins; i ++)
	{
		p = ppIICacheData[i];
		for(int j = 0; j < len;j ++)
			p[j] = 0;
	}
#endif
}
void IICacheHelper::GenerateIntegralImages()
{
	int index = 0;
	//short bins;
	unsigned char bin1,bin2;
	GT mag1,mag2;

	unsigned char* binPtr = m_pHogDescriptor->anglePtr;
	GT* magPtr = m_pHogDescriptor->magnitudePtr;
	ClearIntegralImages();
	unsigned char* bp = binPtr;
	GT* mp = magPtr;
	int i,j,k;


#ifdef _COMPACT_DATA_
	GT* pt = ppIICacheData;
	int len = iiHeight * iiWidth;
	for(i = 0; i < len; i ++)
	{
		bin1 = bp[0];
		bin2 = bp[1];
		mag1 = mp[0];
		mag2 = mp[1];
		pt[bin1] += mag1;
		pt[bin2] += mag2;

		pt += nBins;
		bp += 2;
		mp += 2;
	}
	//Start integration.
	pt = ppIICacheData + nBins;
	for(i = 1; i < iiWidth; i ++)
	{
		for(j = 0; j < nBins;j ++)
		{
			pt[j] += pt[j - nBins];
		}
		pt += nBins;

	}
	index = iiWidth * nBins;
	pt = ppIICacheData + index;
	for (i = 1; i < iiHeight; i ++)
	{

		for(j = 0; j < nBins;j ++)
		{
			pt[j] += pt[j - index];
		}

		pt += index;
	}

	pt = ppIICacheData + index + nBins;
	for (i = 1; i < iiHeight; i ++)
	{
		for(j = 1; j < iiWidth; j ++)
		{

			for (k = 0; k < nBins;k ++)
			{
				pt[k] += (pt[k - nBins] + pt[k - index] - pt[k - index - nBins]);
			}

			pt += nBins;
		}
		pt += nBins;
	}
#else
	int k1,k2,k3;
	int index1,index2,index3;

	//Decompose Gradient Image to Integral Image Inputs, this would cast operating ease in next step of integration.
	for(i = 0; i < iiWidth * iiHeight; i ++)
	{
		bin1 = bp[0];
		bin2 = bp[1];
		mag1 = mp[0];
		mag2 = mp[1];
		ppIICacheData[bin1][i] += mag1;
		ppIICacheData[bin2][i] += mag2;
		bp += 2;
		mp += 2;
	}
	//Start integration.
	for(i = 1; i < iiWidth; i ++)
	{
#ifdef  _PPL_
		for (j = 0; j < nBins - 4; j += 4)
		{
			ppIICacheData[j][i] += ppIICacheData[j][i - 1];
			ppIICacheData[j + 1][i] += ppIICacheData[j + 1][i - 1];
			ppIICacheData[j + 2][i] += ppIICacheData[j + 2][i - 1];
			ppIICacheData[j + 3][i] += ppIICacheData[j + 3][i - 1];
		}
		for (; j < nBins;j ++)
		{
			ppIICacheData[j][i] += ppIICacheData[j][i - 1];
		}
#else
		for(j = 0; j < nBins;j ++)
		{
			ppIICacheData[j][i] += ppIICacheData[j][i - 1];
		}
#endif
	}
	index = iiWidth;
	for (i = 1; i < iiHeight; i ++)
	{
#ifdef _PPL_
		for (j = 0; j < nBins - 4; j += 4)
		{
			ppIICacheData[j][index] += ppIICacheData[j][index - iiWidth];
			ppIICacheData[j + 1][index] += ppIICacheData[j + 1][index - iiWidth];
			ppIICacheData[j + 2][index] += ppIICacheData[j + 2][index - iiWidth];
			ppIICacheData[j + 3][index] += ppIICacheData[j + 3][index - iiWidth];
		}
		for (;j < nBins;j ++)
		{
			ppIICacheData[j][index] += ppIICacheData[j][index - iiWidth];
		}
#else
		for(j = 0; j < nBins;j ++)
		{
			ppIICacheData[j][index] += ppIICacheData[j][index - iiWidth];
		}
#endif
		index += iiWidth;
	}

	index = iiWidth + 1;
	for (i = 1; i < iiHeight; i ++)
	{
		for(j = 1; j < iiWidth; j ++)
		{
#ifdef _PPL_
			index1 = index - 1;
			index2 = index - iiWidth;
			index3 = index2 - 1;
			for (k = 0; k < nBins - 4;k += 4)
			{
				k1 = k + 1;
				k2 = k + 2;
				k3 = k + 3;
				ppIICacheData[k][index] += (ppIICacheData[k][index1] + ppIICacheData[k][index2] - ppIICacheData[k][index3]);
				ppIICacheData[k1][index] += (ppIICacheData[k1][index1] + ppIICacheData[k1][index2] - ppIICacheData[k1][index3]);
				ppIICacheData[k2][index] += (ppIICacheData[k2][index1] + ppIICacheData[k2][index2] - ppIICacheData[k2][index3]);
				ppIICacheData[k3][index] += (ppIICacheData[k3][index1] + ppIICacheData[k3][index2] - ppIICacheData[k3][index3]);
			}
			for(;k < nBins;k ++)
				ppIICacheData[k][index] += (ppIICacheData[k][index1] + ppIICacheData[k][index2] - ppIICacheData[k][index3]);
#else
			for (k = 0; k < nBins;k ++)
			{
				ppIICacheData[k][index] += (ppIICacheData[k][index - 1] + ppIICacheData[k][index - iiWidth] - ppIICacheData[k][index - iiWidth - 1]);
			}
#endif
			index ++;
		}
		index ++;
	}
#endif
}
GT IICacheHelper::GetIIValue(int index,int x,int y)
{
#ifdef _COMPACT_DATA_
	return ppIICacheData[(y * iiWidth + x) * nBins + index];
#else
	return ppIICacheData[index][y * iiWidth + x];
#endif
}
GT IICacheHelper::GetIIRectValue(int binI,Vector2D tlPt,Vector2D brPt)
{
	float v11,v12,v21,v22;
#ifdef _COMPACT_DATA_
	
	if (tlPt.x > 0)
	{
		tlPt.x --;
	}
	if (tlPt.y > 0)
	{
		tlPt.y --;
	}
	if (brPt.x >= iiWidth)
	{
		brPt.x --;
	}
	if (brPt.y >= iiHeight)
	{
		brPt.y --;
	}
	brPt.x --;
	brPt.y --;
	int w = iiWidth * nBins;
	int y1 = tlPt.y * w;
	//int y2 = (brPt.y - 2)* w;
	int y2 = brPt.y* w;
	int x1 = tlPt.x * nBins + binI;
	//int x2 = (brPt.x - 2) * nBins + binI;
	int x2 = brPt.x * nBins + binI;
	v11 = (float)ppIICacheData[y1 + x1];
	v22 = (float)ppIICacheData[y2 + x2];
	v12 = (float)ppIICacheData[y1 + x2];
	v21 = (float)ppIICacheData[y2 + x1];
	if (tlPt.x == 0)
	{
		v11 = 0;
		v21 = 0;
	}
	if (tlPt.y == 0)
	{
		v11 = 0;
		v12 = 0;
	}
#else
	brPt.x --;
	brPt.y --;
	v11 = GetIIValue(binI,tlPt.x,tlPt.y);
	v22 = GetIIValue(binI,brPt.x,brPt.y);
	v12 = GetIIValue(binI,brPt.x,tlPt.y);
	v21 = GetIIValue(binI,tlPt.x,brPt.y);
#endif
	return (GT)(v22 + v11 - v21 - v12);
}
void IICacheHelper::GetRectHist(float* buffer,Vector2D tlPt,Vector2D brPt)
{
#ifdef _DEBUG
	int sum = 0;
#endif
	for(int i = 0; i < nBins;i ++)
	{
		buffer[i] =/**/(float) GetIIRectValue(i,tlPt,brPt);
#ifdef _DEBUG
		sum += buffer[i];
#endif
	}
#ifdef _DEBUG
	printf("sum = %d\r",sum);
	if (sum != 128)
	{
		 sum = 128;
	}
#endif

}
void IICacheHelper::CacheImage(ImageInfo* imagePtr)
{

	m_pHogDescriptor->ComputerGradient(imagePtr);
	iiWidth = imagePtr->width;
	iiHeight = imagePtr->height;
	GenerateGeometryInfo();
	GenerateIntegralImages();
	CacheFullHist();
}
void IICacheHelper::GetBlockHist(int x,int y,GeometryInfo& gi,float* buffer)
{
	float* pt = buffer;

	/////////////////////////////////////////////////////////////////////////////////////////
	//As Comprehensive Code Testing, PCA can be Applied to Reduce Histogram Size and Improve 
	//Processing Speed and without lose any significant discriminative power.Since following 
	//code can be optimized via discarding certain dimensions of HOG feature Histogram, 
	//It depends on your decision to make trade off between speed and discriminative power
	//No further Idea available, Please Do as your wish and wisdom in practical application to
	//improve performance.
	//---IIHOG Coded by Halley---2011-9-11-10:41---ShiTong Opt Software L.T.D.
	/////////////////////////////////////////////////////////////////////////////////////////
	/*for(int i = x; i <= x + gi.blockSize.x - gi.cellSize.x;i += gi.cellSize.x)
	{
		for (int j = y; j <= y + gi.blockSize.y - gi.cellSize.y; j += gi.cellSize.y)
		{
			GetRectHist(pt,Vector2D(i,j),Vector2D(i + gi.cellSize.x,j + gi.cellSize.y));
			pt += nBins;

		}
	}*/
	int x0 = x;
	int y0;
	
	for(int i = 0; i < cellGrid.x;i ++)
	{
		y0 = y;
		for (int j = 0; j < cellGrid.y;j ++)
		{
			GetRectHist(pt,Vector2D(x0,y0),Vector2D(x0 + gi.cellSize.x,y0 + gi.cellSize.y));
			pt += nBins;
			y0 += gi.cellSize.y;
		}
		x0 += gi.cellSize.x;
	}
#ifndef _DISCARD_NORMALIZATION_
	NormalizeHist(buffer);
#endif
}
void IICacheHelper::NormalizeHist(float* hist)
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
	/*static float thresh = 0.2;
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


	scale = 1.f / (sqrt(sum) + 1e-3f);*/

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
#ifdef _DSP_OPT_
void IICacheHelper::GetDspBlockHist(int x,int y,GeometryInfo& gi,float* buffer)
{
	//float* pt = buffer;

	/////////////////////////////////////////////////////////////////////////////////////////
	//As Comprehensive Code Testing, PCA can be Applied to Reduce Histogram Size and Improve 
	//Processing Speed and without lose any significant discriminative power.Since following 
	//code can be optimized via discarding certain dimensions of HOG feature Histogram, 
	//It depends on your decision to make trade off between speed and discriminative power
	//No further Idea available, Please Do as your wish and wisdom in practical application to
	//improve performance.
	//---IIHOG Coded by Halley---2011-9-01-10:41---ShiTong Opt Software L.T.D.
	/////////////////////////////////////////////////////////////////////////////////////////
	int xr = x + 2 * gi.cellSize.x -1;
	int yr = y + 2 * gi.cellSize.y -1;
	int xl = x;
	int yl = y;
	xl = (xl > 0) * (xl - 1);
	yl = (yl > 0) * (yl - 1);
	xr = (xr >= iiWidth) * (xr - 1) + (xr < iiWidth) * (xr);
	yr = (yr >= iiHeight) * (yr - 1) + (yr < iiHeight) * (yr);


	int x0,x2;
	int y0,y2;
#ifdef _DISCARD_NORMALIZATION_
	float* p = buffer;
#else
	int* p = (int*)buffer;
#endif
	int ww = iiWidth * nBins;
	int dx = gi.cellSize.x * nBins;
	int dy = gi.cellSize.y * ww;
	int dd = ww + nBins;
	x0 = xl * nBins;
	y0 = yl * ww;
	x2 = xr * nBins;
	y2 = yr * ww;
	int p00[] = {0,0,0,0,0,0,0,0,0,};
	int* p11,*p12,*p13,*p21,*p22,*p23,*p31,*p32,*p33;
	p11 = ppIICacheData + y0 + x0;
	p12 = p11 + dx;
	p13 = ppIICacheData + y0 + x2;
	p21 = p11 + dy;
	p22 = p12 + dy;
	p23 = p13 + dy;
	p31 = ppIICacheData + y2 + x0;
	p32 = p31 + dx;
	p33 = ppIICacheData + y2 + x2;
	if (xl == 0 )
	{
		p11 = p00;
		p21 = p00;
		p31 = p00;
	}
	if (yl == 0)
	{
		p11 = p00;
		p12 = p00;
		p13 = p00;
	}
	/*int x0 ;
	int y0;
	int* p = (int*)buffer;
	int ww = iiWidth * nBins;
	int dx = gi.cellSize.x * nBins;
	int dy = gi.cellSize.y * ww;
	int dd = ww + nBins;
	x0 = x * nBins;
	y0 = y * ww;
	int* p11,*p12,*p13,*p21,*p22,*p23,*p31,*p32,*p33;
	p11 = ppIICacheData + y0 + x0;// ppIICacheData + (y * iiWidth + x) * nBins;//
	p12 = p11 + dx;//ppIICacheData + (y * iiWidth + x + gi.cellSize.x) * nBins;//
	p13 = p12 + dx;//ppIICacheData + (y * iiWidth + x + 2 * gi.cellSize.x) * nBins;//
	p21 = p11 + dy;//ppIICacheData + ((y + gi.cellSize.y) * iiWidth + x) * nBins;//
	p22 = p12 + dy;//ppIICacheData + ((y + gi.cellSize.y) * iiWidth + x + gi.cellSize.x) * nBins;//
	p23 = p13 + dy;//ppIICacheData + ((y + gi.cellSize.y) * iiWidth + x + 2 * gi.cellSize.x) * nBins;//
	p31 = p21 + dy;//ppIICacheData + ((y + 2 * gi.cellSize.y) * iiWidth + x) * nBins;//
	p32 = p22 + dy;//ppIICacheData + ((y + 2 * gi.cellSize.y) * iiWidth + x + gi.cellSize.x) * nBins;//
	p33 = p23 + dy;//ppIICacheData + ((y + 2 * gi.cellSize.y) * iiWidth + x + 2 * gi.cellSize.x) * nBins;//
	*/
	/*
	//c11
	p[0] = p22[0 - dd] - p21[0 - ww] - p12[0 - nBins] + p11[0];
	p[1] = p22[1 - dd] - p21[1 - ww] - p12[1 - nBins] + p11[1];
	p[2] = p22[2 - dd] - p21[2 - ww] - p12[2 - nBins] + p11[2];
	p[3] = p22[3 - dd] - p21[3 - ww] - p12[3 - nBins] + p11[3];
	p[4] = p22[4 - dd] - p21[4 - ww] - p12[4 - nBins] + p11[4];
	p[5] = p22[5 - dd] - p21[5 - ww] - p12[5 - nBins] + p11[5];
	p[6] = p22[6 - dd] - p21[6 - ww] - p12[6 - nBins] + p11[6];
	p[7] = p22[7 - dd] - p21[7 - ww] - p12[7 - nBins] + p11[7];
	p[8] = p22[8 - dd] - p21[8 - ww] - p12[8 - nBins] + p11[8];
	//cell 21
	p[9] = p32[0 - dd] - p31[0 - ww] - p22[0 - nBins] + p21[0];
	p[10] = p32[1 - dd] - p31[1 - ww] - p22[1 - nBins] + p21[1];
	p[11] = p32[2 - dd] - p31[2 - ww] - p22[2 - nBins] + p21[2];
	p[12] = p32[3 - dd] - p31[3 - ww] - p22[3 - nBins] + p21[3];
	p[13] = p32[4 - dd] - p31[4 - ww] - p22[4 - nBins] + p21[4];
	p[14] = p32[5 - dd] - p31[5 - ww] - p22[5 - nBins] + p21[5];
	p[15] = p32[6 - dd] - p31[6 - ww] - p22[6 - nBins] + p21[6];
	p[16] = p32[7 - dd] - p31[7 - ww] - p22[7 - nBins] + p21[7];
	p[17] = p32[8 - dd] - p31[8 - ww] - p22[8 - nBins] + p21[8];
	//cell 12
	p[18] = p23[0 - dd] - p22[0 - ww] - p13[0 - nBins] + p12[0];
	p[19] = p23[1 - dd] - p22[1 - ww] - p13[1 - nBins] + p12[1];
	p[20] = p23[2 - dd] - p22[2 - ww] - p13[2 - nBins] + p12[2];
	p[21] = p23[3 - dd] - p22[3 - ww] - p13[3 - nBins] + p12[3];
	p[22] = p23[4 - dd] - p22[4 - ww] - p13[4 - nBins] + p12[4];
	p[23] = p23[5 - dd] - p22[5 - ww] - p13[5 - nBins] + p12[5];
	p[24] = p23[6 - dd] - p22[6 - ww] - p13[6 - nBins] + p12[6];
	p[25] = p23[7 - dd] - p22[7 - ww] - p13[7 - nBins] + p12[7];
	p[26] = p23[8 - dd] - p22[8 - ww] - p13[8 - nBins] + p12[8];
	//cell 22
	p[27] = p33[0 - dd] - p32[0 - ww] - p23[0 - nBins] + p22[0];
	p[28] = p33[1 - dd] - p32[1 - ww] - p23[1 - nBins] + p22[1];
	p[29] = p33[2 - dd] - p32[2 - ww] - p23[2 - nBins] + p22[2];
	p[30] = p33[3 - dd] - p32[3 - ww] - p23[3 - nBins] + p22[3];
	p[31] = p33[4 - dd] - p32[4 - ww] - p23[4 - nBins] + p22[4];
	p[32] = p33[5 - dd] - p32[5 - ww] - p23[5 - nBins] + p22[5];
	p[33] = p33[6 - dd] - p32[6 - ww] - p23[6 - nBins] + p22[6];
	p[34] = p33[7 - dd] - p32[7 - ww] - p23[7 - nBins] + p22[7];
	p[35] = p33[8 - dd] - p32[8 - ww] - p23[8 - nBins] + p22[8];
	*/

	//c11
	p[0] = p22[0] - p21[0] - p12[0] + p11[0];
	p[1] = p22[1] - p21[1] - p12[1] + p11[1];
	p[2] = p22[2] - p21[2] - p12[2] + p11[2];
	p[3] = p22[3] - p21[3] - p12[3] + p11[3];
	p[4] = p22[4] - p21[4] - p12[4] + p11[4];
	p[5] = p22[5] - p21[5] - p12[5] + p11[5];
	p[6] = p22[6] - p21[6] - p12[6] + p11[6];
	p[7] = p22[7] - p21[7] - p12[7] + p11[7];
	p[8] = p22[8] - p21[8] - p12[8] + p11[8];
	//cell 21
	p[9] = p32[0] - p31[0] - p22[0] + p21[0];
	p[10] = p32[1] - p31[1] - p22[1] + p21[1];
	p[11] = p32[2] - p31[2] - p22[2] + p21[2];
	p[12] = p32[3] - p31[3] - p22[3] + p21[3];
	p[13] = p32[4] - p31[4] - p22[4] + p21[4];
	p[14] = p32[5] - p31[5] - p22[5] + p21[5];
	p[15] = p32[6] - p31[6] - p22[6] + p21[6];
	p[16] = p32[7] - p31[7] - p22[7] + p21[7];
	p[17] = p32[8] - p31[8] - p22[8] + p21[8];
	//cell 12
	p[18] = p23[0] - p22[0] - p13[0] + p12[0];
	p[19] = p23[1] - p22[1] - p13[1] + p12[1];
	p[20] = p23[2] - p22[2] - p13[2] + p12[2];
	p[21] = p23[3] - p22[3] - p13[3] + p12[3];
	p[22] = p23[4] - p22[4] - p13[4] + p12[4];
	p[23] = p23[5] - p22[5] - p13[5] + p12[5];
	p[24] = p23[6] - p22[6] - p13[6] + p12[6];
	p[25] = p23[7] - p22[7] - p13[7] + p12[7];
	p[26] = p23[8] - p22[8] - p13[8] + p12[8];
	//cell 22
	p[27] = p33[0] - p32[0] - p23[0] + p22[0];
	p[28] = p33[1] - p32[1] - p23[1] + p22[1];
	p[29] = p33[2] - p32[2] - p23[2] + p22[2];
	p[30] = p33[3] - p32[3] - p23[3] + p22[3];
	p[31] = p33[4] - p32[4] - p23[4] + p22[4];
	p[32] = p33[5] - p32[5] - p23[5] + p22[5];
	p[33] = p33[6] - p32[6] - p23[6] + p22[6];
	p[34] = p33[7] - p32[7] - p23[7] + p22[7];
	p[35] = p33[8] - p32[8] - p23[8] + p22[8];
	float s = 0;
	for (int i = 0; i < 36;i ++)
	{
		s += p[i];
	}
	if (s != 512)
	{
		s = 512;
	}
	/*printf("%f\n",s);*/
#ifndef _DISCARD_NORMALIZATION_
	int sum = 0;
	int t0,t1,t2,t3,t4,t5;
	//double tt1,tt2,tt3;
	for (int i = 0; i < 36; i += 6)
	{
		t0 = p[i];
		t1 = p[i + 1];
		t2 = p[i + 2];
		t3 = p[i + 3];
		t4 = p[i + 4];
		t5 = p[i + 5];
		//	printf("%d %d %d %d %d %d \r\n",t0,t1,t2,t3,t4,t5);
		sum += t0 * t0 + t1 * t1 + t2 * t2 + t3 * t3 + t4 * t4 + t5 * t5;
		//sum += t0 + t1 + t2 + t3 + t4 + t5;
	}
	//printf("%d\r\n",sum);
	DspNormalizeHist(p,(float)sum);
	//NormalizeHist(buffer);
#endif
}
void IICacheHelper::DspNormalizeHist(int* buffer, float scale)
{
#ifdef _FIX_POINT_SVM_
	scale = sqrt(scale + blockHistSize / 10);
	int s = (int)scale;
	int i;
	for(i = 0; i < blockHistSize - 4; i += 4)
	{
		buffer[i] = (buffer[i] << 10) / s;
		buffer[i + 1] = (buffer[i + 1] << 10) / s;
		buffer[i + 2] = (buffer[i + 2] << 10) / s;
		buffer[i + 3] =  (buffer[i + 3] << 10) / s;
	}
	for(; i < blockHistSize; i ++)
	{
		buffer[i] = (buffer[i] << 10) / s;
	}
#else
	float* hist = (float*)buffer;
	scale = 1.f / (sqrt(scale + blockHistSize / 10));

	int i;
	for(i = 0; i < blockHistSize - 4; i += 4)
	{
		hist[i]= (float)buffer[i] * scale;
		hist[i + 1]= (float)buffer[i + 1] * scale;
		hist[i + 2] = (float)buffer[i + 2] * scale;
		hist[i + 3] =  (float)buffer[i + 3] *scale;
	}
	for(; i < blockHistSize; i ++)
	{
		hist[i] = (float)buffer[i] * scale;
	}
#endif
}
#endif
float IICacheHelper::EvaluateWindowSignal(int x,int y,GeometryInfo& gi)
{
	const float* ptr = 0;
	double s = 0;
	double* svmVector = m_pHogDescriptor->hyperPanelVector;
	double rho = svmVector[m_pHogDescriptor->GetDescriptorSize()];
	s = rho;
	int index = 0;
	int k;
	for(int i = x; i <= x + gi.winSize.x - gi.blockSize.x; i += gi.blockStride.x)
	{
		for (int j = y; j <= y + gi.winSize.y - gi.blockSize.y; j += gi.blockStride.y)
		{
			 ptr = GetBlockHist(gi,i,j);
			
			for(k = 0; k < blockHistSize - 4; k += 4)
			{
				s += (svmVector[index] * ptr[k] + svmVector[index +1] * ptr[k + 1] + svmVector[index + 2] * ptr[k + 2] + svmVector[index + 3] * ptr[k + 3]);
				index += 4;
			}
			for (;k < blockHistSize; k ++)
			{
				s += svmVector[index ++] * ptr[k];
			}

		}
	}
	return (float)s;
}
void IICacheHelper::Detect(int scale,RegionList*& pList)
{
	GeometryInfo gi = geometryData[scale];
	float s = 0;
	Vector2D offset;
	Vector2D size;
	for(int y = 0; y < iiHeight - gi.winSize.y; y += gi.winStride.y)
	{
		for (int x = 0; x < iiWidth - gi.winSize.x; x += gi.winStride.x)
		{
			s = EvaluateWindowSignal(x,y,gi);
			if(s > 0.1f)
			{
				
				offset.x = x;
				offset.y = y;
				if (pList == 0)
				{
					pList = new RegionList();
					pList->location = offset;
					pList->size = gi.winSize;
				}
				else
					pList->AppendItemToVector2D(offset,gi.winSize);
			}
		}
	}
}
int IICacheHelper::FindBestGI(int x,int y)
{
	for(int i = 0; i < scaleCount; i ++)
	{
		if(geometryData[i].winSize.x <= x && geometryData[i].winSize.y <= y)
		{
			if((x + y -geometryData[i].winSize.x - geometryData[i].winSize.y ) <= 1)
				return i;
		}
	}
	return -1;
}
Vector2D HGDescriptor::PreferScale(int x,int y)
{
#ifdef _IIHOG_
	int id = iiCacheHelper.FindBestControlGI(x,y);
	if(id == -1)
		id = 0;
	return iiCacheHelper.geometryRefTable[id].winSize;
#else
	int x0 = windowSize.x;
	int y0 = windowSize.y;
	Vector2D size(x0,y0);
	const float scale = 1.05f;
	float s = scale;
	for(;1;)
	{
		x0 = (int)(windowSize.x * s);
		y0 = (int)(windowSize.y * s);
		if(x0 > x || y0 > y)
		{
			return size;
		}
		size.x = x0;
		size.y = y0;
		s *= scale;
	}
	return size;/**/
#endif
	

}
int IICacheHelper::FindBestControlGI(int x,int y)
{
	for(int i = 0; i < 64; i ++)
	{
		if(geometryRefTable[i].winSize.x <= x && geometryRefTable[i].winSize.y <= y)
		{
			if((x + y -geometryRefTable[i].winSize.x - geometryRefTable[i].winSize.y ) <= geometryRefTable[i].blockStride.x / 2)
				return i;
		}
	}
	return -1;
}
void IICacheHelper::CacheImage(ImageInfo* imagePtr,GeometryInfo& gi)
{
	m_pHogDescriptor->ComputerGradient(imagePtr);
	iiWidth = imagePtr->width;
	iiHeight = imagePtr->height;
	GenerateGeometryInfo();
	GenerateIntegralImages();
	CacheSpecialHist(gi);
}
void IICacheHelper::CacheSpecialHist(GeometryInfo& gi)
{
	float* pt = pFullHisCacheData;
	int cx = 0;
	int cy = 0;

	cx = 0;
	for (int x = 0; x <= iiWidth - gi.blockSize.x; x += gi.cacheStride.x)
	{
		cx ++;
		cy = 0;
		for (int y = 0; y <= iiHeight - gi.blockSize.y; y += gi.cacheStride.y)
		{
#ifdef _DSP_OPT_
			GetDspBlockHist(x,y,gi,pt);
#else
			GetBlockHist(x,y,gi,pt);
#endif
		//	GetBlockHist(x,y,gi,pt);
			pt += blockHistSize;
			cy ++;
		}
	}
}
void IICacheHelper::Compute2(ImageInfo* imagePtr,float* descriptor)
{
	int id = FindBestControlGI(imagePtr->width,imagePtr->height);
	if(id == -1)
		return;
	GeometryInfo gi = geometryRefTable[id];

	CacheImage(imagePtr,gi);
	const float* ptr = 0;

	for (int i = 0; i < m_pHogDescriptor->GetDescriptorSize();i ++)
	{
		descriptor[i] = pFullHisCacheData[i];
	}

}
bool IICacheHelper::Compute(ImageInfo* imagePtr,float* descriptor)
{
	//if(imagePtr->width != m_pHogDescriptor->windowSize.x || imagePtr->height != m_pHogDescriptor->windowSize.y)
		//return;
	if (imagePtr->width > m_pHogDescriptor->maxImageSize.x
		|| imagePtr->height > m_pHogDescriptor->maxImageSize.y)
	{
		return false;
	}
//#define _BEST_GI_
	CacheImage(imagePtr);
#ifdef _BEST_GI_
	int id = FindBestGI(imagePtr->width,imagePtr->height);
	if(id == -1)
		return false;
	GeometryInfo gi = geometryData[id];
#else
	GeometryInfo gi = geometryData[0];
#endif
	const float* ptr = 0;
	
	int index = 0;
	for(int i = 0; i <= gi.winSize.x - gi.blockSize.x; i += gi.blockStride.x)
	{
		for (int j = 0; j <= gi.winSize.y - gi.blockSize.y; j += gi.blockStride.y)
		{
			ptr = GetBlockHist(gi,i,j);
			for (int k = 0; k < blockHistSize; k ++)
			{
				descriptor[index ++] = ptr[k];
			}
		}
	}

	/*int len = m_pHogDescriptor->GetDescriptorSize();
	float s = m_pHogDescriptor->hyperPanelVector[len];
	float* svm = m_pHogDescriptor->hyperPanelVector;
	for (int i = 0; i < len;i ++)
	{
		s += svm[i]* descriptor[i];
	}
	if(s < 0)
	{
		s = 0;
	}*/
	return true;
}
void IICacheHelper::Detect(ImageInfo* imagePtr,RegionList*& pList)
{

	CacheImage(imagePtr);
	for (int s = 0; s < scaleCount; s ++)
	{
		RegionList* hitList = 0;
		Detect(s,hitList);
		if(hitList)
		{
			if(pList == 0)
				pList = hitList;
			else
			{
				RegionList* p = pList;
				while(p->next)
					p = p->next;
				p->next = hitList;

			}
		}
	}
}
void IICacheHelper::CacheFullHist()
{
	float* pt = pFullHisCacheData;
	//static float histBuffer[256];
	GeometryInfo gi;
	int cx = 0;
	int cy = 0;


	for(int i = 0; i < scaleCount; i ++)
	{
		gi = geometryData[i];

		cx = 0;
		for (int x = 0; x <= iiWidth - gi.blockSize.x; x += gi.cacheStride.x)
		{
			cx ++;
			cy = 0;
			for (int y = 0; y <= iiHeight - gi.blockSize.y; y += gi.cacheStride.y)
			{
				GetBlockHist(x,y,gi,pt);
				pt += blockHistSize;

				cy ++;
			}
		}

		//ASSERT(pt - pFullHisCacheData == geometryData[i + 1].histCacheOffset);
	}
}
const float* IICacheHelper::GetBlockHist(GeometryInfo& gi,int x,int y)
{
	float* pt = pFullHisCacheData + gi.histCacheOffset;
	int cx = x / gi.cacheStride.x;
	int cy = y / gi.cacheStride.y;

	return pt + (cx * gi.cacheGrid.y + cy) * blockHistSize;
}