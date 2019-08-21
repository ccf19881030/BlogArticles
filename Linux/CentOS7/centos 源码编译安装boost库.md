## [centos 源码编译安装boost库](https://www.cnblogs.com/BlueskyRedsea/p/6735699.html)
（1）首先去官网下载boost源码安装包：http://www.boost.org/

        选择下载对应的boost源码包。本次下载使用的是 boost_1_63_0.tar.gz。

　　　执行命令mkdir boostrec创建文件夹。

　　　执行命令cd进入boostrec文件夹下。

　　　执行命令wget https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.gz下载源码

（2）解压文件：tar -zxvf boost_1_63_0.tar.gz

（3）执行命令  ./bootstrap.sh

     默认的boost头文件安装到/usr/local/include/文件夹下。boost库文件会安装到/usr/local/lib/文件夹下。

（4）执行完上一条命令之后可以执行命令  ./b2  进行编译。（注意：编译需要耗费相当长的一段时间）

（5）然后执行下面安装命令 

        ./b2 install  或者 ./bjam install

（6）执行命令：cp -rf /usr/local/include/boost/* /usr/include/boost

　　  将/usr/local/include/boost文件夹及里面的内容全部拷贝到/usr/include/boost下。

（7）执行命令:cp -rf /usr/local/lib/* /usr/lib　  

　　  将/usr/local/lib下的所有文件拷贝到/usr/lib下。

（8）执行命令:ldconfig /usr/local/lib
