#pragma once
#include <cstdint>

class Color {
  public:
    // 默认构造函数 - 使用初始化列表
    Color() : R(255), G(0), B(0), v(calculateValue(255, 0, 0)) {}

    // 从颜色值构造
    explicit Color(int32_t vv) : v(vv) {
        // 从颜色值反推RGB
        R = (vv >> 16) & 0xFF;
        G = (vv >> 8) & 0xFF;
        B = vv & 0xFF;
    }

    // 从RGB构造 - 使用初始化列表和辅助函数
    Color(int32_t r, int32_t g, int32_t b) 
        : R(clamp(r)), G(clamp(g)), B(clamp(b)), v(calculateValue(R, G, B)) {}

    // 拷贝构造函数
    Color(const Color& other) = default;

    // 移动构造函数
    Color(Color&& other) noexcept = default;

    // 拷贝赋值运算符
    Color& operator=(const Color& other) = default;

    // 移动赋值运算符
    Color& operator=(Color&& other) noexcept = default;

    // 设置RGB值
    void SetRGB(int32_t r, int32_t g, int32_t b) {
        R = clamp(r);
        G = clamp(g);
        B = clamp(b);
        v = calculateValue(R, G, B);
    }

    // 比较运算符
    bool operator==(const Color& other) const {
        return R == other.R && G == other.G && B == other.B;
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

  private:
    // 辅助函数：计算颜色值
    static constexpr int32_t calculateValue(int32_t r, int32_t g, int32_t b) {
        return (r << 16) | (g << 8) | b;
    }

    // 辅助函数：限制颜色值范围
    static constexpr int32_t clamp(int32_t value) {
        return value < 0 ? 0 : (value > 255 ? 255 : value);
    }

  public:
    int32_t R;
    int32_t G;
    int32_t B;
    int32_t v; // 用于绘图的颜色值
};
