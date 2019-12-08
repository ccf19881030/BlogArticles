## [https://doc.qt.io/archives/qt-4.8/qftp.html](https://doc.qt.io/archives/qt-4.8/qftp.html)
## [Qt5.0 用qftp下载地址](http://qt.gitorious.org/qt/qtftp)
## [QT5 实现 ftp 的ＱFtp](https://blog.csdn.net/ruoge2007/article/details/79032044)
qt5之后就不在使用QFtp QHttp，因为QNetworkaccessmanager已经替代了大部分功能，不知道digia在想啥，又不完全替换所有功能，
有2种方法供用户选择
 1.现在编译ftp源码 
2.使用第三方libcurl库
由于QT5不再导出QFtp，提供的QNetworkAccessManager仅支持ftp的上传put和下载get


