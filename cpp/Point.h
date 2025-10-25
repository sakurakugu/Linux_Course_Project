#pragma once

#include "Color.h"
#include <iostream>
#include <vector>
#include <numbers>

class Point {
  public:
    Point() {
        x = 0;
        y = 0;
    };

    Point(double x, double y, Color c = Color(0, 0, 255)) {
        this->x = x;
        this->y = y;
        color = c;
    };

    void Set(double x, double y, Color c = Color(0, 0, 255)) {
        this->x = x;
        this->y = y;
        color = c;
    };

  public:
    double x;
    double y;
    Color color;
};
