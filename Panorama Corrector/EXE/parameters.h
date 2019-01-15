#pragma once


#include <string>

//(imgname), the filename of tested image
//(cx,cy), the coordinate of center
//(rr,RR), the imaging range
//(thetamax), the maximum of theta
//(views), the number of sub_views
//(f), the focal length of camera
//(thetamin,thetamax) the minimum and maximum of field of view
//(viewpoint), the virtual view point
//(PI), the const val for PI;

extern std::string imgname;
extern int views;
extern float cx, cy, rr, RR;
extern float thetamax, thetamin, f, viewpoint;
extern const float PI;
extern float ratio;




