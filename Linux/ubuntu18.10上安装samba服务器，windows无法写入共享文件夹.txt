   在Window7系统下安装好VMware Workstation Pro15，并安装好了ubuntu-18.04.2-desktop-amd64.iso，安装samba，并配置smb.conf 后，windows可以登录并访问linux服务器。
但无法向服务器写入数据
sudo vim /etc/samba/smb.conf
修改配置文件为：
[share]
   comment = share folder
   browseable = yes
   path = /home/xxx
   create mask = 0777
   directory mask = 0777
   valid users = zll
   force user = nobody
   force group = nogroup
   public = yes
   available = yes
   writeable = yes
   browseable = yes

重要的是增加writeable = yes。
就可以写入了。
