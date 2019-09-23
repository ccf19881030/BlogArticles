## [DBNETLIB ConnectionRead(recv()) 一般性网络错误](https://blog.csdn.net/owetointernet/article/details/77965165)
一般大家在使用ADO进行C++ 编程时，会遇到DBNETLIB ConnectionRead(recv()) 一般性网络错误，解决这个错误，先使用PING命令检查ADO连接的数据库IP地址，看看是否有网络丢包，在网络正常的情况下，有一种原因会造成上述错误，那就是数据库创建连接之前，_ConnectionPtr指针没有创建唯一实例，以及数据连接没有设置为长连接。解决此问题的代码如下：

1.

m_pConnection.CreateInstance(__uuidof(Connection));
m_pConnection->ConnectionTimeout= 0;
m_pConnection->Open((_bstr_t)m_strConnect,_T(""),_T(""),adModeUnknown);

当然，connectionTimeout，也可根据网络环境设置连接时间，如不设置，默认时间为30s。设置为0，为不限时间一直连接，但这样有可能会导致程序死锁，如果网络环境差，可以设置为100或者更多。

接上述问题，如果_ConnectionPtr指针实例在当前线程中每次数据库操作时创建，也会导致一般性网络错误，所有在一个线程中，唯一实例（_ConnectionPtr、_RecordsetPtr、_CommandPtr）被创建一次后，就可以进行当前线程中所有数据库操作，除非唯一实例被Release，才需要重新创建唯一实例。

2.

打开端口1433，MSSQL默认是TCP:1433；

防火墙将TCP:1433端口,添加入站规则；

SQL Server Browser 服务需要启动，才能正常.
