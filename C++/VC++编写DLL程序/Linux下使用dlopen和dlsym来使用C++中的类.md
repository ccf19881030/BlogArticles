## [Linux中使用dlopen和dlsym来使用C++中的类](http://blog.chinaunix.net/uid-12072359-id-2960897.html)
一般来说，dlopen和dlsym是来处理C库中的函数的，对于C++中存在的name mangle问题，类的问题就不易处理，看下文你会有所收获。
转载自：
http://www.linuxsir.org/bbs/printthread.php?t=266890
 
[C++ dlopen mini HOWTO 中译版](http://blog.chinaunix.net/uid-12072359-id-2960897.html)
 
C++ dlopen mini HOWTO
作者：Aaron Isotton 2006-03-16
译者：Lolita@linuxsir.org 2006-08-05


* The dlopen(3) man page. It explains the purpose and the use of the dlopen API.
* The article Dynamic Class Loading for C++ on Linux by James Norton published on the Linux Journal.
* Your favorite C++ reference about extern "C", inheritance, virtual functions, new and delete. I recommend [STR2000].
* [ISO14882]
* The Program Library HOWTO, which tells you most things you'll ever need about static, shared and dynamically loaded libraries and how to create them. Highly recommended.
* The Linux GCC HOWTO to learn more about how to create libraries with GCC.

参考书目
[ISO14482] ISO/IEC 14482-1998 — The C++ Programming Language. Available as PDF and as printed book from http://webstore.ansi.org/.
[STR2000] StroustrupBjarne The C++ Programming Language, Special Edition. ISBN 0-201-70073-5. Addison-Wesley
