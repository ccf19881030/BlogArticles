## [c++日志记录都有哪些好的开源项目？](https://www.zhihu.com/question/37640953)
日志系统对于项目开发中前期调试分析问题，查找诸如多线程并发，时效性原因很有帮助，但是，如何记录日志，包括其格式，内容，详略程度都很重要。请问，对于c++有没有很好的开源项目
作者：叛逆者
链接：https://www.zhihu.com/question/37640953/answer/72889728
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

问这种问题之前，都应该先看看 [fffaraz/awesome-cpp · GitHub](https://link.zhihu.com/?target=https%3A//github.com/fffaraz/awesome-cpp) 一目了然。Logging

* Boost.Log - Designed to be very modular and extensible. [Boost]
* easyloggingpp - Single header only C++ logging library. [MIT] websiteG3log - Asynchronous logger with Dynamic Sinks. [PublicDomain]Log4cpp - A library of C++ classes for flexible logging to files, syslog, IDSA and other destinations. [LGPL]
* log4cplus - A simple to use C++ logging API providing thread-safe, flexible, and arbitrarily granular control over log management and configuration. [BSD& Apache2]plog - Portable and simple C++ logging library. [MPL2]
* reckless - Low-latency, high-throughput, asynchronous logging library for C++. [MIT]
* spdlog - Super fast, header only, C++ logging library.templog - A very small and lightweight C++ library which you can use to add logging to your C++ applications. [Boost]
 
