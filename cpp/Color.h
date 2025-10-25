#ifndef XXXXX_COLOR
#define XXXXX_COLOR

class CColor {
  public:
    CColor() {
        R = 255;
        G = 0;
        B = 0;
        v = R << 16 | G << 8 | B;
    }

    CColor(int vv) { v = vv; };

    CColor(int r, int g, int b) {
        R = r;
        G = g;
        B = b;
        v = R << 16 | G << 8 | B;
    };

  public:
    int R;
    int G;
    int B;
    int v; // 用于绘图的颜色值
};

#endif // XXXXX_COLOR
