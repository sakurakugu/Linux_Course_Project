#include "Line.h"

std::vector<Point> Line::ToPoints() {
    std::vector<Point> ptVec;

    // 因为要计算斜率，所以先判断在x方向，起点终点是否重合
    if (m_start.x == m_end.x) {

        int32_t x = m_start.x;
        int32_t y = 0;

        if (m_start.y < m_end.y) {
            for (y = m_start.y; y <= m_end.y; y++) {
                ptVec.push_back(Point(x, y, m_color));
            }
        } else {
            for (y = m_end.y; y <= m_start.y; y++) {
                ptVec.push_back(Point(x, y, m_color));
            }
        }

    } else {
        // 计算斜率
        double slope = (double)(m_end.y - m_start.y) / (m_end.x - m_start.x);

        int x = 0;
        int y = 0;

        // 哪个坐标长，就遍历哪个
        if (abs(m_start.x - m_end.x) > abs(m_start.y - m_end.y)) {
            if (m_start.x < m_end.x) {
                for (x = m_start.x; x <= m_end.x; x++) {
                    // 计算y
                    y = slope * (x - m_start.x) + m_start.y;
                    ptVec.push_back(Point(x, y, m_color));
                }
            } else {
                for (x = m_end.x; x <= m_start.x; x++) {
                    // 计算y
                    y = slope * (x - m_end.x) + m_end.y;
                    ptVec.push_back(Point(x, y, m_color));
                }
            }
        } else {
            if (m_start.y < m_end.y) {
                for (y = m_start.y; y <= m_end.y; y++) {
                    // 计算x
                    x = (y - m_start.y) / slope + m_start.x;
                    ptVec.push_back(Point(x, y, m_color));
                }
            } else {
                for (y = m_end.y; y <= m_start.y; y++) {
                    // 计算x
                    x = (y - m_end.y) / slope + m_end.x;
                    ptVec.push_back(Point(x, y, m_color));
                }
            }
        }
    }

    return ptVec;
}