- The server requested authentication method unknown to the client
mysqli_real_connect(): The server requested authentication method unknown to the client [caching_sha2_password]
mysqli_real_connect(): (HY000/2054): The server requested authentication method unknown to the client

```shell
1、命令行登录mysql；
2、mysql>use mysql;
3、mysql>ALTER USER root IDENTIFIED WITH mysql_native_password BY '你的密码';
4、mysql>FLUSH PRIVILEGES;
```
