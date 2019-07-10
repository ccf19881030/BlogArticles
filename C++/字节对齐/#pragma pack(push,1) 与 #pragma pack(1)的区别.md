## [#pragma pack(push,1) 与 #pragma pack(1)的区别](https://www.cnblogs.com/huhu0013/p/4607379.html)
原文链接: http://blog.csdn.net/dutysmart/article/details/7098136

这是给编译器用的参数设置，有关结构体字节对齐方式设置， #pragma pack是指定数据在内存中的对齐方式。

#pragma pack(n)             作用：C编译器将按照n个字节对齐。
#pragma pack()               作用：取消自定义字节对齐方式。


#pragma pack(push,1)     作用：是指把原来对齐方式设置压栈，并设新的对齐方式设置为一个字节对齐

#pragma pack(pop)            作用：恢复对齐状态

因此可见，加入push和pop可以使对齐恢复到原来状态，而不是编译器默认，可以说后者更优，但是很多时候两者差别不大

如：

#pragma pack(push) //保存对齐状态

#pragma pack(4)//设定为4字节对齐

  相当于 #pragma  pack (push,4)  

 

#pragma pack(1)           作用：调整结构体的边界对齐，让其以一个字节对齐；<使结构体按1字节方式对齐>

#pragma pack()

例如：

#pragma pack(1)

struct sample
{
char a;
double b;
};

#pragma pack()

注：若不用#pragma pack(1)和#pragma pack()括起来，则sample按编译器默认方式对齐（成员中size最大的那个）。即按8字节（double）对齐，则sizeof(sample)==16.成员char a占了8个字节（其中7个是空字节）；

若用#pragma pack(1)，则sample按1字节方式对齐sizeof(sample)＝＝9.（无空字节），比较节省空间啦，有些场和还可使结构体更易于控制。
