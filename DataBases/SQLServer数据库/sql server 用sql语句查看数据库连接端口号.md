sql server 用sql语句查看数据库端口号
```sql
--查询端口号
exec sys.sp_readerrorlog 0, 1, 'listening'
```
