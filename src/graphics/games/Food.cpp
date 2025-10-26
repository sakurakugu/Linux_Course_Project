#include "Food.h"
#include <cmath>

Food::Food(int size) : m_position(0, 0), m_size(size), m_gen(m_rd()) {
    m_color = Color(255, 0, 0); // 红色食物
    InvalidatePoints();
}

void Food::GenerateRandomPosition(int minX, int minY, int maxX, int maxY) {
    std::uniform_int_distribution<int> distX(minX + m_size, maxX - m_size);
    std::uniform_int_distribution<int> distY(minY + m_size, maxY - m_size);
    
    m_position.x = distX(m_gen);
    m_position.y = distY(m_gen);
    
    InvalidatePoints();
}

void Food::SetPosition(const Point& pos) {
    m_position = pos;
    InvalidatePoints();
}

bool Food::CheckCollision(const Point& point, int tolerance) const {
    double distance = std::sqrt(std::pow(point.x - m_position.x, 2) + 
                               std::pow(point.y - m_position.y, 2));
    return distance <= (m_size + tolerance);
}

std::vector<Point> Food::ToPoints() {
    std::vector<Point> points;
    GenerateFoodShape(points);
    return points;
}

void Food::GenerateFoodShape(std::vector<Point>& points) const {
    // 生成圆形食物
    int radius = m_size / 2;
    
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            // 检查是否在圆内
            if (dx * dx + dy * dy <= radius * radius) {
                Point p(m_position.x + dx, m_position.y + dy, m_color);
                p = ApplyTransform(p);
                points.push_back(p);
            }
        }
    }
}