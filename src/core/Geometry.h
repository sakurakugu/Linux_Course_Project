#pragma once

#include "Point.h"
#include <cmath>

class Geometry {
  public:
    // 虚析构函数确保正确的多态析构
    virtual ~Geometry() = default;

    // 获取点集合 - 使用缓存机制提高性能
    std::vector<Point> GetPoints() {
        if (m_points_dirty) {
            m_points = ToPoints();
            m_points_dirty = false;
        }
        return m_points;
    }

    // 强制重新计算点集合
    void InvalidatePoints() {
        m_points_dirty = true;
    }

    // 获取颜色
    const Color& GetColor() const {
        return m_color;
    }

    // 设置颜色
    void SetColor(const Color& color) {
        m_color = color;
        m_points_dirty = true; // 颜色改变时需要重新计算点
    }

    // 变换方法
    // 旋转（绕指定中心点旋转指定角度，角度以弧度为单位）
    virtual void Rotate(double angle, const Point& center) {
        m_rotation += angle;
        m_rotationCenter = center;
        InvalidatePoints();
    }

    // 缩放（绕指定中心点缩放）
    virtual void Scale(double factor, const Point& center) {
        m_scale *= factor;
        m_scaleCenter = center;
        InvalidatePoints();
    }

    // 平移
    virtual void Translate(double dx, double dy) {
        m_translation.x += dx;
        m_translation.y += dy;
        InvalidatePoints();
    }

    // 重置所有变换
    virtual void ResetTransform() {
        m_rotation = 0.0;
        m_scale = 1.0;
        m_translation = Point(0, 0);
        m_rotationCenter = Point(0, 0);
        m_scaleCenter = Point(0, 0);
        InvalidatePoints();
    }

    // 获取变换参数
    double GetRotation() const { return m_rotation; }
    double GetScale() const { return m_scale; }
    const Point& GetTranslation() const { return m_translation; }

  protected:
    // 几何图形转换成点的数组，用于绘图的目的
    // 由各个子类负责实现
    virtual std::vector<Point> ToPoints() = 0;

    // 默认构造函数
    Geometry() : m_points_dirty(true), m_rotation(0.0), m_scale(1.0), 
                 m_translation(0, 0), m_rotationCenter(0, 0), m_scaleCenter(0, 0) {}

    // 拷贝构造函数
    Geometry(const Geometry& other) 
        : m_points(other.m_points), m_color(other.m_color), m_points_dirty(other.m_points_dirty),
          m_rotation(other.m_rotation), m_scale(other.m_scale), m_translation(other.m_translation),
          m_rotationCenter(other.m_rotationCenter), m_scaleCenter(other.m_scaleCenter) {}

    // 移动构造函数
    Geometry(Geometry&& other) noexcept
        : m_points(std::move(other.m_points)), m_color(std::move(other.m_color)), 
          m_points_dirty(other.m_points_dirty), m_rotation(other.m_rotation), 
          m_scale(other.m_scale), m_translation(other.m_translation),
          m_rotationCenter(other.m_rotationCenter), m_scaleCenter(other.m_scaleCenter) {}

    // 拷贝赋值运算符
    Geometry& operator=(const Geometry& other) {
        if (this != &other) {
            m_points = other.m_points;
            m_color = other.m_color;
            m_points_dirty = other.m_points_dirty;
            m_rotation = other.m_rotation;
            m_scale = other.m_scale;
            m_translation = other.m_translation;
            m_rotationCenter = other.m_rotationCenter;
            m_scaleCenter = other.m_scaleCenter;
        }
        return *this;
    }

    // 移动赋值运算符
    Geometry& operator=(Geometry&& other) noexcept {
        if (this != &other) {
            m_points = std::move(other.m_points);
            m_color = std::move(other.m_color);
            m_points_dirty = other.m_points_dirty;
            m_rotation = other.m_rotation;
            m_scale = other.m_scale;
            m_translation = other.m_translation;
            m_rotationCenter = other.m_rotationCenter;
            m_scaleCenter = other.m_scaleCenter;
        }
        return *this;
    }

  protected:
    std::vector<Point> m_points; // 用于绘图的点的数组
    Color m_color;
    bool m_points_dirty; // 标记点集合是否需要重新计算
    
    // 变换参数
    double m_rotation;        // 旋转角度（弧度）
    double m_scale;          // 缩放因子
    Point m_translation;     // 平移量
    Point m_rotationCenter;  // 旋转中心
    Point m_scaleCenter;     // 缩放中心

    // 应用变换到点
    Point ApplyTransform(const Point& point) const {
        Point result = point;
        
        // 1. 先应用缩放（绕缩放中心）
        if (m_scale != 1.0) {
            double dx = result.x - m_scaleCenter.x;
            double dy = result.y - m_scaleCenter.y;
            result.x = m_scaleCenter.x + dx * m_scale;
            result.y = m_scaleCenter.y + dy * m_scale;
        }
        
        // 2. 然后应用旋转（绕旋转中心）
        if (m_rotation != 0.0) {
            double dx = result.x - m_rotationCenter.x;
            double dy = result.y - m_rotationCenter.y;
            double cos_a = cos(m_rotation);
            double sin_a = sin(m_rotation);
            result.x = m_rotationCenter.x + dx * cos_a - dy * sin_a;
            result.y = m_rotationCenter.y + dx * sin_a + dy * cos_a;
        }
        
        // 3. 最后应用平移
        result.x += m_translation.x;
        result.y += m_translation.y;
        
        return result;
    }
};
