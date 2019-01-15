#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>

#define M_PI 3.1415926

using namespace std;
using namespace cv;

Mat fisheye2pano2(const Mat& img);

//导出DLL
extern "C" _declspec(dllexport) void Fish2PanoAccess();

void Fish2Pano(char* bmpSrc, int srcSize, char* bmpOut, int outSize);

bool readBmp(char *bmpName);
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable);

extern unsigned char *pBmpBuf;//读入图像数据的指针  
extern int bmpWidth;//图像的宽  
extern int bmpHeight;//图像的高  
extern RGBQUAD *pColorTable;//颜色表指针  
extern int biBitCount;//图像类型，每像素位数  