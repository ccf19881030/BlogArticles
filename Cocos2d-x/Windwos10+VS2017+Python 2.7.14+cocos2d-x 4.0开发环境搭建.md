
## 一、关于Cocos2d-x
[Cocos2d-x ](https://cocos2d-x.org/)是一套成熟的开源跨平台游戏开发框架。引擎提供了图形渲染、GUI、音频、网络、物理、用户输入等丰富的功能， 被广泛应用于游戏开发及交互式应用的构建。其核心采用 C++ 编写，支持使用 C++、Lua 或 JavaScript 进行开发。

很早之前写过一篇博客：[Win7环境下VS2010配置Cocos2d-x-2.1.4最新版本的开发环境(亲测)](https://blog.csdn.net/ccf19881030/article/details/9204801)，当时使用的Win7系统，Visual Studio开发版本是2010，Cocos2d-x对应的版本是2.1.4，到现在Cocos2d-x已经更新到4.0了，其[Cocos2d-x官网](https://cocos2d-x.org/)的Cocos2d-x 4.0的下载地址为：[http://cocos2d-x.org/filedown/cocos2d-x-v4.0](http://cocos2d-x.org/filedown/cocos2d-x-v4.0)
![download Cocos2d-x](https://img-blog.csdnimg.cn/2020092321280112.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 二、编译安装Coco2d-x 4.0的准备工作
关于Coco2d-x 4.0在各个平台下的搭建的Python、CMake的版本，可以参考官方的说明，如下图所示：
![Coco2d-x 4.0的环境搭建](https://img-blog.csdnimg.cn/20200926003033626.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
从上图可以看出，Windows系统下搭建Coco2d-x 4.0开发环境推荐的配置是：
- Windows 7+
- VS 2017+
- CMake 3.1+
- `Python 2.7.5+, P建议 ython 2,7.10, 而不是 Python 3+__`
下面是官方的[V4.0版本的升级指南](https://docs.cocos2d-x.org/cocos2d-x/v4/en/upgradeGuide/)说明：
![V4.0版本](https://img-blog.csdnimg.cn/20200930201922240.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

![V4升级指南](https://img-blog.csdnimg.cn/20200930200450136.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
在Windows下可以使用`cocos`或者`CMake`运行项目，下面是官方的Cocos2d-x 4.0的[CMake Guide](https://docs.cocos2d-x.org/cocos2d-x/v4/en/installation/CMake-Guide.html)
![CMake Guide 1](https://img-blog.csdnimg.cn/20200930200710460.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
在Linux、Windows等平台下使用CMake很简单，我们可以使用VS2017提供的CMake命令行工具编译生成对应的VS项目，命令如下图所示：
```shell
cd cocos2d-x
mkdir win32-build && cd win32-build
cmake .. -G"Visual Studio 15 2017" -Tv141
```
Execute `cmake --build . `to compile, or open `Cocos2d-x.sln` in Explorer to use the generated project.
![CMake Guide](https://img-blog.csdnimg.cn/20200930200908557.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

### 安装VS2017、cmake 3.11.1，Python 2.7.14

本次使用的系统为Windows10操作系统，使用VS2017，Cmake的版本为： 3.11.1，python版本为：2.7.14
![Python和cmake的版本信息](https://img-blog.csdnimg.cn/20200923213017419.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
### 1、下载安装Python2.7.14
首先去[Python官网](https://www.python.org/downloads/release)下载Python2.7版本，目前Coco2d-x 4.0不支持Python 3.x的版本，
![Python 2.7.18](https://img-blog.csdnimg.cn/20200923213748705.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
Python 2.7.18的下载地址为：[https://www.python.org/downloads/release/python-2718/](https://www.python.org/downloads/release/python-2718/)，2020年4月20号最新发布的2.7版本，目前Python 3的最新版本是3.8.5，注意由于Cocos2d-x目前只支持Python 2，不支持Python 3，所以我们直接下载[Python 2.7.18]((https://www.python.org/downloads/release/python-2718/))
![Python 2.7.18](https://img-blog.csdnimg.cn/2020092321414086.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
由于我的系统处理器是AMD的，我直接下载上面的[Windows x86-64 MSI installer](https://www.python.org/ftp/python/2.7.18/python-2.7.18.amd64.msi)，同时包含有X86和X64的32位和64位版本的Python，当然也可以直接下载[Windows x86 MSI installer](https://www.python.org/ftp/python/2.7.18/python-2.7.18.msi)，我之前安装的是Python 2.7.14,，安装目录如下图所示：
![Python 2.7.14](https://img-blog.csdnimg.cn/20200923214454587.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

下载python-2.7.18.amd64.msi或者python-2.7.18.msi后安装到对应的目录下，然后将python.exe所在目录（也就是python安装路径）例如C:\Python27添加至Windows10系统的环境变量中去。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200923214910392.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![添加python环境变量](https://img-blog.csdnimg.cn/2020092321535349.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
接着[WIN+R]打开cmd命令窗口，在其中输入`python --version`命令查看python的版本信息
![查看python版本信息](https://img-blog.csdnimg.cn/20200923215521369.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
如果成功打印出python的版本信息则证明python2.7.x安装成功并且配置好了python2.7.x的环境变量了。

### 2、下载并安装cmake
去[CMake官网](https://cmake.org/download/)下载，安装的时候注意这一步，选择加到环境变量里：
![cmake 3.17.0安装](https://img-blog.csdnimg.cn/20200923215835623.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
然后再cmd窗口看一下版本，是否安装成功：
![cmake 3.11.0](https://img-blog.csdnimg.cn/20200923215919891.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
### 3、安装VS2017
Cocos2d-x 4.0需要Visual Studio 2015之后的版本，我目前使用的是VS2017开发工具，这个自己去[微软官网](https://my.visualstudio.com/Downloads?q=visual%20studio%202017)下载。
vs2017官方下载地址为：[https://docs.microsoft.com/en-us/visualstudio/releasenotes/vs2017-relnotes](https://docs.microsoft.com/en-us/visualstudio/releasenotes/vs2017-relnotes)
![VS2017](https://img-blog.csdnimg.cn/20200923220411789.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
### 4. 下载Coco2d-x 4.0源代码
去[Cocos2d-x](https://cocos2d-x.org/)官网下载稳定版的[Coco2d-x 4.0源代码](http://cocos2d-x.org/filedown/cocos2d-x-v4.0),其下载地址为：[http://cocos2d-x.org/filedown/cocos2d-x-v4.0](http://cocos2d-x.org/filedown/cocos2d-x-v4.0)
下载好cocos2d-x-4.0.zip之后将其解压到系统盘下的某个目录下，比如：E:\SoftDevelop\CPlus\Cocos2d_x_Games
解压后的coco2d-x-4.0的源码目录结构如下图所示：
![coco2d-x-4.0的目录结构](https://img-blog.csdnimg.cn/20200923221333530.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 三、编译安装cocos2d-x 4.0
开始安装，进入cocos2d-x-4.0文件夹，运行setup.py。安装过程中会问你NDK和Android SDK的路径，如果没有，直接回车就行。
在Window10系统中进入`coco2d-x 4.0`所在目录E:\SoftDevelop\CPlus\Cocos2d_x_Games\cocos2d-x-4.0，按住`Shift`+鼠标右键，选择【在此处打开PowerShell窗口(S)】
![PowerShell窗口](https://img-blog.csdnimg.cn/20200923221839124.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
再执行如下命令运行根目录下的`setup.py`脚本
```shell
python setup.py
```
![python setup.py](https://img-blog.csdnimg.cn/202009232220524.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![python setup.py 2](https://img-blog.csdnimg.cn/20200923222238177.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
重新打开一个命令行CMD窗口，输入`cocos --version`查看cocos2d-x的版本信息，如下图所示：
![查看coco2d-x的版本信息](https://img-blog.csdnimg.cn/20200923222710689.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

这中间会问你是否同意发送数据，以便帮助Cocos成长，选是选否都可以。

接下来，创建一个自己项目HelloWorld。

## 四、创建HelloWorld项目
使用`cocos new HelloWorld -l cpp -d 项目所在目录`创建一个`HelloWorld`项目
```shell
cocos new HelloWorld -l cpp -d E:\SoftDevelop\CPlus\Cocos2d_x_Games
```
cocos new后面的HelloWorld是项目名，-l 指定语言（cpp，lua，js），-d是项目存放的路径。还可以用-p指定工程的包名。详细可以看cocos new --help。
![cocos new --help](https://img-blog.csdnimg.cn/20200923223011145.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![copy](https://img-blog.csdnimg.cn/2020092322340277.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
执行完了后，可以看到HelloWorld文件夹内容是这样：
![HelloWorld文件夹](https://img-blog.csdnimg.cn/20200923223441583.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
之后就是启动这个HelloWorld看效果了。不过，当你进到proj.win32里面，是没有VS的工程文件的。这里跟很多博客和书介绍的用VisualStudio启动，是不一样的。cocos2d-x 4.0是需要你先手动编译一下的，按照官方的顺序来，进入到HelloWorld文件夹，建立一个build文件夹。下面是官方给的编译命令：
```shell
$ cd NEW_PROJECTS_DIR/HelloWorld
$ mkdir build
$ cd build
$ cocos run --proj-dir .. -p [mac|windows|android|linux|ios]
```
上面一步说白了就是进入到`HelloWorld`项目所在目录，然后在HelloWorld目录下创建一个build目录用于存放cmake编译的一些中间文件比如Makefile等文件，其中-p指定所使用的目标平台比如linux、windows、mac等，-m MODE参数可以指定运行的模式时debug还是release，默认时debug，--proj-dir PROJ_DIR指定目标平台路径。注意：使用`cocos run --proj-dir .. -p win32`或者`cocos run --proj-dir .. -p win32 -m debug`使用的是debug模式，若需要编译生成win32的release模式，则可将`-m`参数指定为`release`，使用`cocos run --proj-dir .. -p win32 -m release`命令。
![CMakeLists.txt](https://img-blog.csdnimg.cn/20200923224859989.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

可以通`cocos run --help`查看`cocos run`命令的一些参数，如下图所示：
![cocos run --help](https://img-blog.csdnimg.cn/20200923224226504.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

![cocos run --proj-dir .. -p [mac|windows|android|linux|ios]](https://img-blog.csdnimg.cn/20200923224011237.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![cocos run](https://img-blog.csdnimg.cn/20200923224444181.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
接下来就是时间稍微有点长的cmake编译过程了，其中会调用C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.16.27023\bin\HostX86\x86\CL.exe的`CL.exe`命令工具：
![cmake编译过程图1](https://img-blog.csdnimg.cn/20200923225049385.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

![cmake编译过程图2](https://img-blog.csdnimg.cn/20200923224957397.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![运行结果](https://img-blog.csdnimg.cn/20200923225332534.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
到这里我们的项目工程就做好了，工程生成在WorldWorld中win32-build中，如下图所示：
![win32-build目录](https://img-blog.csdnimg.cn/20200923225546421.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
另外，可以在`HelloWorld\win32-build\bin\HelloWorld\Debug`目录下找到编译生成的`HelloWorld.exe`可执行文件，里面还有一些相关的dll动态库文件。双击运行`HelloWorld.exe`即可运行项目。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200923225759642.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

双击执行HelloWorld.sln，在VS2017中启动工程。然后在HelloWorld上右键->设为启动项目，如下图。Ctrl+F5运行程序。
![设为启动项目](https://img-blog.csdnimg.cn/20200923230327383.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![运行结果](https://img-blog.csdnimg.cn/20200923230517245.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
至此，Window10系统下使用VS2017搭建cocos2d-x 4.0开发环境搭建完成。

关于项目的运行，也可以参考[https://github.com/cocos2d/cocos2d-x](https://github.com/cocos2d/cocos2d-x)，Github上面的描述：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200930202253413.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)



## 五、参考资料
- [https://github.com/cocos2d/cocos2d-x](https://github.com/cocos2d/cocos2d-x)
- [Cocos2d-x 4.0在各个平台的环境搭建方法]([https://docs.cocos2d-x.org/cocos2d-x/v4/zh/installation/](https://docs.cocos2d-x.org/cocos2d-x/v4/zh/installation/))
- [Cocos2d-x 4.0升级指南](https://docs.cocos2d-x.org/cocos2d-x/v4/en/upgradeGuide/)
- [CMake Guide for Cocos2d-x 4.0](https://docs.cocos2d-x.org/cocos2d-x/v4/en/installation/CMake-Guide.html)
- [cocos2d-x 4.0 学习之路（二）环境搭建 Windows版](https://blog.csdn.net/sunnyboychina/article/details/104711649)
- [cocos-2dx 4.0 win10 环境搭建血泪史](https://www.cnblogs.com/Airplus/p/12771516.html)
- [Cocos2d-x-4.0在VS2019环境下的环境搭建（官方下载的cocos2dx压缩包）](https://segmentfault.com/a/1190000022416703)
- [https://cocos2d-x.org](https://cocos2d-x.org)
- [https://cocos2d-x.org/download](https://cocos2d-x.org/download)
- [cocos2d-x 4.0 学习之路（三）运行cocos4.0自带的Demo程序](https://blog.csdn.net/sunnyboychina/article/details/104740930/)
- [Cocos 资料大全](https://github.com/fusijie/Cocos-Resource)
- [cocos2d-x 4.0 学习之路（五）第一个小游戏--忍者来袭](https://blog.csdn.net/sunnyboychina/article/details/104837384)
