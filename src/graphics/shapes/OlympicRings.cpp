#include "OlympicRings.h"

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
    m_blackRing.Set(blackCenter, m_ringRadius, Color(0, 0, 0));      // 黑色
    m_redRing.Set(redCenter, m_ringRadius, Color(238, 51, 78));      // 奥运红
    m_yellowRing.Set(yellowCenter, m_ringRadius, Color(252, 177, 49)); // 奥运黄
    m_greenRing.Set(greenCenter, m_ringRadius, Color(0, 166, 81));   // 奥运绿
}

std::vector<Point> OlympicRings::ToPoints() {
    std::vector<Point> points;
    
    // 获取每个环的点并合并
    std::vector<Point> bluePoints = m_blueRing.GetPoints();
    std::vector<Point> blackPoints = m_blackRing.GetPoints();
    std::vector<Point> redPoints = m_redRing.GetPoints();
    std::vector<Point> yellowPoints = m_yellowRing.GetPoints();
    std::vector<Point> greenPoints = m_greenRing.GetPoints();
    
    // 预估总点数
    size_t totalPoints = bluePoints.size() + blackPoints.size() + redPoints.size() + 
                        yellowPoints.size() + greenPoints.size();
    points.reserve(totalPoints);
    
    // 合并所有点
    points.insert(points.end(), 
                 std::make_move_iterator(bluePoints.begin()), 
                 std::make_move_iterator(bluePoints.end()));
    
    points.insert(points.end(), 
                 std::make_move_iterator(blackPoints.begin()), 
                 std::make_move_iterator(blackPoints.end()));
    
    points.insert(points.end(), 
                 std::make_move_iterator(redPoints.begin()), 
                 std::make_move_iterator(redPoints.end()));
    
    points.insert(points.end(), 
                 std::make_move_iterator(yellowPoints.begin()), 
                 std::make_move_iterator(yellowPoints.end()));
    
    points.insert(points.end(), 
                 std::make_move_iterator(greenPoints.begin()), 
                 std::make_move_iterator(greenPoints.end()));
    
    return points;
}