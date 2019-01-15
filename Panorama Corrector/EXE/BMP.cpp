#include "head.h"

int Fish2Pano_BMP(char *bmpSrc, char *bmpOut)
{
	//Mat img = imreadbuff(bmpSrc);
	return 0;
}

//TEST
void testBmpFunc() {
	///读取pano.bmp到内存 c
	//FILE* fp;	//文件指针
	//char *bmpSrc = NULL;
	//fp=fopen("pano.bmp","r+");
	//int fileSize = fseek(...);
	////fseek(...);
	//bmpSrc = new char(fileSize);
	//fread(bmpSrc,);
	//char *bmpOut;
	//Fish2Pano_BMP(bmpSrc, bmpOut);

	//以二进制方式读取图片到内存
	std::ifstream file("fisheye3.bmp", std::ios::binary);
	std::vector<char> data;
	file >> std::noskipws;
	std::copy(std::istream_iterator<char>(file), std::istream_iterator<char>(), std::back_inserter(data));
	Mat frame = imdecode(Mat(data), CV_LOAD_IMAGE_COLOR);
	file.close();

	//矫正前
	imshow("srcbmp", frame);
	waitKey();
	cv::destroyAllWindows();


	//矫正后
	//Mat result;
	//result=fisheye2pano2(frame);
	//imshow("fisheye result", result);
	//waitKey();

	//编码
	//vector<unsigned char> img_encode;
	//cv::imencode(".jpg", frame, img_encode);
	//unsigned char *encode_data = new unsigned char[lSize];
	//for (int i = 0; i<lSize; i++) {
	//	encode_data[i] = img_encode[i];
}

void BMPCodeTest() {
	string fname = "fisheye3.jpg";
	//! 以二进制流方式读取图片到内存
	//FILE* pFile = fopen(bmpSrc, "rb");
	FILE* pFile = fopen(fname.c_str(), "rb");

	//测出文件大小
	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	char* pData = new char[lSize];
	//读入
	fread(pData, sizeof(char), lSize, pFile);
	fclose(pFile);

	//! 解码内存数据，变成cv::Mat数据
	cv::Mat img_decode;
	vector<uchar> data;
	for (int i = 0; i < lSize; ++i) {
		data.push_back(pData[i]);
	}
	img_decode = cv::imdecode(data, CV_LOAD_IMAGE_COLOR);
	cv::flip(img_decode, img_decode, -1);
	img_decode.channels();
	imshow("img_decode", img_decode);
	waitKey();

	//鱼眼矫正
	Mat result;
	result = fisheye2pano2(img_decode);
	imwrite("result.jpg", result);
	imshow("fisheye result", result);
	waitKey();

	//! 将cv::Mat数据编码成数据流
	vector<unsigned char> img_encode;
	cv::imencode(".jpg", result, img_encode);
	unsigned char *encode_data = new unsigned char[lSize];
	for (int i = 0; i<lSize; i++) {
		encode_data[i] = img_encode[i];
	}

	Mat temp = cv::imdecode(img_encode, CV_LOAD_IMAGE_COLOR);

	imwrite("imwrite.jpg", temp);
	imshow("jpg", temp);
	waitKey();

	//写入磁盘
	//	FILE *fpw = fopen("patch.jpg", "wb");
	//if (fpw == NULL)
	//{
	//	cout << "Open error!" << endl;
	//	fclose(fpw);
	//	return;
	//}

	//int labelw = 1;
	//int rows = temp.rows;
	//int cols = temp.cols;

	//fwrite(&labelw, sizeof(char), 1, fpw);

	//char* dp = (char*)temp.data;
	//for (int i = 0; i<rows*cols; i++)
	//{
	//	fwrite(&dp[i * 3], sizeof(char), 1, fpw);
	//	fwrite(&dp[i * 3 + 1], sizeof(char), 1, fpw);
	//	fwrite(&dp[i * 3 + 2], sizeof(char), 1, fpw);
	//}
	//fclose(fpw);
}

void Fish2PanoAccess() {
	char* bmpSrc = "fisheye3.bmp";
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

	Fish2Pano(pData, lSize, pData2, lSize);

	saveBmp("CBMPSave.bmp", pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
}

void Fish2Pano(char* bmpSrc, int srcSize, char* bmpOut, int outSize) {
	//! 解码内存数据，变成cv::Mat数据
	cv::Mat img_decode;
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
	imshow("img_decode-BMP原图", img_decode);
	waitKey();

	//鱼眼矫正
	Mat result;
	result = fisheye2pano2(img_decode);
	imwrite("BMP result-矫正后图像.jpg", result);
	imshow("BMP result-矫正后图像", result);
	waitKey();

	//编码——BMP
	vector<uchar> buff;//buffer for coding
					   //vector<int> param = vector<int>(2);
					   //param[0] = CV_IMWRITE_JPEG_QUALITY;
					   //param[1] = 95;//default(95) 0-100

					   //imencode(".bmp", result, buff, param);
	imencode(".bmp", result, buff);
	//cout << "coded file size(bmp)" << buff.size() << endl;//fit buff size automatically.
	Mat bmpimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
	imwrite("bmp-矫正编码后图像.bmp", bmpimage);
	imshow("bmp-矫正编码后图像", bmpimage);
	waitKey();

	//fread(,,,)
	readBmp("bmp-矫正编码后图像.bmp");
	system("pause");
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