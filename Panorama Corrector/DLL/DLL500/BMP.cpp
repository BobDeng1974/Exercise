#include "stdafx.h"
#include "BMP.h"

int BMPLSize = 0;
char* pData = NULL;
Mat img_decode;

void Fish2PanoAccess(char* BMPSrc) {
	//char* bmpSrc = "fisheye3.bmp";
	char* bmpSrc = BMPSrc;
	//string fname = "fisheye3.jpg";
	//! �Զ���������ʽ��ȡͼƬ���ڴ�
	FILE* pFile = fopen(bmpSrc, "rb");
	//FILE* pFile = fopen(fname.c_str(), "rb");

	//����ļ���С
	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	char* pData = new char[lSize];
	//����
	fread(pData, sizeof(char), lSize, pFile);
	//����fread��ֱ��fwrite
	//FILE* p = fopen("123.bmp", "w+");
	//fwrite(pData, sizeof(char), lSize, p);
	fclose(pFile);
	//��ȡԭͼ���

	char* pData2 = new char[lSize];

	Fish2Pano(pData, lSize);

	//saveBmp("CBMPSave.bmp", pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
}

void Fish2Pano(char* bmpSrc, int srcSize) {
	//! �����ڴ����ݣ����cv::Mat����
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
	//������
	//src:ԭͼ��
	//dst : ��ת���ͼ��
	//flipCode����ת���룬int�͡�0����ֱ��ת��1����ˮƽ��ת����1����ֱ��ˮƽ��ת��
	img_decode.channels();	//ɶҲû��
	//imshow("img_decode-BMPԭͼ", img_decode);
	//waitKey();

	//img_decode.copyTo(Src);

	////���۽���
	//Mat result;
	////result = fisheye2pano2(img_decode);
	//imwrite("BMP result-������ͼ��.jpg", result);
	//imshow("BMP result-������ͼ��", result);
	//waitKey();

	////���롪��BMP
	//vector<uchar> buff;//buffer for coding
	//				   //vector<int> param = vector<int>(2);
	//				   //param[0] = CV_IMWRITE_JPEG_QUALITY;
	//				   //param[1] = 95;//default(95) 0-100

	//				   //imencode(".bmp", result, buff, param);
	//imencode(".bmp", result, buff);
	////cout << "coded file size(bmp)" << buff.size() << endl;//fit buff size automatically.
	//Mat bmpimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
	//imwrite("bmp-���������ͼ��.bmp", bmpimage);
	//imshow("bmp-���������ͼ��", bmpimage);
	//waitKey();

	////fread(,,,)
	//readBmp("bmp-���������ͼ��.bmp");
	//system("pause");
	//���ͼ�����Ϣ  
	//printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	//��ͼ�����ݴ���  
	//saveBmp("CBMPSave.bmp", pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//saveBmp(bmpOut, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);



	//���롪��JPEG
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