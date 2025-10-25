#ifndef FRACTAL_DRAGON
#define FRACTAL_DRAGON

#include "Geometry.h"

class CFractalDragon : public CGeometry {
  public:
    CFractalDragon(CPoint start, CPoint end, int step, CColor cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
        m_step = step;
    };

    void Set(CPoint start, CPoint end, int step, CColor cc) {
        m_start = start;
        m_end = end;
        m_color = cc;
        m_step = step;
    };

  protected:
    virtual VecPt ToPoints();

    VecPt GetVertexs(int step, CPoint start, CPoint end, bool needLeft);

  protected:
    bool IsLeft(CPoint &ptA, CPoint &ptB, CPoint &ptC);
    double GetLength(CPoint &pt1, CPoint &pt2);
    CPoint GetCenter(CPoint &pt1, CPoint &pt2);
    CPoint GetVerticalCenter(CPoint &start, CPoint &end, bool isLeft);

  protected:
    CPoint m_start;
    CPoint m_end;
    int m_step;
};

#endif // FRACTAL_DRAGON
