#include "Image.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>

Image::Image() : width(0), height(0), maxVal(0), loaded(false) {
}

Image::~Image() {
}

void Image::SkipComments(FILE* file) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '#') {
            // 跳过注释行
            while ((ch = fgetc(file)) != EOF && ch != '\n');
        } else if (!isspace(ch)) {
            // 遇到非空白字符，回退一个字符
            ungetc(ch, file);
            break;
        }
    }
}

bool Image::LoadPPM(const std::string& filename) {
    FILE* file = fopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "无法打开图片文件: " << filename << std::endl;
        return false;
    }

    char magic[3];
    if (fread(magic, 1, 2, file) != 2) {
        std::cerr << "读取PPM魔数失败" << std::endl;
        fclose(file);
        return false;
    }
    magic[2] = '\0';

    // 检查是否为P3（ASCII）或P6（二进制）格式
    if (magic[0] != 'P' || (magic[1] != '3' && magic[1] != '6')) {
        std::cerr << "不支持的PPM格式: " << magic << std::endl;
        fclose(file);
        return false;
    }

    bool isBinary = (magic[1] == '6');

    // 跳过空白和注释
    SkipComments(file);

    // 读取宽度、高度和最大值
    if (fscanf(file, "%d", &width) != 1) {
        std::cerr << "读取图片宽度失败" << std::endl;
        fclose(file);
        return false;
    }

    SkipComments(file);
    if (fscanf(file, "%d", &height) != 1) {
        std::cerr << "读取图片高度失败" << std::endl;
        fclose(file);
        return false;
    }

    SkipComments(file);
    if (fscanf(file, "%d", &maxVal) != 1) {
        std::cerr << "读取最大颜色值失败" << std::endl;
        fclose(file);
        return false;
    }

    // 跳过最后一个换行符
    fgetc(file);

    // 分配像素存储空间
    pixels.clear();
    pixels.reserve(width * height);

    // 读取像素数据
    for (int i = 0; i < width * height; i++) {
        int r, g, b;
        
        if (isBinary) {
            // P6格式：二进制数据
            unsigned char rgb[3];
            if (fread(rgb, 1, 3, file) != 3) {
                std::cerr << "读取像素数据失败" << std::endl;
                fclose(file);
                return false;
            }
            r = rgb[0];
            g = rgb[1];
            b = rgb[2];
        } else {
            // P3格式：ASCII数据
            if (fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                std::cerr << "读取像素数据失败" << std::endl;
                fclose(file);
                return false;
            }
        }

        // 将颜色值缩放到0-255范围
        if (maxVal != 255) {
            r = (r * 255) / maxVal;
            g = (g * 255) / maxVal;
            b = (b * 255) / maxVal;
        }

        pixels.push_back(Color(r, g, b));
    }

    fclose(file);
    loaded = true;
    std::cout << "成功加载图片: " << filename << " (" << width << "x" << height << ")" << std::endl;
    return true;
}

Color Image::GetPixel(int x, int y) const {
    if (!loaded || x < 0 || y < 0 || x >= width || y >= height) {
        return Color(0, 0, 0); // 返回黑色
    }
    return pixels[y * width + x];
}

std::vector<Point> Image::GetPoints(int offsetX, int offsetY) const {
    std::vector<Point> points;
    if (!loaded) {
        return points;
    }

    points.reserve(width * height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color color = GetPixel(x, y);
            points.push_back(Point(x + offsetX, y + offsetY, color));
        }
    }

    return points;
}