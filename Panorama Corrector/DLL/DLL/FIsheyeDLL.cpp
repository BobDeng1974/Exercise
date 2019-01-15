#include "FisheyeDLL.h"

Mat fisheye2pano2(const Mat& img)
{
	int midy = img.rows / 2;	//列
	int midx = img.cols / 2;	//行
	int maxmag = (midy > midx ? midy : midx);
	int circum = 2 * M_PI * maxmag;

	int wd = circum;
	int hd = maxmag;

	Mat pano(hd, wd, img.type());
	Mat xmap(pano.size(), CV_32FC1);
	Mat ymap(pano.size(), CV_32FC1);
	for (int i = 0; i < pano.rows; i++) //height
	{
		float* _xmap = xmap.ptr<float>(i);
		float* _ymap = ymap.ptr<float>(i);
		for (int j = 0; j < pano.cols; j++)//width
		{
			double theta = 1.0 * j / maxmag;
			double mag = (pano.rows - (maxmag - i));
			//double mag = i - maxmag;
			*_xmap++ = static_cast<float>(midx + mag * sin(theta));
			*_ymap++ = static_cast<float>(midy + mag * cos(theta));
		}
	}
	remap(img, pano, xmap, ymap, CV_INTER_LINEAR);

	//视频时注释以下三行
	cv::imwrite("pano.bmp", pano);
	imshow("fisheye2pano2", pano);
	waitKey();

	return pano;
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

	//写入测试

	//saveBitmap(bmpimage.cols, bmpimage.rows, &buff[0], bmpimage.rows*bmpimage.cols * 3);

	//char* bmpDestest = "fisheye3resFWrite.bmp";
	//FILE* pFile3 = fopen(bmpDestest, "w+");
	////fseek(pFile3, 0, SEEK_END);
	//long lSize3 = buff.size();
	////rewind(pFile3);
	////char* pData3 = new char[lSize3];
	////fwrite(pData3, sizeof(char), lSize3, pFile3);
	//uchar* pData3 = new uchar[lSize3];

	////for (int i = 0; i <= lSize3; i++) {
	////	pData3[i] = buff[i];
	////}	

	////rewind(pFile3);
	////fwrite(encode_data, 1, lSize3 * sizeof(uchar), pFile3);
	//fwrite(encode_data, sizeof(uchar), buff.size(), pFile3);
	////fwrite(&buff[0], sizeof(uchar), lSize3, pFile3);
	////fwrite(&vec[0], 1, vec.size() * sizeof(index), fp);
	//fclose(pFile3);





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

	//写入
	//char* bmpDes = "fisheye3res.bmp";
	//FILE* pFile2 = fopen(bmpDes, "w+");
	//fseek(pFile2, 0, SEEK_END);
	//long lSize2 = ftell(pFile2);
	//rewind(pFile2);
	//fwrite(pData2, sizeof(char), lSize2, pFile2);
	//fclose(pFile2);
}