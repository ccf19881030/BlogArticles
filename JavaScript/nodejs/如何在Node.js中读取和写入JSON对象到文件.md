本文翻译自[How to read and write a JSON object to a file in Node.js](https://attacomsian.com/blog/nodejs-write-json-object-to-file)

有时您想将`JSON`对象存储到Node.js应用程序中的文件中，然后在以后检索它。 例如，当您开始创建新的RESTful API时，将数据存储在本地文件系统上可能是一个不错的选择。 您可以跳过数据库设置，而是将JSON数据保存到文件中。

在本文中，您将学习如何在Node.js中`将JSON对象写入文件`。 在上一篇文章中，我们研究了如何[在Node.js中读写文件](https://attacomsian.com/blog/reading-writing-files-nodejs0。 如果您需要有关读写文件的更多信息，请查看一下。

## 将JSON写入文件
JavaScript提供了一个内置的·JSON对象，用于解析和序列化JSON数据。 您可以使用`JSON.stringify()`方法将JSON对象转换为其字符串表示形式，然后使用文件系统`fs`模块将·其写入文件。

这是一个使用`fs.writeFile()`方法将JSON对象异步写入文件的示例：
```js
const fs = require('fs');

// create a JSON object
const user = {
    "id": 1,
    "name": "John Doe",
    "age": 22
};

// convert JSON object to string
const data = JSON.stringify(user);

// write JSON string to a file
fs.writeFile('user.json', data, (err) => {
    if (err) {
        throw err;
    }
    console.log("JSON data is saved.");
});
```
[将JSON对象漂亮地打印](https://attacomsian.com/blog/javascript-pretty-print-json)到文件中，可以将其他参数传递给`JSON.stringify()`：
```js
// pretty-print JSON object to string
const data = JSON.stringify(user, null, 4);
```

`fs`模块还提供了一种称为`writeFileSync()`的方法，用于将数据同步写入文件：
```js
try {
    fs.writeFileSync('user.json', data);
    console.log("JSON data is saved.");
} catch (error) {
    console.error(err);
}
```
在Node.js中使用同步文件操作时要小心。 同步方法会阻塞Node.js事件循环，其他所有操作都必须等待文件操作完成。

## 从文件读取JSON
要将文件中的JSON数据检索并解析回JSON对象，可以使用`fs.readFile()`方法和`JSON.parse()`进行反序列化，如下所示：
```js
const fs = require('fs');

// read JSON object from file
fs.readFile('user.json', 'utf-8', (err, data) => {
    if (err) {
        throw err;
    }

    // parse JSON object
    const user = JSON.parse(data.toString());

    // print JSON object
    console.log(user);
});
```
上面的示例将在控制台上输出以下内容：
```
{ id: 1, name: 'John Doe', age: 22 }
```
就像`fs.writeFileSync()`方法一样，您也可以使用`fs.readFileSync()`在Node.js应用程序中同步读取文件。

看一下如何`在Node.js中读写JSON文件`的教程，以了解有关在Node.js应用程序中读写JSON文件的更多信息。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅`RSS Feed](https://feeds.feedburner.com/attacomsian)。

## 您可能还喜欢...
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
