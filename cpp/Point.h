#pragma once

#include "Color.h"
#include <iostream>
#include <vector>
#include <numbers>

class Point {
  public:
    // 默认构造函数 - 使用初始化列表
    Point() : x(0.0), y(0.0), color(0, 0, 255) {}

    // 参数构造函数 - 使用初始化列表和const引用
    Point(double x, double y, const Color& c = Color(0, 0, 255)) 
        : x(x), y(y), color(c) {}

    // 拷贝构造函数
    Point(const Point& other) = default;

    // 移动构造函数
    Point(Point&& other) noexcept 
        : x(other.x), y(other.y), color(std::move(other.color)) {}

    // 拷贝赋值运算符
    Point& operator=(const Point& other) = default;

    // 移动赋值运算符
    Point& operator=(Point&& other) noexcept {
        if (this != &other) {
            x = other.x;
            y = other.y;
            color = std::move(other.color);
        }
        return *this;
    }

    // 设置函数 - 使用const引用
    void Set(double x, double y, const Color& c = Color(0, 0, 255)) {
        this->x = x;
        this->y = y;
        this->color = c;
    }

    // 比较运算符
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

  public:
    double x;
    double y;
    Color color;
};
