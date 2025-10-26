#include "SnakeGame.h"
#include <iostream>
#include <unistd.h>
#include <termios.h>

SnakeGame::SnakeGame(CFramebuffer* framebuffer) 
    : m_framebuffer(framebuffer), 
      m_snake(Point(100, 100), 20),
      m_food(15),
      m_gameState(GameState::PLAYING),
      m_score(0),
      m_gameSpeed(200000) { // 200ms
    
    Initialize();
}

void SnakeGame::Run() {
    std::cout << "贪吃蛇游戏开始！" << std::endl;
    std::cout << "控制说明:" << std::endl;
    std::cout << "  WASD - 控制方向" << std::endl;
    std::cout << "  P    - 暂停/继续" << std::endl;
    std::cout << "  R    - 重新开始" << std::endl;
    std::cout << "  Q/ESC - 退出游戏" << std::endl;
    
    // 设置非阻塞输入
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    
    bool running = true;
    
    while (running) {
        // 处理输入
        char key = 0;
        if (read(STDIN_FILENO, &key, 1) > 0) {
            HandleInput(key);
            
            if (key == 'q' || key == 'Q' || key == 27) { // ESC
                running = false;
                break;
            }
        }
        
        // 更新游戏状态
        if (m_gameState == GameState::PLAYING) {
            Update();
        }
        
        // 渲染游戏
        Render();
        
        // 控制游戏速度
        usleep(m_gameSpeed);
    }
    
    // 恢复终端模式
    ttystate.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    
    std::cout << "游戏结束！最终分数: " << m_score << std::endl;
}

void SnakeGame::HandleInput(char key) {
    switch (key) {
        case 'w':
        case 'W':
            if (m_gameState == GameState::PLAYING) {
                m_snake.SetDirection(Direction::UP);
            }
            break;
        case 's':
        case 'S':
            if (m_gameState == GameState::PLAYING) {
                m_snake.SetDirection(Direction::DOWN);
            }
            break;
        case 'a':
        case 'A':
            if (m_gameState == GameState::PLAYING) {
                m_snake.SetDirection(Direction::LEFT);
            }
            break;
        case 'd':
        case 'D':
            if (m_gameState == GameState::PLAYING) {
                m_snake.SetDirection(Direction::RIGHT);
            }
            break;
        case 'p':
        case 'P':
            if (m_gameState == GameState::PLAYING) {
                m_gameState = GameState::PAUSED;
            } else if (m_gameState == GameState::PAUSED) {
                m_gameState = GameState::PLAYING;
            }
            break;
        case 'r':
        case 'R':
            Reset();
            break;
    }
}

void SnakeGame::Update() {
    if (m_gameState != GameState::PLAYING) {
        return;
    }
    
    // 移动蛇
    m_snake.Move();
    
    // 检查碰撞
    CheckCollisions();
}

void SnakeGame::Render() {
    // 清屏
    m_framebuffer->Clear();
    
    // 绘制边框
    m_framebuffer->DrawBorder();
    
    if (m_gameState == GameState::PLAYING || m_gameState == GameState::PAUSED) {
        // 绘制蛇
        m_framebuffer->DrawPoints(m_snake.GetPoints());
        
        // 绘制食物
        m_framebuffer->DrawPoints(m_food.GetPoints());
        
        // 显示分数
        ShowScore();
        
        if (m_gameState == GameState::PAUSED) {
            ShowPaused();
        }
    } else if (m_gameState == GameState::GAME_OVER) {
        ShowGameOver();
    }
}

void SnakeGame::Reset() {
    m_snake.Reset(Point(100, 100));
    GenerateNewFood();
    m_score = 0;
    m_gameState = GameState::PLAYING;
    m_gameSpeed = 200000; // 重置速度
}

void SnakeGame::Initialize() {
    GenerateNewFood();
}

void SnakeGame::GenerateNewFood() {
    int width = m_framebuffer->GetWidth();
    int height = m_framebuffer->GetHeight();
    
    // 考虑边框和蛇的大小
    const int border = 10;
    
    bool validPosition = false;
    int attempts = 0;
    const int maxAttempts = 100;
    
    while (!validPosition && attempts < maxAttempts) {
        m_food.GenerateRandomPosition(border, border, width - border, height - border);
        
        // 检查食物是否与蛇重叠
        Point foodPos = m_food.GetPosition();
        validPosition = true;
        
        // 简单检查：确保食物不在蛇头附近
        Point headPos = m_snake.GetHeadPosition();
        if (std::abs(foodPos.x - headPos.x) < 40 && std::abs(foodPos.y - headPos.y) < 40) {
            validPosition = false;
        }
        
        attempts++;
    }
}

void SnakeGame::CheckCollisions() {
    // 检查是否吃到食物
    Point headPos = m_snake.GetHeadPosition();
    if (m_food.CheckCollision(headPos, 10)) {
        m_snake.Grow();
        m_score += 10;
        GenerateNewFood();
        
        // 随着分数增加，游戏速度加快
        if (m_gameSpeed > 50000) {
            m_gameSpeed -= 5000;
        }
    }
    
    // 检查是否撞墙
    if (m_snake.CheckBoundaryCollision(m_framebuffer->GetWidth(), m_framebuffer->GetHeight())) {
        m_gameState = GameState::GAME_OVER;
        return;
    }
    
    // 检查是否撞到自己
    if (m_snake.CheckSelfCollision()) {
        m_gameState = GameState::GAME_OVER;
        return;
    }
}

void SnakeGame::ShowGameOver() {
    // 在屏幕中央显示游戏结束信息
    int centerX = m_framebuffer->GetWidth() / 2;
    int centerY = m_framebuffer->GetHeight() / 2;
    
    // 绘制游戏结束背景
    for (int x = centerX - 150; x < centerX + 150; x++) {
        for (int y = centerY - 50; y < centerY + 50; y++) {
            if (x >= 0 && x < m_framebuffer->GetWidth() && 
                y >= 0 && y < m_framebuffer->GetHeight()) {
                Point p(x, y, Color(64, 64, 64)); // 灰色背景
                m_framebuffer->DrawPoint(p);
            }
        }
    }
    
    // 简单的文字显示（用点阵表示）
    // "GAME OVER" 和分数信息会在控制台显示
    static bool messageShown = false;
    if (!messageShown) {
        std::cout << "\n=== 游戏结束 ===" << std::endl;
        std::cout << "最终分数: " << m_score << std::endl;
        std::cout << "按 R 重新开始，按 Q 退出" << std::endl;
        messageShown = true;
    }
}

void SnakeGame::ShowScore() {
    // 分数显示在控制台，这里可以在屏幕上绘制简单的分数指示
    // 在屏幕左上角绘制分数指示点
    int scoreIndicators = std::min(m_score / 10, 20); // 最多20个指示点
    
    for (int i = 0; i < scoreIndicators; i++) {
        Point p(10 + i * 3, 10, Color(255, 255, 0)); // 黄色分数指示
        m_framebuffer->DrawPoint(p);
    }
}

void SnakeGame::ShowPaused() {
    // 在屏幕中央显示暂停信息
    int centerX = m_framebuffer->GetWidth() / 2;
    int centerY = m_framebuffer->GetHeight() / 2;
    
    // 绘制暂停指示
    for (int x = centerX - 20; x < centerX + 20; x++) {
        for (int y = centerY - 20; y < centerY + 20; y++) {
            if ((x - centerX) % 10 < 5) { // 创建暂停符号的效果
                Point p(x, y, Color(255, 255, 255));
                m_framebuffer->DrawPoint(p);
            }
        }
    }
}