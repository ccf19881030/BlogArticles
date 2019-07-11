## [Linux中使用dlopen和dlsym来使用C++中的类](http://blog.chinaunix.net/uid-20648944-id-4371941.html)
一般来说，dlopen和dlsym是来处理C库中的函数的，对于C++中存在的name mangle问题，类的问题就不易处理，看下文你会有所收获。
转载自：
http://www.linuxsir.org/bbs/printthread.php?t=266890
 
C++ dlopen mini HOWTO 中译版 [原创]
 
C++ dlopen mini HOWTO
作者：Aaron Isotton 2006-03-16
译者：Lolita@linuxsir.org 2006-08-05
------------------------------------------------
摘要
　　如何使用dlopen API动态地加载C++函数和类
------------------------------------------------
目录
　　介绍
　　　　版权和许可证
　　　　不承诺
　　　　贡献者
　　　　反馈
　　　　术语
　　问题所在
　　　　Name Mangling
　　　　类
　　解决方案
　　　　extern "C"
　　　　加载函数
　　　　加载类
　　源代码　
　　FAQ
　　其他
　　参考书
------------------------------------------------
介绍
　　如何使用dlopen API动态地加载C++函数和类，是Unix C++程序员经常碰到的问题。事实上，情况偶尔有些复杂，需要一些解释。这正是写这篇mini HOWTO的缘由。
　　理解这篇文档的前提是对C/C++语言中dlopen API有基本的了解。这篇HOWTO的维护链接是 http://www.isotton.com/howtos/C++-dlopen-mini-HOWTO/ 

　　版权和许可证
　　这篇文档《C++ dlopen mini HOWTO》版权为Aaron Isotton所有（copyrighted (c) 2002-2006），任何人在遵守自由软件基金会制定的GPLv2许可证条款前提下可以自由拷贝、分发和修改这份文档。

　　不承诺
　　本文不对文中的任何内容作可靠性承诺。您必须为您自己使用文中任何概念、示例和信息承担风险，因为其中可能存在错误和不准确的地方，或许会损坏您的系统──尽管几乎不可能发生此类事故，但您还是小心行事──作者不会为此负任何责任。

　　贡献者
　　在这篇文档中，我欣然致谢（按字母顺序）：
　　◆ Joy Y Goodreau 她的编辑工作.
　　◆ D. Stimitis 指出一些formatting和name mangling的问题, 还指出extern “C”的一些微妙之处。

　　反馈
　　欢迎对本文档的反馈信息！请把您的补充、评论和批评发送到这个邮件地址：。

　　术语
　　dlopen API
　　　　关于dlclose、dlerror、dlopen和dlsym函数的描述可以在 dlopen(3) man手册页查到。
　　　　请注意，我们使用“dlopen”时，指的是dlopen函数，而使用“dlopen API”则是指整个API集合。
------------------------------------------------
问题所在
　　有时你想在运行时加载一个库（并使用其中的函数），这在你为你的程序写一些插件或模块架构的时候经常发生。
　　在C语言中，加载一个库轻而易举（调用dlopen、dlsym和dlclose就够了），但对C++来说，情况稍微复杂。动态加载一个C++库的困难一部分是因为C++的name mangling（译者注：也有人把它翻译为“名字毁坏”，我觉得还是不翻译好），另一部分是因为dlopen API是用C语言实现的，因而没有提供一个合适的方式来装载类。
　　在解释如何装载C++库之前，最好再详细了解一下name mangling。我推荐您了解一下它，即使您对它不感兴趣。因为这有助于您理解问题是如何产生的，如何才能解决它们。

　　Name Mangling
　　在每个C++程序（或库、目标文件）中，所有非静态（non-static）函数在二进制文件中都是以“符号（symbol）”形式出现的。这些符号都是唯一的字符串，从而把各个函数在程序、库、目标文件中区分开来。
　　在C中，符号名正是函数名：strcpy函数的符号名就是“strcpy”，等等。这可能是因为两个非静态函数的名字一定各不相同的缘故。
　　而C++允许重载（不同的函数有相同的名字但不同的参数），并且有很多C所没有的特性──比如类、成员函数、异常说明──几乎不可能直接用函数名作符号名。为了解决这个问题，C++采用了所谓的name mangling。它把函数名和一些信息（如参数数量和大小）杂糅在一起，改造成奇形怪状，只有编译器才懂的符号名。例如，被mangle后的foo可能看起来像foo@4%6^，或者，符号名里头甚至不包括“foo”。
　　其中一个问题是，C++标准（目前是[ISO14882]）并没有定义名字必须如何被mangle，所以每个编译器都按自己的方式来进行name mangling。有些编译器甚至在不同版本间更换mangling算法（尤其是g++ 2.x和3.x）。即使您搞清楚了您的编译器到底怎么进行mangling的，从而可以用dlsym调用函数了，但可能仅仅限于您手头的这个编译器而已，而无法在下一版编译器下工作。

