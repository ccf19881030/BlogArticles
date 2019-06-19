## [c++ 关于换行符](https://www.cnblogs.com/i80386/p/4599981.html)
windows: \r\n
linux: 　　\n
mac:　　　\r

http://blog.chinaunix.net/uid-12706763-id-10830.html
不同的OS有不同的换行符：
OS	换行符	汉字码
UNIX	LF	JIS, EUC, (ShiftJIS)
Windows	CR+LF	ShiftJIS
Macintosh	CR	ShiftJIS
下面列出了各个系统之间的变换关系：
UNIX => Windows
% perl -pe 's/\n/\r\n/' unixfile > winfile

UNIX => Macintosh
% perl -pe 's/\n/\r/' unixfile > macfile
Win => UNIX
% perl -pe 's/\r\n/\n/' winfile > unixfile
Windows => Macintosh
% perl -pe 's/\r\n/\r/' winfile > macfile
Macintosh => UNIX
% perl -pe 's/\r/\n/g' macfile > unixfile
Macintosh => Windows
% perl -pe 's/\r/\r\n/g' macfile > winfile

在文本处理中, CR, LF, CR/LF是不同操作系统上使用的换行符.
Dos和windows采用回车+换行CR/LF表示下一行, 
而UNIX/Linux采用换行符LF表示下一行，
苹果机(MAC OS系统)则采用回车符CR表示下一行.
CR用符号'\r'表示, 十进制ASCII代码是13, 十六进制代码为0x0D; 
LF使用'\n'符号表示, ASCII代码是10, 十六制为0x0A.
所以Windows平台上换行在文本文件中是使用 0d 0a 两个字节表示, 而UNIX和苹果平台上换行则是使用0a或0d一个字节表示.
一般操作系统上的运行库会自动决定文本文件的换行格式. 如一个程序在windows上运行就生成CR/LF换行格式的文本文件，而在Linux上运行就生成LF格式换行的文本文件.
在一个平台上使用另一种换行符的文件文件可能会带来意想不到的问题, 特别是在编辑程序代码时. 有时候代码在编辑器中显示正常, 但在编辑时却会因为换行符问题而出错.
很多文本/代码编辑器带有换行符转换功能, 使用这个功能可以将文本文件中的换行符在不同格式单互换.
在不同平台间使用FTP软件传送文件时, 在ascii文本模式传输模式下, 一些FTP客户端程序会自动对换行格式进行转换. 经过这种传输的文件字节数可能会发生变化. 如果你不想ftp修改原文件, 可以使用bin模式(二进制模式)传输文本.
