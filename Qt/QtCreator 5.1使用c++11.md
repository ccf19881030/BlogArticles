# QtCreator 5.1使用c++11
---------------------------
## 问题一：qt 5.1使用c++11的问题
今天用qt5.1编译一个使用c++11 的boost 例程，编译#include <thread>时报错说不支持，要编译选项     -std=c++11或-std=gnu++11. 不知该怎么设置让编译器支持c++11呢 
- 方法1：在pro文件中写上： 
QMAKE_CXXFLAGS += -std=c++11 

- 方法2：If you use qmake, you can add that line to your .pro file (Qt5): 
CONFIG += c++11 
(In Qt4, it should be something like: gcc:CXXFLAGS += -std=c++0x) 

## 相关链接
- [qt 5.1使用c++11的问题](http://www.newsmth.net/nForum/#!article/KDE_Qt/9722)
- [C++0x in Qt](http://blog.qt.digia.com/blog/2011/05/26/cpp0x-in-qt/)
- [C++11 in Qt5 ](http://woboq.com/blog/cpp11-in-qt5.html)
- [使用qtcreator在mac下调用C++11特性](http://socol.iteye.com/blog/1846125)
- [QT开发（一）Vs2013集成 QT5.3.1 ](http://www.cnblogs.com/aoldman/p/3860837.html)


