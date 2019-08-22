
## [关于shutdown 和closesocket的彻底理解！](https://blog.csdn.net/wojiuguowei/article/details/82969434)
## [closesocket, shutdown, tcp::socket.close()](https://blog.csdn.net/minglingji/article/details/7485280)
### shutdown 和closesocket
*   来，咱们彻底的来讨论一下这个shutdown 和closesocket 从函数调用上来分析（msdn)：一旦完成了套接字的连接，应当将套接字关闭，并且释放其套接字句柄所占用的所有资源。真正释放一个已经打开的套接字句柄的资源直接调用closesocket即可，但要明白closesocket的调用可能会带来负面影响，具体的影响和如何调用有关，最明显的影响是数据丢失，因此一般都要在closesocket之前调用shutdown来关闭套接字。
*   shutdown:为了保证通信双方都能够收到应用程序发出的所有数据，一个合格的应用程序的做法是通知接受双发都不在发送数据！这就是所谓的“正常关闭”套接字的方法，而这个方法就是由shutdown函数,传递给它的参数有SD_RECEIVE,SD_SEND,SD_BOTH三种，如果是SD_RECEIVE就表示不允许再对此套接字调用接受函数。这对于协议层没有影响，另外对于tcp套接字来说，无论数据是在等候接受还是即将抵达，都要重置连接（注意对于udp协议来说，仍然接受并排列传入的数据，因此udp套接字而言shutdown毫无意义）。如果选择SE_SEND,则表示不允许再调用发送函数。对于tcp套接字来说，这意味着会在所有数据发送出并得到接受端确认后产生一个FIN包。如果指定SD_BOTH，答案不言而喻。
*   closesocket:对此函数的调用会释放套接字的描述，这个道理众所周知（凡是经常翻阅msdn的程序员），因此，调用此函数后，再是用此套接字就会发生调用失败，通常返回的错误是WSAENOTSOCK。此时与被closesocket的套接字描述符相关联的资源都会被释放，包括丢弃传输队列中的数据！！！！对于当前进程中的线程来讲，所有被关起的操作，或者是被挂起的重叠操作以及与其关联的任何事件，完成例程或完成端口的执行都将调用失败！另外SO_LINGER标志还影响着closesocket的行为，但对于传统的socket程序，这里不加解释
因此可以可以看出shutdown对切断连接有着合理的完整性。
*    下面从tcp协议上来分析shutdown和closesocket的行为（behavior)：closesocket或shutdown(使用SD_SEND当作参数时）,会向通信对方发出一个fin包，而此时套接字的状态会由ESTABLISHED变成FIN_WAIT_1，然后对方发送一个ACK包作为回应，套接字又变成FIN_WAIT_2，如果对方也关闭了连接则对方会发出FIN，我方会回应一个ACK并将套接字置为TIME_WAIT。因此可以看出closesocket,shutdown所进行的TCP行为是一样的，所不同的是函数部分，shutdown会确保windows建立的数据传输队列中的数据不被丢失，而closesocket会冒然的抛弃所有的数据，因此如果你愿意closesocket完全可以取代shutdown,然而在数据交互十分复杂的网络协议程序中，最好还是shutdown稳妥一些！

--------------------- 本文来自 hugohut 的CSDN 博客 ，全文地址请点击：https://blog.csdn.net/Hugohut/article/details/8987161?utm_source=copy
