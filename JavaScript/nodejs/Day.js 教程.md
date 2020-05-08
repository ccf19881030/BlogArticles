# Day.js 教程

> 原文： [http://zetcode.com/javascript/dayjs/](http://zetcode.com/javascript/dayjs/)

Day.js 教程展示了如何通过 Day.js 模块在 JavaScript 中使用日期和时间。

## Day.js

Day.js 是用于解析，验证，操作和格式化日期的极简 JavaScript 日期库。 它是 Moment.js 的替代库，并且具有兼容的 API。 Moment.js 在 [Moment.js 教程](/javascript/momentjs/)中进行了介绍。

在本教程中，我们在 Node 应用中使用 Day.js。

## 安装 Day.js

首先，我们安装 Day.js。

```js
$ node -v
v11.5.0

```

我们使用 Node 版本 11.5.0。

```js
$ npm init -y

```

我们启动一个新的 Node 应用。

```js
$ npm i dayjs 

```

我们使用`npm i dayjs` 命令安装 Day.js。

## Day.js 今天的日期

在第一个示例中，我们使用 Day.js 获取今天的日期。

`now.js`

```js
const dayjs = require('dayjs');

let now = dayjs();

console.log(now.format());

```

该示例显示当前日期时间。

```js
const dayjs = require('dayjs');

```

我们加载 Day.js 库。

```js
let now = dayjs();

```

我们使用`dayjs()`获得当前本地日期时间对象。

```js
console.log(now.format());

```

我们使用`format()`格式化输出。 默认情况下，我们使用长日期时间格式。

```js
$ node now.js
2019-05-14T10:12:54+02:00

```

输出为 ISO 标准格式。 日期时间部分用 T 字符分隔。 该字符串以时区结尾。

## 创建 Day.js 对象

我们可以使用几种方法来创建日期时间 Day.js 对象。 这些对象被格式化为人类可读的输出。

`create_objects.js`

```js
const dayjs = require('dayjs');

let d1 = dayjs("2018-06-03");
console.log(d1.format());

let d2 = dayjs.unix(1530471537);
console.log(d2.format());

let d3 = dayjs(new Date(2011, 11, 22));
console.log(d3.format());

```

该示例以三种不同方式创建日期和时间对象。

```js
let d1 = dayjs("2018-06-03");

```

我们通过解析字符串创建一个 dayjs 对象。

```js
let d2 = dayjs.unix(1530471537);
console.log(d2.format());

```

我们使用 unix 时间戳（以秒为单位）定义日期时间对象。

```js
let d3 = dayjs(new Date(2011, 11, 22));
console.log(d3.format());

```

最后，我们使用 JavaScript 内置的 Date 对象来定义 dayjs 对象。

```js
$ node create_objects.js
2018-06-03T00:00:00+02:00
2018-07-01T20:58:57+02:00
2011-12-22T00:00:00+01:00

```

这是输出。

## Day.js 格式化日期时间

Day.js 对象使用`format()`函数格式化。

`formatting.js`

```js
const dayjs = require('dayjs');

let now = dayjs();

console.log("ISO")
console.log(now.format());

console.log("\nTime")
console.log(now.format("HH:mm:ss"));
console.log(now.format("h:mm:ss a"));

console.log("\nDate")
console.log(now.format("dddd, MMMM D YYYY"));
console.log(now.format("YYYY-MM-DD"));

```

使用日的`format()`函数的示例格式的日期和时间。

```js
$ node formatting.js
ISO
2019-05-14T10:19:18+02:00

Time
10:19:18
10:19:18 am

Date
Tuesday, May 14 2019
2019-05-14

```

这是一个示例输出。

## Day.js 计算日期时间差

使用`diff()`函数，我们可以计算两个日期时间对象之间的差。

`difference.js`

```js
const dayjs = require('dayjs');

const date1 = dayjs("2019-14-05");
const date2 = dayjs("2018-06-25");

let df1 = date1.diff(date2); 
console.log(df1);

let df2 = date1.diff(date2, "month"); 
console.log(df2);

let df3 = date1.diff(date2, "month", true); 
console.log(df3);

let df4 = date1.diff(date2, "day"); 
console.log(df4);

let df5 = date1.diff(date2, "week"); 
console.log(df5);

```

该示例以月，日和周为单位计算两个 dayjs 对象之间的差异。

```js
let df2 = date1.diff(date2, "month"); 
console.log(df2);

```

第二个参数表明输出将以月为单位。

```js
let df3 = date1.diff(date2, "month", true); 
console.log(df3);

```

将第三个参数设置为`true`会返回浮点值，例如 7.3 个月

```js
$ node difference.js
19357200000
7
7.3
224
32

```

这是输出。

Borodino 战役是 1812 年 9 月 7 日在法国入侵俄罗斯期间的拿破仑战争中进行的战斗。

`borodino.js`

```js
const dayjs = require('dayjs');

let borodinoBattle = dayjs('1812-09-07');

let now = dayjs();
let days = now.diff(borodinoBattle, 'days');

console.log(`On ${now.format('YYYY-MM-DD')}, ${days} days have passed since the Borodino battle.`);

```

在示例中，我们计算了自著名战斗以来经过的天数。

```js
$ node borodino.js
On 2019-05-14, 75489 days have passed since the Borodino battle.

```

这是一个示例输出。

## Day.js 日期时间算法

`add()`函数用于将日期和时间添加到 dayjs 对象，`subtract()`函数用于从 dayjs 对象中减去日期和时间。

`arithm.js`

```js
const dayjs = require('dayjs');

let now = dayjs();

console.log(now.format('YYYY-MM-DD'));

let d1 = now.add('14', 'day');

console.log(d1.format('YYYY-MM-DD'));

let d2 = now.subtract('3', 'year');

console.log(d2.format('YYYY-MM-DD'));

```

在示例中，我们将十四天加上当前日期时间，再减去两年。

```js
let d1 = now.add('14', 'day');
...
let d2 = now.subtract('3', 'year'););

```

`add()`和`subtract()`函数的第二个参数是单位类型。

```js
$ node arithm.js
2019-05-14
2019-05-28
2016-05-14

```

这是输出。

## Day.js 日期时间部分

在下面的示例中，我们获取了当前日期时间的部分。

`parts.js`

```js
const dayjs = require('dayjs');

let now = dayjs();

console.log(now.toObject());

let year = now.year();
console.log(`Year: ${year}`);

let month = now.month();
console.log(`Month: ${month}`);

let date = now.date();
console.log(`Date: ${date}`);

let hour = now.hour();
console.log(`Hour: ${hour}`);

let minute = now.minute();
console.log(`Minute: ${minute}`);

let second = now.second();
console.log(`Second: ${second}`);

let milli = now.millisecond();
console.log(`Millisecond: ${milli}`);

```

该示例计算当前日期时间。 我们获得日期时间的年，月，日，时，分，秒和毫秒部分。 `toObject()`函数返回带有日期时间部分的 JavaScript 对象。

```js
$ node parts.js
{ years: 2019,
  months: 4,
  date: 14,
  hours: 10,
  minutes: 41,
  seconds: 34,
  milliseconds: 963 }
Year: 2019
Month: 4
Date: 14
Hour: 10
Minute: 41
Second: 34
Millisecond: 963

```

这是一个示例输出。

## Day.js 转换函数

除了`format()`函数外，我们还可以使用一些内置的转换函数。

`converting.js`

```js
const dayjs = require('dayjs');

let now = dayjs();

console.log(now.toString());
console.log(now.toJSON());
console.log(now.toISOString());
console.log(now.toObject());

```

我们有四个函数。 `toJSON()`是`toISOString()`的别名。

```js
$ node converting.js
Tue, 14 May 2019 09:00:51 GMT
2019-05-14T09:00:51.157Z
2019-05-14T09:00:51.157Z
{ years: 2019,
    months: 4,
    date: 14,
    hours: 11,
    minutes: 0,
    seconds: 51,
    milliseconds: 157 }

```

这是输出。

## Day.js 相对日期时间

我们可以使用`startOf()`和`endOf()`函数计算相对日期时间。

`relative_time.js`

```js
const dayjs = require('dayjs');

// let now = dayjs();

let startWeek = dayjs().startOf('week');
console.log(startWeek.format());

let endWeek = dayjs().endOf('week');
console.log(endWeek.format());

let startMonth = dayjs().startOf('month');
console.log(startMonth.format());

let endMonth = dayjs().endOf('month');
console.log(endMonth.format());

let startYear = dayjs().startOf('year');
console.log(startYear.format());

let endYear = dayjs().endOf('year');
console.log(endYear.format());

```

该示例使用上述函数。

```js
let startWeek = dayjs().startOf('week');
console.log(startWeek.format());

```

在这里，我们计算当前星期开始的日期时间。

```js
let endYear = dayjs().endOf('year');
console.log(endYear.format());

```

在这里，我们获取一年中的最后一个日期时间。

```js
$ node relative_time.js
2019-05-12T00:00:00+02:00
2019-05-18T23:59:59+02:00
2019-05-01T00:00:00+02:00
2019-05-31T23:59:59+02:00
2019-01-01T00:00:00+01:00
2019-12-31T23:59:59+01:00

```

这是输出。

## Day.js 检查有效性

我们可以使用`isValid()`函数检查日期和时间对象是否有效。

`validating.js`

```js
const dayjs = require('dayjs');

let day1 = dayjs('2018-12-12');
let day2 = dayjs('2018-11-ks');

if (day1.isValid()) {

    console.log("Day is valid");
    console.log(day1.format());
} else {

    console.log("Day is not valid");
}

if (day2.isValid()) {

    console.log("Day is valid");
    console.log(day2.format());
} else {

    console.log("Day is not valid");
}

```

该示例检查两天的有效性。

## Day.js 日期查询

`isSame()`，`isBefore()`和`isAfter()`函数可用于确定某个日期是在另一个日期之前还是之后。

`queries.js`

```js
const dayjs = require('dayjs');

let d1 = dayjs("2018-05-19");
let d2 = dayjs("2018-05-20");
let d3 = dayjs("2018-05-22");
let d4 = dayjs("2018-05-19");

if (d1.isSame(d4)) {

    console.log('these are same dates');
} else {

    console.log('these are not the same dates');
}

if (d1.isAfter(d2)) {

    console.log(`${d1.format('YYYY-MM-DD')} is after ${d2.format('YYYY-MM-DD')}`);
} else {

    console.log(`${d1.format('YYYY-MM-DD')} is before ${d2.format('YYYY-MM-DD')}`);
}

if (d2.isBefore(d3)) {

    console.log(`${d2.format('YYYY-MM-DD')} is before ${d3.format('YYYY-MM-DD')}`);
} else {

    console.log(`${d2.format('YYYY-MM-DD')} is after ${d3.format('YYYY-MM-DD')}`);
}

```

在示例中，我们比较了三个日期。

```js
$ node queries.js
these are same dates
2018-05-19 is before 2018-05-20
2018-05-20 is before 2018-05-22

```

这是输出。

`isBetween()`函数检查日期是否在给定的日期范围内。

`between.js`

```js
const dayjs = require('dayjs');

const isBetween = require('dayjs/plugin/isBetween');

dayjs.extend(isBetween);

let d1 = dayjs("2018-05-19");

if (d1.isBetween('2018-05-10', '2018-05-25')) {

    console.log("The day is within the date range");
} else {

    console.log("The day is not within the date range");
}

```

该示例使用`isBetween()`函数来确定日期是否在指定的日期范围内。 对于此示例，我们需要`isBetween`插件。

## Day.js Unix 时间

Unix 时间是自 Unix 时代以来的秒数。 `unix()`函数返回自世界标准时间 1970 年 1 月 1 日 0 小时 0 分 0 秒以来的秒数。

`unixtime.js`

```js
const dayjs = require('dayjs');

let unixTime_s = dayjs().unix();
console.log(unixTime_s);

let unixTime_ms = dayjs().valueOf();
console.log(unixTime_ms);

let unixTime2 = dayjs(1);
console.log(unixTime2.format('YYYY-DD-MM'));

```

在该示例中，我们获得了当前的 unix 时间并将 unix 时间 1 s 转换为人类可读的格式。

```js
let unixTime_s = dayjs().unix();

```

我们通过`unix()`函数获得 Unix 时间。 返回的值是从 Unix 纪元开始起经过的秒数。

```js
let unixTime_ms = dayjs().valueOf();

```

使用`valueOf()`函数，我们可以得到以毫秒为单位的 Unix 时间。

```js
let unixTime2 = dayjs(1);
console.log(unixTime2.format('YYYY-DD-MM'));

```

我们得到 1 秒的 unix 时间，并以给定的格式输出。

```js
$ node unix_time.js
1557825803
1557825803834
1970-01-01

```

这是一个示例输出。

## Day.js 闰年

闰年是包含另一天的一年。 日历中额外一天的原因是天文日历年与日历年之间的差异。 我们需要添加`isLeapYear`插件。

`leap_year.js`

```js
const dayjs = require('dayjs');
const isLeapYear = require('dayjs/plugin/isLeapYear');

dayjs.extend(isLeapYear)

// Assume year >= 1582 in the Gregorian calendar.

let years = [ 2000, 2002, 2004, 2008, 2012, 2016, 2020,
    1900, 1800, 1600 ];

for (year of years) {

    let ym = dayjs([year]);

    if (ym.isLeapYear()) {

        console.log(`${year} is a leap year`);
    } else {

        console.log(`${year} is not a leap year`);
    }
}

```

在示例中，我们有很多年。 我们确定哪些年份是 leap 年。

```js
if (ym.isLeapYear()) {

```

我们使用`isLeapYear()`函数确定年份是否为 a 年。

```js
$ node leap_year.js
2000 is a leap year
2002 is not a leap year
2004 is a leap year
2008 is a leap year
2012 is a leap year
2016 is a leap year
2020 is a leap year
1900 is not a leap year
1800 is not a leap year
1600 is a leap year

```

这是输出。

在本教程中，我们使用`Day.js`库在 JavaScript 中使用日期和时间。

您可能也对以下相关教程感兴趣： [Moment.js 教程](/javascript/momentjs/)，或列出[所有 JavaScript 教程](/all/#js)。