　　类
　　使用dlopen API的另一个问题是，它只支持加载函数。但在C++中，您可能要用到库中的一个类，而这需要创建该类的一个实例，这不容易做到。

解决方案

　　extern "C"
　　C++有个特定的关键字用来声明采用C binding的函数：extern "C" 。 用 extern "C"声明的函数将使用函数名作符号名，就像C函数一样。因此，只有非成员函数才能被声明为extern "C"，并且不能被重载。尽管限制多多，extern "C"函数还是非常有用，因为它们可以象C函数一样被dlopen动态加载。冠以extern "C"限定符后，并不意味着函数中无法使用C++代码了，相反，它仍然是一个完全的C++函数，可以使用任何C++特性和各种类型的参数。

　　加载函数
　　在C++中，函数用dlsym加载，就像C中一样。不过，该函数要用extern "C"限定符声明以防止其符号名被mangle。
　　
　　示例1.加载函数
代码:
//----------
//main.cpp:
//----------
#include 
#include 

int main() {
    using std::cout;
    using std::cerr;

    cout << "C++ dlopen demo\n\n";

    // open the library
    cout << "Opening hello.so...\n";
    void* handle = dlopen("./hello.so", RTLD_LAZY);
    
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    
    // load the symbol
    cout << "Loading symbol hello...\n";
    typedef void (*hello_t)();

    // reset errors
    dlerror();
    hello_t hello = (hello_t) dlsym(handle, "hello");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'hello': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return 1;
    }
    
    // use it to do the calculation
    cout << "Calling hello...\n";
    hello();
    
    // close the library
    cout << "Closing library...\n";
    dlclose(handle);
}

//----------
// hello.cpp:
//----------
#include 

extern "C" void hello() {
    std::cout << "hello" << '\n';
}
　　在hello.cpp中函数hello被定义为extern "C"。它在main.cpp中被dlsym调用。函数必须以extern "C"限定，否则我们无从知晓其符号名。
　　警告：
　　extern "C"的声明形式有两种：上面示例中使用的那种内联（inline）形式extern "C" ， 还有才用花括号的extern "C" { ... }这种。 第一种内联形式声明包含两层意义：外部链接(extern linkage)和C语言链接(language linkage)，而第二种仅影响语言链接。
　　下面两种声明形式等价：
代码:
extern "C" int foo;
extern "C" void bar();
和
代码:
extern "C" {
    extern int foo;
    extern void bar();
}
　　对于函数来说，extern和non-extern的函数声明没有区别，但对于变量就有不同了。如果您声明变量，请牢记：
代码:
extern "C" int foo;
和
代码:
extern "C" {
    int foo;
}
　　是不同的物事(译者注：简言之，前者是个声明; 而后者不仅是声明，也可以是定义)。
　　进一步的解释请参考[ISO14882],7.5, 特别注意第7段; 或者参考[STR2000]，9.2.4。在用extern的变量寻幽访胜之前，请细读“其他”一节中罗列的文档。

　　加载类
　　加载类有点困难，因为我们需要类的一个实例，而不仅仅是一个函数指针。我们无法通过new来创建类的实例，因为类不是在可执行文件中定义的，况且（有时候）我们连它的名字都不知道。
　　解决方案是：利用多态性！ 我们在可执行文件中定义一个带虚成员函数的接口基类，而在模块中定义派生实现类。通常来说，接口类是抽象的（如果一个类含有虚函数，那它就是抽象的）。
　　因为动态加载类往往用于实现插件，这意味着必须提供一个清晰定义的接口──我们将定义一个接口类和派生实现类。
　　接下来，在模块中，我们会定义两个附加的helper函数，就是众所周知的“类工厂函数（class factory functions）（译者注：或称对象工厂函数）”。其中一个函数创建一个类实例，并返回其指针; 另一个函数则用以销毁该指针。这两个函数都以extern "C"来限定修饰。
　　为了使用模块中的类，我们用dlsym像示例1中加载hello函数那样加载这两个函数，然后我们就可以随心所欲地创建和销毁实例了。

　　示例2.加载类
　　我们用一个一般性的多边形类作为接口，而继承它的三角形类（译者注：正三角形类）作为实现。
代码:
//----------
//main.cpp:
//----------
#include "polygon.hpp"
#include 
#include 

