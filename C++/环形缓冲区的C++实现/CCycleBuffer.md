## 环形缓冲区的C++实现
// 头文件 CCycleBuffer.h
```cpp
//环形缓冲区头文件

#ifndef CCycleBuffer_H
#define CCycleBuffer_H

class CCycleBuffer
{
public:
	bool isFull();
	bool isEmpty();
	void empty();		// 清空缓冲区
	int getLength();	// 获取缓冲区有效数据长度   

	CCycleBuffer(int size);
	virtual~CCycleBuffer();

	int write(char* buf, int count);	// 往缓冲区中写入数据，返回写入成功的数目
	int read(char* buf, int count);		// 从缓冲区中读取count个字符至buf中，返回实际读取的字符个数

	int getStart()
	{
		return m_nReadPos;
	}

	int getEnd()
	{
		return m_nWritePos;
	}

	// 获取环形消息缓冲区的头指向的数据
	char* msgBuf()
	{
		return m_pBuf;
	}

private:
	bool m_bEmpty, m_bFull;
	char* m_pBuf;
	int m_nBufSize;
	int m_nReadPos;
	int m_nWritePos;
	int test;
};
#endif// CCycleBuffer_H
```

// 源文件 CCycleBuffer.cpp
```cpp
//环形缓冲区源文件
//尽量用C运行时库代码，改变了原作者基于WindowsAPI的代码。
//修改了原作者的两处错误，1是read函数最后的else 少了一个leftcount
//第二个错误，是write函数中，m_nWritePos 变量，他重新定义了一个。这些错误编译不会出错。
//但是运行起来，要了亲命啊。

#include "CCycleBuffer.h"
#include <assert.h>
#include <memory.h>

// 定义 
CCycleBuffer::CCycleBuffer(int size)
{
	m_nBufSize = size;
	m_nReadPos = 0;
	m_nWritePos = 0;
	m_pBuf = new char[m_nBufSize];
	m_bEmpty = true;
	m_bFull = false;
	test = 0;
}

CCycleBuffer::~CCycleBuffer()
{
	delete[] m_pBuf;
}

/************************************************************************/
/* 向缓冲区写入数据，返回实际写入的字节数                               */
/************************************************************************/
int CCycleBuffer::write(char* buf, int count)
{
	if (count <= 0)
		return 0;
	m_bEmpty = false;
	// 缓冲区已满，不能继续写入 
	if (m_bFull)
	{
		return 0;
	}
	else if (m_nReadPos == m_nWritePos)// 缓冲区为空时 
	{
		/*                          == 内存模型 ==
		   (empty)             m_nReadPos                (empty)
		|----------------------------------|-----------------------------------------|
			   m_nWritePos        m_nBufSize
		*/
		int leftcount = m_nBufSize - m_nWritePos;
		if (leftcount > count)
		{
			memcpy(m_pBuf + m_nWritePos, buf, count);
			m_nWritePos += count;
			m_bFull = (m_nWritePos == m_nReadPos);
			return count;
		}
		else
		{
			memcpy(m_pBuf + m_nWritePos, buf, leftcount);
			m_nWritePos = (m_nReadPos > count - leftcount) ? count - leftcount : m_nWritePos;
			memcpy(m_pBuf, buf + leftcount, m_nWritePos);
			m_bFull = (m_nWritePos == m_nReadPos);
			return leftcount + m_nWritePos;
		}
	}
	else if (m_nReadPos < m_nWritePos)// 有剩余空间可写入 
	{
		/*                           == 内存模型 ==
		 (empty)                 (data)                     (empty)
		|-------------------|----------------------------|---------------------------|
		   m_nReadPos                m_nWritePos       (leftcount)
		*/
		// 剩余缓冲区大小(从写入位置到缓冲区尾) 

		int leftcount = m_nBufSize - m_nWritePos;
		int test = m_nWritePos;
		if (leftcount > count)   // 有足够的剩余空间存放 
		{
			memcpy(m_pBuf + m_nWritePos, buf, count);
			m_nWritePos += count;
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);
			return count;
		}
		else       // 剩余空间不足 
		{
			// 先填充满剩余空间，再回头找空间存放 
			memcpy(m_pBuf + test, buf, leftcount);

			m_nWritePos = (m_nReadPos >= count - leftcount) ? count - leftcount : m_nReadPos;
			memcpy(m_pBuf, buf + leftcount, m_nWritePos);
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);

			return leftcount + m_nWritePos;
		}
	}
	else
	{
		/*                          == 内存模型 ==
		 (unread)                 (read)                     (unread)
		|-------------------|----------------------------|---------------------------|
			m_nWritePos    (leftcount)    m_nReadPos
		*/
		int leftcount = m_nReadPos - m_nWritePos;
		if (leftcount > count)
		{
			// 有足够的剩余空间存放 
			memcpy(m_pBuf + m_nWritePos, buf, count);
			m_nWritePos += count;
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);

			assert(m_nWritePos <= m_nBufSize);
			return count;
		}
		else
		{
			// 剩余空间不足时要丢弃后面的数据 
			memcpy(m_pBuf + m_nWritePos, buf, leftcount);
			m_nWritePos += leftcount;
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_bFull);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);

			return leftcount;
		}
	}
}

/************************************************************************/
/* 从缓冲区读数据，返回实际读取的字节数                                 */
/************************************************************************/
int CCycleBuffer::read(char* buf, int count)
{
	if (count <= 0)
		return 0;
	m_bFull = false;
	if (m_bEmpty)       // 缓冲区空，不能继续读取数据 
	{
		return 0;
	}
	else if (m_nReadPos == m_nWritePos)   // 缓冲区满时 
	{
		/*                          == 内存模型 ==
		 (data)          m_nReadPos                (data)
		 |--------------------------------|--------------------------------------------|
		  m_nWritePos         m_nBufSize
		*/
		int leftcount = m_nBufSize - m_nReadPos;
		if (leftcount > count)
		{
			memcpy(buf, m_pBuf + m_nReadPos, count);
			m_nReadPos += count;
			m_bEmpty = (m_nReadPos == m_nWritePos);

			return count;
		}
		else
		{
			memcpy(buf, m_pBuf + m_nReadPos, leftcount);
			m_nReadPos = (m_nWritePos > count - leftcount) ? count - leftcount : m_nWritePos;
			memcpy(buf + leftcount, m_pBuf, m_nReadPos);
			m_bEmpty = (m_nReadPos == m_nWritePos);

			return leftcount + m_nReadPos;
		}
	}
	else if (m_nReadPos < m_nWritePos)   // 写指针在前(未读数据是连接的) 
	{
		/*                          == 内存模型 ==
		 (read)                 (unread)                      (read)
		|-------------------|----------------------------|---------------------------|
		   m_nReadPos                m_nWritePos                     m_nBufSize
		*/
		int leftcount = m_nWritePos - m_nReadPos;
		int c = (leftcount > count) ? count : leftcount;
		memcpy(buf, m_pBuf + m_nReadPos, c);
		m_nReadPos += c;
		m_bEmpty = (m_nReadPos == m_nWritePos);
		assert(m_nReadPos <= m_nBufSize);
		assert(m_nWritePos <= m_nBufSize);

		return c;
	}
	else          // 读指针在前(未读数据可能是不连接的) 
	{
		/*                          == 内存模型 ==
		   (unread)                (read)                      (unread)
		|-------------------|----------------------------|---------------------------|
			m_nWritePos                  m_nReadPos                  m_nBufSize

		*/
		int leftcount = m_nBufSize - m_nReadPos;
		if (leftcount > count)   // 未读缓冲区够大，直接读取数据 
		{
			memcpy(buf, m_pBuf + m_nReadPos, count);
			m_nReadPos += count;
			m_bEmpty = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);

			return count;
		}
		else       // 未读缓冲区不足，需回到缓冲区头开始读 
		{
			memcpy(buf, m_pBuf + m_nReadPos, leftcount);
			m_nReadPos = (m_nWritePos >= count - leftcount) ? count - leftcount : m_nWritePos;
			memcpy(buf + leftcount, m_pBuf, m_nReadPos);
			m_bEmpty = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);

			return leftcount + m_nReadPos;
		}
	}
}

/************************************************************************/
/* 获取缓冲区有效数据长度                                               */
/************************************************************************/
int CCycleBuffer::getLength()
{
	if (m_bEmpty)
	{
		return 0;
	}
	else if (m_bFull)
	{
		return m_nBufSize;
	}
	else if (m_nReadPos < m_nWritePos)
	{
		return m_nWritePos - m_nReadPos;
	}
	else
	{
		return m_nBufSize - m_nReadPos + m_nWritePos;
	}
}

void CCycleBuffer::empty()
{
	m_nReadPos = 0;
	m_nWritePos = 0;
	m_bEmpty = true;
	m_bFull = false;
}

bool CCycleBuffer::isEmpty()
{
	return m_bEmpty;
}

bool CCycleBuffer::isFull()
{
	return m_bFull;
}
```
## Boost库里面提供了环形缓冲区的C++实现 circular buffer 
#include <boost/circular_buffer.hpp>

## 相关参考资料
### [环形缓冲区的实现](https://blog.csdn.net/qq_39736982/article/details/82915115)
### [线程安全的环形缓冲区实现](https://www.cnblogs.com/lidabo/p/3751894.html)
### [Ring Buffer (circular Buffer)环形缓冲区简介](https://www.2cto.com/kf/201305/208947.html)
