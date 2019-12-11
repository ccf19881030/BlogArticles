## [Moment.js-JavaScript 日期处理类库](http://momentjs.cn)
### 安装
```shell
bower install moment --save # bower
npm install moment --save   # npm
Install-Package Moment.js   # NuGet
spm install moment --save   # spm
meteor add momentjs:moment  # meteor
```

### 日期格式化
```javascript
moment().format('MMMM Do YYYY, h:mm:ss a'); // 十二月 11日 2019, 3:47:37 下午
moment().format('dddd');                    // 星期三
moment().format("MMM Do YY");               // 12月 11日 19
moment().format('YYYY [escaped] YYYY');     // 2019 escaped 2019
moment().format();                          // 2019-12-11T15:47:37+08:00
```

### 相对时间
```javascript
moment("20111031", "YYYYMMDD").fromNow(); // 8 年前
moment("20120620", "YYYYMMDD").fromNow(); // 7 年前
moment().startOf('day').fromNow();        // 16 小时前
moment().endOf('day').fromNow();          // 8 小时内
moment().startOf('hour').fromNow();       // 1 小时前
```

### 日历时间
```javascript
moment().subtract(10, 'days').calendar(); // 2019年12月1日
moment().subtract(6, 'days').calendar();  // 上周四下午3点49
moment().subtract(3, 'days').calendar();  // 上周日下午3点49
moment().subtract(1, 'days').calendar();  // 昨天下午3点49分
moment().calendar();                      // 今天下午3点49分
moment().add(1, 'days').calendar();       // 明天下午3点49分
moment().add(3, 'days').calendar();       // 本周六下午3点49
moment().add(10, 'days').calendar();      // 2019年12月21日
```

### 多语言支持
```javascript
moment().format('L');    // 2019-12-11
moment().format('l');    // 2019-12-11
moment().format('LL');   // 2019年12月11日
moment().format('ll');   // 2019年12月11日
moment().format('LLL');  // 2019年12月11日下午3点49分
moment().format('lll');  // 2019年12月11日下午3点49分
moment().format('LLLL'); // 2019年12月11日星期三下午3点49分
moment().format('llll'); // 2019年12月11日星期三下午3点49分
```
