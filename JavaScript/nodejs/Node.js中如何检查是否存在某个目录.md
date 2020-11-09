Node.js `fs`本地模块提供了几种有用的方法，可用于处理目录。 检查Node.js中是否存在某个目录的最简单方法是使用`fs.existsSync()`方法。

`existSync()`方法同步检查给定目录的存在。 这是一个例子：
```js
const fs = require('fs');

// directory to check if exists
const dir = './uploads';

// check if directory exists
if (fs.existsSync(dir)) {
    console.log('Directory exists!');
} else {
    console.log('Directory not found.');
}
```
如果路径存在，则`existSync()`方法返回`true`，否则返回`false`。

如果您更喜欢使用异步检查，请改用`fs.access()`方法。 此方法将路径作为输入并测试用户的权限。

让我们看下面的示例，该示例使用`fs.access()`检查给定目录是否存在：
```js
const fs = require('fs');

// directory to check if exists
const dir = './uploads';

// check if directory exists
fs.access(dir, (err) => {
    console.log(`Directory ${err ? 'does not exist' : 'exists'}`);
});
```
查看[本指南](https://attacomsian.com/blog/reading-writing-files-nodejs)，以了解有关在Node.js应用程序中读写文件的更多信息。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

上次更新时间：2020年4月10日

您可能还喜欢...
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
