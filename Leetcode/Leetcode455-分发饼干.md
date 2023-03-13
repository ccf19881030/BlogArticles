# [Leetcode 455.分发饼干](https://leetcode.cn/problems/assign-cookies/)
## 题目描述：
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；
并且每块饼干 j，都有一个尺寸 s[j] 。
如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。
你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。


示例 1:

输入: g = [1,2,3], s = [1,1]
输出: 1
解释:
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
示例 2:

输入: g = [1,2], s = [1,2,3]
输出: 2
解释:
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.


提示：

1 <= g.length <= 3 * 10^4
0 <= s.length <= 3 * 10^4
1 <= g[i], s[j] <= 2^31 - 1
    
## 思路
先进行排序，从后往前遍历胃口数列，对于一个胃口，当前最大的饼干数如果不能满足要求，就再往前遍历一个胃口，看看当前最大的饼干能不能满足较小的胃口。
最后终止条件为遍历完所有的胃口，或者遍历完所有的饼干数。

## 解题方法
先排序，再采用贪心算法

## 复杂度
时间复杂度: O(mlogm+nlogn)
排序的开销
空间复杂度: O(logm+logn)
排序的开销
```java
class Solution {
    public int findContentChildren(int[] g, int[] s) {
        //贪心算法，也是双指针
        Arrays.sort(g);
        Arrays.sort(s);
        int result = 0;
        if(g.length == 0 || s.length == 0) return 0;
        int j = s.length - 1;
        //已知循环次数，用for循环效率更高
        for(int i = g.length - 1;i >= 0;i--){
            if(j >= 0 && g[i] <= s[j] ){
                result++;
                j--;
            }
        }
        return result;
    }
}
```

```cplus
// 排序+贪心算法+双指针
// 每次将最大的饼干分给胃口最大的孩子
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if (g.size() == 0 || s.size() == 0) {
            return 0;
        }
        int result = 0;
        // 先对g和s从小到到排序
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());

        int gLen = g.size();
        int j = s.size() - 1;
        // 已知循环次数，用for循环效率更高
        for (int i = gLen - 1; i >= 0; i--) {
            if (j >= 0 && s[j] >= g[i]) {
                result++;
                j--;
            }
        }
        return result;
    }
};
```
