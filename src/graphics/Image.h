#pragma once

#include "../core/Point.h"
#include "../core/Color.h"
#include <vector>
#include <string>

class Image {
public:
    Image();
    ~Image();
    
    // 加载PPM格式图片
    bool LoadPPM(const std::string& filename);
    
    // 获取图片尺寸
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    
    // 获取指定位置的像素颜色
    Color GetPixel(int x, int y) const;
    
    // 获取所有像素点（用于绘制）
    std::vector<Point> GetPoints(int offsetX = 0, int offsetY = 0) const;
    
    // 检查图片是否已加载
    bool IsLoaded() const { return loaded; }

private:
    int width;
    int height;
    int maxVal;
    std::vector<Color> pixels;
    bool loaded;
    
    // 跳过PPM文件中的注释
    void SkipComments(FILE* file);
};