## [VScode 全局搜索功能](https://blog.csdn.net/u012529163/article/details/80415572)
最近知道到VScode这个软件，开始试用，总体感觉很不错，就是不能全局搜索，经过了解，是我的配置问题，上网找到了一个解决办法，
在VSCode中依次选择菜单【文件】-》【首选项】-》【设置】，编辑setting.json文件，在settings.json配置文件添加如下内容：
```shell
"search.exclude": { 
        "system/": true, 
        "!/system/*/.ps*": true 
    }
```
现在测试一下吧， 
ctrl + shift +F，输入搜索的内容，查找即可。

