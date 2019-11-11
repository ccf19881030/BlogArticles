## [宏定义#define STR(s) #s 等宏定义后面加#的意思](https://blog.csdn.net/qq_41069421/article/details/91538232)
#define Conn(x,y) x##y
#define ToChar(x) #@x
#define ToString(x) #x
#define CONS(a,b) int(a##e##b)

x##y表示什么?表示x连接y，举例说:
int n = Conn(123,456); 结果就是n=123456;
char* str = Conn(“asdf”, “adf”)结果就是 str = “asdfadf”;
怎么样，很神奇吧

再来看#@x，其实就是给x加上单引号，结果返回是一个const char。举例说:
char a = ToChar(1);结果就是a=‘1’;
做个越界试验char a = ToChar(123);结果是a=‘3’;
但是如果你的参数超过四个字符，编译器就给给你报错了!error C2015: too many characters in constant ?

再看看#x,估计你也明白了，他是给x加双引号
char* str = ToString(123132);就成了str=“123132”;

最后看看#define CONS(a,b) int(a##e##b) 它表示a乘10的b次方，比如CONS(2,3)=2e3=1000.
