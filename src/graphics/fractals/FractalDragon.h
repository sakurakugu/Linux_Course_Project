#pragma once

#include "../../core/Geometry.h"

class FractalDragon : public Geometry {
  public:
    // 使用初始化列表优化构造函数
    FractalDragon(const Point &start, const Point &end, int32_t step, const Color &cc)
        : m_start(start), //
        m_end(end), //
        m_step(step) {
        m_color = cc;
    }

    // 默认构造函数
    FractalDragon() : m_start(0, 0), m_end(100, 100), m_step(1) { m_color = Color(0, 255, 0); }

    void Set(const Point &start, const Point &end, int32_t step, const Color &cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
        m_step = step;
    }

  protected:
    virtual std::vector<Point> ToPoints() override;

    std::vector<Point> GetVertexs(int32_t step, const Point &start, const Point &end, bool needLeft) const;

  protected:
    bool IsLeft(const Point &ptA, const Point &ptB, const Point &ptC) const;
    double GetLength(const Point &pt1, const Point &pt2) const;
    Point GetCenter(const Point &pt1, const Point &pt2) const;
    Point GetVerticalCenter(const Point &start, const Point &end, bool isLeft) const;

  protected:
    Point m_start;
    Point m_end;
    int32_t m_step;
};
