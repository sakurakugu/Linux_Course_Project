#include "Line.h"
#include <cmath>
#include <algorithm>

std::vector<Point> Line::ToPoints() {
    std::vector<Point> ptVec;

    // 预估点的数量以提高性能
    const double length = GetLength();
    ptVec.reserve(static_cast<size_t>(length) + 1);

    // 转换为整数坐标，减少浮点运算
    const int32_t x0 = static_cast<int32_t>(std::round(m_start.x));
    const int32_t y0 = static_cast<int32_t>(std::round(m_start.y));
    const int32_t x1 = static_cast<int32_t>(std::round(m_end.x));
    const int32_t y1 = static_cast<int32_t>(std::round(m_end.y));

    const int32_t dx = std::abs(x1 - x0);
    const int32_t dy = std::abs(y1 - y0);

    // 使用优化的DDA算法，避免重复的浮点计算
    if (dx == 0) {
        // 垂直线 - 优化：直接处理，无需斜率计算
        const int32_t y_start = std::min(y0, y1);
        const int32_t y_end = std::max(y0, y1);
        
        for (int32_t y = y_start; y <= y_end; ++y) {
            ptVec.emplace_back(x0, y, m_color);
        }
    } else if (dy == 0) {
        // 水平线 - 优化：直接处理，无需斜率计算
        const int32_t x_start = std::min(x0, x1);
        const int32_t x_end = std::max(x0, x1);
        
        for (int32_t x = x_start; x <= x_end; ++x) {
            ptVec.emplace_back(x, y0, m_color);
        }
    } else {
        // 使用增量算法，减少浮点运算
        if (dx >= dy) {
            // 按x遍历 - 优化：使用增量而非每次重新计算
            const int32_t x_start = std::min(x0, x1);
            const int32_t x_end = std::max(x0, x1);
            const bool reverse = (x0 > x1);
            
            const double slope = static_cast<double>(y1 - y0) / static_cast<double>(x1 - x0);
            double y_current = reverse ? m_end.y : m_start.y;
            const double y_increment = reverse ? -slope : slope;
            
            for (int32_t x = x_start; x <= x_end; ++x) {
                ptVec.emplace_back(x, static_cast<int32_t>(std::round(y_current)), m_color);
                y_current += y_increment;
            }
        } else {
            // 按y遍历 - 优化：使用增量而非每次重新计算
            const int32_t y_start = std::min(y0, y1);
            const int32_t y_end = std::max(y0, y1);
            const bool reverse = (y0 > y1);
            
            const double inv_slope = static_cast<double>(x1 - x0) / static_cast<double>(y1 - y0);
            double x_current = reverse ? m_end.x : m_start.x;
            const double x_increment = reverse ? -inv_slope : inv_slope;
            
            for (int32_t y = y_start; y <= y_end; ++y) {
                ptVec.emplace_back(static_cast<int32_t>(std::round(x_current)), y, m_color);
                x_current += x_increment;
            }
        }
    }

    return ptVec;
}

double Line::GetLength() const {
        const double dx = m_end.x - m_start.x;
        const double dy = m_end.y - m_start.y;
        return std::sqrt(dx * dx + dy * dy);
    }