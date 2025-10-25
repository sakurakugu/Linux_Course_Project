#pragma once

#include "Geometry.h"

class Polyline : public Geometry {
  public:
    // 使用const引用和移动语义优化构造函数
    Polyline(const std::vector<Point>& vertexs, const Color& cc, bool closure = false) 
        : m_vertexs(vertexs), m_closure(closure) {
        m_color = cc;
    }

    // 移动构造函数
    Polyline(std::vector<Point>&& vertexs, const Color& cc, bool closure = false) 
        : m_vertexs(std::move(vertexs)), m_closure(closure) {
        m_color = cc;
    }

    // 默认构造函数
    Polyline() : m_closure(false) {
        m_color = Color(255, 255, 255);
    }

    // 设置函数 - 使用const引用
    void Set(const std::vector<Point>& vertexs, const Color& color, bool closure = false) {
        m_vertexs = vertexs;
        m_color = color;
        m_closure = closure;
    }

    // 移动设置函数
    void Set(std::vector<Point>&& vertexs, const Color& color, bool closure = false) {
        m_vertexs = std::move(vertexs);
        m_color = color;
        m_closure = closure;
    }

    // 添加顶点
    void AddVertex(const Point& vertex) {
        m_vertexs.push_back(vertex);
    }

    void AddVertex(Point&& vertex) {
        m_vertexs.push_back(std::move(vertex));
    }

    // 获取顶点数量
    size_t GetVertexCount() const {
        return m_vertexs.size();
    }

  protected:
    virtual std::vector<Point> ToPoints() override;

  protected:
    std::vector<Point> m_vertexs;
    bool m_closure; // 多边形是否闭合
};
