## [C/C++中计算函数运行时间的两种方法](https://blog.csdn.net/m0_37925202/article/details/78447052)
在写代码中，有时候我们需要评估某段代码或者函数的执行时间；方法就是在该段代码或者函数前面，记录一个时间T1，在代码段或函数后面记录时间T2，那其运行时间就是T2-T1，下面看看具体运算方法：
### 方法一：
clock()是C/C++中的计时函数，而与其相关的数据类型是clock_t;  头文件：time.h/ctime
在C/C++中，还定义了一个常量CLOCKS_PER_SEC，它用来表示一秒钟会有多少个时钟计时单元，其定义如下：
 ```cpp
  #define    CLOCKS_PER_SEC      ((clock_t)1000)
 ```
代码实现：
```cpp
#include “stdio.h”    
#include “stdlib.h”    
#include “time.h”    
int main( void )    
{    
   long    i = 10000000L;    
   clock_t start, finish;    
   double  duration;    
   /* 测量一个事件持续的时间*/    
   printf( "Time to do %ld empty loops is ", i );    
   start = clock();    
   while( i-- )      ;    
   finish = clock();    
   duration = (double)(finish - start) / CLOCKS_PER_SEC;    
   printf( "%f seconds\n", duration );    
   
   system("pause");    
}    
```

### 方法二：
函数原型：DWORD GetTickCount(void);
头文件：    C/C++头文件：winbase.h
windows程序设计中可以使用头文件windows.h

核心函数                头文件          函数库         精度        准确度
ftime                sys/timeb.h       c函数           ms         较准确
```cpp
#include <time.h> 
#include <stdio.h> 
#include <tchar.h> 
#include <sys/timeb.h> 
#include<Windows.h> 
int main()
{
struct timeb startTime, endTime;
ftime(&startTime);
Sleep(1000);
ftime(&endTime);
printf("time: %d ms\n", (endTime.time - startTime.time) * 1000 
+ (endTime.millitm - startTime.millitm));

return 0;
}
```

### 方法三：
GetTickCount是函数。GetTickCount返回（retrieve）从操作系统启动所经过（elapsed）的毫秒数，它的返回值是DWORD。
```cpp
#include<iostream>  
#include<Windows.h>  
  
using namespace std;  
  
int main()  
{  
    DWORD start_time = GetTickCount();  
    for (int i = 0; i < 100000000; i++)  
    {  
        i++;  
    }  
    DWORD end_time = GetTickCount();  
    cout << "The run time is:" << (end_time - start_time) << "ms!" << endl;  
    system("pause");  
    return 0;  
}
```
