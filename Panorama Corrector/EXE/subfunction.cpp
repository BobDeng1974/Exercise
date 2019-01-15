#include "parameters.h"
#include "subfunction.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


void meshgrid(const cv::Range &xgv, const cv::Range &ygv, cv::Mat &X, cv::Mat &Y)
{
	std::vector<float> t_x, t_y;
	for (int i = xgv.start; i <= xgv.end; i++) t_x.push_back(float(i));
	for (int j = ygv.start; j <= ygv.end; j++) t_y.push_back(float(j));
	cv::repeat(cv::Mat(t_x).t(), t_y.size(), 1, X);
	cv::repeat(cv::Mat(t_y), 1, t_x.size(), Y);
}

void sph2cart(const cv::Mat &phi, const cv::Mat &theta, cv::Mat &x, cv::Mat &y, cv::Mat &z)
{
	for (int j = 0; j < phi.cols; j++)
	for (int i = 0; i < phi.rows; i++)
	{
		if (!(phi.at<float>(i, j) == 0 && theta.at<float>(i, j) == 0))
		{
            // X=COS(phi)*SIN(theta) Y=SIN(phi)*SIN(theta) Z=COS(theta)
			x.at<float>(i, j) = std::sin(theta.at<float>(i, j)) * std::cos(phi.at<float>(i, j) - PI);
			y.at<float>(i, j) = std::sin(theta.at<float>(i, j)) * std::sin(phi.at<float>(i, j) - PI);
			z.at<float>(i, j) = std::cos(theta.at<float>(i, j));
		}
	}
}

void cart2sph(const cv::Mat &x, const cv::Mat &y, const cv::Mat &z, cv::Mat &phi, cv::Mat &theta)
{
	for (int j = 0; j < x.cols; j++)
	for (int i = 0; i < x.rows; i++)
	{
		float r = sqrt(x.at<float>(i, j)*x.at<float>(i, j) + y.at<float>(i, j)*y.at<float>(i, j) + z.at<float>(i, j)*z.at<float>(i, j));
		if (r!=0)
		{
			phi.at<float>(i, j) = atan2(y.at<float>(i, j), x.at<float>(i, j)) + PI;
			theta.at<float>(i, j) = acos(z.at<float>(i, j) / r);
		}
	}
}

void rotate3D(const float &alpha, const float &beta, const float &gamma, cv::Mat &Rx, cv::Mat &Ry, cv::Mat &Rz )
{
	Rx.at<float>(0, 0) = 1; Rx.at<float>(0, 1) = 0;			  Rx.at<float>(0, 2) = 0;
	Rx.at<float>(1, 0) = 0; Rx.at<float>(1, 1) = cos(alpha);  Rx.at<float>(1, 2) = sin(alpha);
	Rx.at<float>(2, 0) = 0; Rx.at<float>(2, 1) = -sin(alpha); Rx.at<float>(2, 2) = cos(alpha);

	Ry.at<float>(0, 0) = cos(beta); Ry.at<float>(0, 1) = 0;	Ry.at<float>(0, 2) = -sin(beta);
	Ry.at<float>(1, 0) = 0;			Ry.at<float>(1, 1) = 1; Ry.at<float>(1, 2) = 0;
	Ry.at<float>(2, 0) = sin(beta); Ry.at<float>(2, 1) = 0; Ry.at<float>(2, 2) = cos(beta);

	Rz.at<float>(0, 0) = cos(gamma);  Rz.at<float>(0, 1) = sin(gamma); Rz.at<float>(0, 2) = 0;
	Rz.at<float>(1, 0) = -sin(gamma); Rz.at<float>(1, 1) = cos(gamma); Rz.at<float>(1, 2) = 0;
	Rz.at<float>(2, 0) = 0;			  Rz.at<float>(2, 1) = 0;		   Rz.at<float>(2, 2) = 1;
}

void cal_subview( float (&pos1)[3], float (&pos2)[3], float (&paras)[2] )
{
    //pos_theta与x轴的夹角（cols），pos_phi与z轴的夹角
	cv::Mat pos_theta(3, 1, CV_32FC1, pos1);
	cv::Mat pos_phi(3, 1, CV_32FC1, pos2);

	cv::Mat pos_x(3, 1, CV_32FC1, cv::Scalar(0));
	cv::Mat pos_y(3, 1, CV_32FC1, cv::Scalar(0));
	cv::Mat pos_z(3, 1, CV_32FC1, cv::Scalar(0));
    //转换为三维 标准球坐标（x，y，z）
	sph2cart(pos_phi, pos_theta, pos_x, pos_y, pos_z );

	cv::Mat Rx(3, 3, CV_32FC1);
	cv::Mat Ry(3, 3, CV_32FC1);
	cv::Mat Rz(3, 3, CV_32FC1);
    //三维旋转，将待经三维投影到 立体空间鱼眼范围中心 三维旋转到 视角线上
	rotate3D(0.0, viewpoint, -PI/2, Rx, Ry, Rz); //获取一定旋转角度的三维旋转矩阵

    //将三维球坐标（x，y，z）分别复制到 stdxyz 矩阵中，进行三维旋转
	cv::Mat stdxyz(pos_x.rows, 3, pos_x.type());
	pos_x.copyTo(stdxyz.col(0));
	pos_y.copyTo(stdxyz.col(1));
	pos_z.copyTo(stdxyz.col(2));

    //进行三维旋转
	stdxyz = stdxyz * Rz * Ry;
    //将三维旋转后的坐标，分别复制给个单独的坐标分量
	stdxyz.col(0).copyTo(pos_x);
	stdxyz.col(1).copyTo(pos_y);
	stdxyz.col(2).copyTo(pos_z);
    //将三维标准球坐标系，转换为三维二角坐标
	cart2sph(pos_x, pos_y, pos_z, pos_phi, pos_theta);

	cv::Mat pos_r(pos_x.rows, pos_x.cols, CV_32FC1);
	//std::cout << pos_x << std::endl;

    //计算二维极坐标
	for (int i = 0; i < pos_r.rows; i++)
		pos_r.at<float>(i, 0) = ratio * f * tanf(pos_theta.at<float>(i, 0));
    //恢复之前三维旋转将与z轴的夹角增加 90度
	pos_phi = pos_phi - PI / 2;
    //极坐标转换为直角坐标
	polarToCart(pos_r, pos_phi, pos_x, pos_y);
    //？
	paras[0] = 2.0f * fabsf( pos_x.at<float>(0, 0) );
	paras[1] = pos_y.at<float>(2, 0) - pos_y.at<float>(1, 0);
}

