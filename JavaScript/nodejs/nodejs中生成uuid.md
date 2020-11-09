nodejs中有一个uuid的生成库uuid：[https://www.npmjs.com/package/uuid](https://www.npmjs.com/package/uuid),使用起来非常简单。

## 快速开始
要创建随机UUID，可以使用`npm`或者`yarn`安装`uuid`库

### 1.使用npm或者yarn安装uuid
```
npm install uuid --save
```
或者
```
yarn add uuid
```

### 2.创建一个UUID（ES6模块语法）

```js
import { v4 as uuidv4 } from 'uuid';
uuidv4(); // ⇨ '9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d'
```
或使用CommonJS语法：
```js
const { v4: uuidv4 } = require('uuid');
uuidv4(); // ⇨ '1b9d6bcd-bbfd-4b2d-9b5d-ab8dfbbd4bed'
```
对于时间戳UUID，名称空间UUID和其他选项，请阅读...

### API摘要
方法     | 功能 | 备注
-------- | ----- |  -----
uuid.NIL	| The nil UUID string (all zeros)	New in uuid@8.3
uuid.parse()	|  Convert UUID string to array of bytes	| New in uuid@8.3
uuid.stringify() |	Convert array of bytes to UUID string	| New in uuid@8.3
uuid.v1()	| Create a version 1 (timestamp) UUID	
uuid.v3()	| Create a version 3 (namespace w/ MD5) UUID	
uuid.v4()	| Create a version 4 (random) UUID	
uuid.v5()	| Create a version 5 (namespace w/ SHA-1) UUID	
uuid.validate() |	Test a string to see if it is a valid UUID	| New in uuid@8.3
uuid.version()	| Detect RFC version of a UUID	| New in uuid@8.3

### API
- uuid.NIL
nil UUID字符串（全零）。
示例：
```js
import { NIL as NIL_UUID } from 'uuid';
 
NIL_UUID; // ⇨ '00000000-0000-0000-0000-000000000000'
```

- uuid.parse(str)
将UUID字符串转换为字节数组


字段 | 说明
-------- | -----
str	|  A valid UUID String
returns | 	Uint8Array[16]
throws	| TypeError if str is not a valid UUID

注意：parse()和stringify()使用的字节数组中的值的顺序遵循UUID字符串中十六进制对的从左往右的顺序。 如下例所示。

示例：
```js
import { parse as uuidParse } from 'uuid';
 
// Parse a UUID
const bytes = uuidParse('6ec0bd7f-11c0-43da-975e-2a8ad9ebae0b');
 
// Convert to hex strings to show byte order (for documentation purposes)
[...bytes].map((v) => v.toString(16).padStart(2, '0')); // ⇨ 
  // [
  //   '6e', 'c0', 'bd', '7f',
  //   '11', 'c0', '43', 'da',
  //   '97', '5e', '2a', '8a',
  //   'd9', 'eb', 'ae', '0b'
  // ]
  ```
  其他关于`uuid`库的方法的使用，具体参考npm官网：[https://www.npmjs.com/package/uuid](https://www.npmjs.com/package/uuid)

## 生成uuid字符串后将其中的-去掉
当使用nodejs中的[uuid](https://www.npmjs.com/package/uuid)库生成了`1b9d6bcd-bbfd-4b2d-9b5d-ab8dfbbd4bed`这种格式的uuid字符串后，有时候我们需要把中间的`-`字符去掉，这时候可以使用`string`的`replace`方法：
```js
const { v4: uuidv4 } = require('uuid');
let strUUID = uuidv4(); // ⇨ '1b9d6bcd-bbfd-4b2d-9b5d-ab8dfbbd4bed'
let strUUID2 = strUUID.replace(/-/g, '');       // 去掉-字符，使用空格代替
```
![CentOS7下的测试结果](https://img-blog.csdnimg.cn/20201105173101911.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

## 参考资料
- [https://www.npmjs.com/package/uuid](https://www.npmjs.com/package/uuid)
- [nodejs 使用uuid](https://www.jianshu.com/p/1fb4be4f9d5d)
- [NPM酷库：uuid，生成随机ID](https://segmentfault.com/a/1190000012903633)
- [js正则表达式替换空格](https://www.cnblogs.com/zhn0823/p/5890686.html)
