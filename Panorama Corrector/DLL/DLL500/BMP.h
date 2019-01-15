#pragma once
#include "stdafx.h"

extern int BMPLSize;
extern char* pData;
extern Mat img_decode;

void Fish2PanoAccess(char* BMPSrc);
void Fish2Pano(char* bmpSrc, int srcSize);