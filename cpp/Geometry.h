#pragma once

#include "Point.h"

class Geometry {
  public:
    std::vector<Point> GetPoints() {
        m_points = ToPoints();
        return m_points;
    };

  protected:
    // 几何图形转换成点的数组，用于绘图的目的
    // 由各个子类负责实现
    virtual std::vector<Point> ToPoints() = 0;

  protected:
    std::vector<Point> m_points; // 用于绘图的点的数组
    Color m_color;
};
