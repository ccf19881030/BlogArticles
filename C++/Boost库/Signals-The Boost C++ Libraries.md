@[TOC](Signals-The Boost C++ Libraries)

本文翻译自[Signals](https://theboostcpplibraries.com/boost.signals2-signals)

# Signals
`Boost.Signals2`提供了`boost::signals2::signal`类，可用于创建信号。 此类在`boost/signals2/signal.hpp`中定义。 或者，您可以使用头文件`boost/signals2.hpp`，它是一个主头文件，定义了`Boost.Signals2`中可用的所有类和函数。

`Boost.Signals2`定义`boost::signals2::signal`和其他类，以及命名空间`boost::signals2`中的所有函数。

## 示例67.1 "Hello,World" 使用boost::signals2::signal
```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

int main()
{
  signal<void()> s;
  s.connect([]{ std::cout << "Hello, world!\n"; });
  s();
}
```

`boost::signals2::signal`是一个类模板，它期望将用作事件处理程序的函数的签名作为模板参数。 在例67.1中，只有具有`void()`签名的函数才能与信号s关联。

Lambda函数通过`connect()`与信号s关联。 因为lambda函数符合所需的签名`void()`，所以成功建立了关联。 每当信号s触发时，都会调用lambda函数。

像常规函数一样通过调用来触发信号。 该函数的签名与作为模板参数传递的签名相匹配。 方括号为空，因为`void()`不需要任何参数。 调用s会导致触发器，该触发器又执行先前与`connect()`关联的lambda函数。

例67.1也可以用`std::function`实现，如例67.2所示。

## 示例67.2  "Hello,World!" 使用std::function
```cpp
#include <functional>
#include <iostream>

int main()
{
  std::function<void()> f;
  f = []{ std::cout << "Hello, world!\n"; };
  f();
}
```

在`示例67.2`中，当调用f时，也会执行lambda函数。 虽然`std::function`仅可用于`示例67.2`之类的场景，但`Boost.Signals2`提供了更多种类。 例如，它可以将多个功能与特定信号关联（请参见`示例67.3`）。

## 示例67.3 使用`boost::signals2::signal`的多个事件处理程序
```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

int main()
{
  signal<void()> s;
  s.connect([]{ std::cout << "Hello"; });
  s.connect([]{ std::cout << ", world!\n"; });
  s();
}
```

`boost::signals2::signal`允许您通过重复调用`connect()`将多个功能分配给特定信号。 无论何时触发信号，函数都会按照它们与`connect()`关联的顺序执行。

还可以在`connect()`的重载版本的帮助下显式定义该顺序，该版本期望将`int`类型的值作为附加参数（`示例67.4`）。

## 示例67.4 具有明确顺序的事件处理程序
```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

int main()
{
  signal<void()> s;
  s.connect(1, []{ std::cout << ", world!\n"; });
  s.connect(0, []{ std::cout << "Hello"; });
  s();
}
```

与前面的示例一样，`示例67.4`显示`Hello，world!`。

要从信号中释放关联的函数，请调用`disconnect()`。

## 示例67.5 断开事件处理程序与`boost::signals2::signal`的连接
```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

void hello() { std::cout << "Hello"; }
void world() { std::cout << ", world!\n"; }

int main()
{
  signal<void()> s;
  s.connect(hello);
  s.connect(world);
  s.disconnect(world);
  s();
}
```

`示例67.5`仅输出Hello，因为在触发信号之前已释放了与`world()`的关联。

除了`connect()`和`disconnect()`外，`boost:: signals2::signal`还提供了一些其他成员函数（请参见`示例67.6`）。

## 示例67.6 `boost::signals2::signal`的其他成员函数
```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

int main()
{
  signal<void()> s;
  s.connect([]{ std::cout << "Hello"; });
  s.connect([]{ std::cout << ", world!"; });
  std::cout << s.num_slots() << '\n';
  if (!s.empty())
    s();
  s.disconnect_all_slots();
}
```

`num_slots()`返回关联函数的数量。 如果没有函数关联，则`num_slots()`返回0。`empty()`告诉您是否连接了事件处理程序。 `disconnect_all_slots()`的功能恰如其名：释放所有现有的关联。

## 示例67.7 处理事件处理程序的返回值
```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

int main()
{
  signal<int()> s;
  s.connect([]{ return 1; });
  s.connect([]{ return 2; });
  std::cout << *s() << '\n';
}
```

在`示例67.7`中，两个λ函数与信号s相关联。第一个lambda函数返回1，第二个返回2。

`例67.7`将`2`写入标准输出。 s正确接受了两个返回值，但忽略了最后一个返回值。默认情况下，仅返回所有关联函数的最后一个返回值。

请注意，`s()`不会直接返回最后一个调用函数的结果。返回类型为`boost::optional`的对象，取消引用后将返回数字2。触发与任何功能均不相关的信号不会产生任何返回值。因此，在这种情况下，`boost::optional`允许`Boost.Signals2`返回一个空对象。[第21章](https://theboostcpplibraries.com/boost.optional)介绍了`boost::optional`。

可以自定义信号，以便相应地处理各个返回值。为此，必须将组合器传递给`boost::signals2::signal`作为第二个模板参数。

## 示例67.8 用用户定义的组合器找到最小的返回值
```cpp
#include <boost/signals2.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace boost::signals2;

template <typename T>
struct min_element
{
  typedef T result_type;

  template <typename InputIterator>
  T operator()(InputIterator first, InputIterator last) const
  {
    std::vector<T> v(first, last);
    return *std::min_element(v.begin(), v.end());
  }
};

int main()
{
  signal<int(), min_element<int>> s;
  s.connect([]{ return 1; });
  s.connect([]{ return 2; });
  std::cout << s() << '\n';
}
```

组合器是带有重载`operator()`的类。该操作符会被两个迭代器自动调用，这两个迭代器用于访问与特定信号关联的功能。当取消迭代器的引用时，将调用函数，并且它们的返回值在组合器中变得可用。然后可以使用标准库中的通用算法（例如`std::min_element()`）来计算并返回最小值（请参见`示例67.8`）。

`boost::signals2::signal`使用`boost::signals2::optional_last_value`作为默认组合器。该组合器返回类型为`boost::optional`的对象。用户可以使用任何类型的返回值定义组合器。例如，`示例67.8`中的组合器`min_element`将作为模板参数传递的类型返回给`min_element`。

无法将诸如`std::min_element()`之类的算法作为模板参数直接传递给`boost::signals2::signal`。 `boost::signals2::signal`期望组合器定义一个称为`result_type`的类型，该类型表示`operato()`返回的值的类型。由于标准算法未定义此类型，因此编译器将报告错误。

请注意，不可能首先将迭代器直接传递到`std::min_element()`，因为此算法需要正向迭代器，而组合器则与输入迭代器一起使用。这就是为什么在使用`std::min_element()`确定最小值之前，使用向量存储所有返回值的原因。

`例67.9`修改了组合器，以将所有返回值存储在容器中，而不是对其求值。它将所有返回值存储在一个向量中，然后由`s()`返回。

`示例67.9`使用用户定义的合并器接收所有返回值

```cpp
#include <boost/signals2.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace boost::signals2;

template <typename T>
struct return_all
{
  typedef T result_type;

  template <typename InputIterator>
  T operator()(InputIterator first, InputIterator last) const
  {
    return T(first, last);
  }
};

int main()
{
  signal<int(), return_all<std::vector<int>>> s;
  s.connect([]{ return 1; });
  s.connect([]{ return 2; });
  std::vector<int> v = s();
  std::cout << *std::min_element(v.begin(), v.end()) << '\n';
}
```

## 练习
创建带有类`button`的一个程序。 该类应表示图形用户界面中的按钮。 添加成员函数·add_handler()`和`remove_handler()`都希望传递一个函数。 如果调用了另一个称为`click()`的成员函数，则应依次调用已注册的处理程序。 实例化按钮并通过注册将消息写入标准输出的处理程序来测试类。 调用`click()`以模拟鼠标在按钮上的单击。

[Prev](https://theboostcpplibraries.com/boost.signals2)     [Next](https://theboostcpplibraries.com/boost.signals2-connections)
