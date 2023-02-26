# [HJ27 查找兄弟单词]( https://www.nowcoder.com/practice/03ba8aeeef73400ca7a37a5f3370fe68)
## 题目描述：
```
描述
    定义一个单词的“兄弟单词”为：交换该单词字母顺序（注：可以交换任意次），
    而不添加、删除、修改原有的字母就能生成的单词。
    兄弟单词要求和原来的单词不同。例如： ab 和 ba 是兄弟单词。 ab 和 ab 则不是兄弟单词。
    现在给定你 n 个单词，另外再给你一个单词 x ，让你寻找 x 的兄弟单词里，按字典序排列后的第 k 个单词是什么？
    注意：字典中可能有重复单词。

    数据范围：1≤n≤1000 ，输入的字符串长度满足 1≤len(str)≤10  ， 1≤k<n
    输入描述：
    输入只有一行。 先输入字典中单词的个数n，再输入n个单词作为字典单词。 然后输入一个单词x 最后后输入一个整数k
    输出描述：
    第一行输出查找到x的兄弟单词的个数m 第二行输出查找到的按照字典顺序排序后的第k个兄弟单词，没有符合第k个的话则不用输出。
    示例1
    输入：
    3 abc bca cab abc 1
    输出：
    2
    bca

    示例2
    输入：
    6 cab ad abcd cba abc bca abc 1
    输出：
    3
    bca
    说明：
    abc的兄弟单词有cab cba bca，所以输出3
    经字典序排列后，变为bca cab cba，所以第1个字典序兄弟单词为bca
  ```
  
  ## 解题思路：
  这是一道字符串的题目。
  编写一个用于判断两个单词字符串s1, s2，如果s1和s2的长度不相同，或者s1和s2相等，则表示s1、s2不是兄弟；接着分别将s1和s2按照字典序进行排序，如果两者相等则是兄弟单词，否则不是。
 具体的C++实现如下：
 ```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isBotherWord(const string &source, const string &dest)
{
	// 注意：排除source == dest的情况
    if (source.length() != dest.length() || source == dest) {
        return false;
    }
    string s1 = source;
    std::sort(s1.begin(), s1.end());
    string s2 = dest;
    std::sort(s2.begin(), s2.end());
    return s1 == s2;
}

int main() {
    int n, k;
    vector<string> sVec;
    string x;
    while (cin >> n) { // 注意 while 处理多个 case
        // 输入n个单词作为字典单词
        string sTemp;
        for (int i = 0; i < n; i++) {
            cin >> sTemp;
            sVec.push_back(sTemp);
        }
        cin >> x;
        cin >> k;
        vector<string> botherWords;
        for (auto word : sVec) {
            if (isBotherWord(x, word)) {
                botherWords.push_back(word);
            }
        }
        // 对botherWords按照字典顺序进行排序
        std::sort(botherWords.begin(), botherWords.end());
        cout << botherWords.size() << endl;
        if ((int)(botherWords.size()) > 0 && k <= (int)(botherWords.size()) - 1) {
            cout << botherWords[k-1] << endl;
        }
        sVec.clear();
    }
}
```
