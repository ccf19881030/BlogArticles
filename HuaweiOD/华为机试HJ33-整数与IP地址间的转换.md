- [华为机试题 HJ33 整数与IP地址间的转换](https://www.nowcoder.com/practice/66ca0e28f90c42a196afd78cc9c496ea)
 ## 一、题目描述
```
  描述
  原理：ip地址的每段可以看成是一个0-255的整数，把每段拆分成一个二进制形式组合起来，然后把这个二进制数转变成
    一个长整数。
    举例：一个ip地址为10.0.3.193
    每段数字             相对应的二进制数
    10                   		00001010
    0                    		00000000
    3                    		00000011
    193                  	11000001

    组合起来即为：00001010 00000000 00000011 11000001,转换为10进制数就是：167773121，即该IP地址转换后的数字就是它了。

    数据范围：保证输入的是合法的 IP 序列

    输入描述：
    输入
    1 输入IP地址
    2 输入10进制型的IP地址

    输出描述：
    输出
    1 输出转换成10进制的IP地址
    2 输出转换后的IP地址

    示例1
    输入：
    10.0.3.193
    167969729
    输出：
    167773121
    10.3.3.193
  ```

题目的主要信息：
- ip地址的每段可以看成是一个0-255的整数，把每段拆分成一个二进制形式组合起来，然后把这个二进制数转变成一个长整数
- 输入需要将一个ip地址转换为整数、将一个整数转换为ip地址

## 解法1
我一开始想到的思路是针对10.0.3.193这种点分十进制的IP地址，将其转换成字符串，然后按照字符.进行分割，放入数组中，然后对数组中的4个数字进行位运算，最后进行组合。而对于167969729这种长整型的IP地址，进行位运算后依次得到点分十进制中的每一项，以8位进行右移运算。具体的代码如下：
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<string> Split(const string& strInput, char split = '.')
{
    vector<string> splitVec;
    size_t len = strInput.size();
    size_t start = 0;
    size_t end = 0;
    string strTemp = "";
    size_t it = 0;
    while ((it = strInput.find(split, start)) != string::npos  && start < len) {
        end = it;
        strTemp = strInput.substr(start, end - start);
        splitVec.push_back(strTemp);
        start = end + 1;
    }
    splitVec.push_back(strInput.substr(start));
    return splitVec;
}

long ConvertIp(const string& strIp)
{
    long ip = 0;
    vector<string> ipVec = Split(strIp, '.');
    for (int i = 0; i < ipVec.size(); i++) {
        long nTemp = atol(ipVec[i].c_str());
        ip += nTemp << ((ipVec.size()-i-1) * 8); // 24 16 8
    }
    return ip;
}

string ConvertToIpString(long ip)
{
    string strIp = "";
    long nTemp = ip >> 24;
    ip = ip - (nTemp << 24);
    strIp += std::to_string(nTemp);
    nTemp = ip >> 16;
    ip = ip - (nTemp << 16);
    strIp += ".";
    strIp += std::to_string(nTemp);
    nTemp = ip >> 8;
    ip = ip - (nTemp << 8);
    strIp += ".";
    strIp += std::to_string(nTemp);
    nTemp = ip;
    strIp += ".";
    strIp += std::to_string(nTemp);
    return strIp;
}

int main() {
    string strIp;
    long ip;
    while (cin >> strIp >> ip) { // 注意 while 处理多个 case
        cout << ConvertIp(strIp) << endl;
        cout << ConvertToIpString(ip) << endl;
    }

    return 0;
}
```

## 解法二
借助scanf进行接收输入数据，然后对输入数据进行位运算，如下所示：
```cpp
#include <iostream>
using namespace std;

int main()
{
    long long int a,b,c,d;
    long long int num;

    while(scanf("%lld.%lld.%lld.%lld",&a,&b,&c,&d)!=EOF){
        cin>>num;
        cout<<(a<<24)+(b<<16)+(c<<8)+d<<endl;
        a = num>>24;
        num = num-(a<<24);
        b = num>>16;
        num = num-(b<<16);
        c = num>>8;
        d = num-(c<<8);
        cout<<a<<"."<<b<<"."<<c<<"."<<d<<endl;
    }
}
```
上面的解法确实很巧妙，借助scanf函数直接接收输入数据，这样避免使用字符串处理输入数据的麻烦。

## 解法三：逐位分割，逐位计算
具体做法：
 对于两个输入，题目已明确表示第一个输入是字符串型的IP地址，第二个输入是整数，
 我们就可以用一个string类型和一个long型来接收（int会超）。

IP地址转换整数，我们首先要将IP地址以点分割出来，将数组提取出来：
遍历字符串，用变量记录点出现的次数，刚好可以作为四个整数的下标，
0次即第0个数组元素，1次即第1个数组元素，一一对应，对于数字我们乘10累加记录这个数字，
对于点我们统计次数即可。得到了四个整数，我们可以将第0个整数左移24位，使其成为32位二进制的头8个，
然后第1个整数左移16位，第2个整数左移8位，最后一个不变，四个数通过位或操作即可组装在一起。

数字转换成IP地址，我们我们也是通过位操作，即IP地址第一部分是数字右移24位后的大小，我们与后8位全1的数做位与运算即可得到，中间添加点，第二部分是数字右移16位后与0xff位与，
第三部分是数字右移8位后与0xff位与，最后一部分是直接与0xff位与，每次只取相应的8位。
![HJ33 整数与IP地址转换](https://img-blog.csdnimg.cn/d8b866d467024df3b06d9ba15fa1bc6a.gif#pic_center)
具体的C++代码如下：
```cpp
#include<iostream>
#include<string>
using namespace std;

void toNum(string ip){
    long num[4] = {0, 0, 0, 0};
    int point = 0; //记录点出现的次数
    for(int i = 0; i < ip.length(); i++){ //遍历ip字符串
        if(ip[i] != '.'){ //通过.分割
            num[point] = num[point] * 10 + ip[i] - '0';
        }else{
            point++; //点数增加
        }
    }
   long output = num[0] << 24 | num[1] << 16 | num[2] << 8 | num[3]; //位运算组装
   cout << output << endl;
}

void toIP(long num){
    string output = "";
    output += to_string((num >> 24) & 0xff); //取第一个八位二进制转换成字符
    output += ".";
    output += to_string((num >> 16) & 0xff); //取第二个八位二进制转换成字符
    output += ".";
    output += to_string((num >> 8) & 0xff); //取第三个八位二进制转换成字符
    output += ".";
    output += to_string(num & 0xff); //取第四个八位二进制转换成字符
    cout << output << endl;
}

int main(){
    string ip;
    long num;
    while(cin >> ip >> num){ //默认第一个是IP地址第二个是整数
        toNum(ip);
        toIP(num);
    }
    return 0;
}
```

复杂度分析：
- 时间复杂度：O(1)，IP地址长度一定，遍历过程为常数时间，所有位运算也是常数时间
- 空间复杂度：O(1)，辅助数组num为常数空间，其他都是必要空间

## 解法四：正则表达式+字符串流输入输出
具体做法：

我们不区分字符串还是数字，都将其看成字符串，检查字符串中有没有点，有点的就是ip地址，否则就是整数。

我们也不用遍历字符串依次分割，我们可以用正则表达式直接匹配点将其替换成空格，然后用字符串流输入stringstream以空格为界将其输入到数组中成为数字，用方法三位运算组装成长整数。

对于整数，我们也可以将其用流输出的方式整理成字符串，然后输出，转换过程同方法三。
具体代码如下：
```cpp
#include<iostream>
#include<sstream>
#include<regex>
#include<string>
using namespace std;

int main(){
    string s;
    while(cin >> s){
        if(s.find_first_of('.') != string::npos){ //查找到有.的就是IP地址
            long num[4];
            stringstream(regex_replace(s, regex("\\."), " ")) >> num[0] >> num[1] >> num[2] >> num[3]; //用正则表达式分割后输入数组
            long output = num[0] << 24 | num[1] << 16 | num[2] << 8 | num[3]; //位运算组装
            cout << output << endl;
        }else{ //否则是整数
            long num;
            stringstream(s) >> num; //流输入转数字
            stringstream output;
            output << ((num >> 24) & 0xff) << "." << ((num >> 16) & 0xff) << "." << ((num >> 8) & 0xff) << "." << (num & 0xff); //流输出格式
            cout << output.str() << endl; //转字符串输出
        }
    }
    return 0;
}
```
### 复杂度分析：
- 时间复杂度：O(1)，IP地址长度一定，正则匹配和流输入输出为常数时间，所有位运算也是常数时间
- 空间复杂度：O(1)，辅助数组num为常数空间，其他都是必要空间
