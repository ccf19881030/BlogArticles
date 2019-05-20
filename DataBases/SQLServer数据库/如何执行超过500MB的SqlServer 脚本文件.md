# [如何执行超过500MB的SqlServer 脚本文件](https://blog.csdn.net/aiming66/article/details/81350109?utm_source=blogxgwz6)
## 什么是osql
osql 是一个 Microsoft Windows 32 命令提示符工具，您可以使用它运行 Transact-SQL 语句和脚本文件！

## 如何用
在开始->运行 中键入cmd,使用 “OSQL -?”命令，就可以显示osql命令行的帮助。 
注意：osql 工具的选项列表是区分大小的，在使用时注意。 
在键入cmd与下面这一个类似的命令：
```
osql -E -q "Transact-SQL statement"  

例如：sql -E -q "use myDB select * from myTable"

其中 -E 表示使用 Microsoft Windows NT 身份验证。

也可以使用sa账户，具体可以看看上面的命令！

而-q 表示运行 Transact-SQL 语句，但是在查询结束时不退出 osql。

如要运行 Transact-SQL 语句并退出 osql，请使用 -Q 参数来代替 -q。
```
## 使用osql执行一个大脚本文件
```
将该工具指向一个脚本文件,步骤：

a.创建一个包含一批 Transact-SQL 语句的脚本文件（如 myfile.sql）。

b.打开命令提示符，键入与下面类似的一个命令，然后按 ENTER 键：

osql -E -i input_file

其中input_file 是脚本文件及其完整路径。例如，如果脚本文件 myfile.sql 在 C:\users文件夹中，

请将参数 myfile 替换为 C:\users\myfile.sql。

该脚本文件的运行结果将出现在控制台窗口中。

如果您想将运行结果定向到一个文件，请向上述命令中添加 -o output_file 参数。例如：

osql -E -i input_file -o output_file

其中output_file 是输出文件及其完整路径。
```
