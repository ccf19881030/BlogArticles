## [windows平台使用VS2017编译libevent源码](https://www.cnblogs.com/xiacaojun/p/10796506.html)
### [夏曹俊老师的网站资源地址](http://ffmpeg.club/tools_download.html)
### [libevent 相关资源下载-夏曹俊老师的网站资源地址](http://www.ffmpeg.club/libevent.html)
### Window下使用VS2017编译libevent源码以及依赖库zlib和openssl
#### 1、使用build_zlib_vs2017_32.bat脚本编译[zlib源代码](http://zlib.net)
```bat
set VS="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
call %VS%
set OUT=D:\OpenSourceProjects\out\vs2017_32_zlib
cd D:\OpenSourceProjects\zlib-1.2.11
nmake /f win32\Makefile.msc clean
nmake /f win32\Makefile.msc
md %OUT%\lib
md %OUT%\bin
md %OUT%\include
copy /Y *.lib %OUT%\lib
copy /Y *.h %OUT%\include
copy /Y *.dll %OUT%\bin
copy /Y *.exe %OUT%\bin
pause
```
#### 2、[windows 平台使用 VS2017 编译openssl源码](https://www.cnblogs.com/xiacaojun/p/10791307.html)
#### 3、使用bat脚本编译libevent源代码
```bat
set VS="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
call %VS%
set OUT=D:\OpenSourceProjects\out\libevent_vs2017_32
cd D:\OpenSourceProjects\libevent-master
nmake /f Makefile.nmake clean
nmake /f Makefile.nmake OPENSSL_DIR=D:\env_build\openssl1.1.1_vs2017_32
md %OUT%\lib
md %OUT%\bin
md %OUT%\include
copy /Y *.lib %OUT%\lib
copy /Y *.h %OUT%\include
copy /Y *.dll %OUT%\bin
copy /Y *.exe %OUT%\bin
pause
```
