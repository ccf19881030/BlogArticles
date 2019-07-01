## 删除vector中重复元素
vector<int> v={1,2,4,3,5.2};

则调用以下语句即可：
```cpp
sort(v.begin(),v.end());
v.erase(unique(v.begin(),v.end()),v.end());
```
vector.pop_back()可以弹出最后加入的元素
