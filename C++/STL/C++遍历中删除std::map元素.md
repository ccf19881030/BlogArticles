## [C++ map（STL map）删除元素（erase函数删除元素）详解](http://c.biancheng.net/view/513.html)
## [C++遍历中删除std::map元素](https://www.cnblogs.com/kex1n/archive/2011/07/08/2100787.html)
在std::list中删除一个元素非常简单，直接使用erase方法即可，代码如下：
```cpp
for(iter = list.begin(); iter != list.end();) {
if (shouldDelete(*iter))
iter = list.erase(iter);
else
++iter;
}
```
或者更简单点
```cpp
list.erase(std::remove_if(list.begin(), list.end(), shouldDelete), list_end());
```
然而根据STL std::map中的定义void erase(iterator pos)，此erase并不返回下一个元素的迭代器，因此不能采用std::list的方法
   The truth is that ‘erase’ in associative containers doesn’t invalidate any iterators except those that point to elements being erased (that’s also true for ’sid::list’). For this reason, you don’t really need ‘map::erase’ to return an iterator. Just do this
```cpp
for(iter = map.begin(); iter != map.end();) {
  if (shouldDelete(*iter))
     map.erase(iter++);
  else
     ++iter;
}
```
当然此方法同样也适合于std::list等
