## [js 将Date 日期对象与时间戳互相转换](https://blog.csdn.net/qq_30100043/article/details/53909780)

### 将Date对象转换成时间戳
第一种方法，使用Number()方法
```js
var newDay = new Date();
console.log(Number(newDay));
```

返回当前的时间的时间戳
第二种方法是，使用日期对象Date.parse()方法
```js
var newDay = new Date();
console.log(Date.parse(newDay));
```

也会返回当前时间的时间戳

第三种方法是利用转义符进行转义
```js
var newDay = +new Date();
console.log(newDay);
```

两种方法对比，

第一种使用数字对象的方法返回的时间戳，精确到了毫秒，而日期对象的Date.parse()方法只精确到了秒，后三位都是用的0填充的，所以个人推荐第一种

### 将时间戳转换成Date对象
```js
var newDate = new Date(时间戳);  //实例化一个Date对象，将时间戳直接传入，注意一定是13位
```

或者
```js
var timestamp3 = 1403058804000;  //声明一个时间戳
var newDate = new Date();  //实例化一个Date对象
newDate.setTime(timestamp3); //设置Date对象的时间为时间戳的时间
```





