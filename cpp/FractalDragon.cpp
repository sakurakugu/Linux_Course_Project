#include "FractalDragon.h"
#include <iostream>
#include <math.h>

#include "Polyline.h"

// 计算两点之间的长度
double FractalDragon::GetLength(Point &pt1, Point &pt2) {
    return sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
}

// 计算两点之间的中点
Point FractalDragon::GetCenter(Point &pt1, Point &pt2) {
    return Point((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
}

// 判断点C 在向量AB的左侧还是右侧
bool FractalDragon::IsLeft(Point &ptA, Point &ptB, Point &ptC) {
    bool isLeft = false;

    // 三角形的有向面积
    // ABC逆时针，面积为正，也即C在AB的左侧
    // ABC顺时针，面积为负，也即C在AB的右侧
    // 面积为0，则C在AB上
    double signedArea = ptA.x * ptB.y + ptC.x * ptA.y + ptB.x * ptC.y - ptC.x * ptB.y - ptB.x * ptA.y - ptA.x * ptC.y;

    if (signedArea > 0) {
        isLeft = true;
    }

    return isLeft;
}

// 计算两点的垂直中点，得到两个结果，一左，一右
// needLeft 为 true，则返回 左侧的点
Point FractalDragon::GetVerticalCenter(Point &start, Point &end, bool needLeft) {
    Point center = GetCenter(start, end);

    double len = GetLength(start, end) / 2;

    Point pt1;
    Point pt2; // 一左，一右两个点

    // 因为下面要计算斜率，所以需要判断y坐标是否相等
    if (end.y == start.y) {
        pt1.x = center.x;
        pt2.x = pt1.x;
        pt1.y = len + center.y;
        pt2.y = -len + center.y;
    } else {
        // 斜率
        double slope = (double)-(end.x - start.x) / (end.y - start.y);

        pt1.x = sqrt(len * len / (slope * slope + 1)) + center.x;
        pt2.x = -sqrt(len * len / (slope * slope + 1)) + center.x;
        pt1.y = slope * (pt1.x - center.x) + center.y;
        pt2.y = slope * (pt2.x - center.x) + center.y;
    }

    // 需要左侧的点
    if (needLeft) {
        if (IsLeft(start, end, pt1)) // 判断点1在左侧
        {
            return pt1;
        } else {
            return pt2;
        }
    } else {                          // 需要右侧的点
        if (!IsLeft(start, end, pt1)) // 判断点1在右侧
        {
            return pt1;
        } else {
            return pt2;
        }
    }
}

std::vector<Point> FractalDragon::GetVertexs(int32_t step, Point start, Point end, bool needLeft) {
    if (step > 0) {
        // 阶数递减
        step--;
        // 获得垂中
        Point verCenter = GetVerticalCenter(start, end, needLeft);
        // 根据 start  verCenter  end 劈成两半
        // 左边
        std::vector<Point> ptVecLeft = GetVertexs(step, start, verCenter, true);
        // 右边
        std::vector<Point> ptVecRight = GetVertexs(step, verCenter, end, false);
        // 左边和右边的拼接起来
        ptVecLeft.insert(ptVecLeft.end(), ptVecRight.begin(), ptVecRight.end());
        // 返回拼接的结果
        return ptVecLeft;
    } else // 阶数为0 退出递归
    {
        std::vector<Point> ptVec;
        // 最后一阶，不用计算垂中点，直接返回 start end
        ptVec.push_back(start);
        ptVec.push_back(end);
        return ptVec;
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
