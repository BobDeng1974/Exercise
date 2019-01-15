#include "stdafx.h"
#include "BMP.h"

int BMPLSize = 0;
char* pData = NULL;
Mat img_decode;

void Fish2PanoAccess(char* BMPSrc) {
	//char* bmpSrc = "fisheye3.bmp";
	char* bmpSrc = BMPSrc;
	//string fname = "fisheye3.jpg";
	//! 以二进制流方式读取图片到内存
	FILE* pFile = fopen(bmpSrc, "rb");
	//FILE* pFile = fopen(fname.c_str(), "rb");

	//测出文件大小
	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	char* pData = new char[lSize];
	//读入
	fread(pData, sizeof(char), lSize, pFile);
	//测试fread后直接fwrite
	//FILE* p = fopen("123.bmp", "w+");
	//fwrite(pData, sizeof(char), lSize, p);
	fclose(pFile);
	//读取原图完毕

	char* pData2 = new char[lSize];

	Fish2Pano(pData, lSize);

	//saveBmp("CBMPSave.bmp", pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
}

void Fish2Pano(char* bmpSrc, int srcSize) {
	//! 解码内存数据，变成cv::Mat数据
	//cv::Mat img_decode;
	//vector<uchar> data;
	vector<uchar> data;
	for (int i = 0; i < srcSize; ++i) {
		data.push_back(bmpSrc[i]);
	}
	//for (int i = 0; i < lSize; ++i) {
	//	data.push_back(pData[i]);
	//}
	img_decode = cv::imdecode(data, CV_LOAD_IMAGE_COLOR);
	cv::flip(img_decode, img_decode, -1);
	//参数：
	//src:原图像。
	//dst : 翻转后的图像
	//flipCode：翻转代码，int型。0代表垂直翻转，1代表水平翻转，－1代表垂直和水平翻转。
	img_decode.channels();	//啥也没做
	//imshow("img_decode-BMP原图", img_decode);
	//waitKey();

	//img_decode.copyTo(Src);

	////鱼眼矫正
	//Mat result;
	////result = fisheye2pano2(img_decode);
	//imwrite("BMP result-矫正后图像.jpg", result);
	//imshow("BMP result-矫正后图像", result);
	//waitKey();

	////编码——BMP
	//vector<uchar> buff;//buffer for coding
	//				   //vector<int> param = vector<int>(2);
	//				   //param[0] = CV_IMWRITE_JPEG_QUALITY;
	//				   //param[1] = 95;//default(95) 0-100

	//				   //imencode(".bmp", result, buff, param);
	//imencode(".bmp", result, buff);
	////cout << "coded file size(bmp)" << buff.size() << endl;//fit buff size automatically.
	//Mat bmpimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
	//imwrite("bmp-矫正编码后图像.bmp", bmpimage);
	//imshow("bmp-矫正编码后图像", bmpimage);
	//waitKey();

	////fread(,,,)
	//readBmp("bmp-矫正编码后图像.bmp");
	//system("pause");
	//输出图像的信息  
	//printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	//将图像数据存盘  
	//saveBmp("CBMPSave.bmp", pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//saveBmp(bmpOut, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);



	//编码——JPEG
	//vector<uchar> buff;//buffer for coding
	//vector<int> param = vector<int>(2);
	//param[0] = CV_IMWRITE_JPEG_QUALITY;
	//param[1] = 95;//default(95) 0-100

	//imencode(".jpg", result, buff, param);
	//cout << "coded file size(jpg)" << buff.size() << endl;//fit buff size automatically.
	//Mat jpegimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
	//imshow("jpeg", jpegimage);
	//waitKey();
}