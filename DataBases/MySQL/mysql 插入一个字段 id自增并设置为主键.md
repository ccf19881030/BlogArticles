## 1.mysql 插入一个字段 id自增并设置为主键
```sql
ALTER TABLE t_security ADD id INT(16) NOT NULL
    PRIMARY KEY AUTO_INCREMENT FIRST;
```

## 2.mysql 将某个字段修改成自增
```sql
alter table `gray_week_analysis_0` modify id int auto_increment;
```
