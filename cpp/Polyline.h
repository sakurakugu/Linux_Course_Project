#pragma once

#include "Geometry.h"

class Polyline : public Geometry {
  public:
    Polyline(std::vector<Point> vertexs, Color cc, bool closure = false) {
        m_vertexs = vertexs;
        m_color = cc;
        m_closure = closure;
    };

    void Set(std::vector<Point> vertexs, Color color, bool closure = false) {
        m_vertexs = vertexs;
        m_color = color;
        m_closure = closure;
    };

  protected:
    virtual std::vector<Point> ToPoints();

  protected:
    std::vector<Point> m_vertexs;
    bool m_closure; // 多边形是否闭合
};
