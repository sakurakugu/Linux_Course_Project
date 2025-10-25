#include "core/Framebuffer.h"
#include "graphics/fractals/FractalDragon.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int32_t step = 2;
    if (argc == 2) {
        step = atoi(argv[1]);
    }

    CFramebuffer framebuffer;
    framebuffer.Init();

    // 清屏，确保每次运行都有干净的画布
    framebuffer.Clear();

    // 绘制分形龙
    Point start = Point(200, 200);
    Point end = Point(400, 400);

    FractalDragon fractalDragon(start, end, step, Color(0, 255, 0));

    framebuffer.DrawPoints(fractalDragon.GetPoints());

    return 0;
}
