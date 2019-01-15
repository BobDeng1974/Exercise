#include "head.h"

void FisheyeRect() {
	Mat img = imread("fisheye3.jpg");
	namedWindow("bmp", CV_WINDOW_AUTOSIZE);
	imshow("bmp", img);
	waitKey();
	destroyWindow("bmp");

	Mat res = fisheye2pano2(img);
	namedWindow("res", CV_WINDOW_NORMAL);
	imshow("res", res);
	//imshow("res123", res);
	waitKey();

	Rect rect(0, 0, 5000, 500);
	Mat image_roi = res(rect);
	imwrite("roi1.bmp", image_roi);
	namedWindow("roi", CV_WINDOW_NORMAL);
	imshow("roi", image_roi);
	waitKey(0);
}

void ManyImages(vector<Mat> Images, Mat& dst, int imgRows)
{
	int Num = Images.size();//得到Vector容器中图片个数
							//设定包含这些图片的窗口大小，这里都是BGR3通道，如果做灰度单通道，稍微改一下下面这行代码就可以
	Mat Window(500 * ((Num - 1) / imgRows + 1), 800 * imgRows, CV_8UC3, Scalar(0, 0, 0));
	//Mat Window(300 * ((Num - 1) / imgRows + 1), 300 * imgRows, CV_8UC3, Scalar(0, 0, 0));
	Mat Std_Image;//存放标准大小的图片
	Mat imageROI;//图片放置区域
	Size Std_Size = Size(800, 500);//每个图片显示大小300*300
								   //Size Std_Size = Size(300, 300);
	int x_Begin = 0;
	int y_Begin = 0;
	for (int i = 0; i < Num; i++)
	{
		x_Begin = (i % imgRows)*Std_Size.width;//每张图片起始坐标
		y_Begin = (i / imgRows)*Std_Size.height;
		resize(Images[i], Std_Image, Std_Size, 0, 0, INTER_LINEAR);//将图像设为标准大小
																   //将其贴在Window上
		imageROI = Window(Rect(x_Begin, y_Begin, Std_Size.width, Std_Size.height));
		Std_Image.copyTo(imageROI);
	}
	dst = Window;
}

void Pictures() {
	//VideoCapture cap1;
	//cap1.open(0);

	VideoCapture cap2;
	//cap2.open("rtsp://admin:admin12345@192.168.1.65/Streaming/Channels/1");	//摄像头1
	//cap2.open("rtsp://root:pass@192.168.1.141:554/axis-media/media.amp");	//摄像头2
	//cap2.open("rtsp://admin:ytkj123456@10.153.26.11/h264/ch1/main/av_stream");
	//capture.open("rtsp://service:@10.153.33.11/?line=1$camera");
	cap2.open("rtsp://administrator:123.com@10.153.25.4/?line=1$camera");		//服务器
	cap2.open(0);

	int temp1 = 300, temp2 = 300, temp3 = 10, temp4 = 10;

	while (true) {
		Mat img_1;
		Mat img_2;
		//cap1 >> img_1;
		//cap1.read(img_1);

		cap2 >> img_2;
		cap2.read(img_2);

		//Mat img_1 = imread("fisheye3.jpg");
		//Mat img_2 = imread("roi1.bmp");

		img_1 = fisheye2pano2(img_2);

		//Mat img_3 = imread("fisheye3.jpg");
		//Mat img_4 = imread("fisheye3.jpg");

		//截取
		//Rect rect_3(0, 0, 300, 300);
		Rect rect_3(20, 20, temp1, temp2);
		//temp1 += 1; temp2 += 1;

		Mat img_3 = img_1(rect_3);
		//Rect rect_4(10, 10, 300, 300);
		Rect rect_4(temp3, temp4, 300, 300);
		//temp3 += 1; //temp4 += 1;
		Mat img_4 = img_1(rect_4);

		Mat dst;
		vector<Mat> manyimgV;
		manyimgV.push_back(img_1);
		manyimgV.push_back(img_2);
		manyimgV.push_back(img_3);
		manyimgV.push_back(img_4);

		//thread t1(ManyImages, manyimgV, dst, 2);
		//t1.join();
		ManyImages(manyimgV, dst, 2);

		//namedWindow("ManyImagesInWindow", CV_WINDOW_AUTOSIZE);
		imshow("ManyImagesInWindow", dst);
		//waitKey(0);

		if (cv::waitKey(3) == 'q')
		{
			break;
		}
		//continue;
	}

	cv::destroyAllWindows();
	//cap1.release();
	cap2.release();

	system("pause");
	//备注：运行速度：约960ms，95%时间用在resize上
}