/*----------------Copyright @Kuo Chen 2016----------------*/

/*----------------Copyright @Wei Wang 2017----------------*/
//1。计算正向矫正过程 鱼眼图像 矫正后 矫正图片的 长宽
//2。计算矫正投影矩阵 （remap逆向投影过程）创建矫正后图片逆向（三维投影、三维旋转、三维恢复、投影二维）求得鱼眼图片
//3。remap 获得矫正图片
#include <stdio.h>
#include "parameters.h"
#include "subfunction.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat Panorama_Four(Mat src) {
	//Read the input image
	//cv::Mat img = cv::imread("fisheye3.bmp");
	Mat img = src;
	//cv::imshow("show", img);
	//cvWaitKey();

	/*int orix = std::max(int(cx - RR), 0);
	int oriy = std::max(int(cy - RR), 0);
	int endx = std::min(int(orix + 2 * RR), img.cols);
	int endy = std::min(int(oriy + 2 * RR), img.rows);
	img = img(cv::Rect(orix, oriy, endx - orix, endy - oriy));
	cx = cx - orix;
	cy = cy - oriy;*/

	//calculate the projection of the sub_view
	//pos1 为三维单元球坐标中特征点（共三个特征点确定一个扇形区域范围），与x轴的夹角（cols）
	//pos2 与z轴的夹角
	float pos1[] = { thetamax, thetamax,  thetamin };
	float pos2[] = { PI / 2 - PI / views, PI / 2, PI / 2 };
	float paras[] = { 0, 0 };
	cal_subview(pos1, pos2, paras);


	//calculate the point vectors
	std::vector<float> tphi, points;
	for (int i = 0; i <= views; i++)
	{
		if (i<views)
			tphi.push_back(i * 2 * PI / views);
		else
			tphi.push_back(tphi.at(0) + 2 * PI);
		if (i>0)
			points.push_back((tphi.at(i - 1) + tphi.at(i)) / 2);
	}


	//calculate the mapping matrix
	int row = int(2 * paras[1]);
	int col = int(2 * paras[0]);
	cv::Mat mapx1(row, col, CV_32FC1, cv::Scalar(0));
	cv::Mat mapy1(row, col, CV_32FC1, cv::Scalar(0));
	cal_mapping(row, col, paras, points, mapx1, mapy1);

	//remap and then save the image
	mapx1 = mapx1 + cx;
	mapy1 = mapy1 + cy;

	//std::string filename = "../Four.xml";
	//cv::FileStorage fs(filename, cv::FileStorage::WRITE);
	//fs << "mapx" << mapx1;
	//fs << "mapy" << mapy1;
	//fs.release();

	/*
	cv::Mat mapx1, mapy1;
	std::string filename = "/home/chenkuo/Desktop/Four/Four.xml";
	cv::FileStorage fs(filename, cv::FileStorage::READ);
	fs["mapx"] >> mapx1;
	fs["mapy"] >> mapy1;
	fs.release();
	*/
	cv::Mat nimg1;
	cv::remap(img, nimg1, mapx1, mapy1, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	//cv::imshow("Panorama", nimg1);
	//cv::waitKey();

	//cv::imwrite("../result.jpg", nimg1);
	//cv::imwrite("Panoramares.bmp", nimg1);

	//cv::waitKey(0);
	return nimg1;
}

void Panorama_Four_Video() {
	VideoCapture capture;
	//capture.open("rtsp://admin:admin12345@192.168.1.65/Streaming/Channels/1");	//摄像头1
	//capture.open("rtsp://root:pass@192.168.1.141:554/axis-media/media.amp");		//	摄像头2
	//capture.open("rtsp://service:@10.153.33.11/?line=1$camera");				//邓大伟 左泽
	capture.open(0);															//open 根据编号打开摄像头

	cout << "-------------" << std::endl;
	if (!capture.isOpened())
	{
		cout << "Read video Failed !" << endl;
		return;
	}

	//cv::VideoCapture capture;

	Mat frame;
	//cv::namedWindow("video test");

	int frame_num = 800;

	for (int i = 0; i < frame_num - 1; ++i)
	{
		capture >> frame;
		capture.read(frame);

		//鱼眼矫正前
		//imshow("Video", frame);

		//鱼眼矫正后 鱼眼摄像头卡顿很严重 前置摄像头不卡顿
		frame = Panorama_Four(frame);
		imshow("FisheyeVideo", frame);

		if (waitKey(30) == 'q')
		{
			break;
		}
	}

	//cv::destroyWindow("video test");
	cv::destroyAllWindows();
	capture.release();

	//system("pause");
}