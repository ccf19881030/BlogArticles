# [c++11特性之override和final关键字](https://www.cnblogs.com/minggong/p/6457726.html)
C++11之前，一直没有继承控制关键字。禁用一个类的进一步衍生是可能的但也很棘手。为避免用户在派生类中重载一个虚函数，你不得不向后考虑。

C++ 11添加了两个继承控制关键字：override和final。override确保在派生类中声明的重载函数跟基类的虚函数有相同的签名。final阻止类的进一步派生和虚函数的进一步重载。

虚函数重载

一个派生类可以重载在基类中声明的成员函数，这是面向对象设计的基础。然而像重载一个函数这么简单的操作也会出错。关于重载虚函数的两个常见错误如下： 
无意中重载 
签名不匹配

首先，我们来分析一下无意中重载的综合症。你可能只是通过声明了一个与基类的某个虚成员函数具有相同的名字和签名的成员函数而无意中重载了这个虚函数。编译器和读代码的人很难发现这个bug因为他们通常以为这个新函数是为了实现对基类函数的重载：
```cpp
class A
{
 public:
    virtual void func();
};            
class B: A{};
class F{};
class D: A, F
{
 public:
  void func();//meant to declare a new function but

 //accidentally overrides A::func};
 ```
 阅读以上代码，你不能确定成员函数D::func()是否故意重载了A::func().它也可能是个偶然发生的重载，因为两个函数的参数列表和名字都碰巧一样。

签名不匹配是一个更为常见的情景。这导致意外创建一个新的虚函数（而不是重载一个已存在的虚函数），正如以下例子所示：
```cpp
class  G
{
public:
 virtual void func(int);
};

class H: G
{
public:
 virtual void func(double); 
};
```
这种情况下，程序员本打算在类H中重载G::func()的。然而，由于H::func()拥有不同的签名，结果创建了一个新的虚函数，而非对基类函数的重载：
```cpp
H *p=new H;
p->func(5); //calls G::f
p->func(5.0); // calls H::f
```
碰到这种情况，不是所有的编译器都会给个警告，有时那样做会被设置成抑制这种警告。

基于上面的两个错误

在C++11中，通过使用新关键字override可以消除这两个bugs。override明确地表示一个函数是对基类中一个虚函数的重载。更重要的是，它会检查基类虚函数和派生类中重载函数的签名不匹配问题。如果签名不匹配，编译器会发出错误信息。

我们来看看override如何消除签名不匹配bug的：
```cpp
class G
{
public:
 virtual void func(int);
};
class H: G
{
public:
 virtual void func(double) override; //compilation error
};
```
当处理到H::func()声明时，编译器会 在一个基类查找与之匹配的虚函数。

final函数和类

C++11的关键字final有两个用途。第一，它阻止了从类继承；第二，阻止一个虚函数的重载。我们先来看看final类吧。

程序员常常在没有意识到风险的情况下坚持从std::vector派生。在C++11中，无子类类型将被声明为如下所示：
```cpp
class TaskManager {/*..*/} final; 
class PrioritizedTaskManager: public TaskManager {
};  //compilation error: base class TaskManager is final
```
同样，你可以通过声明它为final来禁止一个虚函数被进一步重载。如果一个派生类试图重载一个final函数，编译器就会报错：
```cpp
class A
{
pulic:
  virtual void func() const;
};
class  B: A
{
pulic:
  void func() const override final; //OK
};
class C: B
{
pulic:
 void func()const; //error, B::func is final
};
```
C::func()是否声明为override没关系，一旦一个虚函数被声明为final，派生类不能再重载它。
