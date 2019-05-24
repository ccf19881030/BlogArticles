# [C++遍历目录下的所有文件夹，找到某种格式的文件](https://blog.csdn.net/a342500329a/article/details/83855774)
首先需要使用Struct _finddata_t结构体，它是用来存储文件各种信息的结构体，
使用这个结构体要引用的头文件为“ #include <io.h>”
它的结构体定义如下：
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
比如要找个某个目录下的所有txt文件及其路径，代码如下：
```cpp
#include <io.h>		//_finddata_t的头文件
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
void findAllFile(const char * path,const char * format)
{
    char newpath[200];
    strcpy(newpath, path);
    strcat(newpath, "\\*.*");    // 在目录后面加上"\\*.*"进行第一次搜索
    int handle;
    _finddata_t findData;
    handle = _findfirst(newpath, &findData);
    if (handle == -1)        // 检查是否成功
        return;
     while (_findnext(handle, &findData) == 0){
        if (findData.attrib & _A_SUBDIR){
            if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
                continue;
            strcpy(newpath, path);
            strcat(newpath, "\\");
            strcat(newpath, findData.name);
            findAllFile(newpath,format);
        }
        else{
            if(strstr( findData.name,format)){     //判断是不是txt文件
                cout << findData.name << "\t" <<path<<"\t"<< findData.size << " bytes.\n";
            }
        }
    }
    _findclose(handle);    // 关闭搜索句柄
}

int main()
{
    findAllFile("D:\\WorkSpace\\test",".txt");
    return 0;
}
```
