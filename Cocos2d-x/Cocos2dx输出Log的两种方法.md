## [Cocos2dx输出Log的两种方法](https://blog.csdn.net/w174504744/article/details/39026623)
一直使用vs2010开发cocos2dx，查看cocos2dx的log也一直使用CCLog来打印到vs2010的输出控制台，同时也可以将log输出到命令行窗口。 
### log输出方法一:

使用CCLog输出到vs控制台，当然了，这也可以跨平台输出log。 

如: 

CCLog("error buffer:%s" ,response->getErrorBuffer()); 

### log输出方法二: 
在打印前，加入以下代码: 

AllocConsole();

 freopen("CONIN$", "r", stdin);

 freopen("CONOUT$", "w", stdout);

 freopen("CONOUT$", "w", stderr);

那么无论是CCLog，还是sprinf，可以立刻输出到命令行窗口了，非常方便查看。
