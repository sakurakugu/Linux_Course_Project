#pragma once
#include <cstdint>
class CColor {
  public:
    CColor() {
        R = 255;
        G = 0;
        B = 0;
        v = R << 16 | G << 8 | B;
    }

    CColor(int32_t vv) { v = vv; };

    CColor(int32_t r, int32_t g, int32_t b) {
        R = r;
        G = g;
        B = b;
        v = R << 16 | G << 8 | B;
    };

  public:
    int32_t R;
    int32_t G;
    int32_t B;
    int32_t v; // 用于绘图的颜色值
};
