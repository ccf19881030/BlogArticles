# [SQL Server日期时间格式转换字符串详解](https://www.cnblogs.com/zhangleblog/p/3160888.html)
本文我们主要介绍了SQL Server日期时间格式转换字符串的相关知识，并给出了大量实例对其各个参数进行对比说明，希望能够对您有所帮助。

在SQL Server数据库中，SQL Server日期时间格式转换字符串可以改变SQL Server日期和时间的格式，是每个SQL数据库用户都应该掌握的。本文我们主要就介绍一下SQL Server日期时间转字符串的相关知识，接下来就让我们一起来了解一下这部分内容。

日期时间转字符串：

Select CONVERT(varchar(100), GETDATE(), 0): 05 16 2006 10:57AM   
Select CONVERT(varchar(100), GETDATE(), 1): 05/16/06   
Select CONVERT(varchar(100), GETDATE(), 2): 06.05.16   
Select CONVERT(varchar(100), GETDATE(), 3): 16/05/06   
Select CONVERT(varchar(100), GETDATE(), 4): 16.05.06   
Select CONVERT(varchar(100), GETDATE(), 5): 16-05-06   
Select CONVERT(varchar(100), GETDATE(), 6): 16 05 06   
Select CONVERT(varchar(100), GETDATE(), 7): 05 16, 06   
Select CONVERT(varchar(100), GETDATE(), 8): 10:57:46   
Select CONVERT(varchar(100), GETDATE(), 9): 05 16 2006 10:57:46:827AM   
Select CONVERT(varchar(100), GETDATE(), 10): 05-16-06   
Select CONVERT(varchar(100), GETDATE(), 11): 06/05/16   
Select CONVERT(varchar(100), GETDATE(), 12): 060516   
Select CONVERT(varchar(100), GETDATE(), 13): 16 05 2006 10:57:46:937   
Select CONVERT(varchar(100), GETDATE(), 14): 10:57:46:967   
Select CONVERT(varchar(100), GETDATE(), 20): 2006-05-16 10:57:47   
Select CONVERT(varchar(100), GETDATE(), 21): 2006-05-16 10:57:47.157   
Select CONVERT(varchar(100), GETDATE(), 22): 05/16/06 10:57:47 AM   
Select CONVERT(varchar(100), GETDATE(), 23): 2006-05-16   
Select CONVERT(varchar(100), GETDATE(), 24): 10:57:47   
Select CONVERT(varchar(100), GETDATE(), 25): 2006-05-16 10:57:47.250   
Select CONVERT(varchar(100), GETDATE(), 100): 05 16 2006 10:57AM   
Select CONVERT(varchar(100), GETDATE(), 101): 05/16/2006   
Select CONVERT(varchar(100), GETDATE(), 102): 2006.05.16   
Select CONVERT(varchar(100), GETDATE(), 103): 16/05/2006   
Select CONVERT(varchar(100), GETDATE(), 104): 16.05.2006   
Select CONVERT(varchar(100), GETDATE(), 105): 16-05-2006   
Select CONVERT(varchar(100), GETDATE(), 106): 16 05 2006   
Select CONVERT(varchar(100), GETDATE(), 107): 05 16, 2006   
Select CONVERT(varchar(100), GETDATE(), 108): 10:57:49   
Select CONVERT(varchar(100), GETDATE(), 109): 05 16 2006 10:57:49:437AM   
Select CONVERT(varchar(100), GETDATE(), 110): 05-16-2006   
Select CONVERT(varchar(100), GETDATE(), 111): 2006/05/16   
Select CONVERT(varchar(100), GETDATE(), 112): 20060516   
Select CONVERT(varchar(100), GETDATE(), 113): 16 05 2006 10:57:49:513   
Select CONVERT(varchar(100), GETDATE(), 114): 10:57:49:547   
Select CONVERT(varchar(100), GETDATE(), 120): 2006-05-16 10:57:49   
Select CONVERT(varchar(100), GETDATE(), 121): 2006-05-16 10:57:49.700   
Select CONVERT(varchar(100), GETDATE(), 126): 2006-05-16T10:57:49.827   
Select CONVERT(varchar(100), GETDATE(), 130): 18 ???? ?????? 1427 10:57:49:907AM  
在SQL数据库中，有一类函数是不得不提的，那就是SQL Server日期时间函数，这是SQL Server处理日期和时间最常用的函数，下面就将为介绍这类函数。

Sql Server日期与时间函数:

1.  当前系统日期、时间 

select getdate() 

2. dateadd  在向指定日期加上一段时间的基础上，返回新的 datetime 值

例如：向日期加上2天 

select dateadd(day,2,'2004-10-15')  --返回：2004-10-17 00:00:00.000

3. datediff 返回跨两个指定日期的日期和时间边界数。

select datediff(day,'2004-09-01','2004-09-18')   --返回：17

4. datepart 返回代表指定日期的指定日期部分的整数。

SELECT DATEPART(month, '2004-10-15')  --返回 10

5. datename 返回代表指定日期的指定日期部分的字符串

SELECT datename(weekday, '2004-10-15')  --返回：星期五

6. day(), month(),year() --可以与datepart对照一下

select 当前日期=convert(varchar(10),getdate(),120) ,当前时间=convert(varchar(8),getdate(),114)

select datename(dw,'2004-10-15')

select 本年第多少周=datename(week,'2004-10-15'),今天是周几=datename(weekday,'2004-10-15')

SQL Server日期函数     参数/功能

GetDate( )    返回系统目前的日期与时间

DateDiff (interval,date1,date2)   以interval 指定的方式，返回date2 与date1两个日期之间的差值 date2-date1

DateAdd (interval,number,date)   以interval指定的方式，加上number之后的日期

DatePart (interval,date)    返回日期date中，interval指定部分所对应的整数值

DateName (interval,date)   返回日期date中，interval指定部分所对应的字符串名称

参数interval的设定值如下：

值缩写（Sql Server） (Access 和 ASP) 说明

Year Yy yyyy 年 1753 ~ 9999

Quarter Qq q   季 1 ~ 4

Month Mm m   月1 ~ 12

Day of year Dy y  一年的日数,一年中的第几日 1-366

Day Dd d   日，1-31

Weekday Dw w 一周的日数，一周中的第几日 1-7

Week Wk ww  周，一年中的第几周 0 ~ 51

Hour Hh h   时0 ~ 23

Minute Mi n  分钟0 ~ 59

Second Ss s 秒 0 ~ 59

Millisecond Ms - 毫秒 0 ~ 999

Access 和Asp中用date()和now()取得系统日期时间；其中DateDiff,DateAdd,DatePart也同是能用于Access和asp中，这些函数的用法也类似。

SQL Server日期函数举例：

1.GetDate() 用于sql server :select GetDate()

2.DateDiff('s','2005-07-20','2005-7-25 22:56:32')返回值为 514592 秒

DateDiff('d','2005-07-20','2005-7-25 22:56:32')返回值为 5 天

3.DatePart('w','2005-7-25 22:56:32')返回值为 2 即星期一(周日为1，周六为7)

DatePart('d','2005-7-25 22:56:32')返回值为 25即25号

DatePart('y','2005-7-25 22:56:32')返回值为 206即这一年中第206天

DatePart('yyyy','2005-7-25 22:56:32')返回值为 2005即2005年

关于SQL Server日期时间格式转换字符串的相关知识就介绍到这里了，希望本次的介绍能够对您有所收获！
