## [C++ 高级编程 queue 示例：一个网络数据包缓冲区](https://blog.csdn.net/mabing993/article/details/79508714)
参考 C++ 高级编程，实现 queue 示例：一个网络数据包缓冲区

packet_buffer.h
```cpp
#include <queue>
#include <stdexcept>
#include <iostream>
 
using namespace std;
 
template<typename T>
class PacketBuffer
{
	public:
		PacketBuffer(int maxSize = -1);
		void bufferPacket(const T& packet);
		T getNextPacket() throw(std::out_of_range);
 
	private:
		PacketBuffer(const PacketBuffer& src);
		PacketBuffer& operator=(const PacketBuffer& rhs);
 
		queue<T> mPackets;
		int mMaxSize;
};
 
template<typename T>
PacketBuffer<T>::PacketBuffer(int maxSize)
{
	mMaxSize = maxSize;
}
 
template<typename T>
void PacketBuffer<T>::bufferPacket(const T& packet)
{
	if (mMaxSize > 0 && mPackets.size() == static_cast<size_t>(mMaxSize))
	{
		return;
	}
 
	mPackets.push(packet);
	cout << __FUNCTION__ << endl;
}
 
template<typename T>
T PacketBuffer<T>::getNextPacket() throw(std::out_of_range)
{
	if (mPackets.empty())
	{
		throw std::out_of_range("buffer is empty");
	}
 
	T temp = mPackets.front();
	mPackets.pop();
	cout << __FUNCTION__ << endl;
	return temp;
}
```

test.cpp
```cpp
#include "packet_buffer.h"
#include <iostream>
 
using namespace std;
 
class IPPacket
{
 
};
 
int main()
{
	PacketBuffer<IPPacket> ipPackets(3);
 
	for (int i = 0; i < 5; ++i)
	{
		ipPackets.bufferPacket(IPPacket());
	}
 
	while (true)
	{
		try 
		{
			IPPacket packet = ipPackets.getNextPacket();
		}
		catch (std::out_of_range)
		{
			cout << "processed all packets" << endl;
			break;
		}
	}
	
	return 0;
}
```
