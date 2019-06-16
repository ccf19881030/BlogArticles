## [使用libcurl的正确姿势](https://www.cnblogs.com/tinyfish/p/4719467.html)
* libcurl支持访问http、ftp等各种服务器，下载图片AV什么的不在话下。但其存在多种接口，异步接口也很难以理解，到底什么样的使用姿势才是正确滴？我们来看看可用的体位：

* 1.easy interface：最简单的同步接口，容易理解，但同步访问实在不是性能之选。至于引入多线程，那是简单问题复杂化。注意异步访问也是以easy interface为基础，所以还是要学习一下：[《libcurl教程》](http://blog.csdn.net/jgood/article/details/4787670)。
* 2.multi interface：异步访问接口，性能杠杠滴，但是。。。真的很难理解啊。。。官方文档：[《multi interface overview》](http://curl.haxx.se/libcurl/c/libcurl-multi.html)。
curl_multi_perform() + select()：select()性能不够好，还受到file descriptors不能大于1024的限制。参考[《使用libcurl进行异步并发访问与文件上传》](http://blog.csdn.net/yuxikuo_1/article/details/41943755)。
curl_multi_socket_action()：使用epoll模型，性能最好，但更难懂。。。[参考范例](https://github.com/nikhilm/uvbook/blob/master/code/uvwget/main.c)。
curl_multi_perform() + curl_multi_wait()：这个据说是facebook做出的伟大贡献（参见[《Introducing curl_multi_wait》](http://daniel.haxx.se/blog/2012/09/03/introducing-curl_multi_wait)），保证性能的同时也相对容易使用，强力推荐的姿势。抄录[示例代码](https://gist.github.com/clemensg/4960504#file-curl_multi_test-c-L1)如下：
```cpp
/* curl_multi_test.c
     Clemens Gruber, 2013
     <clemens.gruber@pqgruber.com>
     Code description:
      Requests 4 Web pages via the CURL multi interface
      and checks if the HTTP status code is 200.
     Update: Fixed! The check for !numfds was the problem.
  */

  #include <stdio.h>
  #include <stdlib.h>
  #ifndef WIN32
  #include <unistd.h>
  #endif
  #include <curl/multi.h>

  #define MAX_WAIT_MSECS 30*1000 /* Wait max. 30 seconds */

  static const char *urls[] = {
    "http://www.microsoft.com",
    "http://www.yahoo.com",
    "http://www.wikipedia.org",
    "http://slashdot.org"
  };
  #define CNT 4

  static size_t cb(char *d, size_t n, size_t l, void *p)
  {
    /* take care of the data here, ignored in this example */
    (void)d;
    (void)p;
    return n*l;
  }

  static void init(CURLM *cm, int i)
  {
    CURL *eh = curl_easy_init();
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(eh, CURLOPT_HEADER, 0L);
    curl_easy_setopt(eh, CURLOPT_URL, urls[i]);
    curl_easy_setopt(eh, CURLOPT_PRIVATE, urls[i]);
    curl_easy_setopt(eh, CURLOPT_VERBOSE, 0L);
    curl_multi_add_handle(cm, eh);
  }

  int main(void)
  {
      CURLM *cm=NULL;
      CURL *eh=NULL;
      CURLMsg *msg=NULL;
      CURLcode return_code=0;
      int still_running=0, i=0, msgs_left=0;
      int http_status_code;
      const char *szUrl;

      curl_global_init(CURL_GLOBAL_ALL);

      cm = curl_multi_init();

      for (i = 0; i < CNT; ++i) {
          init(cm, i);
      }

      curl_multi_perform(cm, &still_running);

      do {
          int numfds=0;
          int res = curl_multi_wait(cm, NULL, 0, MAX_WAIT_MSECS, &numfds);
          if(res != CURLM_OK) {
              fprintf(stderr, "error: curl_multi_wait() returned %d\n", res);
              return EXIT_FAILURE;
          }
          /*
           if(!numfds) {
              fprintf(stderr, "error: curl_multi_wait() numfds=%d\n", numfds);
              return EXIT_FAILURE;
           }
          */
          curl_multi_perform(cm, &still_running);

      } while(still_running);

      while ((msg = curl_multi_info_read(cm, &msgs_left))) {
          if (msg->msg == CURLMSG_DONE) {
              eh = msg->easy_handle;

              return_code = msg->data.result;
              if(return_code!=CURLE_OK) {
                  fprintf(stderr, "CURL error code: %d\n", msg->data.result);
                  continue;
              }

              // Get HTTP status code
              http_status_code=0;
              szUrl = NULL;

              curl_easy_getinfo(eh, CURLINFO_RESPONSE_CODE, &http_status_code);
              curl_easy_getinfo(eh, CURLINFO_PRIVATE, &szUrl);

              if(http_status_code==200) {
                  printf("200 OK for %s\n", szUrl);
              } else {
                  fprintf(stderr, "GET of %s returned http status code %d\n", szUrl, http_status_code);
              }

              curl_multi_remove_handle(cm, eh);
              curl_easy_cleanup(eh);
          }
          else {
              fprintf(stderr, "error: after curl_multi_info_read(), CURLMsg=%d\n", msg->msg);
          }
      }

      curl_multi_cleanup(cm);

      return EXIT_SUCCESS;
  }
  ```
