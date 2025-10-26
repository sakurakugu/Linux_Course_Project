#include "OlympicRings.h"
#include <cmath>

void OlympicRings::InitializeRings() {
    // 奥运五环的标准布局：
    // 上排：蓝、黑、红（从左到右）
    // 下排：黄、绿（从左到右）
    
    double offsetY = m_ringRadius * 0.6; // 上下排的垂直偏移
    
    // 上排三个环
    Point blueCenter(m_center.x - m_spacing, m_center.y - offsetY);
    Point blackCenter(m_center.x, m_center.y - offsetY);
    Point redCenter(m_center.x + m_spacing, m_center.y - offsetY);
    
    // 下排两个环
    Point yellowCenter(m_center.x - m_spacing * 0.5, m_center.y + offsetY);
    Point greenCenter(m_center.x + m_spacing * 0.5, m_center.y + offsetY);
    
    // 设置各个环的位置和颜色
    m_blueRing.Set(blueCenter, m_ringRadius, Color(0, 129, 200));    // 奥运蓝
    m_blackRing.Set(blackCenter, m_ringRadius, Color(255, 255, 255));      // 白色（黑色背景）
    m_redRing.Set(redCenter, m_ringRadius, Color(238, 51, 78));      // 奥运红
    m_yellowRing.Set(yellowCenter, m_ringRadius, Color(252, 177, 49)); // 奥运黄
    m_greenRing.Set(greenCenter, m_ringRadius, Color(0, 166, 81));   // 奥运绿
}

std::vector<Point> OlympicRings::ToPoints() {
    std::vector<Point> points;
    
    // 计算缩放后的参数
    double scaledRadius = m_ringRadius * GetScale();
    double offsetY = scaledRadius * 0.6; // 上下排的垂直偏移
    
    // 原始位置（相对于中心）
    std::vector<Point> ringCenters = {
        Point(m_center.x - m_spacing, m_center.y - offsetY),      // 蓝环
        Point(m_center.x, m_center.y - offsetY),                  // 黑环
        Point(m_center.x + m_spacing, m_center.y - offsetY),      // 红环
        Point(m_center.x - m_spacing * 0.5, m_center.y + offsetY), // 黄环
        Point(m_center.x + m_spacing * 0.5, m_center.y + offsetY)  // 绿环
    };
    
    // 颜色数组
    std::vector<Color> ringColors = {
        Color(0, 129, 200),    // 奥运蓝
        Color(255, 255, 255),  // 白色（黑色背景）
        Color(238, 51, 78),    // 奥运红
        Color(252, 177, 49),   // 奥运黄
        Color(0, 166, 81)      // 奥运绿
    };
    
    // 为每个环生成点并应用变换
    for (size_t i = 0; i < ringCenters.size(); i++) {
        // 先应用旋转到环心位置（绕五环中心旋转）
        Point rotatedCenter = ringCenters[i];
        if (GetRotation() != 0.0) {
            double dx = rotatedCenter.x - m_center.x;
            double dy = rotatedCenter.y - m_center.y;
            double cos_a = cos(GetRotation());
            double sin_a = sin(GetRotation());
            rotatedCenter.x = m_center.x + dx * cos_a - dy * sin_a;
            rotatedCenter.y = m_center.y + dx * sin_a + dy * cos_a;
        }
        
        // 应用平移
        rotatedCenter.x += GetTranslation().x;
        rotatedCenter.y += GetTranslation().y;
        
        // 使用Bresenham圆算法绘制圆环
        int cx = static_cast<int>(std::round(rotatedCenter.x));
        int cy = static_cast<int>(std::round(rotatedCenter.y));
        int r = static_cast<int>(std::round(scaledRadius));
        
        if (r <= 0) continue; // 避免无效半径
        
        // 使用Bresenham算法绘制圆
        int x = 0;
        int y = r;
        int d = 3 - 2 * r;
        
        // 绘制圆的8个对称点的lambda函数
        auto drawCirclePoints = [&](int x, int y) {
            std::vector<Point> circlePoints = {
                Point(cx + x, cy + y, ringColors[i]),
                Point(cx - x, cy + y, ringColors[i]),
                Point(cx + x, cy - y, ringColors[i]),
                Point(cx - x, cy - y, ringColors[i]),
                Point(cx + y, cy + x, ringColors[i]),
                Point(cx - y, cy + x, ringColors[i]),
                Point(cx + y, cy - x, ringColors[i]),
                Point(cx - y, cy - x, ringColors[i])
            };
            
            for (const auto& point : circlePoints) {
                points.push_back(point);
            }
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
    }
    
    return points;
}