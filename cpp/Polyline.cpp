#include "Polyline.h"
#include "Line.h"

std::vector<Point> Polyline::ToPoints() {
    std::vector<Point> points;

    for (size_t i = 0; i < m_vertexs.size() - 1; ++i) {
        Line line(m_vertexs[i], m_vertexs[i + 1], m_color);
        std::vector<Point> cptVec = line.GetPoints();
        points.insert(points.end(), cptVec.begin(), cptVec.end());
    }

    // 闭合多段线
    if (m_closure) {
        Line line(m_vertexs[m_vertexs.size() - 1], m_vertexs[0], m_color);
        std::vector<Point> cptVec = line.GetPoints();
        points.insert(points.end(), cptVec.begin(), cptVec.end());
    }

    return points;
}