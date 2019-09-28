## [effective c++ 之std::thread 绑定类函数](https://www.cnblogs.com/caoshiwei/p/6379687.html)
effective c++ 之std::thread 绑定类函数

问题：想用std::thread新开线程去执行一个类中的函数，编译报错。

代码示例（手写仅供参考）
```cpp
class A {
public:
    inline void start() {
        std::thread run_thread(&A::real_run);
        run_thread.join();    
    }
    inline void real_run() {
        std::cout << "real_run" << std::endl;
    }
}
```
以上代码会报错

解决方案：

1. 把想绑定的类函数设为static

    但是会引入新的问题，static方法不能使用类的非静态成员变量

    1.1 针对这一问题，解决方法如下: 给该静态成员函数传递this指针，通过this指针调用费静泰成员变量 
```cpp
class A {
public:
    inline void start() {
        std::thread run_thread(&A::real_run, this);
        run_thread.join();    
    }
    inline void real_run(A *ptr) {
        std::cout << "real_run" << ptr->data << std::endl;
    }
   private:
        int data;
}
```
2. 更为优雅的方案（个人认为比较好的方法）

  使用std::bind绑定方法和this指针 传递给thread
```cpp
class A {
public:
    inline void start() {
        std::thread run_thread(std::bind(&A::real_run, this));
        run_thread.join();    
    }
    inline void real_run() {
        std::cout << "real_run" << std::endl;
    }
}
```
