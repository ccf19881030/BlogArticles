# [[C++] 一定要 public 继承 std::enable_shared_from_this](https://fuzhe1989.github.io/2021/07/25/cpp-enable-shared-from-this-must-be-public-inherited/)
`std::enable_shared_from_this`必须要`public`继承，否则调用`shared_from_this()`不会编译失败，但运行时会抛`std::bad_weak_ptr`的异常。

我看到项目中有个类是`struct`，成员都暴露在外面，感觉不太安全，就把它改成了`class`，保证了所有对其成员的访问都通过`public`方法。看起来是个无害的操作，结果 ci test 挂了一大片，报错是`std::bad_weak_ptr`。

我一看这个类，还真是继承了`std::enable_shared_from_this`：
```cpp
class Task: std::enable_shared_from_this {
 // ...
};
```
这个报错通常是因为一个类继承自`std::enable_shared_from_this`，但某个没有被包裹在`std::shared_ptr`中的实例调用了`shared_from_this()`，然后就炸了，因为此时`std::enable_shared_from_this`没办法返回一个安全的`std::shared_ptr`。

但人肉确认过它的所有分配都是走std::shared_ptr，且为了确保这点，我还把Task的构造函数也藏起来了，对外只暴露一个static构造器：
```cpp
class Task: std::enable_shared_from_this {
public:
 template <typename... Args>
 static std::shared_ptr<Task> newTask(Args... args) {
 return std::shared_ptr(new Task(std::forward<Args>(args)...));
 }
private:
 Task(Arg0 arg0, Arg1 arg1);
};
```
再跑一遍，还是不行。

略过 debug 过程，最终我发现是新的`Task`类继承`std::enable_shared_from_this`的方式有问题：它在private继承。此时搞笑的事情发生了，我手头的 gcc7.5 的`std::enable_shared_from_this`的实现不会在这种情况下为`Task`实例构造必要的`_M_weak_this`成员，导致后续调用`shared_from_this()`时报错。

我觉得这里的设计不好，此时`std::enable_shared_from_this`已经失去作用了，但没有产生编译错误，而是延迟到运行时再报错，极大增加了 debug 的成本。按理说这里既然可以有不同的特化版本，就应该可以在编译期发现这类错误。

结论：

- 1.struct默认继承级别是public，而class则是private。
- 2.所有继承都应该显式写出继承级别。
- 3.继承std::enable_shared_from_this时请public继承。
