#include "core/Framebuffer.h"
#include "graphics/fractals/FractalDragon.h"
#include "graphics/shapes/OlympicRings.h"
#include "graphics/Image.h"
#include "graphics/games/SnakeGame.h"
#include "graphics/games/BubbleSort.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <termios.h>

void printUsage(const char* programName) {
    std::cout << "用法: " << std::endl;
    std::cout << "  " << programName << " dragon <迭代次数>  - 绘制分形龙" << std::endl;
    std::cout << "  " << programName << " olympic           - 绘制奥运五环（支持交互控制）" << std::endl;
    std::cout << "  " << programName << " snake             - 贪吃蛇游戏" << std::endl;
    std::cout << "  " << programName << " bubble [数组大小] - 冒泡排序可视化" << std::endl;
    std::cout << "  " << programName << " image <图片路径>  - 显示图片（支持PPM、JPG、PNG、BMP、GIF等格式）" << std::endl;
    std::cout << "示例: " << std::endl;
    std::cout << "  " << programName << " dragon 10" << std::endl;
    std::cout << "  " << programName << " olympic" << std::endl;
    std::cout << "  " << programName << " snake" << std::endl;
    std::cout << "  " << programName << " bubble 30" << std::endl;
    std::cout << "  " << programName << " image /path/to/image.ppm" << std::endl;
    std::cout << "参数说明:" << std::endl;
    std::cout << "  dragon: 绘制分形龙，需要指定迭代次数 (建议范围: 1-15)" << std::endl;
    std::cout << "  olympic: 绘制奥运五环，支持以下控制:" << std::endl;
    std::cout << "    WASD - 移动图形" << std::endl;
    std::cout << "    Q/E  - 旋转图形（Q逆时针，E顺时针）" << std::endl;
    std::cout << "    -/=  - 缩放图形（-缩小，=放大）" << std::endl;
    std::cout << "    Q(大写)/ESC - 退出程序" << std::endl;
    std::cout << "  snake: 贪吃蛇游戏，支持以下控制:" << std::endl;
    std::cout << "    WASD - 控制蛇的移动方向" << std::endl;
    std::cout << "    P    - 暂停/继续游戏" << std::endl;
    std::cout << "    R    - 重新开始游戏" << std::endl;
    std::cout << "    Q/ESC - 退出游戏" << std::endl;
    std::cout << "  bubble: 冒泡排序算法可视化，支持以下控制:" << std::endl;
    std::cout << "    SPACE - 开始/暂停排序" << std::endl;
    std::cout << "    R     - 重新生成随机数组" << std::endl;
    std::cout << "    Q/ESC - 退出程序" << std::endl;
}

// 设置终端为非阻塞模式
void setNonBlockingInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// 恢复终端模式
void restoreInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// 获取键盘输入
char getKey() {
    char ch = 0;
    ssize_t result = read(STDIN_FILENO, &ch, 1);
    (void)result; // 避免未使用变量警告
    return ch;
}

