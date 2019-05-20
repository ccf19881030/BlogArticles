# [sqlcmd实用工具](https://docs.microsoft.com/zh-cn/sql/tools/sqlcmd-utility?view=sql-server-2017)
Sqlcmd实用工具，可以输入 TRANSACT-SQL 语句、 系统过程和脚本文件，通过各种可用模式：
通过命令提示符。
在中查询编辑器在 SQLCMD 模式下。
在 Windows 脚本文件。
在 SQL Server 代理作业的操作系统 (Cmd.exe) 作业步骤。
该实用工具使用 ODBC 执行 TRANSACT-SQL 批处理。
语法
```
sqlcmd   
   -a packet_size  
   -A (dedicated administrator connection)  
   -b (terminate batch job if there is an error)  
   -c batch_terminator  
   -C (trust the server certificate)  
   -d db_name  
   -e (echo input)  
   -E (use trusted connection)  
   -f codepage | i:codepage[,o:codepage] | o:codepage[,i:codepage] 
   -g (enable column encryption) 
   -G (use Azure Active Directory for authentication)
   -h rows_per_header  
   -H workstation_name  
   -i input_file  
   -I (enable quoted identifiers)  
   -j (Print raw error messages)
   -k[1 | 2] (remove or replace control characters)  
   -K application_intent  
   -l login_timeout  
   -L[c] (list servers, optional clean output)  
   -m error_level  
   -M multisubnet_failover  
   -N (encrypt connection)  
   -o output_file  
   -p[1] (print statistics, optional colon format)  
   -P password  
   -q "cmdline query"  
   -Q "cmdline query" (and exit)  
   -r[0 | 1] (msgs to stderr)  
   -R (use client regional settings)  
   -s col_separator  
   -S [protocol:]server[instance_name][,port]  
   -t query_timeout  
   -u (unicode output file)  
   -U login_id  
   -v var = "value"  
   -V error_severity_level  
   -w column_width  
   -W (remove trailing spaces)  
   -x (disable variable substitution)  
   -X[1] (disable commands, startup script, environment variables, optional exit)  
   -y variable_length_type_display_width  
   -Y fixed_length_type_display_width  
   -z new_password   
   -Z new_password (and exit)  
   -? (usage)
```
