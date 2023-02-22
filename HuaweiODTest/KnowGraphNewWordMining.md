# [知识图谱新词挖掘1](https://renjie.blog.csdn.net/article/details/128571197)
题目描述：小华负责公司知识图谱产品，现在要通过新词挖掘完善知识图谱。
  新词挖掘：给出一个待挖掘文本内容字符串Content和一个词的字符串word，找到content中所有word的新词。
  新词：使用词word的字符串排列形成的字符串。
  请帮小华实现新词挖掘，返回发现的新词的数量。
  
输入描述：第一行输入待挖掘的文本内容content；
         第二行输入为词word；
        
输出描述：在content中找到的所有word的新词的数量。

补充说明：0 <= content的长度 <= 10000000;
         1 <= word的长度 <= 2000

示例

示例1
输入：qweebaewqd
      qwe
输出：2
说明：起始索引等于0的子串是"qwe",它是word的新词。
     起始索引等于6的子串是"ewq"，它是word的新词。
     
示例2
输入：abab
     ab
输出：3
说明：起始索引等于0的子串"ab"，它是 word的新词.
     起始索引等于1的子串"ba"，它是 word的新词。
     起始索引等于2的字串"ab"，它是 word的新词。
     
## 解题思路
可以采用滑动窗口算法，这道题和力扣76题.最小覆盖字串以及力扣567题.字符串的排列很类似。
C++实现代码如下：
```cpp
// 知识图谱新词挖掘
// https://renjie.blog.csdn.net/article/details/128571197

#include<iostream>
#include<unordered_map>
#include <string>
using namespace std;

// 滑动窗口算法
int slidingWindow(const string &content, const string &word)
{
    if (content.size() < word.size()) {
        return 0;
    }
    if (word.empty()) {
        return 0;
    }
    unordered_map<char, int> need, window;
    for (char c : word) {
        need[c]++;
    }

    int cnt = 0;
    int left = 0, right = 0;
    int valid = 0;

    // 遍历content字符串
    while (right < content.size()) {
        // a 是将要移入窗口的字符
        char a = content[right];
        // 增大窗口
        right++;
        // 进行窗口内数据的一系列更新
        if (need.count(a)) {
            window[a]++;
            // 如果content中的某个字符个数和word中的个数相同，则valid有效字符计数器加1
            if (need[a] == window[a]) {
                valid++;
            }
        }

        // 此处可以 debug 窗口的位置
        //printf("window: [%d, %d)\n", left, right);

        // 判断左侧窗口是否需要收缩
        // 本题移动left缩小窗口的时机是窗口大小大于word.size()时，因为排列（新词），显然长度是一样的
        while (right - left >= word.size()) {
            // 在这里更新找到新词的计数器，当valid == need.size()时，说明窗口包含合格的新词
            if (valid == need.size()) {
                cnt++;
            }
            // d 是将要移出窗口的字符
            char d = content[left];
            // 缩小窗口
            left++;
            // 进行窗口的一系列更新
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return cnt;
}

int main()
{
    //输入处理
    string content;
    string word;

    while (cin >> content >> word) {
        std::cout << slidingWindow(content, word) << std::endl;
    }

    return 0;
}
```