int main(int argc, char *argv[]) {
    // 自动清屏
    system("clear");
    
    // 检查参数数量
    if (argc < 2) {
        std::cout << "错误: 参数数量不正确" << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    // 解析命令行参数
    const char* command = argv[1];

    CFramebuffer framebuffer;
    framebuffer.Init();

    if (strcmp(command, "dragon") == 0) {
        // 分形龙模式
        if (argc != 3) {
            std::cout << "错误: dragon模式需要指定迭代次数" << std::endl;
            printUsage(argv[0]);
            return 1;
        }

        const char* stepStr = argv[2];
        int32_t step = atoi(stepStr);
        if (step <= 0) {
            std::cout << "错误: 迭代次数必须是正整数" << std::endl;
            printUsage(argv[0]);
            return 1;
        }

        if (step > 20) {
            std::cout << "警告: 迭代次数过大可能导致性能问题，建议使用1-15之间的值" << std::endl;
        }

        std::cout << "绘制分形龙，迭代次数: " << step << std::endl;

        // 清屏，确保每次运行都有干净的画布
        framebuffer.Clear();

        // 绘制白色边框
        framebuffer.DrawBorder();

        // 绘制分形龙
        Point start = Point(200, 200);
        Point end = Point(400, 400);

        FractalDragon fractalDragon(start, end, step, Color(0, 255, 0));
        framebuffer.DrawPoints(fractalDragon.GetPoints());

    } else if (strcmp(command, "olympic") == 0) {
        // 奥运五环模式
        std::cout << "绘制奥运五环，支持交互控制:" << std::endl;
        std::cout << "  WASD - 移动图形" << std::endl;
        std::cout << "  Q/E  - 旋转图形（Q逆时针，E顺时针）" << std::endl;
        std::cout << "  -/=  - 缩放图形（-缩小，=放大）" << std::endl;
        std::cout << "  Q(大写)/ESC - 退出程序" << std::endl;
        
        // 设置非阻塞输入
        setNonBlockingInput();
        
        // 初始化奥运五环位置
        Point center(400, 300);
        OlympicRings olympicRings(center);
        
        bool running = true;
        const int moveStep = 10; // 每次移动的像素数
        const double rotateStep = 0.1; // 每次旋转的角度（弧度）
        const double scaleStep = 0.05; // 每次缩放的步长
        
        while (running) {
            // 清屏
            framebuffer.Clear();
            
            // 绘制白色边框
            framebuffer.DrawBorder();
            
            // 绘制奥运五环
            framebuffer.DrawPoints(olympicRings.GetPoints());
            
            // 检查键盘输入
            char key = getKey();
            
           switch (key) {
        case 'w':
        case 'W':
            olympicRings.Translate(0, -moveStep);
            break;
        case 's':
        case 'S':
            olympicRings.Translate(0, moveStep);
            break;
        case 'a':
        case 'A':
            olympicRings.Translate(-moveStep, 0);
            break;
        case 'd':
        case 'D':
            olympicRings.Translate(moveStep, 0);
            break;
        case 'q':
            olympicRings.Rotate(-rotateStep); // 逆时针旋转
            break;
        case 'Q':
        case 27: // ESC 键
            running = false;
            break;
        case 'e':
        case 'E':
            olympicRings.Rotate(rotateStep); // 顺时针旋转
            break;
        case '-':
        case '_':
            olympicRings.Scale(1.0 - scaleStep); // 缩小
            break;
        case '=':
        case '+':
            olympicRings.Scale(1.0 + scaleStep); // 放大
            break;
    }
            
            // 短暂延迟，避免CPU占用过高
            usleep(50000); // 50ms
        }
        
        // 恢复终端模式
        restoreInput();
        std::cout << "程序退出" << std::endl;
        
    } else if (strcmp(command, "snake") == 0) {
        // 贪吃蛇游戏模式
        std::cout << "启动贪吃蛇游戏..." << std::endl;
        
        SnakeGame snakeGame(&framebuffer);
        snakeGame.Run();
        
    } else if (strcmp(command, "bubble") == 0) {
        // 冒泡排序可视化模式
        int arraySize = 50; // 默认数组大小
        
        if (argc == 3) {
            const char* sizeStr = argv[2];
            int size = atoi(sizeStr);
            if (size > 0 && size <= 100) {
                arraySize = size;
            } else {
                std::cout << "警告: 数组大小无效，使用默认值50（建议范围: 1-100）" << std::endl;
            }
        }
        
        std::cout << "启动冒泡排序可视化，数组大小: " << arraySize << std::endl;
        
        BubbleSort bubbleSort(&framebuffer, arraySize);
        bubbleSort.Run();
        
    } else if (strcmp(command, "image") == 0) {
        // 图片显示模式
        if (argc != 3) {
            std::cout << "错误: image模式需要指定图片路径" << std::endl;
            printUsage(argv[0]);
            return 1;
        }

        const char* imagePath = argv[2];
        std::cout << "加载并显示图片: " << imagePath << std::endl;

        // 加载图片（支持多种格式）
        Image image;
        if (!image.loadImage(imagePath)) {
            // 如果FFmpeg加载失败，尝试PPM格式
            if (!image.loadPPM(imagePath)) {
                std::cout << "错误: 无法加载图片 " << imagePath << std::endl;
                std::cout << "支持的格式: JPG, PNG, BMP, GIF, PPM等" << std::endl;
                return 1;
            }
        }

        // 清屏
        framebuffer.Clear();

        // 绘制白色边框
        framebuffer.DrawBorder();

        // 计算图片居中显示的位置
        int screenWidth = framebuffer.GetWidth();
        int screenHeight = framebuffer.GetHeight();
        int imageWidth = image.getWidth();
        int imageHeight = image.getHeight();
        
        int offsetX = (screenWidth - imageWidth) / 2;
        int offsetY = (screenHeight - imageHeight) / 2;
        
        // 确保图片不会超出屏幕边界（考虑边框）
        if (offsetX < 2) offsetX = 2;
        if (offsetY < 2) offsetY = 2;
        if (offsetX + imageWidth > screenWidth - 2) offsetX = screenWidth - imageWidth - 2;
        if (offsetY + imageHeight > screenHeight - 2) offsetY = screenHeight - imageHeight - 2;

        // std::cout << "图片尺寸: " << imageWidth << "x" << imageHeight << std::endl;
        // std::cout << "显示位置: (" << offsetX << ", " << offsetY << ")" << std::endl;

        // 检查是否为GIF动画
        if (image.isGifAnimated()) {
            std::cout << "检测到GIF动画，共 " << image.getFrameCount() << " 帧" << std::endl;
            std::cout << "按ESC键退出动画播放..." << std::endl;
            
            // 设置非阻塞输入
            setNonBlockingInput();
            
            bool playing = true;
            while (playing) {
                // 清屏
                framebuffer.Clear();
                
                // 绘制白色边框
                framebuffer.DrawBorder();
                
                // 绘制当前帧
                std::vector<Point> imagePoints = image.getAnimatedPoints();
                for (auto& point : imagePoints) {
                    point.x += offsetX;
                    point.y += offsetY;
                }
                framebuffer.DrawPoints(imagePoints);
                
                // 检查键盘输入
                char key = getKey();
                if (key == 27) { // ESC键
                    playing = false;
                    break;
                }
                
                // 等待当前帧的延迟时间
                int delay = image.getFrameDelay(image.getCurrentFrame());
                usleep(delay * 1000); // 转换为微秒
                
                // 切换到下一帧
                image.nextFrame();
            }
            
            // 恢复终端模式
            restoreInput();
            std::cout << "GIF动画播放结束" << std::endl;
        } else {
            // 静态图片显示
            std::vector<Point> imagePoints = image.getPoints();
            for (auto& point : imagePoints) {
                point.x += offsetX;
                point.y += offsetY;
            }
            framebuffer.DrawPoints(imagePoints);
            
            std::cout << "图片显示完成" << std::endl;
        }
        
    } else {
        std::cout << "错误: 未知的命令 '" << command << "'" << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}
