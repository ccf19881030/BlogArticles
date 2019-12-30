由于double浮点数的精度问题，所以在比较大小的时候，不能像int整数型那样，直接if(a==b)，if(a<b)，if(a>b)

要使用一个精度EPS：
```cpp
#include <math.h>　　　　//头文件要记得加
const double EPS = 1e-6;  //一般这样子就够，但有时具体题目要考虑是否要更小的 

if(fabs(a-b) < EPS)  //判断是否相等 

if(a > b+EPS)   // 判断a是否大于b，因为大的肯定大，所以即使你小的加上，还是会更大
```
