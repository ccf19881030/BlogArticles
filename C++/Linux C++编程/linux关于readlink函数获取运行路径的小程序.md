## [linux关于readlink函数获取运行路径的小程序](https://www.cnblogs.com/LiuYanYGZ/p/5499286.html)
http://blog.csdn.net/djzhao/article/details/8178375
## [Linux C/C++获取当前目录和运行文件所在目录](https://www.jianshu.com/p/5ab47db18aa7)
```cpp
获取当前工作目录可以使用
include<unistd.h>
char *getcwd( char *buffer, int maxlen );
而要找到当前所运行的文件的目录，可以使用
readlink("/proc/self/exe", char *buffer, int maxlen );
```
