#include "Image.h"
#include <iostream>
#include <fstream>

Image::Image() : width(0), height(0), formatContext(nullptr), codecContext(nullptr), 
                 frame(nullptr), frameRGB(nullptr), swsContext(nullptr), buffer(nullptr) {
    // FFmpeg 4.0+不再需要av_register_all()
}

Image::~Image() {
    cleanupFFmpeg();
}

bool Image::initFFmpeg() {
    formatContext = avformat_alloc_context();
    if (!formatContext) {
        std::cerr << "Error: Could not allocate format context" << std::endl;
        return false;
    }
    
    frame = av_frame_alloc();
    frameRGB = av_frame_alloc();
    
    if (!frame || !frameRGB) {
        std::cerr << "Error: Could not allocate frames" << std::endl;
        return false;
    }
    
    return true;
}

void Image::cleanupFFmpeg() {
    if (buffer) {
        av_free(buffer);
        buffer = nullptr;
    }
    
    if (frameRGB) {
        av_frame_free(&frameRGB);
    }
    
    if (frame) {
        av_frame_free(&frame);
    }
    
    if (swsContext) {
        sws_freeContext(swsContext);
        swsContext = nullptr;
    }
    
    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
    
    if (formatContext) {
        avformat_close_input(&formatContext);
    }
}

bool Image::loadImage(const std::string& filename) {
    // 清理之前的资源
    cleanupFFmpeg();
    
    // 初始化FFmpeg
    if (!initFFmpeg()) {
        return false;
    }
    
    // 打开输入文件
    if (avformat_open_input(&formatContext, filename.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    // 获取流信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Error: Could not find stream information" << std::endl;
        return false;
    }
    
    // 查找视频流
    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }
    
    if (videoStreamIndex == -1) {
        std::cerr << "Error: Could not find video stream" << std::endl;
        return false;
    }
    
    // 获取解码器参数
    AVCodecParameters* codecParams = formatContext->streams[videoStreamIndex]->codecpar;
    
    // 查找解码器
    const AVCodec* codec = avcodec_find_decoder(codecParams->codec_id);
    if (!codec) {
        std::cerr << "Error: Unsupported codec" << std::endl;
        return false;
    }
    
    // 分配解码器上下文
    codecContext = avcodec_alloc_context3(codec);
    if (!codecContext) {
        std::cerr << "Error: Could not allocate codec context" << std::endl;
        return false;
    }
    
    // 复制解码器参数到上下文
    if (avcodec_parameters_to_context(codecContext, codecParams) < 0) {
        std::cerr << "Error: Could not copy codec parameters to context" << std::endl;
        return false;
    }
    
    // 打开解码器
    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        std::cerr << "Error: Could not open codec" << std::endl;
        return false;
    }
    
    // 设置图片尺寸
    width = codecContext->width;
    height = codecContext->height;
    
    // 分配RGB帧的缓冲区
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, width, height, 1);
    buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
    
    // 设置RGB帧的数据指针
    av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24, width, height, 1);
    
    // 初始化转换上下文
    swsContext = sws_getContext(width, height, codecContext->pix_fmt,
                               width, height, AV_PIX_FMT_RGB24,
                               SWS_BILINEAR, nullptr, nullptr, nullptr);
    
    if (!swsContext) {
        std::cerr << "Error: Could not initialize conversion context" << std::endl;
        return false;
    }
    
    // 解码第一帧
    return decodeFrame();
}

bool Image::decodeFrame() {
    AVPacket* packet = av_packet_alloc();
    if (!packet) {
        return false;
    }
    
    // 读取数据包
    while (av_read_frame(formatContext, packet) >= 0) {
        // 发送数据包到解码器
        if (avcodec_send_packet(codecContext, packet) == 0) {
            // 接收解码后的帧
            if (avcodec_receive_frame(codecContext, frame) == 0) {
                // 转换像素格式
                sws_scale(swsContext, (uint8_t const * const *)frame->data,
                         frame->linesize, 0, height,
                         frameRGB->data, frameRGB->linesize);
                
                // 将RGB数据转换为我们的像素格式
                pixels.resize(height);
                for (int y = 0; y < height; y++) {
                    pixels[y].resize(width);
                    for (int x = 0; x < width; x++) {
                        int index = y * frameRGB->linesize[0] + x * 3;
                        uint8_t r = frameRGB->data[0][index];
                        uint8_t g = frameRGB->data[0][index + 1];
                        uint8_t b = frameRGB->data[0][index + 2];
                        pixels[y][x] = Color(r, g, b);
                    }
                }
                
                av_packet_free(&packet);
                return true;
            }
        }
        av_packet_unref(packet);
    }
    
    av_packet_free(&packet);
    return false;
}

bool Image::loadPPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
    
    std::string format;
    file >> format;
    
    if (format != "P3" && format != "P6") {
        std::cerr << "Error: Unsupported PPM format: " << format << std::endl;
        return false;
    }
    
    // 跳过注释
    char c = file.get();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        c = file.get();
    }
    
    while (c == '#') {
        while (c != '\n' && c != '\r') {
            c = file.get();
        }
        while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            c = file.get();
        }
    }
    file.putback(c);
    
    int maxVal;
    file >> width >> height >> maxVal;
    
    if (width <= 0 || height <= 0 || maxVal <= 0) {
        std::cerr << "Error: Invalid PPM dimensions or max value" << std::endl;
        return false;
    }
    
    pixels.resize(height);
    for (int y = 0; y < height; y++) {
        pixels[y].resize(width);
    }
    
    if (format == "P3") {
        // ASCII格式
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int r, g, b;
                file >> r >> g >> b;
                
                // 将值缩放到0-255范围
                r = (r * 255) / maxVal;
                g = (g * 255) / maxVal;
                b = (b * 255) / maxVal;
                
                pixels[y][x] = Color(r, g, b);
            }
        }
    } else {
        // P6二进制格式
        file.get(); // 跳过换行符
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned char rgb[3];
                file.read(reinterpret_cast<char*>(rgb), 3);
                
                // 将值缩放到0-255范围
                int r = (rgb[0] * 255) / maxVal;
                int g = (rgb[1] * 255) / maxVal;
                int b = (rgb[2] * 255) / maxVal;
                
                pixels[y][x] = Color(r, g, b);
            }
        }
    }
    
    return true;
}

Color Image::getPixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return pixels[y][x];
    }
    return Color(0, 0, 0); // 返回黑色作为默认值
}

std::vector<Point> Image::getPoints() const {
    std::vector<Point> points;
    points.reserve(width * height);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color color = pixels[y][x];
            points.emplace_back(x, y, color);
        }
    }
    
    return points;
}