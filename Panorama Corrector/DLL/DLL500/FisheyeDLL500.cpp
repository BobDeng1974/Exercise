// FisheyeDLL500.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FisheyeDLL500.h"

FisheyeImgCorrect FIC;

int main()
{
	DLL500main();
	return 0;
}

int DLL500main() {
	//char* strsrc = "fisheye3.bmp";
	char* strsrc = "test2.bmp";
	
	//char* outname = "fisheyeout.bmp";
	char* outname = "out-123.bmp";
	readBmp(strsrc);
	int w = bmpWidth;
	int h = bmpHeight;
	int ang1 = 50;
	int ang2 = 50;
	int ang3 = 50;

	int Srcw = 300;
	int Srch = 300;

	int outw = 0, outh = 0;
	BMP500(strsrc, w, h, ang1, ang2, ang3, Srcw, Srch, outname, outw, outh);

	return 0;
}

void BMP500(char * bmpsrc, int width, int height, int ang1, int ang2, int ang3, int ToW,int ToH,char * bmpOut, int& outwidth, int& outheight)	{
	//readBmp(bmpsrc);
	Mat Src;
	Fish2PanoAccess(bmpsrc);
	img_decode.copyTo(Src);
	imshow("BMPSrc", Src);
	waitKey();
	//原图读取已完毕

	//直接内存数据转换成Mat
	//void Fish2Pano(char* bmpSrc, int srcSize);
	//vector<uchar> data;
	//for (int i = 0; i < srcSize; ++i) {
	//	data.push_back(bmpSrc[i]);
	//}
	//img_decode = cv::imdecode(data, CV_LOAD_IMAGE_COLOR);
	//cv::flip(img_decode, img_decode, -1);
	//img_decode.channels();

	//int size = width*height * 3;

	//BITMAPFILEHEADER fileheader;
	//fileheader.bfType = 0x4D42;
	//fileheader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;
	//fileheader.bfReserved1 = 0;
	//fileheader.bfReserved2 = 0;
	//fileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//BITMAPINFOHEADER infoheader;

	//infoheader.biSize = 40;
	//infoheader.biWidth = width;
	//infoheader.biHeight = height;
	//infoheader.biPlanes = 1;
	//infoheader.biBitCount = 24;
	//infoheader.biCompression = BI_RGB;
	//infoheader.biSizeImage = 0;
	//infoheader.biXPelsPerMeter = 0;
	//infoheader.biYPelsPerMeter = 0;
	//infoheader.biClrUsed = 0;
	//infoheader.biClrImportant = 0;


	//vector<uchar> data;

	//for (int i = 0; i < sizeof(BITMAPFILEHEADER); ++i) {
	//	data.push_back(((char *)&fileheader)[i]);
	//}

	//for (int i = 0; i < sizeof(BITMAPINFOHEADER); ++i) {
	//	data.push_back(((char *)&infoheader)[i]);
	//}

	//for (int i = 0; i < size; ++i) {
	//	data.push_back(data[i]);
	//}
	//img_decode = cv::imdecode(data, CV_LOAD_IMAGE_COLOR);
	//cv::flip(img_decode, img_decode, -1);
	//img_decode.channels();	//啥也没做
	//imshow("img_decode-BMP原图", img_decode);
	//waitKey();


	int flag = 0;

	Mat Dst1, Dst2, Dst3;
	//FisheyeImgCorrect FIC;
	FIC.FisheyeImgCorrectInit();
	FIC.Flag = 1;

	//三个角度
	FIC.phi1 = ang1;
	FIC.phi1 = FIC.phi1*3.14159265 / 180;
	FIC.sita1 = ang2;
	FIC.sita1 = (90 - FIC.sita1)*3.14159265 / 180;
	FIC.gama1 = ang3;
	FIC.gama1 = FIC.gama1*3.14159265 / 180;

	FIC.w = ToW;
	FIC.h = ToH;

	ScanningMethod SM;

	if (flag == 0)
	{
		//myTrace.WriteToLog(" frec.s :");
		SM.FindDeviceArea(Src);
		flag = 1;
	}
	//SM.FindDeviceArea(Src);

	Mat tempImg = Src(SM.minArea);
	if (FIC.Flag == 1)
	{
		/*clock_t t5 = clock();
		CString time4;
		time4.Format("%d",t5 - t4);
		CString s4 = " scIn.e :"+time4;
		myTrace.WriteToLog(s4.GetBuffer(0));*/
		FIC.FishCalculate(tempImg);
		FIC.FishImgIndex(tempImg);
		FIC.Flag = 0;
	}

	//imshow("tempImg", tempImg);
	//waitKey();

	FIC.ImageCorrect(tempImg, Dst1, Dst2, Dst3);


	//Rect rect(0, 0, Dst2.cols, Dst2.rows);   //创建一个Rect框，属于cv中的类，四个参数代表x,y,width,height
	Rect rect(0, 0, ToW, ToH);
	Mat image_cut = Mat(Dst2, rect);      //从img中按照rect进行切割，此时修改image_cut时image中对应部分也会修改，因此需要copy
	Mat image_copy = image_cut.clone();   //clone函数创建新的图片
	imshow("456", image_copy);
	waitKey();

	//编码成Buff
	vector<uchar> buff;
	imencode(".bmp", Dst1, buff);

	imshow("Dst1", Dst1);
	waitKey();
	imshow("Dst2", Dst2);
	waitKey();
	imshow("Dst3", Dst3);
	waitKey();
	
	imwrite("Dst1.bmp", Dst1);
	readBmp("Dst1.bmp");
	outheight = bmpHeight;
	outwidth = bmpWidth;
	saveBmp(bmpOut, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//imwrite("Dst1.bmp", Dst1);
	//imwrite("Dst1.bmp", Dst1);

	//system("pause");
}
