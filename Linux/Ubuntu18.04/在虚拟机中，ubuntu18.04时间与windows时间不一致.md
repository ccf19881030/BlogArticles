# [在虚拟机中，ubuntu18.04时间与windows时间不一致](https://blog.csdn.net/qq_35553662/article/details/89430639)

## 1、直接在ubuntu里进入终端。
命令：
```shell
sudo tzselect
```
进入选择时区选择。
然后选择亚洲Asia，继续选择中国China，最后选择北京Beijing。

## 2\创建时区
```shell
sudo ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
```
搞定
