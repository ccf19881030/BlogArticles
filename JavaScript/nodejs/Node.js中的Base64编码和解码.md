本文翻译自[Base64 Encoding and Decoding in Node.js](https://attacomsian.com/blog/nodejs-base64-encode-decode)

在上一篇文章中，我们研究了如何在[Java](https://attacomsian.com/bog/base64-encode-decode-java)和[JavaScript](https://attacomsian.com/blog/javascript-base64-encode-decode)中对Base64进行字符串编码和解码。今天，您将学习如何在Node.js应用程序中进行Base64编码和解码。

不幸的是，Node.js不支持用于Base64编码的标准JavaScript函数，例如`atob()`和`btoa()`。这些方法是窗口对象的一部分，仅在浏览器中可用。

幸运的是，Node.js提供了一个称为`Buffer`的本地模块，可用于执行Base64编码和解码。缓冲区可用作全局对象，这意味着您无需在应用程序中显式包含此模块。

在内部，`Buffer`以字节序列的形式表示二进制数据。 Buffer对象提供了几种方法来执行不同的编码和解码转换。这包括往返于UTF-8，UCS2，Base64，ASCII，UTF-16甚至HEX编码方案。

让我们看下面的示例，这些示例解释了如何使用`Buffer`对象在Node.js应用程序中执行Base64编码和解码。

## Base64 编码
要将字符串转换为Base64编码的字符串，我们首先需要使用`Buffer.from()`方法根据给定的字符串创建一个缓冲区。 此方法采用两个参数，即纯文本字符串和字符编码，并为给定的编码创建缓冲区或二进制数据数组。 如果未指定字符编码，则将使用UTF-8作为默认值。

这里有一个例子：
```js
// plain-text string
const str = 'Base64 Encoding in Node.js';

// create a buffer
const buff = Buffer.from(str, 'utf-8');

// encode buffer as Base64
const base64 = buff.toString('base64');

// print Base64 string
console.log(base64);

// QmFzZTY0IEVuY29kaW5nIGluIE5vZGUuanM=
```

在上面的示例中，我们从字符串创建了一个缓冲区，并使用`toString()`方法将缓冲区编码为Base64字符串。 当您处理纯文本（UTF-8）字符串时，`Buffer.from()`中的第二个参数是可选的。

## Base64解码
Base64解码过程与编码过程非常相似。 您需要做的就是通过使用base64作为`Buffer.from()`的第二个参数从`Base64`编码字符串中创建一个缓冲区，然后使用`toString()`方法将其解码为UTF-8字符串。

看起来是这样的：
```js
// Base64 encoded string
const base64 = 'QmFzZTY0IEVuY29kaW5nIGluIE5vZGUuanM=';

// create a buffer
const buff = Buffer.from(base64, 'base64');

// decode buffer as UTF-8
const str = buff.toString('utf-8');

// print normal string
console.log(str);

// Base64 Encoding in Node.js
```

## 结论
这就是Node.js中Base64编码和解码的全部内容。 我们研究了如何使用本机`Buffer`模块在Node.js应用程序中执行Base64编码和解码。 `Buffer`对象不仅限于Base64转换。 您甚至可以使用它执行ASCII，HEX，UTF-16和UCS2编码和解码。

如果您想了解有关JavaScript中Base64转换的更多信息，请参阅[本指南](https://attacomsian.com/blog/javascript-base64-encode-decode)。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

您可能还喜欢...
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
