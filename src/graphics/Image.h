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
    
    // GIF动画支持
    std::vector<std::vector<std::vector<Color>>> frames; // 存储所有帧
    std::vector<int> frameDelays; // 每帧的延迟时间（毫秒）
    int currentFrame;
    bool isAnimated;
    
    bool initFFmpeg();
    void cleanupFFmpeg();
    bool decodeFrame();
    bool decodeAllFrames();
    
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
    
    // GIF动画支持
    bool isGifAnimated() const { return isAnimated; }
    int getFrameCount() const { return frames.size(); }
    int getCurrentFrame() const { return currentFrame; }
    int getFrameDelay(int frameIndex) const;
    bool nextFrame();
    void setFrame(int frameIndex);
    std::vector<Point> getAnimatedPoints() const;
};

#endif // IMAGE_H