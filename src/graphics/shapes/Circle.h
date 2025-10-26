#pragma once

#include "../../core/Geometry.h"
#include <cmath>

class Circle : public Geometry {
  public:
    // 构造函数
    Circle(const Point& center, double radius, const Color& cc) 
        : m_center(center), m_radius(radius) {
        m_color = cc;
    }

    // 默认构造函数
    Circle() : m_center(0, 0), m_radius(50) {
        m_color = Color(255, 255, 255);
    }

    // 设置函数
    void Set(const Point& center, double radius, const Color& cc) {
        m_center = center;
        m_radius = radius;
        m_color = cc;
        InvalidatePoints(); // 标记需要重新计算点
    }

    // 获取半径
    double GetRadius() const {
        return m_radius;
    }

    // 获取圆心
    const Point& GetCenter() const {
        return m_center;
    }

    // 设置圆心
    void SetCenter(const Point& center) {
        m_center = center;
        InvalidatePoints();
    }

  protected:
    virtual std::vector<Point> ToPoints() override;

  protected:
    Point m_center;
    double m_radius;
};