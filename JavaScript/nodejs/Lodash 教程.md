# Lodash 教程

> 原文： [http://zetcode.com/javascript/lodash/](http://zetcode.com/javascript/lodash/)

Lodash 教程涵盖了 Lodash JavaScript 库。 在这个 Lodash 入门教程中，我们在多个示例中介绍 Lodash 函数。

## Lodash

Lodash 是一个 JavaScript 库，为常见的编程任务提供实用程序功能。 它使用函数式编程范例。 Lodash 受`Underscore.js`的启发。

Lodash 帮助程序员编写更简洁，更易于维护的 JavaScript 代码。 Lodash 包含一些工具，可简化使用字符串，数字，数组，函数和对象的编程。

按照惯例，Lodash 模块被映射到下划线字符。

## Lodash 安装

首先，我们安装 Lodash 库。

```js
$ npm init
$ npm i lodash

```

Lodash 库与`npm`一起本地安装。

```js
$ cat package.json
{
    "name": "lodash-lib",
    "version": "1.0.0",
    "description": "",
    "main": "lo_sample.js",
    "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
    },
    "keywords": [],
    "author": "",
    "license": "ISC",
    "dependencies": {
    "lodash": "^4.17.11"
    }
}

```

我们使用 Lodash 版本 4.17.11。

```js
<script src="lodash.js"></script>    

```

在浏览器内部，我们将库包含在`&lt;script&gt;`标签中。

## Lodash 版本

在第一个示例中，我们确定 Lodash 库的版本。

`version.js`

```js
const _ = require("lodash")

const ver = _.VERSION
console.log(ver);    

```

该示例打印 Lodash 库的版本。

```js
const _ = require("lodash")

```

按照惯例，Lodash 库被映射到下划线字符。

```js
const ver = _.VERSION
console.log(ver);    

```

版本存储在`VERSION`变量中。

```js
$ node version.js 
4.17.11

```

我们使用 Lodash 版本 4.17.5。

## Lodash 第一个和最后一个数组元素

`_.first()` / `_.head()`函数返回第一个数组元素； `_.last()`函数返回最后一个数组元素。

`first_last.js`

```js
const _ = require("lodash")

words = ['sky', 'wood', 'forest', 'falcon', 
    'pear', 'ocean', 'universe'];

let fel = _.first(words);
let lel = _.last(words);

console.log(`First element: ${fel}`);
console.log(`Last element: ${lel}`);

```

该示例输出单词数组的第一个和最后一个元素。

```js
$ node first_last.js
First element: sky
Last element: universe

```

这是输出。

## Lodash 分块数组

`_.chunk()`函数创建一个元素数组，将指定长度的元素分成几组。

`chunking.js`

```js
const _ = require("lodash")

nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];

let c1 = _.chunk(nums, 2);
console.log(c1);

let c2 = _.chunk(nums, 3);
console.log(c2);

```

该示例将`nums`数组分为两个和三个元素子数组的数组。

```js
$ node chunking.js
[ [ 1, 2 ], [ 3, 4 ], [ 5, 6 ], [ 7, 8 ], [ 9 ] ]
[ [ 1, 2, 3 ], [ 4, 5, 6 ], [ 7, 8, 9 ] ]

```

这是输出。

## 获取数组切片

`_.slice()`方法从数组获取切片。 它有两个索引：开始索引和结束索引，其中开始索引是包含端点的，结束索引是互斥的。

`slice_fun.js`

```js
const _ = require("lodash")

nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];

let c1 = _.slice(nums, 2, 6);
console.log(c1);

let c2 = _.slice(nums, 0, 8);
console.log(c2);

```

该示例从`nums`数组创建两个切片。

```js
$ node slice_fun.js
[ 3, 4, 5, 6 ]
[ 1, 2, 3, 4, 5, 6, 7, 8 ]

```

这是输出。

## Lodash 随机数

`_.random()`函数在上下限之间产生随机值。

`random_vals.js`

```js
const _ = require("lodash")

var r = _.random(10);
console.log(r);

r = _.random(5, 10);
console.log(r);

```

该示例打印两个随机值。

```js
var r = _.random(10);

```

我们产生 0 到 10 之间的随机值。

```js
r = _.random(5, 10);

```

在这里，我们产生 5 到 10 之间的随机值。

## Lodash 随机数组元素

使用`_.sample()`函数，我们可以从数组中选择随机元素。

`sample_fun.js`

```js
const _ = require("lodash")

words = ['sky', 'wood', 'forest', 'falcon', 
    'pear', 'ocean', 'universe'];

let word = _.sample(words);
console.log(word);

```

该示例使用`_.sample()`从数组中选择一个随机单词。

```js
$ node sample_fun.js
falcon

```

这是一个示例输出。

## Lodash 改组数组元素

`_.shuffle()`功能可对集合进行混洗。

`shuffle_fun.js`

```js
const _ = require("lodash")

words = ['sky', 'wood', 'forest', 'falcon', 
    'pear', 'ocean', 'universe'];

console.log(_.shuffle(words));
console.log(_.shuffle(words));
console.log(_.shuffle(words));
console.log(words);

```

该示例从初始单词数组创建三个新的随机重组的数组。

```js
$ node shuffle_fun.js
[ 'sky', 'ocean', 'universe', 'falcon', 'pear', 'wood', 'forest' ]
[ 'wood', 'ocean', 'falcon', 'forest', 'sky', 'universe', 'pear' ]
[ 'forest', 'ocean', 'sky', 'wood', 'falcon', 'universe', 'pear' ]
[ 'sky', 'wood', 'forest', 'falcon', 'pear', 'ocean', 'universe' ]

```

这是输出。 原始数组未修改； `_.shuffle()`函数创建一个新数组。

## Lodash `_.times`函数

`_.times()`执行该功能 n 次。

`times_fun.js`

```js
const _ = require("lodash");

_.times(4, () => {

    console.log("brave");
})

```

在示例中，我们执行了 innter 函数四次。 该功能将单词打印到控制台。

```js
$ node times_fun.js 
brave
brave
brave
brave

```

这是输出。

## Lodash `_.delay`函数

`_.delay()`功能将功能的执行延迟指定的毫秒数。

`delay_fun.js`

```js
const _ = require("lodash")

function message()
{
    console.log("Some message");
}

_.delay(message, 150);
console.log("Some other message");

```

该示例输出两个消息。 第一个延迟 150ms。

```js
$ node delay_fun.js
Some other message
Some message

```

这是输出。

## Lodash 确定数据类型

Lodash 包含确定值的数据类型的函数。

`datatype.js`

```js
const _ = require("lodash");

const vals = [1, 2, 'good', [1, 2], {name: 'Peter', age: 32}];

vals.forEach( (e) => {

    if (_.isNumber(e)) {
        console.log(`${e} is a number`);
    }

    if (_.isString(e)) {
        console.log(JSON.stringify(e) + ' is a string');
    }

    if (_.isArray(e)) {
        console.log(JSON.stringify(e) + ' is an array');
    }

    if (_.isObject(e)) {
        console.log(JSON.stringify(e) + ' is an object');
    }

});

```

在示例中，我们确定数组元素的数据类型。

```js
const vals = [1, 2, 'good', [1, 2], {name: 'Peter', age: 32}];

```

我们有一个值数组，包括数字，字符串，数组和对象。

```js
if (_.isNumber(e)) {
    console.log(`${e} is a number`);
}

```

`_.isNumber()`功能检查值是否为数字。

```js
if (_.isString(e)) {
    console.log(JSON.stringify(e) + ' is a string');
}

```

`_.isString()`函数检查值是否为字符串。

```js
if (_.isArray(e)) {
    console.log(JSON.stringify(e) + ' is an array');
}

```

`_.isArray()`函数检查值是否为数组。

```js
if (_.isObject(e)) {
    console.log(JSON.stringify(e) + ' is an object');
}

```

`_.isObject()`函数检查值是否为对象。

```js
$ node index.js 
1 is a number
2 is a number
"good" is a string
[1,2] is an array
[1,2] is an object
{"name":"Peter","age":32} is an object

```

这是程序的输出。

## Lodash `_.range`函数

Lodash `_.range()`函数创建一个数字数组。 该函数接受`start`，`end`和`step`参数。

`range_fun.js`

```js
const _ = require("lodash");

const vals = _.range(10);
console.log(vals);

const vals2 = _.range(0, 15);
console.log(vals2);

const vals3 = _.range(0, 15, 5);
console.log(vals3);

```

在代码示例中，我们创建了三个值范围。

```js
const vals = _.range(10);

```

该行创建一个值 0..9 的数组。 `end`值是必需的，`start`和`step`是可选的。 `end`不包含在内； 因此，不包括值 10。

```js
const vals2 = _.range(0, 15);

```

在这里，我们指定`start`和`step`参数。 我们创建一个值数组 0..14。

```js
const vals3 = _.range(0, 15, 5);

```

最后，我们提供所有三个参数。 将创建一个包含 0、5 和 10 个值的数组。

```js
$ node range_fun.js
[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ]
[ 0, 5, 10 ]

```

这是输出。

## Lodash 最大值和最小值

Lodash 允许计算数组的最大值和最小值。

`min_max.js`

```js
const _ = require("lodash");

const vals = [-3, 4, 0, 12, 43, 9, -12];

var min = _.min(vals);
console.log(min);

var max = _.max(vals);
console.log(max);

max = _.max(_.range(5, 25));
console.log(max);

const obs = [{n: 12}, {n: -4}, {n: 4}, {n: -11}];

min = _.minBy(obs, 'n');
console.log(min);

max = _.maxBy(obs, 'n');
console.log(max);

```

该示例计算数组的最小值和最大值。

```js
var min = _.min(vals);
console.log(min);

```

`_.min()`函数返回数组的最小值。

```js
var max = _.max(vals);
console.log(max);    

```

`._max()`函数返回数组的最大值。

```js
min = _.minBy(obs, 'n');
console.log(min);

max = _.maxBy(obs, 'n');
console.log(max);    

```

要计算对象属性的最小和最大值，我们使用`_.minBy()`和`.maxBy()`函数。

```js
$ node min_max.js 
-12
43
24
{ n: -11 }
{ n: 12 }

```

这是输出。

## Lodash `_.sum`函数

`_.sum()`函数计算数组值的总和。

`sum_fun.js`

```js
const _ = require("lodash");

const vals = [-2, 0, 3, 7, -5, 1, 2];

const sum = _.sum(vals);
console.log(sum);

```

在代码示例中，我们计算并打印数组值的总和。

```js
$ node sum_fun.js 
6

```

这是输出。

## Lodash 集合过滤器

`_.filter()`函数返回其谓词函数返回 true 的元素数组。

`col_filter.js`

```js
const _ = require("lodash");

const nums = [4, -5, 3, 2, -1, 7, -6, 8, 9];

const pos_nums = _.filter(nums, (e) => e > 0);
console.log(pos_nums);

```

在代码示例中，我们过滤掉数组的正值。

```js
const pos_nums = _.filter(nums, (e) => e > 0);

```

谓词是一个返回布尔值的函数。 在我们的例子中，我们有一个匿名函数，该函数对于大于 0 的值返回 true。

```js
$ node col_filter.js 
[ 4, 3, 2, 7, 8, 9 ]

```

这是输出。

## Lodash 集合分区

分区操作将原始集合拆分为一对数组。 第一个数组包含其指定谓词产生 true 的元素，而第二个列表包含其谓词产生 false 的元素。

`col_partition.js`

```js
const _ = require("lodash");

const nums = [4, -5, 3, 2, -1, 7, -6, 8, 9];

const [nums2, nums3] = _.partition(nums, (e) => e < 0);
console.log(nums2);
console.log(nums3);

```

使用`_.partition()`函数，我们将数组分为两个数组； 第一个包含正值，第二个包含负值。

```js
const [nums2, nums3] = _.partition(nums, (e) => e < 0);

```

`_.partition()`函数根据谓词函数创建两个数组。 通过数组解构操作，我们将创建的数组分配给两个变量：`nums2`和`nums3`。

```js
$ node col_partition.js 
[ -5, -1, -6 ]
[ 4, 3, 2, 7, 8, 9 ]

```

这是输出。

## Lodash 集合归约

归约是将列表值聚合为单个值的终端操作。 `_.reduce()`函数对累加器和数组中的每个元素（从左到右）应用一个函数，以将其减小为单个值。

`col_reduce.js`

```js
const _ = require("lodash");

const nums = [4, 5, 3, 2, 1, 7, 6, 8, 9];

const sum = _.reduce(nums, (total, next) => { return total + next });
console.log(sum);

const colours = ["red", "green", "white", "blue", "black"];

const res = _.reduceRight(colours, (next, total) => { return `${total}-${next}` });
console.log(res);

```

在示例中，我们对整数和字符串列表使用 reduce 操作。

```js
const sum = _.reduce(nums, (total, next) => { return total + next });
console.log(sum);

```

我们计算值的总和。 `total`是累加器，`next`是列表中的下一个值。

```js
const res = _.reduceRight(colours, (next, total) => { return `${total}-${next}` });

```

`_.reduceRight()`累加一个从最后一个元素开始的值，并将从右到左的操作应用于每个元素和当前累加器值。

```js
$ node col_reduce.js 
45
red-green-white-blue-black

```

这是输出。

## Lodash 字符串大小写

Locash 库包含几个针对单词大小写的函数。

`string_case.js`

```js
const _ = require("lodash");

const words = ["sky", "Sun", "Blue Island"];

console.log(_.map(words, _.camelCase));
console.log(_.map(words, _.capitalize));
console.log(_.map(words, _.kebabCase));
console.log(_.map(words, _.lowerCase));
console.log(_.map(words, _.upperCase));

```

在示例中，我们用`_.camelCase()`，`_.capitalize()`，`._kebabCase()`，`_lowerCase()`和`_.upperCase()`修改单词的大小写。

```js
$ node string_case.js 
[ 'sky', 'sun', 'blueIsland' ]
[ 'Sky', 'Sun', 'Blue island' ]
[ 'sky', 'sun', 'blue-island' ]
[ 'sky', 'sun', 'blue island' ]
[ 'SKY', 'SUN', 'BLUE ISLAND' ]

```

这是输出。

## Lodash 字符串`_.startsWith`和`_.endsWith`

`_.startsWith()`函数确定字符串是否以指定的字符串开头。 `_.endsWith()`函数确定字符串是否以指定的字符串结尾。

`string_startend.js`

```js
const _ = require("lodash");

const words = ["tank", "boy", "tourist", "ten",
        "pen", "car", "marble", "sonnet", "pleasant",
        "ink", "atom"]

console.log("Starting with 't'");
words.forEach( e => {

    if (_.startsWith(e, 't')) {

        console.log(e);
    }
});

console.log("Ending with 'k'");
words.forEach( e => {

    if (_.endsWith(e, 'k')) {

        console.log(e);
    }
});

```

在示例中，我们打印以“ t”开头和以“ k”结尾的单词。

```js
$ nodejs string_startend.js 
Starting with 't'
tank
tourist
ten
Ending with 'k'
tank
ink

```

这是输出。

## Lodash 字符串填充

如果字符串小于指定的数字，则可以用字符填充字符串。

`string_pad.js`

```js
const _ = require("lodash");

const nums = [657, 122, 3245, 345, 99, 18];

nums.forEach( e => {

    console.log(_.padStart(e.toString(), 20, '.'));
});

```

该示例使用`_.padStart()`将数字用点字符填充。

```js
$ node string_pad.js 
.................657
.................122
................3245
.................345
..................99
..................18

```

这是输出。

## Lodash 对象键和值

`_.keys()`函数返回 JavaScript 对象的属性名称的数组，`_.values()`函数返回其值的数组。

`keys_values.js`

```js
const _ = require("lodash");

const p = {age: 24, name: "Rebecca", occupation: "teacher"};

const keys = _.keys(p);
console.log(keys);

const values = _.values(p);
console.log(values);

```

在示例中，我们打印人员对象的键和值。

```js
$ node keys_values.js 
[ 'age', 'name', 'occupation' ]
[ 24, 'Rebecca', 'teacher' ]

```

这是输出。

## Lodash 迭代对象属性

`_.forIn()`函数可用于遍历对象属性。

`iter_object_props.js`

```js
const _ = require("lodash");

const p = {age: 24, name: "Rebecca", occupation: "teacher"};

_.forIn(p, (value, key) => {

    console.log(`${key}: ${value}`);
})

```

在示例中，我们使用`_.forIn()`遍历人员对象的属性。

```js
$ node iter_object_props.js 
age: 24
name: Rebecca
occupation: teacher

```

这是输出。

在本教程中，我们介绍了 Lodash JavaScript 库。

您可能也对以下相关教程感兴趣： [Ramda 教程](/javascript/ramda/)， [Collect.js 教程](/javascript/collectjs/)， [JSON Server 教程](/javascript/jsonserver/)， [Moment.js 教程](/javascript/momentjs/)，[从 JavaScript 中的 URL 读取 JSON](/articles/javascriptjsonurl/) ， [JavaScript Snake 教程](/javascript/snake/)， [JQuery 教程](/web/jquery/)， [jQuery Autocomplete 教程](/articles/jqueryautocomplete/)或[使用 jQuery DatePicker](/articles/jquerydatepicker/) 。
