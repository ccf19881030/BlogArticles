## [vscode 做php开发环境配置](https://blog.csdn.net/wyljz/article/details/82109669)
vscode 中安装插件：
php server
php debug
php intellisense
Code Runner
Composer
PHP DocBlocker

在https://xdebug.org/download.php 下载xdebug，需与Php的版本对应
将下载的xdebug的dll文件放入php路径下的ext目录中

系统环境变量path中加入php路径

php路径下的php.ini-development 改名为php.ini
php.ini 最后面添加：

[xdebug]
zend_extension=“E:/php-7.2.9-Win32-VC15-x64/ext/php_xdebug-2.7.0alpha1-7.2-vc15-x86_64.dll”
xdebug.remote_enable = 1
xdebug.remote_autostart = 1

vscode中Php代码加断点，启动调试，就可以进入断点了。

下载并安装composer，路径加入系统环境变量path中
https://getcomposer.org/Composer-Setup.exe

安装php格式化插件
cmd窗口运行命令：composer global require friendsofphp/php-cs-fixer
--------------------- 
作者：wyljz 
来源：CSDN 
原文：https://blog.csdn.net/wyljz/article/details/82109669 
版权声明：本文为博主原创文章，转载请附上博文链接！
