#pragma once

#include "Point.h"

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

  protected:
    // 几何图形转换成点的数组，用于绘图的目的
    // 由各个子类负责实现
    virtual std::vector<Point> ToPoints() = 0;

    // 默认构造函数
    Geometry() : m_points_dirty(true) {}

    // 拷贝构造函数
    Geometry(const Geometry& other) 
        : m_points(other.m_points), m_color(other.m_color), m_points_dirty(other.m_points_dirty) {}

    // 移动构造函数
    Geometry(Geometry&& other) noexcept
        : m_points(std::move(other.m_points)), m_color(std::move(other.m_color)), 
          m_points_dirty(other.m_points_dirty) {}

    // 拷贝赋值运算符
    Geometry& operator=(const Geometry& other) {
        if (this != &other) {
            m_points = other.m_points;
            m_color = other.m_color;
            m_points_dirty = other.m_points_dirty;
        }
        return *this;
    }

    // 移动赋值运算符
    Geometry& operator=(Geometry&& other) noexcept {
        if (this != &other) {
            m_points = std::move(other.m_points);
            m_color = std::move(other.m_color);
            m_points_dirty = other.m_points_dirty;
        }
        return *this;
    }

  protected:
    std::vector<Point> m_points; // 用于绘图的点的数组
    Color m_color;
    bool m_points_dirty; // 标记点集合是否需要重新计算
};
