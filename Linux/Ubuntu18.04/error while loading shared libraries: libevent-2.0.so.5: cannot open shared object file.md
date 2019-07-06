## [error while loading shared libraries: libevent-2.0.so.5: cannot open shared object file](https://blog.csdn.net/rongxiaojun1989/article/details/18266697)
   在Ubuntu18.10中安装了libevent 2.1.6
   参考[Ubuntu安装libevent](https://www.cnblogs.com/willaty/p/8022039.html)
   ```shell
   按照github官方做法:
$ sudo apt-get install openssl
$ mkdir build && cd build
$ cmake .. # Default to Unix Makefiles.
$ make
$ make verify # (optional)
$ make install
  
老版本:
$ tar zxvf libevent-1.2.tar.gz
$ cd libevent-1.2
$ ./configure –prefix=/usr
$ make
$ make install
  
也可采用:
apt-cache search libevent
apt-get install libevent-dev
```
### 注意:
linux下用qtcreator进行编程的时候注意点 
在安装之后，利用Qtcreator进行项目管理的时候，需要在pro文件中添加如下： 
LIBS += -levent

正如在gcc中编译的时候，添加如下： 
gcc -o basic basic.c -levent


默认将libevent库安装到了/usr/local目录，导致运行libevent的示例程序时，找不到动态库 libevent.so.2.2.0，因为系统默认的一般是如下的目录
/usr/local/lib
/usr/local/lib/x86_64-linux-gnu
/lib/x86_64-linux-gnu
/usr/lib/x86_64-linux-gnu
```shell
havealex@havealex:~/programming/cplus/libevent-master$ cd /etc/ld.so.conf.d/
havealex@havealex:/etc/ld.so.conf.d$ ls
libc.conf  x86_64-linux-gnu.conf
havealex@havealex:/etc/ld.so.conf.d$ cat libc.conf 
# libc default configuration
/usr/local/lib
havealex@havealex:/etc/ld.so.conf.d$ cat x86_64-linux-gnu.conf 
# Multiarch support
/usr/local/lib/x86_64-linux-gnu
/lib/x86_64-linux-gnu
/usr/lib/x86_64-linux-gnu
havealex@havealex:/etc/ld.so.conf.d$ 
```
以root账户修改x86_64-linux-gnu.conf 文件，在文件末尾追加上刚才libevent安装的lib位置/usr/local/lib即可
```shell
havealex@havealex:/etc/ld.so.conf.d$ whereis  libevent.so.2.2.0
libevent.so.2.2: /usr/local/lib/libevent.so.2.2.0
havealex@havealex:/etc/ld.so.conf.d$ ls /usr/local/lib/
cmake            libevent_core.so        libevent_extra.so        libevent_openssl.so        libevent_pthreads.so        libevent.so.2.2.0  python3.6
libevent.a       libevent_core.so.2.2.0  libevent_extra.so.2.2.0  libevent_openssl.so.2.2.0  libevent_pthreads.so.2.2.0  pkgconfig
libevent_core.a  libevent_extra.a        libevent_openssl.a       libevent_pthreads.a        libevent.so                 python2.7
```shell
havealex@havealex:/etc/ld.so.conf.d$ ls
libc.conf  x86_64-linux-gnu.conf
havealex@havealex:/etc/ld.so.conf.d$ sudo vim x86_64-linux-gnu.conf 
# Multiarch support
/usr/local/lib/x86_64-linux-gnu
/lib/x86_64-linux-gnu
/usr/lib/x86_64-linux-gnu
/usr/local/lib  # 这个是追加的路径，libevent的lib库的路径存放位置

havealex@havealex:/etc/ld.so.conf.d$ sudo ldconfig
```

