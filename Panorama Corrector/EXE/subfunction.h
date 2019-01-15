#pragma once

#include <opencv2/core/core.hpp>

//the Matlab function meshgrid for float type output
void meshgrid(const cv::Range &xgv, const cv::Range &ygv, cv::Mat &X, cv::Mat &Y);

//the Matlab function sph2cart for float type only ( time consuming )
void sph2cart(const cv::Mat &phi, const cv::Mat &theta, cv::Mat &x, cv::Mat &y, cv::Mat &z);

//the Matlab function cart2sph for float type only ( time consuming )
void cart2sph(const cv::Mat &x, const cv::Mat &y, const cv::Mat &z, cv::Mat &phi, cv::Mat &theta);

//the 3D rotation matrix for float type only
void rotate3D(const float &alpha, const float &beta, const float &gamma, cv::Mat &Rx, cv::Mat &Ry, cv::Mat &Rz);

//the function for calculating the projection of the sub_view
void cal_subview(float(&pos1)[3], float(&pos2)[3], float(&paras)[2]);

//the function for calculating the mapping matrix
void cal_mapping(int &row, int &col, float(&paras)[2], std::vector<float> &points, cv::Mat &mapx1, cv::Mat &mapy1);