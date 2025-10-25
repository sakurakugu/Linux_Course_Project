#pragma once

#include "Color.h"
#include <iostream>
#include <vector>
using namespace std;

#define PI 3.1415926

class CPoint {
  public:
    CPoint() {
        x = 0;
        y = 0;
    };

    CPoint(double xx, double yy, CColor cc = CColor(0, 0, 255)) {
        x = xx;
        y = yy;
        color = cc;
    };

    void Set(double xx, double yy, CColor cc = CColor(0, 0, 255)) {
        x = xx;
        y = yy;
        color = cc;
    };

  public:
    double x;
    double y;
    CColor color;
};

// 点vector，简单的认为是一个点的数组类型
typedef vector<CPoint> VecPt;
