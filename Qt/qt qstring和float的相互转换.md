## qt qstring和float的相互转换
在使用Qt Creator编程时，难免会用到将float类型转换为QString类型的时候下面是我所有的方法：

1. 将QString类型转化为float类型，很简单
```cpp
    QString data;            
    float num = data.toFloat();
```

    即可很轻松的实现。

2. 但是如何将float类型转化为QString类型呢？

    查看API很难发现封装好的转化函数

    可以尝试使用下面的代码转化：
```cpp
    float num = 1.222;

    QString data = QString("float is %1").arg(num);
```
    输出结果是：float is 1.222

    如果只要float转化成的数值，则使用如下：
```cpp
    QString data = QString("%1").arg(num);
```
