#pragma once

#include "Point.h"

class CGeometry {
  public:
    VecPt GetPoints() {
        m_points = ToPoints();
        return m_points;
    };

  protected:
    // 几何图形转换成点的数组，用于绘图的目的
    // 由各个子类负责实现
    virtual VecPt ToPoints() = 0;

  protected:
    VecPt m_points; // 用于绘图的点的数组
    CColor m_color;
};
