#pragma once

#include "Geometry.h"

class FractalDragon : public Geometry {
  public:
    FractalDragon(Point start, Point end, int32_t step, Color cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
        m_step = step;
    };

    void Set(Point start, Point end, int32_t step, Color cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
        m_step = step;
    };

  protected:
    virtual std::vector<Point> ToPoints();

    std::vector<Point> GetVertexs(int32_t step, Point start, Point end, bool needLeft);

  protected:
    bool IsLeft(Point &ptA, Point &ptB, Point &ptC);
    double GetLength(Point &pt1, Point &pt2);
    Point GetCenter(Point &pt1, Point &pt2);
    Point GetVerticalCenter(Point &start, Point &end, bool isLeft);

  protected:
    Point m_start;
    Point m_end;
    int32_t m_step;
};
