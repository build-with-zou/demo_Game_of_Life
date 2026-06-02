// This is a demo of the Game-of-Life in raylib
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <stdlib.h>

using namespace std;

int main() {
    const int screenWidth = 1300;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Game of Life");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);   // 放大字体

    // 右侧面板区域设置（固定大小，紧贴右边缘）
    const int panelWidth = 220;
    const int panelMargin = 10;
    const int panelX = screenWidth - panelWidth - panelMargin;
    const int panelY = panelMargin;
    const int panelHeight = 150;

    // 网格可用宽度 = 面板左侧所有区域
    const int gridAreaWidth = panelX;  // 从0到panelX

    float cellSize = 10;
    int gridWidth = gridAreaWidth / cellSize;
    int gridHeight = screenHeight / cellSize;
    vector<vector<bool>> grid(gridHeight, vector<bool>(gridWidth, false));
    bool isRunning = false;
    float updateDelay = 100.0f; // 毫秒
    float lastCellSize = cellSize;
    double lastUpdateTime = 0;
    SetTargetFPS(100);

    while (!WindowShouldClose()) {
        // --- 输入处理（仅在网格区域有效）---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if (mousePos.x >= 0 && mousePos.x < gridAreaWidth && mousePos.y >= 0 && mousePos.y < screenHeight) {
                int x = mousePos.x / cellSize;
                int y = mousePos.y / cellSize;
                if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                    grid[y][x] = !grid[y][x];
                }
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            isRunning = !isRunning;
        }

        // 细胞大小改变时重置网格
        if (cellSize != lastCellSize) {
            lastCellSize = cellSize;
            gridWidth = gridAreaWidth / cellSize;
            gridHeight = screenHeight / cellSize;
            grid.assign(gridHeight, vector<bool>(gridWidth, false));
        }

        // --- GUI 控制台（独立右侧区域）---
        // 注意：不要在半透明矩形之后绘制GUI，否则会被覆盖。
        // 我们这里先绘制GUI，然后不需要额外覆盖矩形。
        GuiPanel((Rectangle){panelX, panelY, panelWidth, panelHeight}, "Game Controls");

        if (GuiButton((Rectangle){panelX + 10, panelY + 40, panelWidth - 20, 30},
                      isRunning ? "Pause (Space)" : "Start (Space)"))
        {
            isRunning = !isRunning;
        }

        GuiSliderBar((Rectangle){panelX + 10, panelY + 80, panelWidth - 120, 20},
                     "Cell Size", TextFormat("%.2f", cellSize), &cellSize, 1, 50);
        GuiSliderBar((Rectangle){panelX + 10, panelY + 110, panelWidth - 120, 20},
             "Update Delay", TextFormat("%.0f ms", updateDelay), &updateDelay, 0, 1000);
        // --- 生命演化逻辑 ---
        // 逻辑：如果一个细胞是活的，且周围活细胞数小于2或大于3，则它死去；如果一个细胞是死的，且周围活细胞数正好为3，则它复活。
        if (isRunning && (GetTime() - lastUpdateTime) >= updateDelay / 1000.0f) {
            lastUpdateTime = GetTime();
            vector<vector<bool>> newGrid = grid;
            for (int y = 0; y < gridHeight; y++) {
                for (int x = 0; x < gridWidth; x++) {
                    int liveNeighbours = 0;
                    for (int j = -1; j <= 1; j++) {
                        for (int i = -1; i <= 1; i++) {
                            if (i == 0 && j == 0) continue;
                            int nx = x + i;
                            int ny = y + j;
                            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                                if (grid[ny][nx]) liveNeighbours++;
                            }
                        }
                    }
                    if (grid[y][x]) {
                        if (liveNeighbours < 2 || liveNeighbours > 3)
                            newGrid[y][x] = false;
                    } else {
                        if (liveNeighbours == 3)
                            newGrid[y][x] = true;
                    }
                }
            }
            grid = newGrid;
        }

        // --- 绘制 ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 绘制网格线（仅网格区域）
        for (int y = 0; y <= gridHeight; y++) {
            DrawLine(0, y * cellSize, gridAreaWidth, y * cellSize, LIGHTGRAY);
        }
        for (int x = 0; x <= gridWidth; x++) {
            DrawLine(x * cellSize, 0, x * cellSize, screenHeight, LIGHTGRAY);
        }

        // 绘制活细胞
        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                if (grid[y][x]) {
                    DrawRectangle(x * cellSize, y * cellSize, cellSize - 1, cellSize - 1, BLACK);
                }
            }
        }

        // 在网格和面板之间画一条分隔线，使界面更清晰
        DrawLine(gridAreaWidth, 0, gridAreaWidth, screenHeight, DARKGRAY);
  
        EndDrawing();
    }

    CloseWindow();
    return 0;
}