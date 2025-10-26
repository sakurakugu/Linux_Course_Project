#include "BubbleSort.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <termios.h>

// 设置终端为非阻塞模式
void setBubbleSortNonBlockingInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// 恢复终端模式
void restoreBubbleSortInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// 获取键盘输入
char getBubbleSortKey() {
    char ch = 0;
    ssize_t result = read(STDIN_FILENO, &ch, 1);
    (void)result; // 避免未使用变量警告
    return ch;
}

BubbleSort::BubbleSort(CFramebuffer* framebuffer, int arraySize) 
    : m_framebuffer(framebuffer)
    , m_arraySize(arraySize)
    , m_state(SortState::READY)
    , m_currentI(0)
    , m_currentJ(0)
    , m_comparingIndex1(-1)
    , m_comparingIndex2(-1)
    , m_swapped(false)
    , m_comparisons(0)
    , m_swaps(0)
    , m_normalColor(100, 150, 255)      // 蓝色
    , m_comparingColor(255, 255, 0)     // 黄色
    , m_swappingColor(255, 100, 100)    // 红色
    , m_sortedColor(100, 255, 100)      // 绿色
    , m_textColor(255, 255, 255)        // 白色
{
    Initialize();
}

void BubbleSort::Initialize() {
    GenerateRandomArray();
    CalculateRenderParams();
    m_state = SortState::READY;
    m_currentI = 0;
    m_currentJ = 0;
    m_comparingIndex1 = -1;
    m_comparingIndex2 = -1;
    m_swapped = false;
    m_comparisons = 0;
    m_swaps = 0;
}

void BubbleSort::GenerateRandomArray() {
    m_array.clear();
    m_array.resize(m_arraySize);
    
    // 使用随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10, 300);
    
    for (int i = 0; i < m_arraySize; i++) {
        m_array[i] = dis(gen);
    }
}

void BubbleSort::CalculateRenderParams() {
    int screenWidth = m_framebuffer->GetWidth();
    int screenHeight = m_framebuffer->GetHeight();
    
    // 计算柱状图参数
    int availableWidth = screenWidth - 40; // 留出边距
    m_barWidth = std::max(1, availableWidth / m_arraySize - 2);
    m_barSpacing = 2;
    
    // 如果柱状图太窄，减少数组大小
    if (m_barWidth < 3) {
        m_arraySize = std::min(m_arraySize, availableWidth / 5);
        m_array.resize(m_arraySize);
        GenerateRandomArray();
        m_barWidth = availableWidth / m_arraySize - 2;
    }
    
    m_baseY = screenHeight - 50;  // 柱状图底部位置
    m_maxBarHeight = screenHeight - 150; // 最大柱状图高度
}

void BubbleSort::Run() {
    std::cout << "冒泡排序可视化启动..." << std::endl;
    std::cout << "操作说明:" << std::endl;
    std::cout << "  SPACE - 开始/暂停排序" << std::endl;
    std::cout << "  R     - 重新生成数组" << std::endl;
    std::cout << "  Q/ESC - 退出程序" << std::endl;
    
    setBubbleSortNonBlockingInput();
    
    bool running = true;
    while (running) {
        // 处理输入
        char key = getBubbleSortKey();
        if (key != 0) {
            HandleInput(key);
            if (key == 'q' || key == 'Q' || key == 27) { // ESC
                running = false;
                break;
            }
        }
        
        // 更新状态
        Update();
        
        // 渲染
        Render();
        
        // 控制帧率
        usleep(100000); // 100ms
    }
    
    restoreBubbleSortInput();
    std::cout << "冒泡排序可视化结束" << std::endl;
}

void BubbleSort::HandleInput(char key) {
    switch (key) {
        case ' ': // 空格键
            if (m_state == SortState::READY || m_state == SortState::PAUSED) {
                StartSort();
            } else if (m_state == SortState::SORTING) {
                TogglePause();
            }
            break;
        case 'r':
        case 'R':
            Reset();
            break;
    }
}

void BubbleSort::Update() {
    if (m_state == SortState::SORTING) {
        if (PerformSortStep()) {
            m_state = SortState::COMPLETED;
            m_comparingIndex1 = -1;
            m_comparingIndex2 = -1;
        }
    }
}

bool BubbleSort::PerformSortStep() {
    if (m_currentI >= m_arraySize - 1) {
        return true; // 排序完成
    }
    
    if (m_currentJ >= m_arraySize - m_currentI - 1) {
        // 当前轮次完成
        if (!m_swapped) {
            return true; // 如果这一轮没有交换，说明已经排序完成
        }
        m_currentI++;
        m_currentJ = 0;
        m_swapped = false;
        m_comparingIndex1 = -1;
        m_comparingIndex2 = -1;
        return false;
    }
    
    // 设置当前比较的元素
    m_comparingIndex1 = m_currentJ;
    m_comparingIndex2 = m_currentJ + 1;
    m_comparisons++;
    
    // 比较并交换
    if (m_array[m_currentJ] > m_array[m_currentJ + 1]) {
        std::swap(m_array[m_currentJ], m_array[m_currentJ + 1]);
        m_swapped = true;
        m_swaps++;
    }
    
    m_currentJ++;
    return false;
}

