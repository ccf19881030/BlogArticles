## [centos 7 下升级自带 sqlite3](https://www.cnblogs.com/leffss/p/11555556.html)
### 问题
在 centos 7 上面运行 django 2.2 开发服务器时出现：
```shell
django.core.exceptions.ImproperlyConfigured: SQLite 3.8.3 or later is required (found 3.7.17).
```
原因时系统自带 sqlite3 版本太低，解决方法是升级就可以了。

### 升级
```shell
# 下载源码
wget https://www.sqlite.org/2019/sqlite-autoconf-3290000.tar.gz
# 编译
tar zxvf sqlite-autoconf-3290000.tar.gz 
cd sqlite-autoconf-3290000/
./configure --prefix=/usr/local
make && make install

# 替换系统低版本 sqlite3
mv /usr/bin/sqlite3  /usr/bin/sqlite3_old
ln -s /usr/local/bin/sqlite3   /usr/bin/sqlite3
echo "/usr/local/lib" > /etc/ld.so.conf.d/sqlite3.conf
ldconfig
sqlite3 -version
```

再次启动运行 django 2.2 开发服务器就 ok 了。
