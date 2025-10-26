# Linux 图形编程项目

这是一个基于 Linux framebuffer 的图形编程项目，实现了分形龙、奥运五环的绘制和图片显示功能。

## 功能特性

- **分形龙绘制**: 使用递归算法绘制分形龙图案
- **奥运五环**: 绘制标准的奥运五环，支持交互式控制
- **图片显示**: 支持PPM格式图片的加载和显示
- **白色边框**: 所有模式都支持白色边框显示
- **实时交互**: 支持键盘控制图形的移动、旋转和缩放
- **跨平台**: 支持在 Linux 和 WSL 环境中编译运行

## 编译环境

### 系统要求
- Linux 系统或 Windows WSL
- GCC 编译器 (支持 C++23)
- CMake (>= 3.10)
- Make 工具

### 依赖安装

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake git
```

#### CentOS/RHEL
```bash
sudo yum groupinstall "Development Tools"
sudo yum install cmake git
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

### 图片显示模式
```bash
./build/bin/HomeWork image <图片路径>
```

示例：
```bash
./build/bin/HomeWork image test_image.ppm
```

#### 支持的图片格式
- **PPM P3**: ASCII格式的PPM图片
- **PPM P6**: 二进制格式的PPM图片
- 图片会自动居中显示
- 超出屏幕的图片会自动调整位置

## 新功能说明

### 1. 白色边框
- 所有显示模式都会自动添加白色边框
- 边框宽度默认为2像素
- 边框颜色为白色(255, 255, 255)

### 2. 图片显示功能
- 支持加载PPM格式图片文件
- 自动检测P3(ASCII)和P6(二进制)格式
- 图片居中显示，自动处理边界
- 支持不同颜色深度的图片

### 3. WSL编译支持
- 完整的WSL环境配置脚本
- 自动检测和安装编译依赖
- 支持WSL1和WSL2
- 提供详细的环境检查和配置指导

## 项目结构

```
├── src/
│   ├── core/           # 核心功能
│   │   ├── Framebuffer.cpp/h  # framebuffer操作
│   │   ├── Point.h     # 点和颜色定义
│   │   └── Color.h     # 颜色处理
│   ├── graphics/       # 图形绘制
│   │   ├── Image.cpp/h # 图片处理类
│   │   ├── fractals/   # 分形算法
│   │   └── shapes/     # 几何图形
│   └── main.cpp        # 主程序
├── build.sh            # 构建脚本
├── wsl-setup.sh        # WSL环境配置脚本
├── test_image.ppm      # 测试图片文件
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
- **图片处理**: 支持多种PPM格式的图片加载
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
1. 在 `Image` 类中添加新的加载方法
2. 实现对应格式的解析逻辑
3. 确保返回标准的颜色格式

### 性能优化
- 使用向量化操作批量绘制点
- 实现了高效的 framebuffer 清屏算法
- 支持多线程编译加速构建过程
- 图片加载使用内存预分配优化


