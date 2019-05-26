## [windows下堆异常调试神器--gflags](https://blog.csdn.net/xiexievv/article/details/7707377)
经常遇到一很郁闷的事情：发布给外部客户使用的程序crash了，把dump文件丢过来，对上pdb之后发现显示的调用栈莫名奇妙，或者是一个stl::vector的push_back调用，要么是在一个malloc分配内存或者new创建对象，甚至可能是一个字符串赋值；这些从代码上看怎么看都不应该导致程序crash的，这时候一般就是程序写内存越界，堆被破坏，导致显示的调用栈异常了。怎样才能确定导致程序异常的实际代码行呢？
用windows的debug tools中的global flags即gflags就可以了。gflags工作的时候，可以在用户每次分配内存的时候都在要分配的内存后边紧跟着分配一个保护区间（一般是一个虚拟页），一旦出现堆越界，就会立刻触发中断，这样就可以让调试器准确的定位代码行。

这里所说的立刻触发中断并不是必然的，取决于gflags的设置参数，如果启用了/unaligned参数，则会以不对齐的方式分配保护区间，这样即使越界一个字节都会立即触发异常；默认情况下分配保护区间是以对齐内存为单位的，因此在下面这种越界情况是检测不到的：
```cpp
int main()
{
      char *p = new char[10];
      for(int i=10; i<16; i++)
           p[i] = i;
      return 0;
}
```
具体的gflags使用可以参见使用手册，最常用的几个指令如下：

>> gflags.exe /p /enable myapp.exe /full#对进程myapp.exe完全启用page heap，注意进程名不能带路径

>> gflags.exe /p /disable myapp.exe#禁止myapp的page heap

>> gflags.exe /p /enable myapp.exe /full /unaligned#非对齐方式启用page heap

另外值得注意的是：由于gflags会给程序分配大量的保护区间，因此调试的时候会占用大量的内存，一定要保证机器设置了足够的虚拟内存空间,并且在不进行调试的时候及时禁用页堆。
