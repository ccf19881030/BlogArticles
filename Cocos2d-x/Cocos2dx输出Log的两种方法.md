## [VS2010-win32下cocos2dx控制台打印的方法](https://blog.csdn.net/kaitiren/article/details/9120271)
## [Cocos2dx输出Log的两种方法](https://blog.csdn.net/w174504744/article/details/39026623)
一直使用vs2010开发cocos2dx，查看cocos2dx的log也一直使用CCLog来打印到vs2010的输出控制台，同时也可以将log输出到命令行窗口。 
### log输出方法一:

使用CCLog输出到vs控制台，当然了，这也可以跨平台输出log。 

如: 
```cpp
CCLog("error buffer:%s" ,response->getErrorBuffer()); 
```
### log输出方法二: 
在打印前，加入以下代码: 
```cpp
AllocConsole();
freopen("CONIN$", "r", stdin);
freopen("CONOUT$", "w", stdout);
freopen("CONOUT$", "w", stderr);
```
那么无论是CCLog，还是sprinf，可以立刻输出到命令行窗口了，非常方便查看。
例如，以下是在VS2013中运行Cocos2d-x 2.2.6测试代码的main.cpp
```cpp
#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#define USE_WIN32_CONSOLE
#endif

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//分配
#ifdef USE_WIN32_CONSOLE
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("T0718");
    eglView->setFrameSize(480, 320);
    return CCApplication::sharedApplication()->run();

	//释放
#ifdef USE_WIN32_CONSOLE
	FreeConsole();
#endif

}
```
