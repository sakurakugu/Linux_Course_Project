#include "Line.h"
#include <cmath>
#include <algorithm>

std::vector<Point> Line::ToPoints() {
    std::vector<Point> ptVec;

    // 预估点的数量以提高性能
    const double length = GetLength();
    ptVec.reserve(static_cast<size_t>(length) + 1);

    // 因为要计算斜率，所以先判断在x方向，起点终点是否重合
    if (std::abs(m_start.x - m_end.x) < 1e-9) {
        // 垂直线
        const int32_t x = static_cast<int32_t>(std::round(m_start.x));
        const int32_t y_start = static_cast<int32_t>(std::round(std::min(m_start.y, m_end.y)));
        const int32_t y_end = static_cast<int32_t>(std::round(std::max(m_start.y, m_end.y)));

        for (int32_t y = y_start; y <= y_end; ++y) {
            ptVec.emplace_back(x, y, m_color);
        }
    } else {
        // 计算斜率
        const double slope = (m_end.y - m_start.y) / (m_end.x - m_start.x);

        // 哪个坐标长，就遍历哪个 - 使用更精确的比较
        if (std::abs(m_end.x - m_start.x) >= std::abs(m_end.y - m_start.y)) {
            // 按x遍历
            const int32_t x_start = static_cast<int32_t>(std::round(std::min(m_start.x, m_end.x)));
            const int32_t x_end = static_cast<int32_t>(std::round(std::max(m_start.x, m_end.x)));
            
            for (int32_t x = x_start; x <= x_end; ++x) {
                const int32_t y = static_cast<int32_t>(std::round(slope * (x - m_start.x) + m_start.y));
                ptVec.emplace_back(x, y, m_color);
            }
        } else {
            // 按y遍历
            const int32_t y_start = static_cast<int32_t>(std::round(std::min(m_start.y, m_end.y)));
            const int32_t y_end = static_cast<int32_t>(std::round(std::max(m_start.y, m_end.y)));
            
            for (int32_t y = y_start; y <= y_end; ++y) {
                const int32_t x = static_cast<int32_t>(std::round((y - m_start.y) / slope + m_start.x));
                ptVec.emplace_back(x, y, m_color);
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