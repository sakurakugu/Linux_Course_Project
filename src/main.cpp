#include "core/Framebuffer.h"
#include "graphics/fractals/FractalDragon.h"
#include "graphics/shapes/OlympicRings.h"
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
    std::cout << "  " << programName << " olympic           - 绘制奥运五环（可用WASD移动）" << std::endl;
    std::cout << "示例: " << std::endl;
    std::cout << "  " << programName << " dragon 10" << std::endl;
    std::cout << "  " << programName << " olympic" << std::endl;
    std::cout << "参数说明:" << std::endl;
    std::cout << "  dragon: 绘制分形龙，需要指定迭代次数 (建议范围: 1-15)" << std::endl;
    std::cout << "  olympic: 绘制奥运五环，按WASD键移动，按q键退出" << std::endl;
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
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

int main(int argc, char *argv[]) {
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

        // 绘制分形龙
        Point start = Point(200, 200);
        Point end = Point(400, 400);

        FractalDragon fractalDragon(start, end, step, Color(0, 255, 0));
        framebuffer.DrawPoints(fractalDragon.GetPoints());

    } else if (strcmp(command, "olympic") == 0) {
        // 奥运五环模式
        std::cout << "绘制奥运五环，使用WASD键移动，按q键退出" << std::endl;
        
        // 设置非阻塞输入
        setNonBlockingInput();
        
        // 初始化奥运五环位置
        Point center(400, 300);
        OlympicRings olympicRings(center);
        
        bool running = true;
        const int moveStep = 10; // 每次移动的像素数
        
        while (running) {
            // 清屏
            framebuffer.Clear();
            
            // 绘制奥运五环
            framebuffer.DrawPoints(olympicRings.GetPoints());
            
            // 检查键盘输入
            char key = getKey();
            Point currentCenter = olympicRings.GetCenter();
            
            switch (key) {
                case 'w':
                case 'W':
                    olympicRings.SetCenter(Point(currentCenter.x, currentCenter.y - moveStep));
                    break;
                case 's':
                case 'S':
                    olympicRings.SetCenter(Point(currentCenter.x, currentCenter.y + moveStep));
                    break;
                case 'a':
                case 'A':
                    olympicRings.SetCenter(Point(currentCenter.x - moveStep, currentCenter.y));
                    break;
                case 'd':
                case 'D':
                    olympicRings.SetCenter(Point(currentCenter.x + moveStep, currentCenter.y));
                    break;
                case 'q':
                case 'Q':
                    running = false;
                    break;
            }
            
            // 短暂延迟，避免CPU占用过高
            usleep(50000); // 50ms
        }
        
        // 恢复终端模式
        restoreInput();
        std::cout << "程序退出" << std::endl;
        
    } else {
        std::cout << "错误: 未知的命令 '" << command << "'" << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}
