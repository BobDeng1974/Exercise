#include "head.h"

void Video() {
	VideoCapture capture;
	//capture.open("rtsp://admin:admin12345@192.168.1.65/Streaming/Channels/1");	//摄像头1
	//capture.open("rtsp://root:pass@192.168.1.141:554/axis-media/media.amp");		//	摄像头2
	//capture.open("rtsp://service:@10.153.33.11/?line=1$camera");	//邓大伟 左泽
	string s = "rtsp://admin:admin12345@192.168.1.65/Streaming/Channels/1";
	capture.open(s);
	//capture.open(0);														//open 根据编号打开摄像头

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
		imshow("Video", frame);

		//鱼眼矫正后 鱼眼摄像头卡顿很严重 前置摄像头不卡顿
		//frame = fisheye2pano2(frame);
		//imshow("FisheyeVideo", frame);

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

void VideoAndSound() {
	VideoCapture capture;
	//capture.open("rtsp://admin:admin12345@192.168.1.65/Streaming/Channels/1");	//摄像头1
	capture.open("rtsp://root:pass@192.168.1.141:554/axis-media/media.amp");		//	摄像头2
																					//capture.open("rtsp://service:@10.153.33.11/?line=1$camera");					//邓大伟	左泽
																					//capture.open(0);																//open 根据编号打开摄像头
																					//AVI or ASF
																					// MPEG4 CV_FOURCC('D', 'I', 'V', 'X')
																					// MJPG  CV_FOURCC('M', 'J', 'P', 'G')
	VideoWriter writer("VideoTestDemo.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30.0, Size(640, 480));

	std::cout << "-------------" << std::endl;
	if (!capture.isOpened())
	{
		std::cout << "Read video Failed !" << std::endl;
		return;
	}

	//cv::VideoCapture capture;

	cv::Mat frame;
	cv::namedWindow("video test");

	int frame_num = 800;

	//开始录音
	StartRecord();

	//for (;;) {
	//	if (!capture.read(frame)) {
	//		std::cout << "No frame" << std::endl;
	//		cv::waitKey();
	//	}
	//	writer << frame;
	//	cv::imshow("Output Window", frame);
	//	if (cv::waitKey(1) >= 0) break;
	//}

	for (int i = 0; i < frame_num - 1; ++i)
	{
		capture >> frame;
		capture.read(frame);

		//鱼眼矫正前
		imshow("video test", frame);
		writer << frame;

		//鱼眼矫正后 视频存储和录音会有问题
		//writer << fisheye2pano2(frame);
		//frame = fisheye2pano2(frame);
		//imshow("fisheyevideo test", frame);

		if (cv::waitKey(30) == 'q')
		{
			break;
		}
	}

	//保存音频
	StopRecord();
	SaveRecord();

	cv::destroyWindow("video test");
	//cv::destroyAllWindows();
	capture.release();

	Encode();
}

//合并视频和音频
void Encode() {
	system("ffmpeg -i VideoTestDemo.avi -i SoundDemo.wav -vcodec mpeg4 -acodec copy Video.avi");
}