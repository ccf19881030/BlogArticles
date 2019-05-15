* [sqlserver中的bcp查询导出海量数据](https://blog.csdn.net/zhangshufei8001/article/details/51130072)
 * 在SQLServer中要开启组件 'xp_cmdshell',要不就报错,因为为了安全,sql默认是关闭的.
错误信息:在执行上述命令的时候可能会报错 ： 错误提示：消息 15281，级别 16，状态 1，过程 xp_cmdshell，第 1 行
打开SQLServer数据库，新建查询语句，输入以下命令：
```sql
-- 允许配置高级选项  
EXEC master.sys.sp_configure 'show advanced options', 1  
-- 重新配置  
RECONFIGURE  
-- 启用xp_cmdshell  
EXEC master.sys.sp_configure 'xp_cmdshell', 1  
--重新配置  
RECONFIGURE
```
