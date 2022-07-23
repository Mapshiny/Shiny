<div align="center">


## Shiny：基于mmap的高性能、高可用日志收集库

![](https://img.shields.io/badge/release-v1.0-blue.svg)
![](https://img.shields.io/badge/build-passing-green.svg)
![](https://img.shields.io/badge/dependencies-up%20to%20date-green.svg)
![](https://img.shields.io/badge/license-MIT-blue.svg)

</div>

-----

## ✨ 特征

- 基于mmap的文件IO
- 面向现代的C++11开发，充分利用C++11新特性，包括thread库、smart pointer等
- 基于zlib的日志压缩
- 可拓展的日志加密

----

## 💎 依赖

- Linux环境
- cmake version >= 3.20.2
- gcc、gcc-c++
- make
- automake
- kernel-devel

----

## ⌛️ 构建

```
$ sudo yum install make automake gcc gcc-c++ kernel-devel

$ git clone git@github.com:Mapshiny/Shiny.git

$ cd Shiny/build

$ cmake ..

$ make

```

----

## 🥇 性能测试

待续...

----

## 📚 文档

待续...

----

## 致谢

感谢 Visual Studio Code，Copilot等对项目的支持。
