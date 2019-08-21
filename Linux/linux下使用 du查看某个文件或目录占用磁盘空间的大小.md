## [linux下使用 du查看某个文件或目录占用磁盘空间的大小](https://www.cnblogs.com/mitang/p/7724750.html)
Ubuntu 查看磁盘空间大小命令

http://www.cnblogs.com/zhuiluoyu/p/6598928.html
 
df -h Df命令是linux系统以磁盘分区为单位查看文件系统，可以加上参数查看磁盘剩余空间信息，
命令格式： df -hl 
显示格式为： 
　　文件系统 容量 已用 可用 已用% 挂载点 Filesystem Size Used Avail Use% Mounted on /dev/hda2 45G 19G 24G 44% / /dev/hda1 494
 
当前目录大小

http://www.cnblogs.com/kobe8/p/3825461.html

du -ah --max-depth=1

这个是我想要的结果  a表示显示目录下所有的文件和文件夹（不含子目录），h表示以人类能看懂的方式，max-depth表示目录的深度。

 
## 解释如下：
du命令用来查看目录或文件所占用磁盘空间的大小。常用选项组合为：du -sh
### 一、du的功能：`du` reports the amount of disk space used by the specified files and for each subdirectory (of directory arguments). with no arguments,`du` reports the disk space for the current directory。
　　很明显，与df不同，它用来查看文件或目录所占用的磁盘空间的大小。
### 二、du常用的选项：
　　-h：以人类可读的方式显示
　　-a：显示目录占用的磁盘空间大小，还要显示其下目录和文件占用磁盘空间的大小
　　-s：显示目录占用的磁盘空间大小，不要显示其下子目录和文件占用的磁盘空间大小
　　-c：显示几个目录或文件占用的磁盘空间大小，还要统计它们的总和
　　--apparent-size：显示目录或文件自身的大小
　　-l ：统计硬链接占用磁盘空间的大小
　　-L：统计符号链接所指向的文件占用的磁盘空间大小
　　一、du -h：这个就不多说了。
　　二、du -a：使用此选项时，显示目录和目录下子目录和文件占用磁盘空间的大小。
 

