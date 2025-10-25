#pragma once

#include "Geometry.h"

class CLine : public CGeometry {
  public:
    CLine(CPoint start, CPoint end, CColor cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
    };

    void Set(CPoint start, CPoint end, CColor cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
    };

  protected:
    virtual VecPt ToPoints();

  protected:
    CPoint m_start;
    CPoint m_end;
};
