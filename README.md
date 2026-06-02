# Conway's Game of Life - raylib 实现

基于 [raylib](https://www.raylib.com/) 和 [raygui](https://github.com/raysan5/raygui) 开发的康威生命游戏模拟器。支持交互式编辑、实时演化、速度调节和网格缩放。



## 功能特性

- 🖱️ **鼠标点击**：在网格区域左键单击可以切换细胞的死活。
- ▶️ **开始/暂停**：按 `Space` 键或点击面板上的按钮控制演化进程。
- 🔘 **单步演化**：*(当前版本未实现，建议后续添加)*
- 📏 **细胞大小调节**：通过滑块调整每个细胞的像素尺寸（1~50 像素），网格会自动重置。
- ⏱️ **演化速度控制**：调节“Update Delay”滑块，设置每代之间的延迟（0 ~ 1000 毫秒）。
- 🎨 **可视化**：白色背景，灰色网格线，活细胞显示为黑色方块。
- 📐 **自适应布局**：右侧固定控制面板，左侧为完整的网格区域。

## 操作说明

| 操作                     | 功能                                 |
| ------------------------ | ------------------------------------ |
| 鼠标左键（在网格区域）   | 单击切换细胞的死活（支持连续点击）   |
| `Space` 键               | 开始 / 暂停演化                      |
| 面板按钮 “Start/Pause”   | 同上                                 |
| 滑块 “Cell Size”         | 调整单元格大小（1~50 像素）          |
| 滑块 “Update Delay”      | 调整演化延迟（0~1000 毫秒，0 表示最快速度） |

## 编译与运行

### 依赖库

- [raylib](https://github.com/raysan5/raylib) (≥ 4.0)
- [raygui](https://github.com/raysan5/raygui) (header‑only，已包含在代码中)

### 编译命令（示例）

使用 g++ 和 raylib（Linux / macOS / Windows with MinGW）：

```bash
g++ -o game_of_life main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

如果你使用 CMake，可以简单的：

```cmake
find_package(raylib REQUIRED)
add_executable(game_of_life main.cpp)
target_link_libraries(game_of_life raylib)
```

### 运行

```bash
./game_of_life
```

## 代码结构

- `main()` 包含全部逻辑：窗口初始化、网格管理、GUI 绘制、演化计算、输入处理。
- 网格使用 `vector<vector<bool>>` 存储，每代计算使用双重循环遍历邻居。
- 时间延迟使用 `GetTime()` 与 `lastUpdateTime` 比较，确保演化速度与帧率解耦。

## 待扩展方向（建议）

- [ ] **单步执行**：增加 “Step” 按钮，手动前进一代。
- [ ] **随机填充**：一键生成随机初始布局。
- [ ] **清空网格**：重置所有细胞为死亡状态。
- [ ] **预设图案**：滑翔机、高斯帕滑翔机枪等。
- [ ] **边界模式**：环形边界（Torus）或反射边界。
- [ ] **种群统计**：实时显示活细胞数量与演化代数。
- [ ] **相机控制**：用 `Camera2D` 支持拖拽和缩放视图。
- [ ] **颜色渐变**：根据细胞存活时间改变颜色。


## 许可证

本项目采用与 raylib 相同的许可证（zlib/libpng）。你可以自由使用、修改和分发。

---

**Enjoy the Game of Life!** 🧬
