#include "Circle.h"
#include <cmath>
#include <algorithm>

std::vector<Point> Circle::ToPoints() {
    std::vector<Point> points;
    
    if (m_radius <= 0) {
        return points;
    }

    // 使用Bresenham圆算法绘制圆形
    int cx = static_cast<int>(std::round(m_center.x));
    int cy = static_cast<int>(std::round(m_center.y));
    int r = static_cast<int>(std::round(m_radius));
    
    // 预估点的数量
    points.reserve(static_cast<size_t>(2 * M_PI * r) + 8);
    
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    // 绘制圆的8个对称点
    auto drawCirclePoints = [&](int x, int y) {
        points.emplace_back(cx + x, cy + y, m_color);
        points.emplace_back(cx - x, cy + y, m_color);
        points.emplace_back(cx + x, cy - y, m_color);
        points.emplace_back(cx - x, cy - y, m_color);
        points.emplace_back(cx + y, cy + x, m_color);
        points.emplace_back(cx - y, cy + x, m_color);
        points.emplace_back(cx + y, cy - x, m_color);
        points.emplace_back(cx - y, cy - x, m_color);
    };
    
    drawCirclePoints(x, y);
    
    while (y >= x) {
        x++;
        
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        
        drawCirclePoints(x, y);
    }
    
    // 去除重复点
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    
    points.erase(std::unique(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return std::abs(a.x - b.x) < 1e-9 && std::abs(a.y - b.y) < 1e-9;
    }), points.end());
    
    return points;
}