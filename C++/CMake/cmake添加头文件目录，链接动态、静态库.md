最近需要将Windows10系统下使用VS2017编译的VC++项目放到CentOS Linux服务器上跑，最简单的当然是使用cmake作为项目编译和管理工具了，这样就不需要写makefile了，使用cmake管理编译项目相对来说比较简单。遇到一个问题就是，由于我在CentOS7服务器上用的是普通用户账号，一些第三方库比如Boost库、yaml-cpp、mariadb、mariadb++、hiredis库放到一个统一的目录下比如/opt/env目录，而不是常见的/usr/、/usr/local等目录，使用cmake进行编译时需要注意头文件和库文件的目录的设置。

# cmake 添加头文件目录，链接动态、静态库
罗列一下cmake常用的命令。

CMake支持大写、小写、混合大小写的命令。

## 1. 添加头文件目录INCLUDE_DIRECTORIES

语法：
`include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])`
它相当于`g++`选项中的`-I`参数的作用，也相当于环境变量中增加路径到`CPLUS_INCLUDE_PATH`变量的作用。
```cmake
include_directories(../../../thirdparty/comm/include)
```

## 2. 添加需要链接的库文件目录LINK_DIRECTORIES

语法：
`link_directories(directory1 directory2 ...)`
它相当于`g++`命令的`-L`选项的作用，也相当于环境变量中增加`LD_LIBRARY_PATH`的路径的作用。
```cmake
link_directories("/home/server/third/lib")
```

## 3. 查找库所在目录FIND_LIBRARY

语法：
```cmake
A short-hand signature is:

find_library (<VAR> name1 [path1 path2 ...])
The general signature is:

find_library (
          <VAR>
          name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [HINTS path1 [path2 ... ENV var]]
          [PATHS path1 [path2 ... ENV var]]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_DEFAULT_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_CMAKE_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

例子如下：
```cmake
FIND_LIBRARY(RUNTIME_LIB rt /usr/lib  /usr/local/lib NO_DEFAULT_PATH)
```
`cmake`会在目录中查找，如果所有目录中都没有，值`RUNTIME_LIB`就会被赋为`NO_DEFAULT_PATH`

## 4. 添加需要链接的库文件路径LINK_LIBRARIES

语法：

`link_libraries(library1 <debug | optimized> library2 ...)`

```
# 直接是全路径link_libraries(“/home/server/third/lib/libcommon.a”)
# 下面的例子，只有库名，cmake会自动去所包含的目录搜索link_libraries(iconv)# 传入变量link_libraries(${RUNTIME_LIB})
# 也可以链接多个link_libraries("/opt/MATLAB/R2012a/bin/glnxa64/libeng.so"　"/opt/MATLAB/R2012a/bin/glnxa64/libmx.so")
```

可以链接一个，也可以多个，中间使用空格分隔.

## 5. 设置要链接的库文件的名称TARGET_LINK_LIBRARIES 

语法：

`target_link_libraries(<target> [item1 [item2 [...]]]
                      [[debug|optimized|general] <item>] ...)`

```
# 以下写法都可以： 
target_link_libraries(myProject comm)       # 连接libhello.so库，默认优先链接动态库
target_link_libraries(myProject libcomm.a)  # 显示指定链接静态库
target_link_libraries(myProject libcomm.so) # 显示指定链接动态库

# 再如：
target_link_libraries(myProject libcomm.so)　　#这些库名写法都可以。
target_link_libraries(myProject comm)
target_link_libraries(myProject -lcomm)   
```

## 6. 为工程生成目标文件
语法
```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               source1 [source2 ...])
```

简单的例子如下：
```cmake
add_executable(demo
        main.cpp
)
```

## 7.最后贴一个完整的例子
```cmake
cmake_minimum_required (VERSION 2.6)

INCLUDE_DIRECTORIES(../../thirdparty/comm)

FIND_LIBRARY(COMM_LIB comm ../../thirdparty/comm/lib NO_DEFAULT_PATH)
FIND_LIBRARY(RUNTIME_LIB rt /usr/lib  /usr/local/lib NO_DEFAULT_PATH)

link_libraries(${COMM_LIB} ${RUNTIME_LIB})

ADD_DEFINITIONS(
-O3 -g -W -Wall
 -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
 -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
 -D__WUR= -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DTIXML_USE_STL
)


add_library(lib_demo
        cmd.cpp
        global.cpp
        md5.cpp
)

link_libraries(lib_demo)
add_executable(demo
        main.cpp
)

# link library in static mode
target_link_libraries(demo libuuid.a)
```

另外，使用cmake生成makefile之后，make edit_cache可以编辑编译选项。

不熟悉的命令可以去查找文档，贴个目前最新的cmake3.19官方帮助文档地址
[https://cmake.org/cmake/help/v3.19/index.html](https://cmake.org/cmake/help/v3.19/index.html])


# 参考资料
- [cmake 添加头文件目录，链接动态、静态库](https://www.cnblogs.com/binbinjx/p/5626916.html)
- [cmake 链接动态链接库](https://blog.csdn.net/mtt_sky/article/details/43018859)
- [cmake 3.19官网帮助文档](https://cmake.org/cmake/help/v3.19/)
- [Getting started with cmake](https://riptutorial.com/cmake)
- [CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160)
- [Configure builds using CMake](https://docs.microsoft.com/en-us/azure-sphere/app-development/using-cmake-functions)
- [A Step-By-Step Guide to Install CMake on Linux](https://www.linuxfordevices.com/tutorials/install-cmake-on-linux)
