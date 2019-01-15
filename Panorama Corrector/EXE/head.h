#include <math.h>
#include <iostream>
#include <iterator>
#include <opencv2/opencv.hpp>
#include <vector>
#include <Windows.h>
#include "stdio.h"  
#include "string.h"  
#include "malloc.h"

#include <thread>

using namespace std;
using namespace cv;

#define M_PI 3.1415926

Mat fisheye2pano(const Mat& img);
Mat fisheye2pano2(const Mat& img);

//��Ƶ
void Video();
void VideoAndSound();

void StartRecord();
void StopRecord();
void SaveRecord();
void Encode();

//BMP
void Fish2PanoAccess();
void Fish2Pano(char* bmpSrc, int srcSize, char* bmpOut, int outSize);

//CBMP
bool readBmp(char *bmpName);
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable);

extern unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��  
extern int bmpWidth;//ͼ��Ŀ�  
extern int bmpHeight;//ͼ��ĸ�  
extern RGBQUAD *pColorTable;//��ɫ��ָ��  
extern int biBitCount;//ͼ�����ͣ�ÿ����λ��

//�ķ���
void ManyImages(vector<Mat> Images, Mat& dst, int imgRows);
void Pictures();
//int Panorama_Four();
Mat Panorama_Four(Mat src);
void Panorama_Four_Video();