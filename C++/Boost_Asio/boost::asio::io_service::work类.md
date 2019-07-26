## [boost::asio::io_service::work类](https://www.royalchen.com/?p=2328)
work是一个很小的辅助类，只支持构造函数和析构函数。（还有一个get_io_service返回所关联的io_service）
构造一个work时，outstanding_work_+1，使得io.run在完成所有异步消息后判断outstanding_work_时不会为0，因此会继续调用GetQueuedCompletionStatus并阻塞在这个函数上。
而析构函数中将其-1，并判断其是否为0，如果是，则post退出消息给GetQueuedCompletionStatus让其退出。

因此work如果析构，则io.run会在处理完所有消息之后正常退出。work如果不析构，则io.run会一直运行不退出。如果用户直接调用io.stop，则会让io.run立刻退出。

特别注意的是，work提供了一个拷贝构造函数，因此可以直接在任意地方使用。对于一个io_service来说，有多少个work实例关 联，则outstanding_work_就+1了多少次，只有关联到同一个io_service的work全被

析构之后，io.run才会在所有消息处 理结束之后正常退出。

转自:http://blog.csdn.net/pud_zha/article/details/37561011
