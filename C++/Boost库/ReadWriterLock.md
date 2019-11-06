## 读写锁的Boost简单封装
```cpp
#ifndef _READWRITERLOCK_H__
#define _READWRITERLOCK_H__
#include <boost/thread/thread.hpp>

typedef boost::shared_mutex RWMutex;
// 读锁
typedef boost::shared_lock<boost::shared_mutex> ReadLocker;
// 写锁
typedef boost::unique_lock<boost::shared_mutex> WriteLocker;
#endif
```

## 简单使用
* 读操作 在需要对加锁的共享数据读取时，调用如下操作进行读取，假如需要读取的是一个std::map<string, DataItem> dataMap;的map缓存结构
```cpp
RWMutex mutex_;
ReadLocker locker(mutex_);
// 读操作
// ...

```
* 写操作
```cpp
WriteLocker locker(mutex_);
// 写操作
// ...
DataItem item;
dataMap.insert({"001", item};
```

