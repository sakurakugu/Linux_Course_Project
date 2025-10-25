#include "Polyline.h"
#include "Line.h"
#include <cmath>

std::vector<Point> Polyline::ToPoints() {
    std::vector<Point> points;
    
    // 如果顶点数量不足，直接返回空向量
    if (m_vertexs.size() < 2) {
        return points;
    }

    // 预估点的数量以提高性能
    size_t estimated_size = 0;
    for (size_t i = 0; i < m_vertexs.size() - 1; ++i) {
        const double dx = m_vertexs[i + 1].x - m_vertexs[i].x;
        const double dy = m_vertexs[i + 1].y - m_vertexs[i].y;
        estimated_size += static_cast<size_t>(std::sqrt(dx * dx + dy * dy)) + 1;
    }
    
    if (m_closure && m_vertexs.size() > 2) {
        const double dx = m_vertexs[0].x - m_vertexs.back().x;
        const double dy = m_vertexs[0].y - m_vertexs.back().y;
        estimated_size += static_cast<size_t>(std::sqrt(dx * dx + dy * dy)) + 1;
    }
    
    points.reserve(estimated_size);

    // 生成线段点
    for (size_t i = 0; i < m_vertexs.size() - 1; ++i) {
        Line line(m_vertexs[i], m_vertexs[i + 1], m_color);
        std::vector<Point> linePoints = line.GetPoints();
        
        // 使用移动语义提高性能
        points.insert(points.end(), 
                     std::make_move_iterator(linePoints.begin()), 
                     std::make_move_iterator(linePoints.end()));
    }

    // 闭合多段线
    if (m_closure && m_vertexs.size() > 2) {
        Line line(m_vertexs.back(), m_vertexs[0], m_color);
        std::vector<Point> linePoints = line.GetPoints();
        
        points.insert(points.end(), 
                     std::make_move_iterator(linePoints.begin()), 
                     std::make_move_iterator(linePoints.end()));
    }

    return points;
}