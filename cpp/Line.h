#pragma once

#include "Geometry.h"

class Line : public Geometry {
  public:
    Line(Point start, Point end, Color cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
    };

    void Set(Point start, Point end, Color cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
    };

  protected:
    virtual std::vector<Point> ToPoints();

  protected:
    Point m_start;
    Point m_end;
};
