#pragma once

#include "../../core/Geometry.h"
#include <random>

class Food : public Geometry {
public:
    // 构造函数
    Food(int size = 15);
    
    // 随机生成食物位置
    void GenerateRandomPosition(int minX, int minY, int maxX, int maxY);
    
    // 设置位置
    void SetPosition(const Point& pos);
    
    // 获取位置
    Point GetPosition() const { return m_position; }
    
    // 获取大小
    int GetSize() const { return m_size; }
    
    // 检查是否与指定点碰撞
    bool CheckCollision(const Point& point, int tolerance = 0) const;

protected:
    virtual std::vector<Point> ToPoints() override;

private:
    Point m_position;
    int m_size;
    std::random_device m_rd;
    std::mt19937 m_gen;
    
    // 生成食物的形状点
    void GenerateFoodShape(std::vector<Point>& points) const;
};