@[TOC](CentOS8中源码安装libcurl库)
# CentOS8中源码安装libcurl库
## 一、下载libcurl源代码
首先下载libcurl的源代码，可以从github中下载：
```
    git clone https://github.com/curl/curl.git
```
或者直接下载最新的libcurl源代码：[curl-7.82.0.tar.gz](https://curl.se/download/curl-7.82.0.tar.gz)
![libcurl源代码](https://img-blog.csdnimg.cn/a3737566af92414f9996b429dba18846.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)

## 二、编译构建libcurl库
### 1、方式一：使用configure和make构建
参考了[centos 7.6 源码编译curl 7.75.0](https://blog.csdn.net/qd1308504206/article/details/115198566)和[curl安装时出现：configure: error: select TLS backend(s) or disable TLS with --without-ssl.](https://blog.csdn.net/qq_38801506/article/details/117959761)这两篇博客，
由于libcurl源代码目录没有提供configure文件，所以要使用buildconf脚本生成对应的configure文件，步骤如下：
1)、安装automake、autoreconf、libtool工具，执行如下命令：
```
	yum instal autoconf automake libtool -y
```
2)、执行./buildconf生成configure文件，如下图所示：![执行./buildconf生成configure文件](https://img-blog.csdnimg.cn/f0c9dafea6fb42d8931a09b2434d121a.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
有了configure文件，本来以为就可以顺利的执行通常的以下3个步骤就可以了：
A、./configure --prefix=/usr
B 、make
C、make install
没想到执行`./configure --prefix=/usr`后提示报错了：
```
[root@iZuf6dcz9uks38gipvu9vhZ curl]# ./configure --prefix=/usr
configure: loading site script /usr/share/config.site
checking whether to enable maintainer-specific portions of Makefiles... no
checking whether make supports nested variables... yes
checking whether to enable debug build options... no
checking whether to enable compiler optimizer... (assumed) yes
checking whether to enable strict compiler warnings... no
checking whether to enable compiler warnings as errors... no
checking whether to enable curl debug memory tracking... no
checking whether to enable hiding of library internal symbols... yes
checking whether to enable c-ares for DNS lookups... no
checking whether to disable dependency on -lrt... (assumed no)
checking whether to enable ECH support... no
checking for path separator... :
checking for sed... /usr/bin/sed
checking for grep... /usr/bin/grep
checking for egrep... /usr/bin/grep -E
checking for ar... /usr/bin/ar
checking for a BSD-compatible install... /usr/bin/install -c
checking for gcc... gcc
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether gcc accepts -g... yes
checking for gcc option to accept ISO C89... none needed
checking whether gcc understands -c and -o together... yes
checking how to run the C preprocessor... gcc -E
checking for a sed that does not truncate output... (cached) /usr/bin/sed
checking for code coverage support... no
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /usr/bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether make supports the include directive... yes (GNU style)
checking dependency style of gcc... gcc3
checking curl version... 7.83.0-DEV
configure: error: select TLS backend(s) or disable TLS with --without-ssl.

Select from these:

  --with-amissl
  --with-bearssl
  --with-gnutls
  --with-mbedtls
  --with-nss
  --with-openssl (also works for BoringSSL and libressl)
  --with-rustls
  --with-schannel
  --with-secure-transport
  --with-wolfssl
  ```
报错为：`configure: error: select TLS backend(s) or disable TLS with --without-ssl.`
根据[curl安装时出现：configure: error: select TLS backend(s) or disable TLS with --without-ssl.](https://blog.csdn.net/qq_38801506/article/details/117959761)这篇博客的方法，末尾加上参数` --with-wolfssl`即可
`./configure --prefix=/usr/ --with-wolfssl`
所以：
首先执行：`./configure --prefix=/usr/ --with-wolfssl`，如下图所示：![./configure --prefix=/usr/ --with-wolfssl](https://img-blog.csdnimg.cn/e6e0227506cc4ac19786768320b55da8.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
![configure执行成功](https://img-blog.csdnimg.cn/7c62c28738764b2984199fe7613bf005.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
执行`make`
![执行make](https://img-blog.csdnimg.cn/90f52fcef09c4766839bf456f35a4239.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)

![make成功](https://img-blog.csdnimg.cn/23a76e365ed547238bd22b5f2aba8d98.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)

执行`make install`安装
![执行`make install`安装](https://img-blog.csdnimg.cn/6df9f6ff73af46778f24eb6b45e46477.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)

![make install完毕](https://img-blog.csdnimg.cn/cf95a4685f78435eaf7dd7dec952c7b2.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
### 2、方式二：直接使用cmake和make工具构建
首先需要下载安装cmake工具，可以去[cmake官网](https://cmake.org/)下载，目前最新版本是：3.23.0
![下载cmake工具](https://img-blog.csdnimg.cn/7ac4a3c3823a4a638c125178ab640cbc.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
在libcurl源码目录`/root/GithubProjects/curl`分别执行如下命令：
```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..  
make
make install
```

## 三、编写libcurl测试程序
可以在libcurl源代码目录的docs/examples/找到一些官方提供的示例程序，如下图所示：
![libcurl示例程序](https://img-blog.csdnimg.cn/d9a577695365419b84dcd3002133e24f.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
随便找一个示例程序例如`http-post.c`进行验证：
`http-post.c`
```c
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2019, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * simple HTTP POST using the easy interface
 * </DESC>
 */
#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "http://postit.example.com/moo.cgi");
    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}

```
`gcc http-post.c -o http-post -lcurl`
`./http-post`
执行结果如下图所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/bf86dae3837d4a4888510f71bef53dcb.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6Zuq5Z-f6L-35b2x,size_20,color_FFFFFF,t_70,g_se,x_16)
## 四、参考资料
- [libcurl - the multiprotocol file transfer library](https://curl.se/libcurl/)
- [libcurl programming tutorial](https://curl.se/libcurl/c/libcurl-tutorial.html)
- [libcurl - small example snippets](https://curl.se/libcurl/c/example.html)
- [centos 7.6 源码编译curl 7.75.0](https://blog.csdn.net/qd1308504206/article/details/115198566)
- [curl安装时出现：configure: error: select TLS backend(s) or disable TLS with --without-ssl.](https://blog.csdn.net/qq_38801506/article/details/117959761)
- [C++ 用libcurl库进行http通讯网络编程](https://www.cnblogs.com/moodlxs/archive/2012/10/15/2724318.html)