int main() {
    using std::cout;
    using std::cerr;

    // load the triangle library
    void* triangle = dlopen("./triangle.so", RTLD_LAZY);
    if (!triangle) {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // reset errors
    dlerror();
    
    // load the symbols
    create_t* create_triangle = (create_t*) dlsym(triangle, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return 1;
    }
    
    destroy_t* destroy_triangle = (destroy_t*) dlsym(triangle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        return 1;
    }

    // create an instance of the class
    polygon* poly = create_triangle();

    // use the class
    poly->set_side_length(7);
        cout << "The area is: " << poly->area() << '\n';

    // destroy the class
    destroy_triangle(poly);

    // unload the triangle library
    dlclose(triangle);
}


//----------
//polygon.hpp:
//----------
#ifndef POLYGON_HPP
#define POLYGON_HPP

class polygon {
protected:
    double side_length_;

public:
    polygon()
        : side_length_(0) {}

    virtual ~polygon() {}

    void set_side_length(double side_length) {
        side_length_ = side_length;
    }

    virtual double area() const = 0;
};

// the types of the class factories
typedef polygon* create_t();
typedef void destroy_t(polygon*);

#endif

//----------
//triangle.cpp:
//----------
#include "polygon.hpp"
#include 

class triangle : public polygon {
public:
    virtual double area() const {
        return side_length_ * side_length_ * sqrt(3) / 2;
    }
};


// the class factories
extern "C" polygon* create() {
    return new triangle;
}

extern "C" void destroy(polygon* p) {
    delete p;
}
　　加载类时有一些值得注意的地方：
　　◆ 你必须（译者注：在模块或者说共享库中）同时提供一个创造函数和一个销毁函数，且不能在执行文件内部使用delete来销毁实例，只能把实例指针传递给模块的销毁函数处理。这是因为C++里头，new操作符可以被重载;这容易导致new-delete的不匹配调用，造成莫名其妙的内存泄漏和段错误。这在用不同的标准库链接模块和可执行文件时也一样。
　　◆ 接口类的析构函数在任何情况下都必须是虚函数（virtual）。因为即使出错的可能极小，近乎杞人忧天了，但仍旧不值得去冒险，反正额外的开销微不足道。如果基类不需要析构函数，定义一个空的（但必须虚的）析构函数吧，否则你迟早要遇到问题，我向您保证。你可以在comp.lang.c++ FAQ( http://www.parashift.com/c++-faq-lite/ )的第20节了解到更多关于该问题的信息。

源代码
　　你可以下载所有包含在本文档中的代码包： http://www.isotton.com/howtos/C++-dl...xamples.tar.gz

FAQ
(译者注：下文翻译暂时省略)
1.I'm using Windows and I can't find the dlfcn.h header file! What's the problem?

The problem is that Windows doesn't have the dlopen API, and thus there is no dlfcn.h header. There is a similar API around the LoadLibrary function, and most of what is written here applies to it, too. Please refer to the Microsoft Developer Network Website for more information.

2.Is there some kind of dlopen-compatible wrapper for the Windows LoadLibrary API?

I don't know of any, and I don't think there'll ever be one supporting all of dlopen's options.

There are alternatives though: libtltdl (a part of libtool), which wraps a variety of different dynamic loading APIs, among others dlopen and LoadLibrary. Another one is the Dynamic Module Loading functionality of GLib. You can use one of these to ensure better possible cross-platform compatibility. I've never used any of them, so I can't tell you how stable they are and whether they really work.

You should also read section 4, “Dynamically Loaded (DL) Libraries”, of the Program Library HOWTO for more techniques to load libraries and create classes independently of your platform.


其他

* The dlopen(3) man page. It explains the purpose and the use of the dlopen API.
* The article Dynamic Class Loading for C++ on Linux by James Norton published on the Linux Journal.
* Your favorite C++ reference about extern "C", inheritance, virtual functions, new and delete. I recommend [STR2000].
* [ISO14882]
* The Program Library HOWTO, which tells you most things you'll ever need about static, shared and dynamically loaded libraries and how to create them. Highly recommended.
* The Linux GCC HOWTO to learn more about how to create libraries with GCC.

参考书目
[ISO14482] ISO/IEC 14482-1998 — The C++ Programming Language. Available as PDF and as printed book from http://webstore.ansi.org/.
[STR2000] StroustrupBjarne The C++ Programming Language, Special Edition. ISBN 0-201-70073-5. Addison-Wesley
