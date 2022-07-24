<div align="center">


## Shiny：基于mmap的Linux轻量级日志模块

![](https://img.shields.io/badge/release-v1.0-blue.svg)
![](https://img.shields.io/badge/build-passing-green.svg)
![](https://img.shields.io/badge/dependencies-up%20to%20date-green.svg)
![](https://img.shields.io/badge/license-MIT-blue.svg)

</div>

-----

## 🐣 前言

Shiny 是基于[mmap](./docs/mmap.md)的Linux轻量级日志模块, 目前仅支持linux环境, 其他环境暂不支持。它的核心是通过mmap对磁盘文件进行一一映射, 只进行映射而没有任何文件的IO、用户态内核态之间的数据拷贝操作。基于mmap进行文件的读写与内存读写的性能是一样的, 保证了日志模块的的高性能。

项目仅对mmap进行了一些日志文件IO的封装, 提供了一些简单的日志接口, 主要包括：获取单例的logger、配置日志文件路径、设置日志等级等。同时, 对多线程打印日志进行了并发控制, 避免多线程打印日志产生的race condition。

更多关于Shiny和mmap的相关知识, 参考[Shiny的文档](#docs)


## ✨ 特征

- 基于mmap的内存映射IO, 进程虚拟地址空间与内核空间映射至同一内存空间，同时该空间建立与磁盘文件的一一映射关系，实现日志高性能读写
- 基于zlib的日志压缩，封装了zlib压缩的基本使用方法
- 面向现代的C++11开发风格, 充分利用C++11新特性，包括泛型编程、thread库、智能指针、mutex、条件变量等
- 可拓展的日志加密、解密功能

## 💎 依赖

- Linux环境
- cmake >= 3.20.2
- gcc、gcc-c++
- make
- automake
- kernel-devel

## ⛏️ 构建

```
$ sudo yum install make automake gcc gcc-c++ kernel-devel

$ git clone git@github.com:Mapshiny/Shiny.git

$ cd Shiny

$ mkdir build bin

$ cd build && cmake ..

$ make
```

## 🥇 性能测试

待续...

<div id="docs" hidden="true">docs</div>
## 📚 文档

* mmap
  * [什么是mmap](./docs/mmap.md)

* Shiny基本使用
  * [Shiny的简单使用](./docs/shiny.md)
  
* example

待续...

## 📅 TODO

待续...

## 📀 参考资料

1. [微信终端跨平台组件 mars 系列(一) - 高性能日志模块xlog](https://mp.weixin.qq.com/s/cnhuEodJGIbdodh0IxNeXQ)
2. [微信终端跨平台组件 mars 系列(二) - 信令传输超时设计](https://mp.weixin.qq.com/s/cnhuEodJGIbdodh0IxNeXQ)
3. [微信终端跨平台组件 mars 系列 - 我们如约而至](https://mp.weixin.qq.com/s/JVsVrKwJlOwoB3Rz0e17wQ)

## 🧧 致谢

感谢 Visual Studio Code, Copilot
