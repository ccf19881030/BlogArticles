## [Boost ASIO: How can a server know if a client is still connected?](https://stackoverflow.com/questions/16568672/boost-asio-how-can-a-server-know-if-a-client-is-still-connected?noredirect=1)
I am using boost::asio for a server/client application. The server only accepts one connection at a time. 
I am wondering what is the best way for the server to verify if the client is still connected.

The purpose of this is that I would like to be able to know if the client has crashed, so that I can restart listening to 
new connection attempts.

4

In my application I am using following flags and my read comes out when client disconnects. Please try it if it in your application. Apply this flags just after connection.

in my case skt_TCP is of type boost::asio::ip::tcp::socket
```cpp
int32_t accept_server_socket = skt_TCP.native_handle();

int32_t timeout = 8;
int32_t cnt = 2;
int32_t intverval = 2;

// Added Keepalive flag
boost::asio::socket_base::keep_alive opt_keep_alive(true);
skt_TCP.set_option(opt_keep_alive);
setsockopt(accept_server_socket, SOL_TCP, TCP_KEEPIDLE, &timeout, sizeof(timeout));
setsockopt(accept_server_socket, SOL_TCP, TCP_KEEPCNT, &cnt, sizeof(cnt));
setsockopt(accept_server_socket, SOL_TCP, TCP_KEEPINTVL, &intverval, sizeof(intverval));
```
0

This really depends on your choice of protocol.

Simple Command Protocol
If your server protocol always waits for a message from the client, you will always have a pending async_read for every client connected. This should return with an error (EOF) when a client disconnects in any fashion.

Keep-alive is an approach as said above, but pending async_read's work just fine for this purpose.

Simple Event Protocol
A simple event protocol involves a client listening for data and the server sending it. In this protocol, the server has no idea whether the client is there, because the client merely accepts the data and continues waiting. The client never sends the server any message whatsoever.

This presents the requirement for keep-alive. async_write operations do not fail in the same way that async_read's do when a client is already disconnected.

There are other options, like having the server always have a pending async_read operation that tries to read 1 byte. This will fail when the client disconnects similar to the Simple Command Protocol discussion above, but will never succeed either because the client doesn't send data over the Simple Event Protocol.
