# Big.js 教程

> 原文： [http://zetcode.com/javascript/bigjs/](http://zetcode.com/javascript/bigjs/)

Big.js 教程展示了如何使用 Big.js 模块在 JavaScript 中使用任意精度的大十进制算术运算。

## Big.js

Big.js 是一个小型，快速的 JavaScript 库，用于任意精度的十进制算术。

在本教程中，我们在 Node 应用中使用 Big.js。

## 安装 Big.js

首先，我们安装 Big.js。

```js
$ nodejs -v
v9.11.2

```

我们使用 Node 版本 9.11.2。

```js
$ npm init

```

我们启动一个新的 Node 应用。

```js
$ npm i big.js

```

我们使用`npm i big.js`命令安装 Big.js。

## JavaScript 数字精度错误

在第一个示例中，我们显示 JavaScript 数字对于执行任意精度算术不是精确的。

`count_currency.js`

```js
var sum = 0;
// two euros fifty-five cents
var amount = 2.55;

for (let i = 0; i < 100000; i++) {

    sum += amount;
}

console.log(sum);

```

在此示例中，我们将两欧元五十五美分十万倍。

```js
$ nodejs numbers.js 
254999.9999995398

```

我们的计算有误。

## Big.js 示例

在下一个示例中，我们使用 Big.js 更正错误。

`big_decimal.js`

```js
const Big = require('big.js');

var val = new Big(0.0);
var amount = new Big(2.55);

var sum = val.plus(amount).times(100000);

console.log(sum.toFixed(2));

```

使用 Big.js 库，计算非常精确。

```js
const Big = require('big.js');

```

我们加载`big.js`模块。

```js
var val = new Big(0.0);
var amount = new Big(2.55);

```

我们创建两个大十进制值。

```js
var sum = val.plus(amount).times(100000);

```

我们将值相加 100000 次。 请注意，大十进制值是不可变的，因此我们生成一个新变量。

```js
$ nodejs big_decimal.js 
255000.00

```

这是输出。

在本教程中，我们使用`Big.js`库对任意精度算法进行了处理。

您可能也对以下相关教程感兴趣： [Moment.js 教程](/javascript/momentjs/)，[从 JavaScript 中的 URL 读取 JSON](/articles/javascriptjsonurl/) ， [JavaScript Snake 教程](/javascript/snake/)， [JQuery 教程](/web/jquery/) ， [Node Sass 教程](/javascript/nodesass/)， [Lodash 教程](/javascript/lodash/)。
