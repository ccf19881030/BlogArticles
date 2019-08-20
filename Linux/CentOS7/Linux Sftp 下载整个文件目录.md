## [Linux Sftp 下载整个文件目录](https://blog.csdn.net/shikenian520/article/details/80177294)
直接看图：
 ```shell
sftp> get -r /opt/work/ .
```
有两个特点：
1：使用-r参数
2：在目录后面使用"."号
这样的话就可以把/opt/work 目录和子目录里面的文件全部下载到本地了。
