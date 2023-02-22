# [知识图谱新词挖掘1](https://renjie.blog.csdn.net/article/details/128571197)
## 题目描述：
```
小华负责公司知识图谱产品，现在要通过新词挖掘完善知识图谱。
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
```

## 解法1：
```
1、和leetcode 76.最小覆盖子串和leetcode 576.字符串的排列这两道题很像，但是输出要求有所区别。
2、其实考察的就是hash的数据结构，很直观的做法是：
1) 先分析word中的字符有哪些，每种字符出现了多少次。用一个hashmap结构保存
2) 遍历content中每个长度为m的子串（滑动窗口），统计字符，然后与word的统计结果对照。
这种解法时间复杂度是O(2*n+m)，但要做统计的对照，所以时间复杂度还与字符种类有关。若只有26个小写字母，时间复杂度就是O(26*2n+m)。
其实也是常数级别。但是，这个26的系数可以优化掉：
用一个整数N表示word中字符的种类数；用整数M表示，在content中长度为m的子串出现次数不少于在word中长度为m的子串出现次数不少于在word中出现次数的字符的种数。
遍历content种每个长度为m的子串时，当前子串的统计结果，只是在上一次统计结果的基础上添加和去掉一个元素。
去掉一个字符ch，若去掉前，ch出现的次数正好等于在word中出现的次数，则--M。
添加一个字符ch，若添加后，ch出现的次数正好等于在word中出现的次数，（表示content子串中这个字符出现的次数和word中出现次数一致），那么++M。
若M == N，那么就在content中找到了一个word的全排列子串。
这样，不论字符的种类有多少，时间复杂度总是O(2n+m)
```

```cpp
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<set>
#include<numeric>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
#include<cctype>
using namespace std;
 
vector<int> split(string params_str) {
    vector<int> p;
    while (params_str.find(" ") != string::npos) {
        int found = params_str.find(" ");
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
 
 
vector<string> split_str(string params_str, string op) {
    vector<string> p;
    while (params_str.find(op) != string::npos) {
        int found = params_str.find(op);
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}
 
int contin(const string &content, const string &word){
	if(content.size() < word.size())
		return 0;
	if(word.empty() == true)
		return 0;
	unordered_map<char, int> content_map, word_map;
    //先统计出word中的字符组成
	for(char ch : word)
		++word_map[ch];
 
	int word_char_kind = word_map.size();
	int right = 0;
	int content_child_char_kind = 0;
    int result = 0;
	while(right < content.size()){
		if(right >= word.size()){
			int left = right - word.size();
			int tmp = content_map[content[left]]--;
			auto it = word_map.find(content[left]);
			if(it != word_map.end() && tmp == it->second)
				--content_child_char_kind;
		}
		int tmp = ++content_map[content[right]];
		auto it = word_map.find(content[right]);
		if(it != word_map.end() && tmp == it->second)
			++content_child_char_kind;
		++right;
        if (content_child_char_kind == word_char_kind) {
            result += 1;
        }
	}
	return result;
}
 
int main()
{
    //输入处理
    string content;
    string word;
    cin >> content >> word;
    cout << contin(content, word);
    return 0;
}
```
     
## 解题思路2
可以采用[滑动窗口算法](https://labuladong.gitee.io/algo/di-ling-zh-bfe1b/wo-xie-le--f02cd/)，这道题和[力扣76题.最小覆盖字串](https://leetcode.cn/problems/minimum-window-substring/)以及[力扣567题.字符串的排列](https://leetcode.cn/problems/permutation-in-string/)很类似。
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
