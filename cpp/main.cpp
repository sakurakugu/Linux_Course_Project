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
    int step = 2;
    if (argc == 2) {
        step = atoi(argv[1]);
    }

    CFramebuffer framebuffer;
    framebuffer.Init();

    // TODO
    // 绘制分形龙
    CPoint start = CPoint(200, 200);
    CPoint end = CPoint(400, 400);

    CFractalDragon fractalDragon(start, end, step, CColor(0, 255, 0));

    framebuffer.DrawPoints(fractalDragon.GetPoints());

    return 0;
}
