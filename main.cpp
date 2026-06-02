// This is a demo of the Game-of-Life in raylib
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"                 // Required for GUI controls

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <stdlib.h>

using namespace std;

int main(){
    const int screenWidth = 1200;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Game of Life");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);   // 将默认字体大小设为 20（默认是 10）
    float cellSize = 10;
    int gridWidth = screenWidth / cellSize;
    int gridHeight = screenHeight / cellSize;
    vector<vector<bool>> grid(gridHeight, vector<bool>(gridWidth, false)); // 一开始所有的细胞都是死的
    bool isRunning = false; // 游戏是否在运行
    SetTargetFPS(60); // 设置帧率

    while (!WindowShouldClose()){
        // 处理输入
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 mousePos = GetMousePosition();
            int x = mousePos.x / cellSize;
            int y = mousePos.y / cellSize;
            grid[y][x] = !grid[y][x]; // 切换细胞状态
        }
        if (IsKeyPressed(KEY_SPACE)){
            isRunning = !isRunning; // 切换游戏状态
        }
        //----------------------------
        // Gui控制台
        //----------------------------
        GuiPanel((Rectangle){1000, 10, 1200, 100}, "Controls");
        if (GuiButton((Rectangle){1020, 40, 180, 30}, isRunning ? "Pause (Space)" : "Start (Space)")){
            isRunning = !isRunning; // 切换游戏状态
        }
        // 切换网格大小
        GuiSliderBar((Rectangle){ 1020, 80, 120, 20}, "Grid Size", TextFormat("%.2f", (float)cellSize), &cellSize, 1, 100);
 
        //----------------------------
        // 更新游戏状态
        //----------------------------
        if (isRunning){
            vector<vector<bool>> newGrid = grid; // 创建一个新的网格来存储下一代状态
            for (int y = 0; y < gridHeight; y++){
                for (int x = 0; x < gridWidth; x++){
                    int liveneighbours = 0;
                    for (int j = -1; j <= 1; j++){
                        for (int i = -1; i <= 1; i++){
                            if (i == 0 && j == 0) continue; // 跳过当前细胞
                            int nx = x + i;
                            int ny = y + j;
                            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight){
                                if (grid[ny][nx]) liveneighbours++; // 统计活邻居数量
                            }
                        }
                    }
                    // 根据生命游戏的规则更新细胞状态
                    if (grid[y][x]){
                        if (liveneighbours < 2 || liveneighbours > 3) newGrid[y][x] = false; // 死亡
                    } else {
                        if (liveneighbours == 3) newGrid[y][x] = true; // 复活
                    }
                }
            }
            grid = newGrid; // 更新网格
        }

        //----------------------------
        // 绘制
        //----------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //----------------------------
        // 绘制网格线
        for (int y = 0; y < gridHeight; y++){
            DrawLine(0, y * cellSize, screenWidth, y * cellSize, LIGHTGRAY);
        }
        for (int x = 0; x < gridWidth; x++){
            DrawLine(x * cellSize, 0, x * cellSize, screenHeight, LIGHTGRAY);
        }
        //----------------------------
        for (int y = 0; y < gridHeight; y++){
            for (int x = 0; x < gridWidth; x++){
                if (grid[y][x]){
                    DrawRectangle(x * cellSize, y * cellSize, cellSize - 1, cellSize - 1, BLACK); // 绘制活细胞
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}