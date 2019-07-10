## [#pragma pack(push,1) 与 #pragma pack(1)的区别](https://www.cnblogs.com/huhu0013/p/4607379.html)
## [#pragma pack(push,1)与#pragma pack(1)的区别](https://www.jianshu.com/p/c44dff63094d)
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
```cpp
#pragma pack(1)

struct sample
{
char a;
double b;
};

#pragma pack()
```
注：若不用#pragma pack(1)和#pragma pack()括起来，则sample按编译器默认方式对齐（成员中size最大的那个）。即按8字节（double）对齐，则sizeof(sample)==16.成员char a占了8个字节（其中7个是空字节）；

若用#pragma pack(1)，则sample按1字节方式对齐sizeof(sample)＝＝9.（无空字节），比较节省空间啦，有些场和还可使结构体更易于控制。

## 应用实例
在网络协议编程中，经常会处理不同协议的数据报文。一种方法是通过指针偏移的方法来得到各种信息，但这样做不仅编程复杂，而且一旦协议有变化，程序修改起来也比较麻烦。在了解了编译器对结构空间的分配原则之后，我们完全可以利用这一特性定义自己的协议结构，通过访问结构的成员来获取各种信息。这样做，不仅简化了编程，而且即使协议发生变化，我们也只需修改协议结构的定义即可，其它程序无需修改，省时省力。下面以TCP协议首部为例，说明如何定义协议结构。其协议结构定义如下：
```cpp
#pragma pack(1) // 按照1字节方式进行对齐
struct TCPHEADER 
{
     short SrcPort; // 16位源端口号
     short DstPort; // 16位目的端口号
     int SerialNo; // 32位序列号
     int AckNo; // 32位确认号
     unsigned char HaderLen : 4; // 4位首部长度
     unsigned char Reserved1 : 4; // 保留6位中的4位
     unsigned char Reserved2 : 2; // 保留6位中的2位
     unsigned char URG : 1;
     unsigned char ACK : 1;
     unsigned char PSH : 1;
     unsigned char RST : 1;
     unsigned char SYN : 1;
     unsigned char FIN : 1;
     short WindowSize; // 16位窗口大小
     short TcpChkSum; // 16位TCP检验和
     short UrgentPointer; // 16位紧急指针
}; 
#pragma pack()
```

