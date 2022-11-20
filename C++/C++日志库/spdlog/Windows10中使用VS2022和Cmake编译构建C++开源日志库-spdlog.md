# 一、关于C++中的开源日志库spdlog
Java中有很多日志库：java.util.logging、Log4j、Logback、Log4j2、slf4j、common-logging。C++的日志库相对来说就比较少了，比如说[glog](https://github.com/google/glog)、[log4cpp](https://github.com/orocos-toolchain/log4cpp)、[spdllog](https://github.com/gabime/spdlog)等，目前个人感觉比较好用的C++开源日志库当属于spdlog了，跨平台，支持cmake编译，在维护中。
具体可以参考github上面的示例：[https://github.com/gabime/spdlog](https://github.com/gabime/spdlog)
另外spdlog支持两种使用方式：一种是将源代码目录下的include头文件直接添加到自己的项目中使用；另一种使用cmake编译构建出lib静态库或者dll动态库之后以静态和动态链接方式使用。

# 二、在Windows10中使用cmake和VS2022编译构建spdlog库
## 1、下载spdlog源代码
首先从github上面下载[spdllog](https://github.com/gabime/spdlog)的zip包源代码：[spdlog-1.x.zip](https://github.com/gabime/spdlog/archive/refs/heads/v1.x.zip)
![下载spdlog源代码](https://img-blog.csdnimg.cn/a573608863c0484abdc38ae75195fe83.png)
下载完spdlog-1.x.zip之后，将其解压到自己电脑的某个目录下，比如：D:\env目录

## 2、使用Cmake编译spdlog源代码
首先确保自己的电脑上已经安装了Cmake，我安装的Cmake版本是3.22.1。目前spdlog支持[cmake](https://cmake.org/)的构建，跨平台支持Windows、Linux、MacOS等，spdlog最低支持cmake 3.10版本。如果没有安装cmake可以到cmake官网下载，目前最新版本的稳定版cmake是3.25版本，下载地址为：[https://cmake.org/download/](https://cmake.org/download/)
- [cmake-3.25.0-windows-x86_64.msi](https://github.com/Kitware/CMake/releases/download/v3.25.0/cmake-3.25.0-windows-x86_64.msi)
- [cmake-3.25.0-windows-x86_64.zip](https://github.com/Kitware/CMake/releases/download/v3.25.0/cmake-3.25.0-windows-x86_64.zip)
- 如下图所示：
![cmake官网下载](https://img-blog.csdnimg.cn/7e054658f2fd4b0b8b0b4bcae1d7e8e4.png)

![编译spdlog](https://img-blog.csdnimg.cn/f5fea7bd4d0b489884f87591ffeb761f.png)
如果是在Linux或MacOS下使用cmake编译构建比较简单，如下：
```shell
$ git clone https://github.com/gabime/spdlog.git
$ cd spdlog && mkdir build && cd build
$ cmake .. && make -j
```
安装好Cmake之后，接下来打开Cmake-Gui开始编译构建spdlog源代码了。
首先在`D:\env\spdlog-1.x`源码目录新建一个`build`目录，这样做的好处是将编译生成的文件全部放到一起，防止污染源代码。![选择spdlog源代码目录](https://img-blog.csdnimg.cn/298c9b572b9744dfb85b5e8291de23ba.png)
![选择编译生成目录](https://img-blog.csdnimg.cn/c6cc735f8a3d49d49ecb1dc1e50aff23.png)
选择了源代码目录和编译生成之后，点击左下角的`·Configure·`按钮，会弹出对话框，让我们选择Visual Studio编译器，我电脑上安装了VS2017和VS2022,此处我选择了Visual Studio 17 2022，下面的平台我选择了x64位，选好之后点击`Finish`按钮，如下图所示：
![Configure](https://img-blog.csdnimg.cn/7ace7fd9e4804c689a066a9f08c0174e.png)
![Configure之后](https://img-blog.csdnimg.cn/9c624f98a6164a268d64d1b3f2c3cf8c.png)
上面红色的部分大家可以根据自己的需求来进行勾选，比如说`CMake_INSTALL_PREFIX`这一项默认安装目录是：`C:/Program Files/spdlog`，我们可以根据自己的需要修改；`SPDLOG_BUILD_SHARED`可以编译出动态库；`SPDLOG_BUILD_TESTS`可以编译出测试示例。此我保持默认选项。

接着在Cmake-gui界面，点击`Generate`按钮，如下图所示：
![Generate](https://img-blog.csdnimg.cn/a430799ce5254162a3db279a0debd515.png)
点击`Generate`按钮之后，可以看到`D:\env\spdlog-1.x\build`编译生成目录下面多出了一个spdlog的VC++工程，如下图所示：
![spdlog工程](https://img-blog.csdnimg.cn/0232863fcdbc4c6aa016f342ae9bfb44.png)

最后在Cmake-Gui界面中，点击`Open Project`按钮，选择VS2022打开spdlog项目，如下图所示：
![Open Project](https://img-blog.csdnimg.cn/862a4124c40c4843b07b83a1d82deb33.png)
或者直接到`D:\env\spdlog-1.x\build`目录下，找到`spdlog.sln`工程文件，直接使用VS2022打开也可以，效果是等价的。
![VS2022打开spdlog工程](https://img-blog.csdnimg.cn/163c77fb2e4546f596239b07398b2d19.png)
默认是Debug模式，x64位，我们选择`ALL_BUILD`项目，右键菜单中选择`生成`，
![VS2022编译spdlog项目](https://img-blog.csdnimg.cn/d9d2b2772bae4cdb84b0b1720ea55add.png)

可以看到最终生成了`spdlogd.lib`静态库和`example.exe`示例程序。所在目录为：`D:\env\spdlog-1.x\build\Debug`和`D:\env\spdlog-1.x\build\example\Debug`
![spdlogd.lib](https://img-blog.csdnimg.cn/0c2ce841a5ad476a880a415c6c3e68a5.png)
![example.exe](https://img-blog.csdnimg.cn/7e0ac5ab8a63422d8839f0ae334f656a.png)
同样的，我们可以生成`Release`和`x64`位的`spdlog.lib`静态库，如下图所示：
![spdlog.lib](https://img-blog.csdnimg.cn/199b2dcbaa3b403cb5a2334afa46e427.png)
编译生成出了`spdlogd.lib`和`spdlog.lib`库之后，我们可以将includ头文件和库文件放在某个目录下，供自己创建`spdlog`项目中使用，如下图所示：






![spdlog-1.x库目录](https://img-blog.csdnimg.cn/d4e246b1fb624c4ca0ef7ce5be798a31.png)
```
PS D:\spdlog-1.x>
PS D:\spdlog-1.x> tree
卷 Data 的文件夹 PATH 列表
卷序列号为 3EE8-BA3A
D:.
├─include
│  └─spdlog
│      ├─cfg
│      ├─details
│      ├─fmt
│      │  └─bundled
│      └─sinks
└─lib
    ├─Debug
    └─Release
PS D:\spdlog-1.x>
```
# 3、VS2022使用spdlog项目
打开VS2022，新疆一个基于VC++的控制台项目
![spdlogTest01](https://img-blog.csdnimg.cn/fa1a2ed9da6a487bbef0a2bc2c02f621.png)
![spdlogTest01](https://img-blog.csdnimg.cn/26649257449e4dbda2c0fee2f56ec056.png)

为该项目添加spdlog的头文件和lib库文件，由于是Debug x64项目，所以需要选择对应的`spdlogd.lib`库，如下所示：
![添加头文件目录](https://img-blog.csdnimg.cn/09a066c347cc479fafcb9d526501f08f.png)
lib库目录：
![lib库目录](https://img-blog.csdnimg.cn/56de9d2b2b704213a6f8b14554c7bc36.png)

![spdlogd.lib](https://img-blog.csdnimg.cn/7487704f4f464a048816f0aa62c7300c.png)
然后在程序中添加如下的`spdlogTest01.cpp`代码：
```cpp
#include "spdlog/spdlog.h"

int main() 
{
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");
    
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");    
    
    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    
    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");
	
	return 0;
}
```
运行上述代码，结果如下图所示：
![程序运行结果](https://img-blog.csdnimg.cn/01274580825141d28ea5a95c7d76ed75.png)
至此，Windows10中使用VS2022和Cmake编译构建、使用spdlog日志库完毕，当然如果是Release x64位的则需要选择spdlog.lib库了。
