#ifndef XXXXX_Polyline
#define XXXXX_Polyline

#include "Geometry.h"

class CPolyline : public CGeometry {
  public:
    CPolyline(VecPt vertexs, CColor cc, bool closure = false) {
        m_vertexs = vertexs;
        m_color = cc;
        m_closure = closure;
    };

    void Set(VecPt vertexs, CColor cc, bool closure = false) {
        m_vertexs = vertexs;
        m_color = cc;
        m_closure = closure;
    };

  protected:
    virtual VecPt ToPoints();

  protected:
    VecPt m_vertexs;
    bool m_closure; // 多边形是否闭合
};

#endif // XXXXX_LINE
