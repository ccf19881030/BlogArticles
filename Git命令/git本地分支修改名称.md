## 一、git 修改本地分支名称
给一个git分支改名的方法很简单

如果对于分支不是当前分支，可以使用下面的命令：
```shell
git branch -m "原分支名" "新分支名"
```
如果是当前，那么可以使用加上新名字
```
git branch -m "新分支名称"
```

## 二、git | 修改分支名字（包括本地分支和远程分支）
假设分支名称为oldName
想要修改为 newName
### 1. 本地分支重命名(还没有推送到远程)
```
git branch -m oldName newName
```
### 2. 远程分支重命名 (已经推送远程-假设本地分支和远程对应分支名称相同)
-a. 重命名远程分支对应的本地分支
```
git branch -m oldName newName
```
-b. 删除远程分支
```
git push --delete origin oldName
```
-c. 上传新命名的本地分支
```
git push origin newName
```
-d.把修改后的本地分支与远程分支关联
```
git branch --set-upstream-to origin/newName
```
