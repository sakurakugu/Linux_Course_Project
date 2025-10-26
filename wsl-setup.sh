#!/bin/bash

# WSL环境一键配置脚本
# 用于在WSL中快速设置分形龙项目的开发环境

set -e

echo "=== WSL分形龙项目环境配置脚本 ==="

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 打印彩色信息
print_info() {
    echo -e "${BLUE}[信息]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[成功]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[警告]${NC} $1"
}

print_error() {
    echo -e "${RED}[错误]${NC} $1"
}

# 检查是否在WSL环境中
check_wsl() {
    print_info "检查WSL环境..."
    
    if grep -qi microsoft /proc/version; then
        print_success "检测到WSL环境"
        
        # 检查WSL版本
        if grep -qi "microsoft-standard" /proc/version; then
            print_info "WSL版本: WSL2"
        else
            print_info "WSL版本: WSL1"
        fi
    else
        print_warning "未检测到WSL环境，脚本仍可在普通Linux中使用"
    fi
}

# 更新系统包
update_system() {
    print_info "更新系统包..."
    
    # 检测发行版
    if [ -f /etc/debian_version ]; then
        sudo apt update
        print_success "Debian/Ubuntu系统包列表已更新"
    elif [ -f /etc/redhat-release ]; then
        sudo yum update -y
        print_success "RedHat/CentOS系统包已更新"
    else
        print_warning "未识别的Linux发行版，请手动安装依赖"
    fi
}

# 安装开发工具
install_dev_tools() {
    print_info "安装开发工具..."
    
    if [ -f /etc/debian_version ]; then
        # Debian/Ubuntu
        sudo apt install -y \
            build-essential \
            cmake \
            git \
            vim \
            tree \
            htop \
            pkg-config \
            libavformat-dev \
            libavcodec-dev \
            libavutil-dev \
            libswscale-dev \
            ffmpeg
        print_success "开发工具和FFmpeg库安装完成"
    elif [ -f /etc/redhat-release ]; then
        # RedHat/CentOS
        sudo yum groupinstall -y "Development Tools"
        sudo yum install -y cmake git vim tree htop pkg-config
        # 对于CentOS/RHEL，可能需要启用EPEL仓库来安装FFmpeg
        sudo yum install -y epel-release
        sudo yum install -y ffmpeg-devel
        print_success "开发工具和FFmpeg库安装完成"
    fi
}

# 检查framebuffer设备
check_framebuffer() {
    print_info "检查framebuffer设备..."
    
    if [ -e /dev/fb0 ]; then
        print_success "找到framebuffer设备: /dev/fb0"
        ls -l /dev/fb0
    else
        print_warning "未找到framebuffer设备"
        print_info "在WSL中，framebuffer通常不可用"
        print_info "建议使用以下替代方案:"
        echo "  1. 使用WSLg (Windows 11)"
        echo "  2. 安装X11服务器"
        echo "  3. 修改代码使用其他图形库"
    fi
}

# 设置X11转发 (如果需要)
setup_x11() {
    print_info "配置X11转发..."
    
    # 安装X11应用用于测试
    if [ -f /etc/debian_version ]; then
        sudo apt install -y x11-apps
    elif [ -f /etc/redhat-release ]; then
        sudo yum install -y xorg-x11-apps
    fi
    
    # 设置DISPLAY环境变量
    if ! grep -q "export DISPLAY" ~/.bashrc; then
        echo "export DISPLAY=:0" >> ~/.bashrc
        print_success "已添加DISPLAY环境变量到~/.bashrc"
    fi
    
    print_info "X11配置完成，重启终端后生效"
    print_info "测试X11: xeyes (需要Windows X服务器)"
}

# 构建项目
build_project() {
    print_info "构建分形龙项目..."
    
    # 给脚本执行权限
    chmod +x build.sh
    
    # 构建项目
    ./build.sh
    
    print_success "项目构建完成"
}

# 创建桌面快捷方式 (如果支持)
create_shortcuts() {
    print_info "创建便捷脚本..."
    
    # 创建运行脚本
    cat > run-fractal.sh << 'EOF'
#!/bin/bash
cd "$(dirname "$0")"
if [ -f build/bin/FractalDragon ]; then
    echo "运行分形龙程序..."
    ./build/bin/FractalDragon $1
else
    echo "错误: 程序未构建，请先运行 ./build.sh"
    exit 1
fi
EOF
    
    chmod +x run-fractal.sh
    print_success "创建运行脚本: ./run-fractal.sh"
}

# 显示使用说明
show_usage() {
    echo ""
    echo "=== 配置完成 ==="
    echo ""
    print_success "环境配置完成！"
    echo ""
    echo "使用方法:"
    echo "  1. 构建项目:     ./build.sh"
    echo "  2. 运行程序:     ./run-fractal.sh [步数]"
    echo "  3. 手动运行:     ./build/bin/FractalDragon [步数]"
    echo ""
    echo "示例:"
    echo "  ./run-fractal.sh     # 默认步数"
    echo "  ./run-fractal.sh 3   # 指定步数为3"
    echo ""
    
    if [ ! -e /dev/fb0 ]; then
        print_warning "注意: 当前环境无framebuffer设备"
        echo "程序可能无法正常显示图形，建议:"
        echo "  1. 在真实Linux系统中运行"
        echo "  2. 配置WSL图形支持"
        echo "  3. 修改代码使用其他图形输出方式"
    fi
}

# 主函数
main() {
    echo "开始配置WSL开发环境..."
    echo ""
    
    check_wsl
    
    # 询问是否继续
    read -p "是否继续安装开发工具? (y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        update_system
        install_dev_tools
    fi
    
    check_framebuffer
    
    # 询问是否配置X11
    read -p "是否配置X11转发? (y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        setup_x11
    fi
    
    # 询问是否构建项目
    read -p "是否立即构建项目? (y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        build_project
    fi
    
    create_shortcuts
    show_usage
}

# 显示帮助
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "WSL分形龙项目环境配置脚本"
    echo ""
    echo "用法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  -h, --help    显示帮助信息"
    echo "  --auto        自动安装所有组件"
    echo ""
    echo "功能:"
    echo "  - 检查WSL环境"
    echo "  - 安装开发工具 (gcc, cmake, git等)"
    echo "  - 检查framebuffer设备"
    echo "  - 配置X11转发"
    echo "  - 构建项目"
    echo "  - 创建便捷脚本"
    exit 0
fi

# 自动安装模式
if [ "$1" = "--auto" ]; then
    check_wsl
    update_system
    install_dev_tools
    check_framebuffer
    setup_x11
    build_project
    create_shortcuts
    show_usage
else
    main
fi