void BubbleSort::Render() {
    // 清屏
    m_framebuffer->Clear();
    
    // 绘制边框
    m_framebuffer->DrawBorder();
    
    // 绘制标题
    DrawTitle();
    
    // 绘制数组
    DrawArray();
    
    // 绘制统计信息
    DrawStatistics();
    
    // 绘制操作说明
    DrawInstructions();
}

void BubbleSort::DrawArray() {
    for (int i = 0; i < m_arraySize; i++) {
        Color barColor = m_normalColor;
        
        // 根据状态选择颜色
        if (m_state == SortState::COMPLETED) {
            barColor = m_sortedColor;
        } else if (i == m_comparingIndex1 || i == m_comparingIndex2) {
            if (m_state == SortState::SORTING && 
                i == m_comparingIndex1 && i == m_comparingIndex2 - 1 &&
                m_array[i] > m_array[i + 1]) {
                barColor = m_swappingColor; // 正在交换
            } else {
                barColor = m_comparingColor; // 正在比较
            }
        } else if (i >= m_arraySize - m_currentI) {
            barColor = m_sortedColor; // 已排序部分
        }
        
        DrawBar(i, barColor);
    }
}

void BubbleSort::DrawBar(int index, Color color) {
    int startX = 20;
    int x = startX + index * (m_barWidth + m_barSpacing);
    int height = (m_array[index] * m_maxBarHeight) / 300; // 假设最大值为300
    
    // 绘制柱状图
    for (int i = 0; i < m_barWidth; i++) {
        for (int j = 0; j < height; j++) {
            Point pt(x + i, m_baseY - j, color);
            m_framebuffer->DrawPoint(pt);
        }
    }
}

void BubbleSort::DrawTitle() {
    // 简单的标题显示（使用点阵方式）
    std::vector<Point> titlePoints;
    
    // 在屏幕顶部绘制"BUBBLE SORT"字样的简单点阵
    int startX = m_framebuffer->GetWidth() / 2 - 50;
    int startY = 20;
    
    // 简单的点阵字母（这里只是示例，实际可以更复杂）
    for (int i = 0; i < 100; i += 5) {
        titlePoints.push_back(Point(startX + i, startY, m_textColor));
        titlePoints.push_back(Point(startX + i, startY + 1, m_textColor));
    }
    
    m_framebuffer->DrawPoints(titlePoints);
}

void BubbleSort::DrawStatistics() {
    std::vector<Point> statPoints;
    int startX = 20;
    int startY = 50;
    
    // 绘制统计信息的简单表示
    // 比较次数指示器
    for (int i = 0; i < std::min(m_comparisons / 10, 50); i++) {
        statPoints.push_back(Point(startX + i * 2, startY, Color(255, 255, 0)));
    }
    
    // 交换次数指示器
    for (int i = 0; i < std::min(m_swaps / 5, 50); i++) {
        statPoints.push_back(Point(startX + i * 2, startY + 10, Color(255, 100, 100)));
    }
    
    m_framebuffer->DrawPoints(statPoints);
}

void BubbleSort::DrawInstructions() {
    std::vector<Point> instrPoints;
    int startX = m_framebuffer->GetWidth() - 200;
    int startY = 50;
    
    // 绘制状态指示器
    Color stateColor;
    switch (m_state) {
        case SortState::READY:
            stateColor = Color(255, 255, 255); // 白色
            break;
        case SortState::SORTING:
            stateColor = Color(0, 255, 0); // 绿色
            break;
        case SortState::PAUSED:
            stateColor = Color(255, 255, 0); // 黄色
            break;
        case SortState::COMPLETED:
            stateColor = Color(0, 255, 255); // 青色
            break;
    }
    
    // 绘制状态指示圆点
    for (int i = -3; i <= 3; i++) {
        for (int j = -3; j <= 3; j++) {
            if (i * i + j * j <= 9) {
                instrPoints.push_back(Point(startX + i, startY + j, stateColor));
            }
        }
    }
    
    m_framebuffer->DrawPoints(instrPoints);
}

void BubbleSort::Reset() {
    Initialize();
}

void BubbleSort::StartSort() {
    if (m_state == SortState::READY) {
        m_state = SortState::SORTING;
    } else if (m_state == SortState::PAUSED) {
        m_state = SortState::SORTING;
    }
}

void BubbleSort::TogglePause() {
    if (m_state == SortState::SORTING) {
        m_state = SortState::PAUSED;
    } else if (m_state == SortState::PAUSED) {
        m_state = SortState::SORTING;
    }
}