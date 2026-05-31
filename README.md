# CoinGame - 耄耋版翻金币

基于 **Qt 6.8.3** 和 **C++17** 开发的翻金币益智小游戏。

## 游戏截图

![coin-2](https://github.com/user-attachments/assets/dd5da9da-8c15-421d-a175-fbb2fdff3f40)

![coin-1](https://github.com/user-attachments/assets/2cd713c6-4250-4525-bd3f-9d1da6b58734)

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/ddb9e6c5-ad77-45b4-95af-8be18ff95021" />

<img width="500" height="500" alt="屏幕截图 2026-02-25 164909" src="https://github.com/user-attachments/assets/00ed7906-07c4-4eb4-9351-34bf6f496b1d" />

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/fdce3588-e81e-4b1a-86dc-aee457df3496" />

## 游戏介绍

经典翻金币玩法：点击一枚金币时，该金币及其上下左右相邻的金币都会翻转。玩家需要通过点击使所有金币都变成正面。

- 篮球耄耋 = **正面**（金色）
- 飞行耄耋 = **反面**（银色）
- **关卡数量**：20 关
- **胜利条件**：4×4 区域内所有金币均为正面

细节优化：对游戏配乐、按钮点击、页面切换、logo 以及一系列小细节进行了优化，基本玩法较为流畅。

## 技术架构

| 技术 | 说明 |
|------|------|
| 语言 | C++17 |
| UI 框架 | Qt 6.8.3 (Widgets) |
| 多媒体 | Qt Multimedia（音效播放） |
| 构建系统 | CMake 3.16+ |
| 编译器 | MinGW 64-bit (Windows) |

## 项目结构

```
CoinGame/
├── main.cpp                 # 程序入口
├── mainwindow.h/.cpp/.ui    # 主菜单界面
├── chooselevelscene.h/.cpp  # 关卡选择界面（20 关网格）
├── playscene.h/.cpp         # 游戏游玩界面（4×4 金币矩阵）
├── mypushbutton.h/.cpp      # 自定义按钮（弹跳动画效果）
├── mycoin.h/.cpp            # 金币按钮（正反翻转逻辑）
├── dataconfig.h/.cpp        # 关卡数据配置（20 关预设）
├── CMakeLists.txt           # CMake 构建配置
├── res.qrc                  # Qt 资源文件
└── images/                  # 图片和音效资源
    ├── coin-1.gif           # 金币正面（篮球耄耋）
    ├── coin-2.gif           # 金币反面（飞行耄耋）
    ├── *.jpg / *.png        # 背景图、按钮图等
    └── *.wav                # 背景音乐和音效
```

## 核心类说明

| 类 | 基类 | 职责 |
|---|------|------|
| `MainWindow` | QMainWindow | 主菜单界面，包含开始按钮和背景音乐，管理场景切换 |
| `ChooseLevelScene` | QMainWindow | 关卡选择界面，4×5 网格展示 20 个关卡 |
| `PlayScene` | QMainWindow | 游戏核心场景，管理 4×4 金币矩阵，处理点击翻转与胜利判定 |
| `MyCoin` | QPushButton | 金币按钮，封装正反翻转动画（QTimer 驱动的 GIF 切换） |
| `MyPushButton` | QPushButton | 通用按钮，支持弹跳动画效果和按下/释放切换图标 |
| `DataConfig` | QObject | 关卡数据容器，存储 20 个关卡的 4×4 初始布局 |

## 游戏玩法

1. 点击**开始按钮**进入关卡选择界面
2. 选择关卡（1~20）进入游戏场景
3. 点击金币使其翻转，同时**上下左右相邻**的金币也会翻转
4. 当所有金币都变成**篮球耄耋（正面）**时，屏幕显示胜利动画并播放音效
5. 点击返回按钮可退出当前界面

## 构建与运行

### 环境要求

- Qt 6.8+ (Widgets + Multimedia 模块)
- CMake 3.16+
- 支持 C++17 的编译器（MinGW 64-bit / MSVC / GCC）

### 使用 CMake 构建

```bash
# 克隆项目
git clone https://github.com/orange11-forever/CoinGame.git
cd CoinGame

# 配置
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.8.3/gcc_64

# 编译
cmake --build build

# 运行
./build/CoinGame
```

### 使用 Qt Creator

1. 打开 Qt Creator，选择 **File → Open File or Project...**
2. 选择 `CMakeLists.txt`
3. 配置 Kit（推荐 Qt 6.8.3 MinGW 64-bit）
4. 点击 **Run** 运行

## 音效资源

| 文件 | 用途 |
|------|------|
| `nomoremanbo.wav` | 主界面背景音乐（循环播放） |
| `wow.wav` | 按钮点击 / 关卡选择音效 |
| `ohyeah.wav` | 胜利音效 |

## 作者

该项目为 Qt/C++ 学习练习项目，欢迎交流与改进。

## 许可

本项目仅供学习交流使用。
