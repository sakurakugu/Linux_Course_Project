#include "Polyline.h"
#include "Line.h"

VecPt CPolyline::ToPoints() {
    VecPt ptVec;

    for (size_t i = 0; i < m_vertexs.size() - 1; ++i) {
        CLine line(m_vertexs[i], m_vertexs[i + 1], m_color);
        VecPt cptVec = line.GetPoints();
        ptVec.insert(ptVec.end(), cptVec.begin(), cptVec.end());
    }

    // 闭合多段线
    if (m_closure) {
        CLine line(m_vertexs[m_vertexs.size() - 1], m_vertexs[0], m_color);
        VecPt cptVec = line.GetPoints();
        ptVec.insert(ptVec.end(), cptVec.begin(), cptVec.end());
    }

    return ptVec;
}