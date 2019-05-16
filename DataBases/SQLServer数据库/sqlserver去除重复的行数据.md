1、利用 distinct 关键字过滤重复的行,将查询的结果写入临时表
```sql
select distinct * into #temp from  mytable 
```
2、删除表
```sql
delete mytable
```
3、将临时表插入到表中
```sql
insert mytable select * from #temp
```
4、释放临时表
```sql
drop #temp
```
