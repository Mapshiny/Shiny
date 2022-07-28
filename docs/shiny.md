# `Shiny`的简单使用



##  一、简介

Logger设计为一个静态的单例类，通过以下静态成员函数获取**全局的唯一实例**：

```cpp
    Logger* Logger::getLogger() {
        static LoggerImpl logger;
        return &logger;
    }
```

随后，通过该实例进行日志**输出目录、缓存目录、日志等级、日志前缀名、输出方式**的配置：

```cpp
void LoggerImpl::config(
    const std::string& logDir, 
    const std::string& cacheDir, 
    const std::string& logFileName, LogMode mode)
```

其中，`logDIr`保存日志的输出目录，`cacheDir`保存为日志的高速缓存，该目录下的文件通过`mmap`映射保证在进程`crash`时日志持久化至该目录下的临时文件，`logFileName`为日志的前缀名，最终文件名为：前缀名_时间戳.shiny，mode设置日志的IO方式，默认异步IO，后台线程按照一定策略进行日志的输出

最后，通过`looger`提供的`logprint`接口进行日志的输出：

```cpp
void logPrint(LoggerInfo &info, const char *msg)
```



## 二、使用

`Shiny`对微信官方的跨平台组件mars中的xlog模块进行了裁剪，目前仅实现了日志的代码接口，暂未面向开发者提供宏函数的封装，待项目完成后进行文档的完善

待续。。。

