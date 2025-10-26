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
    
    // 重新计算各个环的位置（考虑变换）
    double scaledRadius = m_ringRadius * GetScale(); // 缩放后的半径
    double scaledSpacing = m_spacing * GetScale(); // 缩放后的间距
    double offsetY = scaledRadius * 0.6; // 上下排的垂直偏移
    
    // 原始位置（相对于中心）
    std::vector<Point> ringCenters = {
        Point(m_center.x - scaledSpacing, m_center.y - offsetY),      // 蓝环
        Point(m_center.x, m_center.y - offsetY),                      // 黑环
        Point(m_center.x + scaledSpacing, m_center.y - offsetY),      // 红环
        Point(m_center.x - scaledSpacing * 0.5, m_center.y + offsetY), // 黄环
        Point(m_center.x + scaledSpacing * 0.5, m_center.y + offsetY)  // 绿环
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
        // 生成圆环的点
        std::vector<Point> ringPoints;
        const int numPoints = 360; // 每个圆环的点数
        
        for (int j = 0; j < numPoints; j++) {
            double angle = 2.0 * M_PI * j / numPoints;
            double x = ringCenters[i].x + scaledRadius * cos(angle);
            double y = ringCenters[i].y + scaledRadius * sin(angle);
            
            // 应用变换
            Point transformedPoint = ApplyTransform(Point(x, y, ringColors[i]));
            points.push_back(transformedPoint);
        }
    }
    
    return points;
}