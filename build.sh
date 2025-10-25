#!/bin/bash

# 分形龙项目构建脚本
# 适用于WSL和Linux环境

set -e  # 遇到错误时退出

echo "=== 分形龙项目构建脚本 ==="

# 检查是否安装了必要的工具
check_dependencies() {
    echo "检查依赖..."
    
    if ! command -v cmake &> /dev/null; then
        echo "错误: 未找到cmake，请安装cmake"
        echo "Ubuntu/Debian: sudo apt-get install cmake"
        echo "CentOS/RHEL: sudo yum install cmake"
        exit 1
    fi
    
    if ! command -v make &> /dev/null; then
        echo "错误: 未找到make，请安装build-essential"
        echo "Ubuntu/Debian: sudo apt-get install build-essential"
        exit 1
    fi
    
    if ! command -v g++ &> /dev/null; then
        echo "错误: 未找到g++编译器"
        echo "Ubuntu/Debian: sudo apt-get install g++"
        exit 1
    fi
    
    echo "依赖检查完成 ✓"
}

# 创建构建目录
create_build_dir() {
    echo "创建构建目录..."
    if [ -d "build" ]; then
        echo "清理旧的构建目录..."
        rm -rf build
    fi
    mkdir build
    echo "构建目录创建完成 ✓"
}

# 配置项目
configure_project() {
    echo "配置项目..."
    cd build
    
    # 默认使用Release模式，可以通过参数修改
    BUILD_TYPE=${1:-Release}
    echo "构建类型: $BUILD_TYPE"
    
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    echo "项目配置完成 ✓"
}

# 编译项目
build_project() {
    echo "编译项目..."
    make -j$(nproc)
    echo "编译完成 ✓"
}

# 显示结果
show_result() {
    echo ""
    echo "=== 构建完成 ==="
    echo "可执行文件位置: $(pwd)/bin/FractalDragon"
    echo ""
    echo "运行方法:"
    echo "  ./bin/FractalDragon [步数]"
    echo ""
    echo "注意: 此程序需要在有framebuffer设备的Linux环境中运行"
    echo "      (如真实的Linux系统或配置了图形的WSL)"
}

# 主函数
main() {
    check_dependencies
    create_build_dir
    configure_project $1
    build_project
    show_result
}

# 显示帮助信息
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "用法: $0 [BUILD_TYPE]"
    echo ""
    echo "BUILD_TYPE:"
    echo "  Debug   - 调试版本 (默认包含调试信息)"
    echo "  Release - 发布版本 (默认，优化编译)"
    echo ""
    echo "示例:"
    echo "  $0          # 构建Release版本"
    echo "  $0 Debug    # 构建Debug版本"
    echo ""
    echo "依赖要求:"
    echo "  - cmake (>= 3.10)"
    echo "  - g++"
    echo "  - make"
    echo "  - Linux framebuffer支持"
    exit 0
fi

# 执行主函数
main $1