#pragma once

#include "../../core/Geometry.h"
#include <deque>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake : public Geometry {
public:
    // 构造函数
    Snake(const Point& startPos, int segmentSize = 20);
    
    // 移动蛇
    void Move();
    
    // 改变方向
    void SetDirection(Direction dir);
    
    // 获取当前方向
    Direction GetDirection() const { return m_direction; }
    
    // 增长（吃到食物时调用）
    void Grow();
    
    // 检查是否撞到自己
    bool CheckSelfCollision() const;
    
    // 检查是否撞到边界
    bool CheckBoundaryCollision(int width, int height) const;
    
    // 获取头部位置
    Point GetHeadPosition() const;
    
    // 获取身体段数
    size_t GetLength() const { return m_body.size(); }
    
    // 重置蛇到初始状态
    void Reset(const Point& startPos);

protected:
    virtual std::vector<Point> ToPoints() override;

private:
    std::deque<Point> m_body;  // 蛇的身体，头部在前
    Direction m_direction;
    Direction m_nextDirection; // 下一个方向，防止快速按键导致的反向移动
    int m_segmentSize;         // 每个身体段的大小
    bool m_shouldGrow;         // 是否应该增长
    
    // 获取方向向量
    Point GetDirectionVector() const;
    
    // 检查方向是否有效（不能反向移动）
    bool IsValidDirection(Direction newDir) const;
};