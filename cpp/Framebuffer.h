#pragma once

#include "Point.h"
#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>

class CFramebuffer {
  public:
    CFramebuffer();
    ~CFramebuffer();
    int32_t Init();
    void DrawPoint(Point pt);
    void DrawPoints(std::vector<Point> ptVec);

    int32_t GetWidth();
    int32_t GetHeight();
    Point GetCenter();

  protected:
    void UnInit();

  protected:
    char *buf;
    int32_t fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int64_t screensize;
};
