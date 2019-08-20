## [【学习cmake】在 linux 下使用 CMake 构建应用程序 实践篇1](https://blog.csdn.net/KYJL888/article/details/80497176)
## [linux下使用cmake构建C/C++项目](https://www.cnblogs.com/lchb/articles/2797495.html)
## [part01_Linux下使用Cmake构建工程](https://www.jianshu.com/p/a7c88b7a9020)
## [Linux下如何完整的构建cmake项目](https://blog.csdn.net/felaim/article/details/71601017)
## [使用CMake构建复杂工程](https://www.linuxidc.com/Linux/2016-12/138082.htm)
## [在linux下使用CMake构建应用程序](http://blog.chinaunix.net/uid-28458801-id-3501768.html)
## [cmake 安装文件到指定目录](https://www.cnblogs.com/hanrp/p/11155909.html
### 使用 CMAKE_INSTALL_PREFIX 来指定。 
方法1： 
[plain] view plain copy print? 
cmake -DCMAKE_INSTALL_PREFIX=/usr .. 

### 方法二： 
修改cmake文件，加入： 
SET(CMAKE_INSTALL_PREFIX < install_path >) 

要加在 PROJECT(< project_name>) 之后。 
```cpp
摘录： 
Default Build and Installation: 

Installing vidstab library: 

cd path/to/vid.stab/dir/ 
cmake . 
make 
sudo make install 
默认会安装到： 
1）.h文件： 
/usr/local/include/vid.stab 
2).so文件： 
/usr/local/lib/libvidstab.so

方法一，在Ubuntu12.04 64位系统下测试使用有效。
参考：http://ju.outofmemory.cn/entry/329181
```
