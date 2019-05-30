## [Visual Studio 2015 自动生成 *.VC.db 文件的问题](https://blog.csdn.net/u012611878/article/details/53574480)
用vs2015创建Visual C++项目，编写生成后，每次都会生成一个project_name.VC.db文件，而且会随着你工程修改运行变的越来越大。

project_name.VC.db是sqlite后端用于intellisense的新数据库，相当于之前的*.sdf SQL Server Compact数据库。它与VS2015提供的智能感知、代码恢复、团队本地仓库功能有关，VS重新加载解决方案时速度超快。如果不需要，可以禁止，就不会产生该文件了。

这发生在安装VS2015 Update 2后。projectname.vc.db文件是新的IntelliSense数据库，它替换旧的projname.sdf数据库。你还可能会看到一个隐藏的projname.vc.vc.opendb文件，一个锁文件，用于指示dbase正在使用。不过你迟早得手动删除这个文件。

projectname.vc.db文件在之前实验阶段就已经可以使用，现在是正式应用。它承诺大约是IntelliSense的x2加速。 这里最大的变化似乎是转向另一个dbase引擎，现在使用SQLite而不是SQL Compact。

不要马上删除该文件，否则下一次打开项目IS将需要一段时间。当你完成了项目，继续并删除该文件，它将不再使用。

但是如果你不想生成该文件或不需要生成该文件的话可以通过以下方式取消：

设置方法：工具–》选项–》文本编辑器–》C/C++–》高级，把回退位置和警告设置为true或者禁用数据库设为true，这样就不会产生那个文件了。
