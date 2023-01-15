# YimMenu

![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Online%20Version&query=%24.game.online&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000) ![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Game%20Build&query=%24.game.build&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000)

这是YimMenu的中文版构建教程

这是一款适用于Grand Theft Auto V的作弊菜单。

仅用于学习交流，禁止做出破坏游戏平衡的事情

YimMenu is originally based of off [BigBaseV2](https://github.com/Pocakking/BigBaseV2) which was an amazing base at the time but nowadays is a bit dated.

YimMenu 最初基于 [BigBaseV2](https://github.com/Pocakking/BigBaseV2)，这在当时是一个了不起的菜单，但现在有点过时了。 

所以在这里有一个新开发的菜单，重点是保护用户免受其他有攻击性的菜单的侵害。

## Table of contents

 * [构建方法](#how-to-build)
    * [Curl](#curl)
    * [Git](#git)
    * [CMake](#CMake)
    * [克隆并生成项目文件](#cloning-and-generating-project-files)
 * [保持代码最新](#staying-up-to-date)
 * [项目结构](#project-structure)
 * [特点](#features)
 * [贡献](#contributing)
 
## 构建方法

环境要求:

 * [Git](#git)
 * [CMake](#cmake)

如果您同时满足上述两个要求，则可以跳至 [克隆存储库并生成项目文件](#cloning-and-generating-project-files).

### Curl

Curl 应该已经安装在您的计算机上，但是如果您在构建项目时遇到问题，则需要下载并安装它。

[下载链接](https://curl.se/download.html)

### Git

如果你还没有在你的电脑上安装git，那就先安装它，它是设置项目构建环境的**必需品**

[下载链接](https://git-scm.com/download/win)

### CMake

CMake 用于生成我们的项目文件，如果您之前没有使用过它，则需要下载并安装它。

[下载链接](https://cmake.org/download/)

### 克隆和生成项目文件

- 确保您已经安装了 Git 和 CMake。

- 克隆存储库:
  ```bash
  git clone https://github.com/YimMenu/YimMenu.git
  ```

-  进入刚刚克隆的目录：
  ```bash
  cd YimMenu
  ```

#### 生成项目文件

> **注意**
> 如果你添加了新文件或修改了代码，您需要再次进行 cd build 和 cmake，否则在构建时会出错。

- 仅windows

  - Visual Studio

   如果您只使用 Visual Studio 并且不想弄乱命令行，Visual Studio 有一个 CMake 扩展可以完成所有工作。

    确保它已[安装](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation).

    然后，打开 Visual Studio，选择打开本地文件夹选项，然后打开刚刚通过 `git clone` 命令创建的 `YimMenu` 文件夹。

    让 CMake 扩展生成构建所需的文件，您可以在 Visual Studio 的“输出”选项卡中跟踪进度。

    然后，您可以使用顶部的“生成”菜单并单击“全部生成”来build。


- 其他操作系统/集成开发环境

  如果您使用其他工具或更喜欢在 Windows 上使用控制台，请按照以下步骤操作：

  ```bash
  mkdir build
  cd build
  cmake ..
  ```

 现在，您将能够打开解决方案并生成它。
  
## 保持最新状态

从此存储库中提取最新更改。

使用一个很简单的命令:

```bash
git pull
```

CMake 会在没有任何用户输入的情况下自动处理删除/添加的文件。

如果由于某种原因不是这种情况，您将需要重做上面[生成项目文件](#generate-project-files) 部分中的步骤.

如果您正在对代码库进行自定义修改并拥有一个分支，那么您可以自己与upstream（此存储库）保持同步，谷歌搜索诸如“从upstream合并”之类的东西并学习如何使用 Git。

## 项目结构

- `backend/` 在循环中运行的所有功能都在这里按类别排序
- `gui/` 包括与 UI 元素相关的所有内容
- `hooks/` 函数挂钩
- `native_hooks/` 本机挂钩
- `services/` 用于交互和维护内容的服务文件
- `util/` 通用实用函数，使代码尽可能紧凑并尽可能多地放在一个地方

## 特点

以下是我认为此“基础”或菜单值得注意的不完成的功能列表

- 返回本机欺骗
- 自定义 [设置](src/core/globals.hpp) 与深度比较是否进行了更改，包括自动保存
- 清晰且结构良好的源代码
- 包括一个线程池，用于排队不应阻塞游戏线程的任务，与纤维池非常相似
- 从 https://nativedb.spyral.dev 更新了 natives.hpp
- 实现了 ReClass.NET 结构，可从 `common.hpp` 中定义的名为 g_local_player 的全局访问

## 贡献

你可以自由地为 YimMenu 做贡献，只要这些功能有用，不过分有害，并且不包含任何可能成为 Take2 目标菜单的与金钱相关的内容。

请务必阅读 [CONTRIBUTING.md](CONTRIBUTING.md) 文件。
