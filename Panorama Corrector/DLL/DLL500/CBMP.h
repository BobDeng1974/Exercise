#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>

bool readBmp(char *bmpName);
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable);

extern unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��  
extern int bmpWidth;//ͼ��Ŀ�  
extern int bmpHeight;//ͼ��ĸ�  
extern RGBQUAD *pColorTable;//��ɫ��ָ��  
extern int biBitCount;//ͼ�����ͣ�ÿ����λ��