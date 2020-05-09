## [使用boost::shared_mutex实现读写锁](https://blog.csdn.net/AC_hell/article/details/72629246)
伟大的Boost库给我们提供了 shared_mutex  类，结合 unique_lock 与 shared_lock 的使用，可以实现读写锁。

通常读写锁需要完成以下功能：

1.当 data 被线程A读取时，其他线程仍可以进行读取却不能写入

2.当 data 被线程A写入时，其他线程既不能读取也不能写入


对应于功能1,2我们可以这样来描述：

1.当线程A获得共享锁时，其他线程仍可以获得共享锁但不能获得独占锁

2.当线程A获得独占锁时，其他线程既不能获得共享锁也不能获得独占锁
```cpp
typedef boost::shared_lock<boost::shared_mutex> read_lock;
typedef boost::unique_lock<boost::shared_mutex> write_lock;
 
boost::shared_mutex read_write_mutex;
int32_t data = 1;
 
//线程A,读data
{
	read_lock rlock(read_write_mutex);
	std::cout << data << std:; endl;
}
 
//线程B,读data
{
	read_lock rlock(read_write_mutex);
	std::cout << data << std:; endl;
}
 
//线程C,写data
{
	write_lock rlock(read_write_mutex);
	data = 2;
}
```
通过 shared_lock 为 shared_mutex 上锁之后，线程将获得其共享锁，此时其他线程仍可以获得共享锁来读取 data，
但是此时 unique_lock 将无法为 shared_mutex 上独占锁，功能1实现了。通过 unique_lock 为 shared_lock 上锁之后，线程将获得独占锁，此时无法再被上锁，功能2也实现了。
