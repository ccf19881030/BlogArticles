* 参考博客:[如何修改PKG_CONFIG_PATH环境变量](https://blog.csdn.net/xiamentingtao/article/details/78370693)
```shell
 $ export PKG_CONFIG_PATH=/usr/lib/x86_64-linux-gnu/pkgconfig/:/usr/local/lib/pkgconfig/:/usr/lib/pkgconfig/:$PKG_CONFIG_PATH
```
 *可以通过下面命令查看
```shell
$ echo $PKG_CONFIG_PATH
/usr/lib/x86_64-linux-gnu/pkgconfig/:/usr/local/lib/pkgconfig/:/usr/lib/pkgconfig/:
```
