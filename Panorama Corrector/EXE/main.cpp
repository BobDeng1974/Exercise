#include "head.h"

Mat fisheye2pano(const Mat& img)
{

	int Cx = img.cols / 2;
	int Cy = img.rows / 2;
	// iner and outer radius
	float R1, R2;
	//	R1 = img.cols / 6.0;
	//	R2 = img.cols / 2.0;
	R1 = img.cols / 60.0;
	R2 = img.cols / 2.0;

	// source and destination image sizes
	int Wd = 2.0 * ((R2 + R1) / 2) * M_PI;
	int Hd = R2 - R1;
	int H = Wd / 2;

	int Ws = img.cols;
	int Hs = img.rows;
	//Mat pano(Hd, Wd, img.type());
	Mat pano(H, Wd, img.type());
	// specify maps for transforming the source image
	Mat xmap(pano.size(), CV_32FC1);
	Mat ymap(pano.size(), CV_32FC1);
	for (int i = 0; i < pano.rows; i++) {
		float* _xmap = xmap.ptr<float>(i);
		float* _ymap = ymap.ptr<float>(i);
		for (int j = 0; j < pano.cols; j++) {
			// 	[r theta] coordinates in the fisheye image
			float r = float(i) / float(Hd) * (R2 - R1) + R1;
			float theta = float(j) / float(Wd) * 2.0 * M_PI;
			*_xmap++ = static_cast<float>(Cx + r * sin(theta));
			*_ymap++ = static_cast<float>(Cy + r * cos(theta));
		}
	}

	// apply a generic geometrical transformation
	remap(img, pano, xmap, ymap, CV_INTER_LINEAR);

	//视频时注释以下三行
	//cv::imwrite("pano60.bmp", pano);
	//imshow("fisheye2pano", pano);
	//waitKey();


	return pano;
}

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
	//cv::imwrite("pano.bmp", pano);
	//imshow("fisheye2pano2", pano);
	//waitKey();

	return pano;
}


void EXE() {
	system("FishVideo.exe");
}
int main()
{
	//鱼眼矫正
	//Mat img = imread("fisheye3.bmp");
	//Mat img = imread("CBMPSave.bmp");
	//imshow("img", img);
	//waitKey();
	//fisheye2pano2(img);

	//四分屏
	//FisheyeRect();
	//Pictures();

	thread t(EXE);
	t.detach();
	Video();
	t.~thread();
	
	
	//Mat img = imread("fisheye3.bmp");
	//Panorama_Four(img);
	//Panorama_Four_Video();

	//测试bmp函数
	//BMPCodeTest();

	//最终版本
	//BMP传入参数
	//readBmp("fisheye3.bmp");
	//Fish2PanoAccess();

	//bmp函数
	//testBmpFunc();

	//仅图像
	//Video();

	//整合录音功能
	//VideoAndSound();

	//拼接视频
	//system("ffmpeg - f concat - i filelist.txt - c copy output.avi");
	//system("ffmpeg - i "concat : Video.avi|VideoTest.avi" - c copy output.mkv");
	//system("ffmpeg - i "concat:input1.mpg | input2.mpg | input3.mpg" - c copy output.mpg")
	//ffmpeg - i concat : "intermediate1.mpg|intermediate2.mpg" - c copy intermediate_all.mpg

	//删除全局变量
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;

	cv::destroyAllWindows();
	//system("pause");
	return 0;
}