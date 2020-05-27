## [C++相对路径转换为绝对路径和linux、window移植api](https://blog.csdn.net/earbao/article/details/51941696)
```cpp
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include  <limits.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <io.h>
#else
#include<unistd.h>
#endif
#include <iostream>
using namespace std;
 
/**
linux和window移植api
头文件, 函数的不同，可以用如下宏，预处理：
#ifdef WIN32
  // windows handle
#elif __linux__
  // linux handle
#else
  // others handle
#endif
如果两个函数参数和返回值都相同时，如在windows下没有sleep，会使用宏里面定义的Sleep。
在linux下由于定义了sleep这样就不会用到这个宏了，它会调用linux下的sleep函数。
#ifndef sleep
#define sleep(seconds) (Sleep((seconds)*1000))
#endif
windows        替代     linux
localtime_s             localtime_r
inet_addr               inet_pton
GetTickCount            GetTickCount
Sleep毫秒               sleep秒
_mkdir                  mkdir
memset                  bzero
_fullpath               realpath
  */
//C++相对路径转换为绝对路径和linux、window移植api
//http://blog.csdn.net/tujiaw/article/details/7871547
int main()
{
    char* buffer;
    if( (buffer = _getcwd( NULL, 0 )) == NULL ) {
        perror( "_getcwd error" );
    } else {
        printf( "Current Dir: %s\n", buffer);
        //free(buffer);
    }
    char currentdir[1024]={0},dir[1024]={0};
    sprintf(currentdir,"%s/../../dir/test/",buffer);
    printf("%s\n", currentdir);
#ifdef _WIN32
    _fullpath(dir,currentdir,1024);
#else
    realpath(currentdir,dir);
#endif
     printf("dir=%s\n", dir);
 
    char resolved_path[1024];
#ifdef _WIN32
    _fullpath(resolved_path,"/usr/X11R6/lib/modules/../../include/../",1024);
#else
    realpath("/usr/X11R6/lib/modules/../../include/../",resolved_path);
#endif
    printf("resolved_path: %s\n", resolved_path);
    return 0;
 
}
```

```cpp
 string abs_path(string path)
 {
 #ifdef _WIN32
      #define max_path 4096
      char resolved_path[max_path]={0};
     _fullpath(resolved_path,path.c_str(),max_path);
 #else
     //linux release有个坑，需要大点的空间
     #define max_path 40960
     char resolved_path[max_path]={0};
     realpath(path.c_str(),resolved_path);
 #endif
     return string(resolved_path);
 }
 ```
