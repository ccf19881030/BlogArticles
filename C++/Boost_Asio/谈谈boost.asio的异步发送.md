## [谈谈boost.asio的异步发送](https://www.cnblogs.com/qicosmos/p/3487169.html)
在上一篇博文中提到asio的异步发送稍微复杂一点，有必要单独拿出来说说。asio异步发送复杂的地方在于: 不能连续调用异步发送接口async_write，因为async_write内部是不断调用async_write_some，直到所有的数据发送完成为止。由于async_write调用之后就直接返回了，如果第一次调用async_write发送一个较大的包时，马上又再调用async_write发送一个很小的包时，有可能这时第一次的async_write还在循环调用async_write_some发送，而第二次的async_write要发送的数据很小，一下子就发出去了，这使得第一次发送的数据和第二次发送的数据交织在一起了，导致发送乱序的问题。解决这个问题的方法就是在第一次发送完成之后再发送第二次的数据。具体的做法是用一个发送缓冲区，在异步发送完成之后从缓冲区再取下一个数据包发送。下面看看异步发送的代码是如何实现的。
```cpp
list<MyMessage> m_sendQueue; //发送队列

void HandleAsyncWrite(char* data, int len)
    {
        bool write_in_progress = !m_sendQueue.empty();
        m_sendQueue.emplace_back(data, len);
        if (!write_in_progress)
        {
            AsyncWrite();
        }
    }

    void AsyncWrite()
    {
        auto msg = m_sendQueue.front();
        async_write(m_sock, buffer(msg.pData, msg.len),
            [this](const boost::system::error_code& ec, std::size_t size)
        {
            if (!ec)
            {
                m_sendQueue.pop_front();

                if (!m_sendQueue.empty())
                {
                    AsyncWrite();
                }
            }
            else
            {
                HandleError(ec);
                if (!m_sendQueue.empty())
                    m_sendQueue.clear();
            }
        });
    }
    ```
    　代码的逻辑是这样的：当用户发送数据时，不直接调用异步发送接口，而是将数据放到一个发送队列中，异步发送接口会循环从队列中取数据发送。循环发送过程的一个细节需要注意，用户发送数据时，如果发送队列为空时，说明异步发送已经将队列中所有的数据都发送完了，也意味着循环发送结束了，这时，需要在数据入队列之后再调用一下async_write重新发起异步循环发送。

　　可以看到，异步发送比异步接收等其他异步操作更复杂，需要一个发送队列来保证发送不会乱序。但是，还有一个问题需要注意就是这个发送队列是没有加限制的，如果接收端收到数据之后阻塞处理，而发送又很快的话，就会导致发送队列的内存快速增长甚至内存爆掉。解决办法有两个：

发慢一点，并且保证接收端不会长时间阻塞socket；
控制发送队列的上限。
　　第一种方法对实际应用的约束性较强，实际可操作性不高。第二种方法需要控制队列上限，不可避免的要加锁，这样就丧失了单线程异步发送的性能优势。所以建议用同步发送接口来发送数据，一来不用发送队列，自然也不会有内存暴涨的问题，二来也不会有复杂的循环发送过程，而且还可以通过线程池来提高发送效率。

总结：

不要连续发起异步发送，要等上次发送完成之后再发起下一个异步发送；
要考虑异步发送的发送队列内存可能会暴涨的问题；
相比复杂的异步发送，同步发送简单可靠，推荐优先使用同步发送接口。

## [purecpp一个很酷的modern c++开源社区](http://purecpp.org)
