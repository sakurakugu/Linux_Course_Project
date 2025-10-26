#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include "../core/Point.h"
#include "../core/Color.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

class Image {
private:
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;
    
    // FFmpeg相关成员
    AVFormatContext* formatContext;
    AVCodecContext* codecContext;
    AVFrame* frame;
    AVFrame* frameRGB;
    SwsContext* swsContext;
    uint8_t* buffer;
    
    bool initFFmpeg();
    void cleanupFFmpeg();
    bool decodeFrame();
    
public:
    Image();
    ~Image();
    
    // 支持多种图片格式
    bool loadImage(const std::string& filename);
    
    // 保持向后兼容的PPM加载方法
    bool loadPPM(const std::string& filename);
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    Color getPixel(int x, int y) const;
    std::vector<Point> getPoints() const;
};

#endif // IMAGE_H