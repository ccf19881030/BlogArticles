## [centos7安装mariadb](https://www.cnblogs.com/ifelz/p/9140000.html)
centos7安装mariadb
~]# cat /etc/redhat-release 
CentOS Linux release 7.4.1708 (Core)

1.官方um安装mariadb

1).准备官方yum
[mariadb]
name = MariaDB
baseurl = http://yum.mariadb.org/10.2/rhel7-amd64
gpgkey=https://yum.mariadb.org/RPM-GPG-KEY-MariaDB
gpgcheck=1

yum install MariaDB-server MariaDB-client
2.二进制格式安装mariadb

1).检查环境,如系统已经安装mysql或mariadb先卸载
iptables; selinux; mariadb-server

2).安装配置

> 用户,解压,目录,权限修改
useradd -r -s /sbin/nologin mysql -d /data/mysql -m
tar -xvf mariadb-10.2.15-linux-x86_64.tar.gz -C /usr/local/
cd /usr/local/;ln -s mariadb-10.2.15-linux-x86_64/ mysql;chown -R mysql. /usr/local/mysql/.*

> 数据库文件存放目录
mkdir /data/mysql
chown -R mysql.mysql /data/mysql

> 初始化数据库
/usr/local/mysql/scripts/mysql_install_db --datadir=/data/mysql --user=mysql
./bin/mysqld: error while loading shared libraries: libaio.so.1: cannot open shared object file: No such file or directory

yum install libaio-devel.x86_64

> 拷贝编辑配置文件
cp /usr/local/mysql/support-files/my-huge.cnf /etc/my.cnf
sed -i '/\[mysqld\]/a\datadir = /data/mysql' /etc/my.cnf

> 添加环境变量
cat > /etc/profile.d/mysql.sh << EOF 
export PATH=/usr/local/mysql/bin:$PATH
EOF

> 拷贝服务脚本
cp /usr/local/mysql/support-files/mysql.server /etc/init.d/mysqld -a; cp /usr/local/mysql/support-files/mysql.server /usr/lib/systemd/mysqld.server
systemctl start mysql

> 运行加固脚本
mysql_secure_installation

 

3.源码编译安装mariadb

> 依赖包安装
yum install bison bison-devel zlib-devel libcurl-devel libarchive-devel boost-devel gcc gcc-c++ cmake libevent-devel gnutls-devel libaio-devel openssl-devel ncurses-devel libxml2-devel

> 准备用户及相关目录
mkdir /data/mysql -p; chown -R mysql:mysql /data/mysql
mkdir /usr/local/mysql
useradd -r -s /sbin/nologin mysql

> 编译安装
tar -xvf mariadb-10.2.15.tar.gz
cd mariadb-10.2.15
cmake . \
-DCMAKE_INSTALL_PREFIX=/usr/local/mysql \
-DMYSQL_DATADIR=/data/mysql/ \
-DSYSCONFDIR=/etc \
-DMYSQL_USER=mysql \
-DWITH_INNOBASE_STORAGE_ENGINE=1 \
-DWITH_ARCHIVE_STORAGE_ENGINE=1 \
-DWITH_BLACKHOLE_STORAGE_ENGINE=1 \
-DWITH_PARTITION_STORAGE_ENGINE=1 \
-DWITHOUT_MROONGA_STORAGE_ENGINE=1 \
-DWITH_DEBUG=0 \
-DWITH_READLINE=1 \
-DWITH_SSL=system \
-DWITH_ZLIB=system \
-DWITH_LIBWRAP=0 \
-DENABLED_LOCAL_INFILE=1 \
-DMYSQL_UNIX_ADDR=/data/mysql/mysql.sock \
-DDEFAULT_CHARSET=utf8 \
-DDEFAULT_COLLATION=utf8_general_ci

make -j$(cat /proc/cpuinfo| grep "processor"| wc -l) && make install

> 添加环境变量
cat > /etc/profile.d/mysql.sh << EOF 
export PATH=/usr/local/mysql/bin:$PATH
EOF

source /etc/profile.d/mysql.sh

> 初始化数据库
cd /usr/local/mysql
./scripts/mysql_install_db --datadir=/data/mysql/ --basedir=/usr/local/mysql/ --user=mysql

> 拷贝启动脚本及配置文件
cp support-files/mysql.server /etc/init.d/mysqld
cp support-files/my-huge.cnf /etc/my.cnf

> 启动服务
/etc/init.d/mysqld start

> 初始化安全脚本
mysql_secure_installation

分类: mysql
