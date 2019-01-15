#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>

#define M_PI 3.1415926

using namespace std;
using namespace cv;

Mat fisheye2pano2(const Mat& img);

//����DLL
extern "C" _declspec(dllexport) void Fish2PanoAccess();

void Fish2Pano(char* bmpSrc, int srcSize, char* bmpOut, int outSize);

bool readBmp(char *bmpName);
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable);

extern unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��  
extern int bmpWidth;//ͼ��Ŀ�  
extern int bmpHeight;//ͼ��ĸ�  
extern RGBQUAD *pColorTable;//��ɫ��ָ��  
extern int biBitCount;//ͼ�����ͣ�ÿ����λ��  