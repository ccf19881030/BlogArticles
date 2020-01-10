## 一、CMake下载
### [https://cmake.org/download/](https://cmake.org/download/)
## 二、CMake升级
### 1.[记一次 Centos7 cmake 版本升级（由 v2.8.12.2 升级至 v3.14.5）](https://blog.csdn.net/llwy1428/article/details/95473542)
### 2.[CentOS7升级cmake](https://www.jianshu.com/p/b283fad5e4de)
### 3、[centos7下升级cmake，很简单](https://blog.csdn.net/u013714645/article/details/77002555)
#### （1）、下载cmake，我下载的是最新版的[cmake 3.16.2](https://cmake.org/files/v3.16/cmake-3.16.2.tar.gz)
如果已经安装了cmake，比如用yum install cmake -y命令安装了cmake，默认的是2.8版本的cmake，在使用cmake编译一些项目时会提示cmake版本过低。
卸载cmake的命令很简单：
```shell
yum remove cmake -y
```

然后下载cmake
```shell
wget https://cmake.org/files/v3.16/cmake-3.16.2.tar.gz
```
解压并编译
```shell
tar -zxvf cmake-3.16.2.tar.gz
cd cmake-3.16.2
./bootstrap
gmake
# （需要在su命令下执行，或者直接使用root账户安装）
gmake install
```
编译安装cmake完成后查看cmake的版本
```shell
cmake --version
[root@VM_0_9_centos cmake-3.16.2]# cmake --version
cmake version 3.16.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
[root@VM_0_9_centos cmake-3.16.2]# 
```
