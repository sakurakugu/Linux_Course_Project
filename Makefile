# 分形龙项目 Makefile
# 备选构建方案，如果CMake不可用时使用

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Icpp
LDFLAGS = -lm

# 目录设置
SRCDIR = cpp
BUILDDIR = build
BINDIR = $(BUILDDIR)/bin

# 源文件和目标文件
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TARGET = $(BINDIR)/FractalDragon

# 默认目标
.PHONY: all clean debug release install help

all: release

# Release版本 (优化编译)
release: CXXFLAGS += -O3 -DNDEBUG
release: $(TARGET)

# Debug版本 (包含调试信息)
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: $(TARGET)

# 创建可执行文件
$(TARGET): $(OBJECTS) | $(BINDIR)
	@echo "链接: $@"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "构建完成: $@"

# 编译源文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@echo "编译: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建目录
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# 清理构建文件
clean:
	@echo "清理构建文件..."
	rm -rf $(BUILDDIR)
	@echo "清理完成"

# 安装 (复制到系统目录)
install: $(TARGET)
	@echo "安装到 /usr/local/bin/"
	sudo cp $(TARGET) /usr/local/bin/
	@echo "安装完成"

# 运行程序
run: $(TARGET)
	@echo "运行程序..."
	$(TARGET)

# 运行程序 (带参数)
run-step3: $(TARGET)
	@echo "运行程序 (步数=3)..."
	$(TARGET) 3

# 显示帮助信息
help:
	@echo "分形龙项目 Makefile"
	@echo ""
	@echo "可用目标:"
	@echo "  all      - 构建Release版本 (默认)"
	@echo "  release  - 构建Release版本 (优化)"
	@echo "  debug    - 构建Debug版本 (调试信息)"
	@echo "  clean    - 清理构建文件"
	@echo "  install  - 安装到系统目录"
	@echo "  run      - 运行程序"
	@echo "  run-step3- 运行程序 (步数=3)"
	@echo "  help     - 显示此帮助信息"
	@echo ""
	@echo "示例:"
	@echo "  make           # 构建Release版本"
	@echo "  make debug     # 构建Debug版本"
	@echo "  make clean     # 清理"
	@echo "  make run       # 运行"

# 显示构建信息
info:
	@echo "编译器: $(CXX)"
	@echo "编译标志: $(CXXFLAGS)"
	@echo "链接标志: $(LDFLAGS)"
	@echo "源文件: $(SOURCES)"
	@echo "目标文件: $(OBJECTS)"
	@echo "可执行文件: $(TARGET)"