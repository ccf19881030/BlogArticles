## [c++日志记录都有哪些好的开源项目？](https://www.zhihu.com/question/37640953)
日志系统对于项目开发中前期调试分析问题，查找诸如多线程并发，时效性原因很有帮助，但是，如何记录日志，包括其格式，内容，详略程度都很重要。请问，对于c++有没有很好的开源项目
作者：叛逆者
链接：https://www.zhihu.com/question/37640953/answer/72889728
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

问这种问题之前，都应该先看看 [fffaraz/awesome-cpp · GitHub](https://link.zhihu.com/?target=https%3A//github.com/fffaraz/awesome-cpp) 一目了然。Logging

Boost.Log - Designed to be very modular and extensible. [Boost]easyloggingpp - Single header only C++ logging library. [MIT] websiteG3log - Asynchronous logger with Dynamic Sinks. [PublicDomain]Log4cpp - A library of C++ classes for flexible logging to files, syslog, IDSA and other destinations. [LGPL]log4cplus - A 
simple to use C++ logging API providing thread-safe, flexible, and 
arbitrarily granular control over log management and configuration. [BSD
 & Apache2]plog - Portable and simple C++ logging library. [MPL2]reckless - Low-latency, high-throughput, asynchronous logging library for C++. [MIT]spdlog - Super fast, header only, C++ logging library.templog - A very small and lightweight C++ library which you can use to add logging to your C++ applications. [Boost]
 

叛逆者 给出的awesome cpp中已经包含了好多库，对比了一下自己前几天看到过的别人的一个简单总结，发现有些库并不包括在awesome cpp中，
于是就再贴一下：
log4cxx – Apache logging framework for C++ patterned after Apache log4j (for Java).

log4cplus – Another port of log4j from Java.log4cpp – Log for C++ (also similar to Log4j in Java). Not very well documented, but there is an introductory article.boost.log (proposal by John Torjo) – v2, but NOT accepted into boost by review 03/17/2008.boost.log (by Andrey Semashev) – accepted by review 03/24/2010, not yet included in current boost 1.43, but is separately downloadable.Pantheios – Open source C/C++ diagnostic logging API, claimed the sweet-spot with comparisons to ACE logging, boost.log (v2, John Torjo proposal), log4cpp, log4cplus and log4cxx). Installation and first tutorial.glog – Google Logging LibraryRLogEzLoggerPOCO – POCO also has a nice logging support explained.ACE – ACE also has logging support.出处：Logging libraries in C++自己有用过log4cxx，和log4j同门，用着还不错。大厂一般都有自己的日志库，相比于开源库，会在性能上进行一定优化，同时统一各个产品线的日志格式，方便日志的分析处理。相比于选择哪个日志库，如何打出规范且漂亮的日志才是问题的关键。再次做一个搬运工（来自stackoverflow，本人非常心水这种类型的回答，言简意赅且相当实用）：[Practice]When to use log level WARN vs ERROR?
