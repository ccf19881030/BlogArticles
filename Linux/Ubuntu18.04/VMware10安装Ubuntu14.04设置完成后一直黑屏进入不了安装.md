* [VMware10安装Ubuntu14.04设置完成后一直黑屏进入不了安装](https://www.cnblogs.com/dylanhu/p/8068227.html)
  * 解决方法一：关闭Ubuntu(注意是关闭，不是挂起，只是挂起的话，加速3D图形选项不能勾选)；
    依次选择虚拟机->设置->显示器，然后把加速3D图形选项的勾点掉。

  * 解决方法二：
    管理员模式运行CMD, netsh winsock reset然后重启电脑！
