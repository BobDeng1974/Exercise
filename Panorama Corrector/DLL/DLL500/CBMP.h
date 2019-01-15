#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>

bool readBmp(char *bmpName);
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable);

extern unsigned char *pBmpBuf;//读入图像数据的指针  
extern int bmpWidth;//图像的宽  
extern int bmpHeight;//图像的高  
extern RGBQUAD *pColorTable;//颜色表指针  
extern int biBitCount;//图像类型，每像素位数