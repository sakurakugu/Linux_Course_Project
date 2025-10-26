#include "Snake.h"
#include <algorithm>

Snake::Snake(const Point& startPos, int segmentSize) 
    : m_direction(Direction::RIGHT), m_nextDirection(Direction::RIGHT),
      m_segmentSize(segmentSize), m_shouldGrow(false) {
    
    m_color = Color(0, 255, 0); // 绿色蛇
    
    // 初始化蛇身（3个段）
    m_body.push_back(startPos);
    m_body.push_back(Point(startPos.x - segmentSize, startPos.y));
    m_body.push_back(Point(startPos.x - 2 * segmentSize, startPos.y));
    
    InvalidatePoints();
}

void Snake::Move() {
    // 更新方向
    if (IsValidDirection(m_nextDirection)) {
        m_direction = m_nextDirection;
    }
    
    // 计算新的头部位置
    Point dirVector = GetDirectionVector();
    Point newHead = m_body.front();
    newHead.x += dirVector.x * m_segmentSize;
    newHead.y += dirVector.y * m_segmentSize;
    
    // 添加新头部
    m_body.push_front(newHead);
    
    // 如果不需要增长，移除尾部
    if (!m_shouldGrow) {
        m_body.pop_back();
    } else {
        m_shouldGrow = false;
    }
    
    InvalidatePoints();
}

void Snake::SetDirection(Direction dir) {
    m_nextDirection = dir;
}

void Snake::Grow() {
    m_shouldGrow = true;
}

bool Snake::CheckSelfCollision() const {
    if (m_body.size() < 4) return false; // 至少4个段才可能撞到自己
    
    const Point& head = m_body.front();
    
    // 检查头部是否与身体其他部分重叠
    for (auto it = m_body.begin() + 1; it != m_body.end(); ++it) {
        if (std::abs(head.x - it->x) < m_segmentSize && 
            std::abs(head.y - it->y) < m_segmentSize) {
            return true;
        }
    }
    
    return false;
}

bool Snake::CheckBoundaryCollision(int width, int height) const {
    const Point& head = m_body.front();
    
    // 考虑边框宽度（2像素）
    const int border = 2;
    
    return (head.x < border + m_segmentSize/2 || 
            head.x >= width - border - m_segmentSize/2 ||
            head.y < border + m_segmentSize/2 || 
            head.y >= height - border - m_segmentSize/2);
}

Point Snake::GetHeadPosition() const {
    return m_body.front();
}

void Snake::Reset(const Point& startPos) {
    m_body.clear();
    m_direction = Direction::RIGHT;
    m_nextDirection = Direction::RIGHT;
    m_shouldGrow = false;
    
    // 重新初始化蛇身
    m_body.push_back(startPos);
    m_body.push_back(Point(startPos.x - m_segmentSize, startPos.y));
    m_body.push_back(Point(startPos.x - 2 * m_segmentSize, startPos.y));
    
    InvalidatePoints();
}

std::vector<Point> Snake::ToPoints() {
    std::vector<Point> points;
    
    for (const auto& segment : m_body) {
        // 为每个身体段生成一个矩形
        for (int dx = -m_segmentSize/2; dx < m_segmentSize/2; dx++) {
            for (int dy = -m_segmentSize/2; dy < m_segmentSize/2; dy++) {
                Point p(segment.x + dx, segment.y + dy, m_color);
                p = ApplyTransform(p);
                points.push_back(p);
            }
        }
    }
    
    return points;
}

Point Snake::GetDirectionVector() const {
    switch (m_direction) {
        case Direction::UP:    return Point(0, -1);
        case Direction::DOWN:  return Point(0, 1);
        case Direction::LEFT:  return Point(-1, 0);
        case Direction::RIGHT: return Point(1, 0);
        default:               return Point(1, 0);
    }
}

bool Snake::IsValidDirection(Direction newDir) const {
    // 防止反向移动
    switch (m_direction) {
        case Direction::UP:    return newDir != Direction::DOWN;
        case Direction::DOWN:  return newDir != Direction::UP;
        case Direction::LEFT:  return newDir != Direction::RIGHT;
        case Direction::RIGHT: return newDir != Direction::LEFT;
        default:               return true;
    }
}