#pragma once

#include "Geometry.h"

class Line : public Geometry {
  public:
    Line(const Point& start, const Point& end, const Color& cc) 
        : m_start(start), //
        m_end(end) {
        m_color = cc;
    }

    // 默认构造函数
    Line() : m_start(0, 0), m_end(100, 100) {
        m_color = Color(255, 255, 255);
    }

    // 设置函数
    void Set(const Point& start, const Point& end, const Color& cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
    }

    // 获取线段长度
    double GetLength() const;

  protected:
    virtual std::vector<Point> ToPoints() override;

  protected:
    Point m_start;
    Point m_end;
};
