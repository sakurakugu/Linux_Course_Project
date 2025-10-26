# Linux 图形编程项目

这是一个基于 Linux framebuffer 的图形编程项目，实现了分形龙、奥运五环的绘制和图片显示功能。

## 功能特性

- **分形龙绘制**: 使用递归算法绘制分形龙图案
- **奥运五环**: 绘制标准的奥运五环，支持交互式控制
- **贪吃蛇游戏**: 经典的贪吃蛇游戏，支持实时控制和游戏状态管理
- **冒泡排序可视化**: 动态展示冒泡排序算法的执行过程
- **图片显示**: 支持多种图片格式的加载和显示（PNG、JPEG、BMP、GIF、PPM等）
- **实时交互**: 支持键盘控制图形的移动、旋转和缩放
- **跨平台**: 支持在 Linux 和 WSL 环境中编译运行

## 编译环境

### 系统要求
- Linux 系统或 Windows WSL
- GCC 编译器 (支持 C++23)
- CMake (>= 3.10)
- Make 工具
- FFmpeg 开发库 (用于图片格式支持)

### 依赖安装

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake git pkg-config
sudo apt-get install libavformat-dev libavcodec-dev libavutil-dev libswscale-dev ffmpeg
```

#### CentOS/RHEL
```bash
sudo yum groupinstall "Development Tools"
sudo yum install cmake git pkg-config
sudo yum install epel-release
sudo yum install ffmpeg-devel
```

## 编译方法

### 快速编译
```bash
chmod +x build.sh
./build.sh
```

### WSL环境一键配置
```bash
chmod +x wsl-setup.sh
./wsl-setup.sh
```

### 手动编译
```bash
mkdir build
cd build
cmake ..
make
```

## 运行方法

### 分形龙模式
```bash
./build/bin/HomeWork dragon <迭代次数>
```

示例：
```bash
./build/bin/HomeWork dragon 10
```

### 奥运五环模式
```bash
./build/bin/HomeWork olympic
```

#### 控制方式
- **WASD**: 移动图形
- **Q/E**: 旋转图形（Q逆时针，E顺时针）
- **-/=**: 缩放图形（-缩小，=放大）
- **Q(大写)/ESC**: 退出程序

### 贪吃蛇游戏模式
```bash
./build/bin/HomeWork snake
```

#### 游戏控制
- **WASD**: 控制蛇的移动方向
  - **W**: 向上移动
  - **A**: 向左移动
  - **S**: 向下移动
  - **D**: 向右移动
- **P**: 暂停/继续游戏
- **R**: 重新开始游戏
- **Q/ESC**: 退出游戏

#### 游戏规则
- 控制蛇吃食物来增长身体
- 避免撞到墙壁或自己的身体
- 每吃到一个食物得分增加
- 蛇的移动速度会随着长度增加而加快

### 冒泡排序可视化模式
```bash
./build/bin/HomeWork bubble [数组大小]
```

示例：
```bash
./build/bin/HomeWork bubble 30    # 30个元素的数组
./build/bin/HomeWork bubble 50    # 50个元素的数组（默认）
./build/bin/HomeWork bubble 80    # 80个元素的数组
```

#### 控制方式
- **SPACE**: 开始/暂停排序过程
- **R**: 重新生成随机数组
- **Q/ESC**: 退出程序

#### 可视化特性
- 实时显示排序过程中的数组状态
- 不同颜色表示不同的元素状态
- 支持1-100个元素的数组大小
- 动态调整排序速度以便观察

### 图片显示模式
```bash
./build/bin/HomeWork image <图片路径>
```

示例：
```bash
./build/bin/HomeWork image test_image.png
./build/bin/HomeWork image test_image.jpg
./build/bin/HomeWork image test_image.bmp
./build/bin/HomeWork image test_image.ppm
```

#### 支持的图片格式
- **PNG**: 便携式网络图形格式
- **JPEG/JPG**: 联合图像专家组格式
- **BMP**: Windows位图格式
- **GIF**: 图形交换格式
- **PPM P3**: ASCII格式的PPM图片
- **PPM P6**: 二进制格式的PPM图片
- 图片会自动居中显示
- 超出屏幕的图片会自动调整位置
- 使用FFmpeg库提供强大的格式支持

## 项目结构

```
├── src/
│   ├── core/           # 核心功能
│   │   ├── Framebuffer.cpp/h  # framebuffer操作
│   │   ├── Point.h     # 点和颜色定义
│   │   ├── Color.h     # 颜色处理
│   │   └── Geometry.h  # 几何计算
│   ├── graphics/       # 图形绘制
│   │   ├── Image.cpp/h # 图片处理类
│   │   ├── fractals/   # 分形算法
│   │   │   └── FractalDragon.cpp/h  # 分形龙实现
│   │   ├── games/      # 游戏模块
│   │   │   ├── SnakeGame.cpp/h      # 贪吃蛇游戏
│   │   │   ├── Snake.cpp/h          # 蛇类实现
│   │   │   ├── Food.cpp/h           # 食物类实现
│   │   │   └── BubbleSort.cpp/h     # 冒泡排序可视化
│   │   └── shapes/     # 几何图形
│   │       ├── OlympicRings.cpp/h   # 奥运五环
│   │       ├── Circle.cpp/h         # 圆形
│   │       ├── Line.cpp/h           # 直线
│   │       └── Polyline.cpp/h       # 多段线
│   ├── utils/          # 工具类
│   │   ├── Application.cpp/h        # 应用程序管理
│   │   └── InputHandler.cpp/h       # 输入处理
│   └── main.cpp        # 主程序入口
├── test/               # 测试文件
│   ├── test_image.ppm  # PPM测试图片
│   ├── test_image.jpg  # JPEG测试图片
│   ├── test_image.png  # PNG测试图片
│   ├── test_image.bmp  # BMP测试图片
│   └── test_image.gif  # GIF测试图片
├── build.sh            # 构建脚本
├── wsl-setup.sh        # WSL环境配置脚本
└── CMakeLists.txt      # CMake配置
```

## WSL 支持

项目完全支持在 Windows WSL 环境中编译和开发。

### WSL 环境配置
```bash
chmod +x wsl-setup.sh
./wsl-setup.sh
```

### 注意事项
- WSL 环境中可能无法直接访问 framebuffer 设备
- 建议在真实 Linux 系统中运行图形程序
- 或者配置 WSLg/X11 转发来支持图形显示

## 技术特点

- **高效绘制**: 直接操作 framebuffer，性能优异
- **模块化设计**: 清晰的代码结构，易于扩展
- **多媒体支持**: 集成FFmpeg库，支持多种图片格式
- **图片处理**: 强大的图片解码和格式转换能力
- **边框绘制**: 高效的边框绘制算法
- **数学算法**: 实现了复杂的分形几何算法
- **交互控制**: 实时响应用户输入
- **跨平台兼容**: 支持多种 Linux 发行版和WSL

## 开发说明

### 添加新图形
1. 在 `src/graphics/shapes/` 目录下创建新的图形类
2. 继承基础图形接口
3. 实现 `GetPoints()` 方法返回绘制点集
4. 在 `main.cpp` 中添加对应的命令行选项

### 添加新图片格式
1. FFmpeg已支持大多数主流图片格式，无需额外开发
2. 如需支持特殊格式，可在 `Image` 类中添加专用加载方法
3. 利用FFmpeg的强大解码能力，自动处理格式转换
4. 确保返回标准的RGB颜色格式

### 性能优化
- 使用向量化操作批量绘制点
- 实现了高效的 framebuffer 清屏算法
- 支持多线程编译加速构建过程
- 图片加载使用内存预分配优化


