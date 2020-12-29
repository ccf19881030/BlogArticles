## [如何修改github上仓库的项目的语言类型](https://www.cnblogs.com/baichendongyang/p/13235474.html)
### 问题：

在把项目上传到github仓库上时语言会显示错误语言
比如我刚写的python程序显示的语言是html

### 原理：
github 是采用 Linguist来自动识别你的代码判断归为哪一类

### 解决办法：

我们在仓库的根目录下添加.gitattributes文件:并写入
```
*.js linguist-language=java
*.css linguist-language=java
*.html linguist-language=java
```
意思是将.js、css、html当作java语言来统计
