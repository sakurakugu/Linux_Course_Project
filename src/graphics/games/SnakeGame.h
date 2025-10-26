#pragma once

#include "Snake.h"
#include "Food.h"
#include "../../core/Framebuffer.h"

enum class GameState {
    PLAYING,
    GAME_OVER,
    PAUSED
};

class SnakeGame {
public:
    // 构造函数
    SnakeGame(CFramebuffer* framebuffer);
    
    // 游戏主循环
    void Run();
    
    // 处理输入
    void HandleInput(char key);
    
    // 更新游戏状态
    void Update();
    
    // 渲染游戏
    void Render();
    
    // 重置游戏
    void Reset();
    
    // 获取游戏状态
    GameState GetState() const { return m_gameState; }
    
    // 获取分数
    int GetScore() const { return m_score; }

private:
    CFramebuffer* m_framebuffer;
    Snake m_snake;
    Food m_food;
    GameState m_gameState;
    int m_score;
    int m_gameSpeed; // 游戏速度（毫秒）
    
    // 初始化游戏
    void Initialize();
    
    // 生成新食物
    void GenerateNewFood();
    
    // 检查碰撞
    void CheckCollisions();
    
    // 显示游戏结束画面
    void ShowGameOver();
    
    // 显示分数
    void ShowScore();
    
    // 显示暂停画面
    void ShowPaused();
};