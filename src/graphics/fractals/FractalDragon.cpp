#include "FractalDragon.h"
#include <iostream>
#include <cmath>

#include "../shapes/Polyline.h"

// 计算两点之间的长度
double FractalDragon::GetLength(const Point& pt1, const Point& pt2) const {
    const double dx = pt1.x - pt2.x;
    const double dy = pt1.y - pt2.y;
    return std::sqrt(dx * dx + dy * dy);
}

// 计算两点之间的中点
Point FractalDragon::GetCenter(const Point& pt1, const Point& pt2) const {
    return Point((pt1.x + pt2.x) * 0.5, (pt1.y + pt2.y) * 0.5);
}

// 判断点C 在向量AB的左侧还是右侧
bool FractalDragon::IsLeft(const Point& ptA, const Point& ptB, const Point& ptC) const {
    // 三角形的有向面积
    // ABC逆时针，面积为正，也即C在AB的左侧
    // ABC顺时针，面积为负，也即C在AB的右侧
    // 面积为0，则C在AB上
    const double signedArea = ptA.x * ptB.y + ptC.x * ptA.y + ptB.x * ptC.y 
                            - ptC.x * ptB.y - ptB.x * ptA.y - ptA.x * ptC.y;

    return signedArea > 0;
}

// 计算两点的垂直中点，得到两个结果，一左，一右
// needLeft 为 true，则返回 左侧的点
Point FractalDragon::GetVerticalCenter(const Point& start, const Point& end, bool needLeft) const {
    const Point center = GetCenter(start, end);
    const double len = GetLength(start, end) * 0.5;

    Point pt1, pt2; // 一左，一右两个点

    // 因为下面要计算斜率，所以需要判断y坐标是否相等
    if (std::abs(end.y - start.y) < 1e-9) { // 使用浮点数比较的安全方法
        pt1.x = pt2.x = center.x;
        pt1.y = center.y + len;
        pt2.y = center.y - len;
    } else {
        // 斜率 - 优化计算
        const double slope = -(end.x - start.x) / (end.y - start.y);
        const double denominator = std::sqrt(slope * slope + 1);
        const double offset = len / denominator;

        pt1.x = center.x + offset;
        pt2.x = center.x - offset;
        pt1.y = slope * (pt1.x - center.x) + center.y;
        pt2.y = slope * (pt2.x - center.x) + center.y;
    }

    // 需要左侧的点
    if (needLeft) {
        return IsLeft(start, end, pt1) ? pt1 : pt2;
    } else {
        return IsLeft(start, end, pt1) ? pt2 : pt1;
    }
}

std::vector<Point> FractalDragon::GetVertexs(int32_t step, const Point& start, const Point& end, bool needLeft) const {
    if (step > 0) {
        // 阶数递减
        step--;
        // 获得垂中
        const Point verCenter = GetVerticalCenter(start, end, needLeft);
        // 根据 start  verCenter  end 劈成两半
        // 左边
        std::vector<Point> ptVecLeft = GetVertexs(step, start, verCenter, true);
        // 右边
        std::vector<Point> ptVecRight = GetVertexs(step, verCenter, end, false);
        
        // 预分配空间以提高性能
        ptVecLeft.reserve(ptVecLeft.size() + ptVecRight.size());
        // 左边和右边的拼接起来
        ptVecLeft.insert(ptVecLeft.end(), 
                        std::make_move_iterator(ptVecRight.begin()), 
                        std::make_move_iterator(ptVecRight.end()));
        // 返回拼接的结果
        return ptVecLeft;
    } else { // 阶数为0 退出递归
        // 最后一阶，不用计算垂中点，直接返回 start end
        return {start, end}; // 使用初始化列表，更高效
    }
}

std::vector<Point> FractalDragon::ToPoints() {
    // 通过递归算法计算分形龙的所有顶点
    std::vector<Point> vertexs = GetVertexs(m_step, m_start, m_end, true);

    // 转换成多段线
    Polyline polyline(vertexs, m_color, false);

    // 返回Points 用于绘图
    return polyline.GetPoints();
}
