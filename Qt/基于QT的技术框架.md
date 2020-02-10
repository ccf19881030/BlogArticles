## [基于QT的技术框架](https://www.oschina.net/question/2324267_2304270)
有个项目，要求用QT widget进行开发。但本人较为熟悉web开发模式，比如基于vue的模式。不知道QT有没有什么相似的框架，还请各位大神介绍介绍。
1、基于QWebEngine开发：适合桌面操作系统环境，且不考虑支持XP；

2、基于QWebKit开发：版本很老了，Qt5.6后就废弃，改为QWebEngine模块了；不建议用，bug多；

3、基于QML开发：类似web开发模式，可以混合js开发，但目前不大成熟，bug多，且生态环境没有html等好；

【注：如果不用Qt，还可以考虑CEF（网易、微信、讯飞等公司都在用）、Electron（Vs  Code就是个案列）等技术框架】
