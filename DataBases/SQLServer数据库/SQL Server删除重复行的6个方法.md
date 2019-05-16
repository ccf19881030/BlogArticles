# [SQL Server删除重复行的6个方法](https://www.cnblogs.com/kayvanguo/p/5851015.html)

## SQL Server删除重复行的6个方法:
SQL Server删除重复行是我们最常见的操作之一，下面就为您介绍六种适合不同情况的SQL Server删除重复行的方法，供您参考。

### 1.如果有ID字段，就是具有唯一性的字段  
```sql
delect   table  tableName  where   id   not   in   (   select   max(id)   from   table   group   by   col1,col2,col3...   )     

group   by   子句后跟的字段就是你用来判断重复的条件，如只有col1，那么只要col1字段内容相同即表示记录相同。  
```
### 2. 如果是判断所有字段也可以这样  ，【对于表中的指定的字段的进行检查是否相同】
```sql
select   *   into   #temp  from   tablename    group   by   id1,id2,....     

delete    tablename       

insert   into   table  select   *   from   #temp  

drop   table   #temp  
```
### 3.  首先去重复，再获取N*1条数据插入到临时表中，【对于表中的所有字段的进行检查是否相同】，再将原表的数据删除，然后将临时表的数据插入到原表，最后删除临时表。
```sql
select   distinct   *   into   #temp   from   tablename       

delete       tablename       

go     

insert   tablename   select   *   from   #temp     

go     

drop   table   #temp  
```
  

### 4. 没有ID的情况  
```sql
select   identity(int,1,1)   as   id,*   into   #temp   from   tabel     

delect   #   where   id   not   in   (     

select   max(id)   from   #   group   by   col1,col2,col3...)     

delect   table     

inset   into   table(...)     

select   .....   from   #temp    
```
### 5. col1+','+col2+','...col5 联合主键  
```sql
select   *   from     table   where   col1+','+col2+','...col5   in   (     

select   max(col1+','+col2+','...col5)   from   table       

where   having   count(*)>1     

group   by   col1,col2,col3,col4       

)    

group   by   子句后跟的字段就是你用来判断重复的条件，如只有col1，那么只要col1字段内容相同即表示记录相同。  
```
### 6. 第6种方法
```sql
select   identity(int,1,1)   as   id,*   into   #temp   from   tabel     

select   *   from     #temp   where   id   in   (     

select   max(id)   from   #emp   where   having   count(*)>1   group   by   col1,col2,col3...)   
```
