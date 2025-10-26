#pragma once

#include "../../core/Framebuffer.h"
#include "../../core/Point.h"
#include "../../core/Color.h"
#include <vector>
#include <random>

enum class SortState {
    READY,      // 准备状态
    SORTING,    // 排序中
    COMPLETED,  // 排序完成
    PAUSED      // 暂停
};

class BubbleSort {
public:
    // 构造函数
    BubbleSort(CFramebuffer* framebuffer, int arraySize = 50);
    
    // 运行可视化
    void Run();
    
    // 处理输入
    void HandleInput(char key);
    
    // 更新排序状态
    void Update();
    
    // 渲染排序过程
    void Render();
    
    // 重置数组
    void Reset();
    
    // 开始排序
    void StartSort();
    
    // 暂停/继续排序
    void TogglePause();
    
    // 获取当前状态
    SortState GetState() const { return m_state; }
    
    // 获取比较次数
    int GetComparisons() const { return m_comparisons; }
    
    // 获取交换次数
    int GetSwaps() const { return m_swaps; }

private:
    CFramebuffer* m_framebuffer;
    std::vector<int> m_array;           // 待排序数组
    int m_arraySize;                    // 数组大小
    SortState m_state;                  // 当前状态
    
    // 排序过程控制
    int m_currentI;                     // 外层循环索引
    int m_currentJ;                     // 内层循环索引
    int m_comparingIndex1;              // 当前比较的第一个元素索引
    int m_comparingIndex2;              // 当前比较的第二个元素索引
    bool m_swapped;                     // 本轮是否发生交换
    
    // 统计信息
    int m_comparisons;                  // 比较次数
    int m_swaps;                        // 交换次数
    
    // 渲染参数
    int m_barWidth;                     // 柱状图宽度
    int m_barSpacing;                   // 柱状图间距
    int m_baseY;                        // 柱状图基准Y坐标
    int m_maxBarHeight;                 // 最大柱状图高度
    
    // 颜色定义
    Color m_normalColor;                // 普通元素颜色
    Color m_comparingColor;             // 正在比较的元素颜色
    Color m_swappingColor;              // 正在交换的元素颜色
    Color m_sortedColor;                // 已排序元素颜色
    Color m_textColor;                  // 文本颜色
    
    // 私有方法
    void Initialize();                  // 初始化
    void GenerateRandomArray();         // 生成随机数组
    void CalculateRenderParams();       // 计算渲染参数
    void DrawBar(int index, Color color); // 绘制单个柱状图
    void DrawArray();                   // 绘制整个数组
    void DrawStatistics();              // 绘制统计信息
    void DrawInstructions();            // 绘制操作说明
    void DrawTitle();                   // 绘制标题
    bool PerformSortStep();             // 执行一步排序，返回是否完成
};