## [rapidjson中文教程](http://rapidjson.org/zh-cn/md_doc_tutorial_8zh-cn.html)
## [rapidjson-tutorial](https://github.com/Tencent/rapidjson/blob/master/example/tutorial/tutorial.cpp)
## [rapidjson-流](http://rapidjson.org/zh-cn/md_doc_stream_8zh-cn.html)
在 RapidJSON 中，rapidjson::Stream 是用於读写 JSON 的概念（概念是指 C++ 的 concept）。在这里我们先介绍如何使用 RapidJSON 提供的各种流。然后再看看如何自行定义流。
文件流
当要从文件解析一个 JSON，你可以把整个 JSON 读入内存并使用上述的 StringStream。

然而，若 JSON 很大，或是内存有限，你可以改用 FileReadStream。它只会从文件读取一部分至缓冲区，然后让那部分被解析。若缓冲区的字符都被读完，它会再从文件读取下一部分。

FileReadStream（输入）
FileReadStream 通过 FILE 指针读取文件。使用者需要提供一个缓冲区。
```cpp
#include "rapidjson/filereadstream.h"
#include <cstdio>
using namespace rapidjson;
FILE* fp = fopen("big.json", "rb"); // 非 Windows 平台使用 "r"
char readBuffer[65536];
FileReadStream is(fp, readBuffer, sizeof(readBuffer));
Document d;
d.ParseStream(is);
fclose(fp);
```
与 StringStreams 不一样，FileReadStream 是一个字节流。它不处理编码。若文件并非 UTF-8 编码，可以把字节流用 EncodedInputStream 包装。我们很快会讨论这个问题。

除了读取文件，使用者也可以使用 FileReadStream 来读取 stdin。
## [rapidjson::FileReadStream类 参考](http://rapidjson.org/zh-cn/classrapidjson_1_1_file_read_stream.html)
## [在线JSON校验格式化工具(Be JSON)](http://www.bejson.com)
## [C++文件读写详解](https://www.cnblogs.com/hdk1993/p/5853233.html)
## [有一个很大的 json 文件，要如何才能将它读到内存中呢， 4 个多 G](https://tw.v2ex.com/t/460511)
## [RAPIDJSON_ASSERT(IsObject()) fails](https://discuss.cocos2d-x.org/t/rapidjson-assert-isobject-fails/20578)
