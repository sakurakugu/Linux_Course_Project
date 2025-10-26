#pragma once

#include "../../core/Geometry.h"
#include "Circle.h"

class OlympicRings : public Geometry {
  public:
    // 构造函数
    OlympicRings(const Point& center, double ringRadius = 50, double spacing = 120) 
        : m_center(center), m_ringRadius(ringRadius), m_spacing(spacing) {
        m_color = Color(255, 255, 255); // 默认颜色，实际会被各个环的颜色覆盖
        InitializeRings();
    }

    // 默认构造函数
    OlympicRings() : m_center(400, 300), m_ringRadius(50), m_spacing(120) {
        m_color = Color(255, 255, 255);
        InitializeRings();
    }

    // 设置函数
    void Set(const Point& center, double ringRadius = 50, double spacing = 120) {
        m_center = center;
        m_ringRadius = ringRadius;
        m_spacing = spacing;
        InitializeRings();
        InvalidatePoints();
    }

    // 设置中心位置
    void SetCenter(const Point& center) {
        m_center = center;
        InitializeRings();
        InvalidatePoints();
    }

    // 获取中心位置
    const Point& GetCenter() const {
        return m_center;
    }

  protected:
    virtual std::vector<Point> ToPoints() override;
    void InitializeRings();

  protected:
    Point m_center;
    double m_ringRadius;
    double m_spacing;
    
    // 五个奥运环
    Circle m_blueRing;    // 蓝环
    Circle m_yellowRing;  // 黄环
    Circle m_blackRing;   // 黑环
    Circle m_greenRing;   // 绿环
    Circle m_redRing;     // 红环
};