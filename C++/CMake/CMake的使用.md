  CMake是一个跨平台的Makefile生成工具，可以根据特定的规则生成相应的Makefile文件，并对C/C++源代码进行编译和管理。
 有两篇博客介绍CMake的使用，比较通俗易懂，链接地址是：
* [Cmake 详解](https://blog.codekissyoung.com/常用软件/cmake)
* [CMake 入门实战](https://www.hahack.com/codes/cmake/)
* CMake的官方下载地址为：[https://cmake.org/download/](https://cmake.org/download/)
* 官方文档地址为：[CMake 3.16 Documentation](https://cmake.org/documentation/)
* 官方的CMake指南地址为：[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
 ##  一、CMake中添加对C++11的支持
 ### 1、在对应的CMakeLists.txt文件中加入以下语句：
 ```shell
add_definitions(-std=c++11)
```
或者
```shell
 if(CMAKE_COMPILER_IS_GNUCXX)
      set(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")
 endif(CMAKE_COMPILER_IS_GNUCXX)
 ```
 ### 2、延伸 [如何写cmake使其包含c++11特性 （-std=c++11如何写进cmakeList.txt）](https://blog.csdn.net/chigusakawada/article/details/83655690)
 使用的g++版本和cmake版本分别是g++ 4.8.2和cmake 2.8
 之前写cmkae编译带有c++11特性的代码有这么一句：
 ```shell
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
```
但是总会出现cc1plus: error: unrecognized command line option "-std=c++11" 报错。
所以set(QMAKE_CXXFLAGS "-std=c++11")  类似的写法肯定不行。
后来发现是std=c++11 这种写法老版本不支持。
ok
直接测试新写法 CMakeLists.txt文件如下所示：
 ```shell
 #CMakeLists.txt
project(test)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST}${PROJECT_NAME}.cpp)
 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
```
#### 测试c++11代码如下：
```cpp
//test.cc
#include <iostream>
#include<vector>
using namespace std; 
int main()
{
    const std::vector<int>v(1);
    auto a = v[0];//a为int类型
        cout <<"a : "<< a <<endl;
    decltype(v[0]) b = 0;//b为const int&类型，即std::vector<int>::operator[]（size_type）const的返回类型
    auto c = 0;//c为int类型
    auto d = c;//d为int类型
    decltype(c) e;//e为int类型，c实体的类型
    decltype((c)) f = e;//f为int&类型，因为（c）是左值
    decltype(0) g;//g为int类型，因为0是右值
    
    return 0;
}
```

## examples_CMake项目
github上面有一个韩国人jacking75写的简单的cmake使用示例，
examples_CMake项目地址是：[https://github.com/jacking75/examples_CMake](https://github.com/jacking75/examples_CMake)
### CMake例子
#### 范例介绍
示例代码在CMake_example目录中。
##### 01 helloworld 一个简单文件中的-C ++代码
* main.cpp
```cpp
#include <iostream>

int main()
{
  auto name = "jacking";
  std::cout << "hello world: " << name << std::endl;
  return 0;
}
```
* CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)
add_executable(Main main.cpp)
```
##### 02 helloworld-设置编译器选项。 -Wall，C ++ 14
* main.cpp
```cpp
#include <iostream>

int main()
{
  auto name = "jacking";
  std::cout << "hello world: " << name << std::endl;
  return 0;
}
```
* CMakeLists.txt
```make
cmake_minimum_required(VERSION 2.8)
add_definitions("-Wall -std=c++14")
add_executable(Main main.cpp)
```
##### 03 helloworld-如果您有除主代码文件以外的其他代码文件
* main.cpp
```cpp
#include "test.h"

int main()
{
    TEST test;
    test.Print();
    return 0;
}
```
*  test.h
```cpp
class TEST
{
public:
    void Print();
};
```
* test.cpp
```cpp
#include "test.h"

#include <iostream>

void TEST::Print()
{
    std::cout << "Test::Print" << std::endl;
}
```
* CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 2.8)
add_executable(Main
  main.cpp
  test.cpp
)
```
##### 04 helloworld-如果mai.cpp以外的文件位于其他目录中
源代码04_helloworld目录结构如下：
```shell
[root@ltcos01 04_helloworld]$ tree -L 2
.
├── CMakeLists.txt
├── main.cpp
├── test01
│   ├── test01.cpp
│   └── test01.h
└── test02
    ├── test02.cpp
    └── test02.h

2 directories, 6 files
```
* main.cpp
```cpp
#include "test01/test01.h"
#include "test02/test02.h"

int main()
{
  TEST01 test01;
  test01.Print();

  TEST02 test02;
  test02.Print();
  return 0;
}
```
 test01目录下 有test01.h和test01.cpp这两个文件
 
* test01/test01.h
```cpp
class TEST01
{
public:
  void Print();
};
```
* test01/test01.cpp
```cpp
#include "test01.h"
#include <iostream>

void TEST01::Print()
{
    std::cout << "Test01::Print" << std::endl;
}
```
test02目录下有test02.h和test02.cpp这两个文件
* test02/test02.h
```cpp
class TEST02
{
public:
    void Print();
};
```
* test02/test02.cpp
```cpp
#include "test02.h"
#include <iostream>

void TEST02::Print()
{
    std::cout << "Test02::Print" << std::endl;
}
```
*  CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 2.8)
add_executable(Main
  main.cpp
  test01/test01.cpp
  test02/test02.cpp
)
```

##### 05 helloworld-reference 创建静态文件后
05_helloworld源代码目录树结构如下所示：
```shell
[root@ltcos01 05_helloworld]$ tree -L 2
.
├── CMakeLists.txt
├── main.cpp
├── test01
│   ├── CMakeLists.txt
│   ├── test01.cpp
│   └── test01.h
└── test02
    ├── CMakeLists.txt
    ├── test02.cpp
    └── test02.h

2 directories, 8 files
```
* main.cpp
```cpp
#include "test01/test01.h"
#include "test02/test02.h"

int main()
{
    TEST01 test01;
    test01.Print();

    TEST02 test02;
    test02.Print();
    return 0;
}
```
* CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 2.8)
add_subdirectory(test01)                
add_subdirectory(test02)                
add_executable(Main main.cpp)
target_link_libraries(Main Test01 Test02)
```
test01目录下有test01.h和test01.cpp以及相应的CMakeLists.txt文件
* test01/test01.h
```cpp
class TEST01
{
public:
    void Print();
};
```
* test01/test01.cpp
```cpp
#include "test01.h"

#include <iostream>

void TEST01::Print()
{
    std::cout << "Test01::Print" << std::endl;
}
```
* test01/CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 2.8)
add_library(Test01 STATIC
  test01.cpp
)
```
上面的test01目录下的CMakeLists.txt的add_library(Test01 STATIC test01.cpp)指令会生成相应的静态库文件libTest01.a

 test02目录下和test01目录结构一样，也有test02.h和test02.cpp以及相应的CMakeLists.txt文件
* test01/test02.h
```cpp
class TEST02
{
public:
    void Print();
};
```
* test02/test02.cpp
```cpp
#include "test02.h"

#include <iostream>

void TEST02::Print()
{
    std::cout << "Test02::Print" << std::endl;
}
```
* test02/CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 2.8)
add_library(Test02 STATIC
  test02.cpp
)
```
同样的，在上面的test02目录下执行cmake命令会生成相应的静态库文件libTest02.a。具体操作过程如下：新建一个build目录，然后进入到build目录下执行cmake ..运行上一级目录即test02下的CMakeLists.txt文件，操作如下：
```shell
[root@ltcos01 test02]$ ls
build  CMakeLists.txt  test02.cpp  test02.h
[root@ltcos01 test02]$ cd build/
[root@ltcos01 build]$ ls
[root@ltcos01 build]$ cmake ..
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /data/public/home/cchufeng/GithubProjects/examples_CMake/CMake_example/05_helloworld/test02/build
[root@ltcos01 build]$ make
Scanning dependencies of target Test02
[ 50%] Building CXX object CMakeFiles/Test02.dir/test02.cpp.o
[100%] Linking CXX static library libTest02.a
[100%] Built target Test02
[root@ltcos01 build]$ ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  libTest02.a  Makefile
[root@ltcos01 build]$ 
```
##### 06 helloworld-指定编译器
* main.cpp
```cpp
#include <iostream>

int main()
{
    auto name = "jacking";
  std::cout << "hello world: " << name << std::endl;
  return 0;
}
```
* CMakeLists.txt
```cmake
PROJECT(hello)

set(CMAKE_CXX_COMPILER g++)
add_definitions("-Wall -std=c++14")

ADD_EXECUTABLE(main main.cpp)
```
##### 07 helloworld-使用外部库（此处为Boost库）
* main.cpp
```cpp
#include <boost/thread.hpp>
#include <iostream>

int main()
{
    std::cout << "Boost.Thread !!!" << std::endl;
    boost::thread Thread1( [] ()
    {
        for( int i = 0; i < 5; ++i )
        {
            std::cout << "Thread Num : " << i << std::endl;
        }
    } );

    Thread1.join();
    return 0;
}
```
* CMakeLists.txt
```cmake
PROJECT(hello)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-m64")
add_definitions("-Wall -std=c++14")

INCLUDE_DIRECTORIES(/$ENV{HOME}/Dev/C++/ThirdParty/boost_1_60_0)
LINK_DIRECTORIES(/$ENV{HOME}/Dev/C++/ThirdParty/boost_1_60_0/stage/gcc/lib)

ADD_EXECUTABLE(hello-boost hello-boost.cpp)

TARGET_LINK_LIBRARIES(hello-boost pthread boost_thread boost_system boost_chrono)
```