void cal_mapping(int &row, int &col, float(&paras)[2], std::vector<float> &points, cv::Mat &mapx1, cv::Mat &mapy1)
{
	float width = paras[0];
	float height = paras[1];
	int lens = points.size();
	for (int k = 0; k < lens; k++)
	{
		cv::Mat X, Y;
		meshgrid(cv::Range(1, col), cv::Range(1, row), X, Y);
		cv::Mat c_X = X - col/2;
		cv::Mat c_Y = Y - row/2;

		float centerx, centery;

		switch (k + 1)
		{
		case 1:
			centerx = width / 2;
			centery = height / 2;
			break;
		case 2:
			centerx = -width / 2;
			centery = height / 2;
			break;
		case 3:
			centerx = -width / 2;
			centery = -height / 2;
			break;
		case 4:
			centerx = width / 2;
			centery = -height / 2;
			break;
		}
		c_X = c_X - centerx;
		c_Y = c_Y - centery;


		cv::Mat temp(row, col, CV_32FC1, cv::Scalar(0));
		for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (c_X.at<float>(i, j)<width / 2 && c_X.at<float>(i, j)>-width / 2 && c_Y.at<float>(i, j)<height / 2 && c_Y.at<float>(i, j)>-height / 2)
				temp.at<float>(i, j) = 1;
		}


		cv::Mat phi, rou;
		cv::cartToPolar(c_X, c_Y, rou, phi);
		phi = phi + PI / 2;

		cv::Mat theta(row, col, CV_32FC1);
		for (int j = 0; j < col; j++)
		for (int i = 0; i < row; i++)
			theta.at<float>(i, j) = atan2(rou.at<float>(i, j), f*ratio);

		cv::Mat XX(row, col, CV_32FC1, cv::Scalar(0));
		cv::Mat YY(row, col, CV_32FC1, cv::Scalar(0));
		cv::Mat ZZ(row, col, CV_32FC1, cv::Scalar(0));
		sph2cart(phi, theta, XX, YY, ZZ);

		cv::Mat Rx(3, 3, CV_32FC1);
		cv::Mat Ry(3, 3, CV_32FC1);
		cv::Mat Rz(3, 3, CV_32FC1);
		rotate3D(0.0f, -viewpoint, points.at(k), Rx, Ry, Rz);

		XX = XX.mul(temp); YY = YY.mul(temp); ZZ = ZZ.mul(temp);

		cv::Mat XYZ(row*col, 3, XX.type());
		cv::Mat TXX = XX.reshape(0, row*col);
		cv::Mat TYY = YY.reshape(0, row*col);
		cv::Mat TZZ = ZZ.reshape(0, row*col);
		TXX.copyTo(XYZ.col(0));
		TYY.copyTo(XYZ.col(1));
		TZZ.copyTo(XYZ.col(2));
		XYZ = XYZ * ( Ry * Rz );
		XYZ.col(0).copyTo(TXX);
		XYZ.col(1).copyTo(TYY);
		XYZ.col(2).copyTo(TZZ);
		cv::Mat nXX(XX.size(), XX.type());
		cv::Mat nYY(XX.size(), XX.type());
		cv::Mat nZZ(XX.size(), XX.type());
		TXX.reshape(0, row).copyTo(nXX);
		TYY.reshape(0, row).copyTo(nYY);
		TZZ.reshape(0, row).copyTo(nZZ);

		cv::Mat nphi(row, col, CV_32FC1, cv::Scalar(0));
		cv::Mat ntheta(row, col, CV_32FC1, cv::Scalar(0));
		cart2sph(nXX, nYY, nZZ, nphi, ntheta);

		cv::Mat nrou(row, col, CV_32FC1);
		for (int j = 0; j < col; j++)
		for (int i = 0; i < row; i++)
			nrou.at<float>(i, j) = f * ntheta.at<float>(i, j);

		cv::Mat nX, nY;
		polarToCart(nrou, nphi, nX, nY);

		mapx1 = mapx1 + nX;
		mapy1 = mapy1 + nY;
	}
}