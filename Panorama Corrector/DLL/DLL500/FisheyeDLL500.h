#pragma once
#include "stdafx.h"

extern FisheyeImgCorrect FIC;

int DLL500main();
void BMP500(char * bmpsrc, int width, int height, int ang1, int ang2, int ang3, int ToW, int ToH, char * bmpOut, int& outwidth, int& outheight);