# DOSBox-OH

DOSBox Staging 的 HarmonyOS / OpenHarmony 移植版本。

[![License: GPL v2+](https://img.shields.io/badge/License-GPL%20v2+-blue.svg)](./LICENSE)

## 项目简介

本项目是基于 [DOSBox Staging](https://github.com/dosbox-staging/dosbox-staging) 的 HarmonyOS 平台移植版本，使用 ArkTS 和 NAPI 技术栈构建，让 DOS 游戏和应用程序能够在鸿蒙设备上运行。

## 功能特性（待完善）

- 🎮 完整的 DOS 环境模拟
- 🖥️ 支持 VGA/SVGA 图形显示
- 🔊 音频支持（OPL、Sound Blaster、GUS 等）
- 🎹 键盘和鼠标输入支持
- 💾 磁盘镜像挂载（ISO、IMG 等）
- 📱 适配 HarmonyOS 原生界面

## 项目结构

```
DOSBox-OH/
├── AppScope/                          # 鸿蒙应用全局配置
│   ├── resources/                     # 应用资源
│   └── app.json5                      # 应用配置
├── entry/
│   └── src/
│       ├── main/
│       │   ├── cpp/                   # C++ 原生代码
│       │   │   ├── dosbox-src/        # DOSBox Staging 源码（Git 子模块）
│       │   │   ├── platform/          # HarmonyOS 平台适配层
│       │   │   │   ├── sdl_ohos_video.cpp
│       │   │   │   ├── sdl_ohos_timer.cpp
│       │   │   │   ├── sdl_ohos_thread.cpp
│       │   │   │   ├── sdl_ohos_events.cpp
│       │   │   │   └── sdl_ohos_stubs.cpp
│       │   │   ├── CMakeLists.txt     # CMake 构建配置
│       │   │   ├── dosbox_bridge.cpp  # NAPI 桥接层
│       │   │   ├── dosbox_main_wrapper.cpp
│       │   │   └── napi_init.cpp      # NAPI 初始化
│       │   └── ets/                   # ArkTS 前端代码
│       │       ├── entryability/
│       │       ├── pages/
│       │       └── viewmodel/
│       └── oh-package.json5           # 模块配置
├── build-profile.json5                # 构建配置
├── code-linter.json5                  # 代码检查配置
└── README.md                          # 本文件
```

## 构建要求

- **DevEco Studio**: 4.0 Release 或更高版本
- **HarmonyOS SDK**: API 9 或更高版本
- **CMake**: 3.5.0 或更高版本
- **NDK**: 支持 C++20

## 快速开始

### 1. 克隆仓库

```bash
git clone https://github.com/DunoDoge/DOSBox-OH.git
cd DOSBox-OH
```

### 2. 初始化子模块

```bash
git submodule update --init --recursive
```

### 3. 在 DevEco Studio 中打开

1. 打开 DevEco Studio
2. 选择 "Open"，选择项目根目录
3. 等待 Gradle 同步完成

### 4. 构建和运行

1. 连接 HarmonyOS 设备或启动模拟器
2. 点击 "Run" 按钮（或按 Shift+F10）
3. 等待编译和安装完成

## 使用说明

### 基本操作

- **虚拟键盘**: 点击屏幕调出虚拟键盘
- **鼠标模式**: 支持触摸屏模拟鼠标
- **配置编辑**: 在设置中修改 dosbox.conf

### 文件管理

- 将 DOS 游戏文件放入设备的 `/data/app/el2/100/base/com.example.dosbox/files/` 目录
- 支持 `.exe`、`.com`、`.bat` 等 DOS 可执行文件

## 平台适配说明

本项目对 DOSBox Staging 进行了以下 HarmonyOS 平台适配：

| 模块  | 适配文件                  | 说明         |
| --- | --------------------- | ---------- |
| 视频  | `sdl_ohos_video.cpp`  | 适配鸿蒙原生窗口系统 |
| 定时器 | `sdl_ohos_timer.cpp`  | 使用鸿蒙高精度定时器 |
| 线程  | `sdl_ohos_thread.cpp` | 适配鸿蒙线程 API |
| 事件  | `sdl_ohos_events.cpp` | 处理触摸和按键事件  |
| 音频  | `sdl_ohos_stubs.cpp`  | 音频输出适配     |

## 贡献指南

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建 Pull Request

## 许可证

本项目遵循 **GPL-2.0-or-later** 许可证，与上游 DOSBox Staging 保持一致。

```
Copyright (C) 2024 DOSBox-OH Contributors

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
```

详见 [LICENSE](./LICENSE) 文件。

### 第三方许可证

- **DOSBox Staging**: GPL-2.0-or-later
- 项目中使用的第三方库许可证详见 `entry/src/main/cpp/dosbox-src/LICENSE`

## 致谢

- [DOSBox Staging](https://github.com/dosbox-staging/dosbox-staging) - 优秀的 DOS 模拟器项目
- [DOSBox Team](https://www.dosbox.com/) - 原始的 DOSBox 项目
- 鸿蒙开发者社区 - 提供技术支持

## 联系方式

- 项目主页: <https://github.com/DunoDoge/DOSBox-OH>
- 问题反馈: <https://github.com/DunoDoge/DOSBox-OH/issues>

***

**免责声明**: 本项目仅供学习和研究使用。使用本项目运行商业软件时，请确保您拥有合法的软件授权。
