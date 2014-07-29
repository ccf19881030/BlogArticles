## 参考文章：
- 1、[ubuntu12.04samba服务器配置](http://www.cnblogs.com/king-77024128/articles/2666298.html)
- 2、[ubuntu下的Samba配置：使每个用户可以用自己的用户名和密码登录自己的home目录](http://blog.csdn.net/fly_qj/article/details/21744797)

## 使用Samba服务使Windows7可以访问Vmware9.0中的Ubuntu12.04的home用户目录

在Vmware9.0下安装好Ubuntu12.04之后，想要在Windows7下访问虚拟机下的Ubuntu12.04，比较好的方式当然是使用Samba服务了。我使用的系统平台是：Windows7+VMware Workstation9.0 + Ubuntu12.04，当然首先要保证Vmware虚拟机里面的Ubuntu12.04系统与Windows7主机能够互相ping通。

步骤如下：
- 1.先要安装Samba
```
sudo apt-get install samba openssh-server
```

- 2.编辑Samba配置文件
```
sudo vi /etc/samba/smb.conf
```
找到[homes]项，此项默认是注释掉的，取消其注释，然后修改其具体内容，修改成如下：
```
[homes]
   comment = Home Directories
   browseable = yes
# By default, the home directories are exported read-only. Change the
# next parameter to 'no' if you want to be able to write to them.
   read only = no
# File creation mask is set to 0700 for security reasons. If you want to
# create files with group=rw permissions, set next parameter to 0775.
   create mask = 0755 #建议将权限修改成0755，这样其它用户只是不能修改
# Directory creation mask is set to 0700 for security reasons. If you want to
# create dirs. with group=rw permissions, set next parameter to 0775.
   directory mask = 0755
# By default, \\server\username shares can be connected to by anyone
# with access to the samba server. Un-comment the following parameter
# to make sure that only "username" can connect to \\server\username
# The following parameter makes sure that only "username" can connect
#
# This might need tweaking when using external authentication schemes
   valid users = %S
```

如上修改完成后wq保存退出！


- 3. 配置完成后要重启samba服务：
```
#sudo /etc/init.d/smbd restart
```
- 4. 增加一个现有用户的对应samba帐号：

如我已经有一个用户叫reddy，现在给reddy开通samba帐号：
```
sudo smbpasswd -a reddy
```
根据提示输入两次密码即可。

- 5.现在可以测试了，在Window7下选择【我的电脑】->【工具】-> 【映射网络驱动器】，按照\\server\\share的格式输入相应的Ubuntu12.04下的IP地址和home用户如reddy：
```
\\10.0.0.2\reddy
```
- 6.此时windows7应该会弹出窗口要求输入用户名和密码了，输入吧。Enjoy！




