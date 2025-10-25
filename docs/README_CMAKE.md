# 分形龙项目 - CMake构建指南

这是一个使用Linux framebuffer绘制分形龙的C++项目，现已添加CMake支持，可在WSL环境中编译运行。

## 项目结构

```
Linux_Course_Project/
├── CMakeLists.txt          # CMake配置文件
├── build.sh               # 自动构建脚本
├── README_CMAKE.md        # 本文件
└── cpp/                   # 源代码目录
    ├── main.cpp           # 主程序
    ├── Framebuffer.cpp/h  # Linux framebuffer操作
    ├── FractalDragon.cpp/h # 分形龙算法
    ├── Color.h            # 颜色定义
    ├── Point.h            # 点定义
    ├── Geometry.h         # 几何基类
    ├── Line.cpp/h         # 线段类
    └── Polyline.cpp/h     # 多段线类
```

## 系统要求

### WSL环境准备

1. **安装WSL2** (推荐)
   ```bash
   # 在Windows PowerShell中执行
   wsl --install
   ```

2. **安装Ubuntu** (或其他Linux发行版)
   ```bash
   wsl --install -d Ubuntu
   ```

### 依赖安装

在WSL中安装必要的开发工具：

```bash
# 更新包管理器
sudo apt update

# 安装编译工具链
sudo apt install build-essential cmake

# 安装其他可能需要的包
sudo apt install git vim
```

## 构建方法

### 方法1: 使用自动构建脚本 (推荐)

```bash
# 进入项目目录
cd Linux_Course_Project

# 给脚本执行权限
chmod +x build.sh

# 构建Release版本
./build.sh

# 或构建Debug版本
./build.sh Debug
```

### 方法2: 手动使用CMake

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目 (Release版本)
cmake -DCMAKE_BUILD_TYPE=Release ..

# 或配置Debug版本
cmake -DCMAKE_BUILD_TYPE=Debug ..

# 编译
make -j$(nproc)
```

## 运行程序

```bash
# 在build目录中
./bin/FractalDragon

# 或指定分形步数 (默认为2)
./bin/FractalDragon 3
```

## 重要说明

### Framebuffer设备

此程序使用Linux framebuffer设备进行图形绘制，需要：

1. **真实的Linux系统**: 程序可以直接运行
2. **WSL环境**: 需要特殊配置才能访问framebuffer设备

### WSL中的图形支持

WSL默认不支持framebuffer设备。要在WSL中运行图形程序，有以下选项：

1. **WSL2 + WSLg** (Windows 11)
   - Windows 11自带WSLg支持
   - 可以运行Linux GUI应用

2. **X11转发**
   ```bash
   # 安装X11应用
   sudo apt install x11-apps
   
   # 设置DISPLAY环境变量
   export DISPLAY=:0
   ```

3. **VcXsrv或Xming** (Windows X服务器)
   - 在Windows中安装X服务器
   - 配置WSL使用Windows的X服务器

### 替代方案

如果framebuffer不可用，可以考虑修改代码使用其他图形库：
- SDL2
- OpenGL
- SFML
- 或输出到图像文件

## 故障排除

### 编译错误

1. **找不到头文件**
   ```bash
   # 确保安装了开发包
   sudo apt install linux-libc-dev
   ```

2. **CMake版本过低**
   ```bash
   # 检查CMake版本
   cmake --version
   
   # 如果版本低于3.10，需要升级
   ```

### 运行时错误

1. **无法打开framebuffer设备**
   ```
   错误: 无法打开 /dev/fb0
   ```
   - 检查设备是否存在: `ls -l /dev/fb*`
   - 检查权限: `sudo chmod 666 /dev/fb0`

2. **权限不足**
   ```bash
   # 尝试使用sudo运行
   sudo ./bin/FractalDragon
   ```

## 开发说明

### 项目特点

- 使用C++11标准
- 面向对象设计
- 支持不同的几何图形绘制
- 模块化的代码结构

### 编译选项

- **Debug模式**: 包含调试信息，未优化
- **Release模式**: 优化编译，适合发布

### 扩展建议

1. 添加更多分形图案
2. 支持不同的输出格式
3. 添加交互功能
4. 优化绘制性能

## 许可证

请参考项目根目录的LICENSE文件。