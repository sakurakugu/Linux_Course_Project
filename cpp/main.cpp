#include "Framebuffer.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "FractalDragon.h"
#include "Framebuffer.h"
#include <math.h>

int main(int argc, char *argv[]) {
    int32_t step = 2;
    if (argc == 2) {
        step = atoi(argv[1]);
    }

    CFramebuffer framebuffer;
    framebuffer.Init();

    // 绘制分形龙
    Point start = Point(200, 200);
    Point end = Point(400, 400);

    FractalDragon fractalDragon(start, end, step, Color(0, 255, 0));

    framebuffer.DrawPoints(fractalDragon.GetPoints());

    return 0;
}
