## [cmake编译缺失pthread_create等thread库解决方案](https://justchen.com/2017/02/27/cmake编译缺失pthread_create等thread库解决方案.html)
在使用cmake来编译项目时,明明在CMAKE_CXX_FLAGS项中设置了-lpthread项目,在运行生成makefile时确实也看到了有-lpthread,但还是报错:对‘pthread_create’未定义的引用,简直是日了狗了…
后来google到了答案,如果是cmake项目需要修改Cmakefile.txt,增加以下内容
```shell
find_package(Threads)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
```
果然,加上后就解决问题了,makefile,只是把-lpthread移到了最后,如果只是动CMAKE_CXX_FLAGS项-lpthread是紧根着g++后,也许这样不起作用….
