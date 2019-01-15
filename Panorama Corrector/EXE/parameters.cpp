#include "parameters.h"

std::string imgname = "../data/2.jpg";
float cx = 1263.3f;
float cy = 977.6f;
float rr = 225.0f;
float RR = 953.5f;


const float PI = 3.14159267f;
float thetamax = 89.0f * PI / 180.0f;
int views = 4;
float f = RR / thetamax;
float thetamin = rr / f;
float viewpoint = 0.5f*(thetamin + thetamax);
float ratio = 1.0f;
