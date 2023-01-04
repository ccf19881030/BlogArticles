# 编程题2 单词倒序 [【华为OD机试真题 Python】英文句子倒序](https://blog.csdn.net/A_D_I_D_A_S/article/details/127857791)
- 时间限制：1s 空间限制：256MB 限定语言：不限
- 题目描述：输入单行英文句子，里面包含英文字母，空格以及,.?三种标点符号，请将句子内每个单词进行倒序，病输出倒序后的语句。
- 输入描述：输入字符串S，S的长度1 <= N <= 100
- 输出描述：输出逆序后的字符串
- 补充说明：标点符号左右的空格>=0，单词间空格>0
- 示例
```
示例1
输入：yM eman si boB.
输出：My name is Bob.

示例2:
输入：woh era uoy ?I ma enid.
输出：how are you ?I am fine.
```

## C++代码实现
```
#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

using namespace std;

std::string GetReverStr(std::string &inputStr)
{
    std::string resultStr;
    int i = 0;
    bool bEnd =false;
    while (i < inputStr.size() && !bEnd) {
        std::string word = "";
        char ch = inputStr[i];
        if (isaplpha(ch)) {
            word += ch;
        } else if (ch == ',' || ch == '.' || ch == '?' || ch == ' ') {
            resultStr += ch;
            i++;
            continue;
        }
        for (int j = i + 1; j < inputStr.size(); j++) {
            if (j == inputStr.size() -1) {
                if (isalpha(inputStr[j])) {
                    word += inputStr[j];
                    std::reverse(word.begin(), word.end());
                    resultStr += word;
                } else if (inputStr[j] == ',' || inputStr[j] == '.' || inputStr[j] == '?' || inputStr[j] == ' ') {
                    std::reverse(word.begin(), word.end());
                    resultStr += word;
                    resultStr += inputStr[j];
                }
                bEnd = true;
                break;
            }
            char ch2 = inputStr[j];
            if (isalpha(ch2) {
                    word += ch2;
                } else if (ch2 == ',' || ch2 == '.' || ch2 == '?' || ch2 == ' ') {
                        if (isalpha(inputStr[j-1])) {
                          std::reverse(word.begin(), word.end());
                          resultStr += word;
                       } else if (inputStr[j-1] == ',' || inputStr[j-1] == '.' || inputStr[j-1] == '?' || inputStr[j-1] == ' ') {
                          std::reverse(word.begin(), word.end());
                          resultStr += word;
                          resultStr += inputStr[j-1];
                      }
                      i = j;
                      break;
                }

        }
    }
    
    return resultStr;
}

int main()
{
    std::string inputStr;
    while (getline(cin, inputStr) {
        std::string resultStr = GetReverseStr(inputStr);
        std::cout << resultStr << std::endl;
    }
}
```
