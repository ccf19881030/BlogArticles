
本文翻译自[Reading and Writing Files in Node.js](https://attacomsian.com/blog/reading-writing-files-nodejs)

能够从本地文件系统上的文件进行读取和写入对于从JSON和XML文件记录，导出和导入数据，将数据从一个地方转移到另一个地方等等非常有用。

与其他任何编程语言一样，Node.js提供了用于处理操作系统文件的本机[fs模块](https://nodejs.org/api/fs.html)。 使用此模块，您可以轻松地读取，写入和观看文件以及许多其他内容。

在本教程中，我们将学习如何使用Node.js FS包从本地文件系统读取和写入文件。

`注意`：
无需安装。 由于fs是本机模块，因此不需要安装它。 只需通过调用const fs = require（'fs'）将其导入代码中即可。

`fs`模块为我们提供了异步和同步选项来处理文件：

- 同步选项将阻止代码执行，直到文件操作完成为止。
- 异步选项不会阻止代码的执行。 文件操作完成后，它将调用回调函数。

## 从文件读取
在Node.js中读取文件的最简单方法是使用`fs.readFile()`方法，该方法异步读取文件的全部内容。 它带有两个参数：文件路径和将与文件数据一起调用的回调函数：
```js
const fs = require('fs');

fs.readFile('file.txt', (err, data) => {
    if(err) {
        throw err;
    }
    console.log(data.toString());
});
```
回调函数传递了两个参数：`err`和`data`，其中`data`是文件的内容。 `err`对象包含有关运行时错误的信息（如果有）。

读取文件的另一种方法是使用称为`fs.readFileSync()`的`fs.readFile()`同步版本：
```js
const fs = require('fs');

try {
    const data = fs.readFileSync('file.txt');
    console.log(data.toString());
} catch (err) {
    console.error(err);
}
```
默认文件编码为`UTF-8`。 如果未指定编码，则返回原始缓冲区。 因此，如果您不想在终端中看到缓冲区已被打印出来，请在文件路径之后将文件编码指定为第二个参数：
```js
const fs = require('fs');

fs.readFile('file.txt', 'utf-8', (err, data) => {
    if(err) {
        throw err;
    }
    console.log(data);
});
```
`fs.readFile()`和`fs.writeFile()`函数均在调用回调函数之前读取内存中文件的全部内容。 因此，如果您正在读取一个大文件，则可能会影响您的内存消耗和程序执行。

对于大文件，最好使用[streams](https://nodejs.org/api/stream.html)来读取文件的内容。

## 写入文件
在Node.js中将数据写入文件的最简单方法是使用同一`fs`模块中的`fs.writeFile()`方法。 它使用三个参数-文件名，要写入的数据和一个回调函数-并异步写入数据：
```js
const fs = require('fs');

const data = "This is the new content of the file.";

fs.writeFile('file.txt', data, (err) => {
    if(err) {
        throw err;
    }
    console.log("Data has been written to file successfully.");
});
```

注意：
创建新文件：上面的示例将自动为您创建一个新文件（如果不存在）。 这对于创建新文件然后一次写入就特别有用。

`fs.writeFileSync()`是此方法的另一个版本，用于同步写入文件：
```js
const fs = require('fs');

const data = "This is the new content of the file.";

try {
    fs.writeFileSync('file.txt', data);
    console.log("File has been saved.");
} catch (error) {
    console.error(err);
}
```
默认情况下，这些方法将覆盖文件的内容（如果已存在）。 如果要将数据追加到文件，则应传递一个标志作为第三个参数：
```js
const fs = require('fs');

const data = "Append this data at the end of the file.";

fs.writeFile('file.txt', data, {flag: 'a+'}, (err) => {
    if (err) {
        throw err;
    }
    console.log("File is updated.");
});
```

您最可能使用的一些标志选项：

- r —以只读模式打开文件。如果文件不存在，则会引发异常。
- r+ —打开文件进行读写。如果文件不存在，则会引发异常。
- w —以只写模式打开文件。文件已创建（仅当尚不存在时）或被截断（如果存在）。
- w+ —打开文件进行读写，将流放在文件的开头。如果不存在，则创建该文件。
+ a —打开要附加的文件，将流放在文件末尾。如果不存在，则创建该文件。
- a+ —打开文件进行读取和追加，将流放在文件末尾。如果文件不存在，则会创建该文件。
在将控制返回到程序之前，这两种方法都将继续写入文件，直到写入了全部内容。如果要写入大量数据，则可能会影响应用程序性能。

在这种情况下，更好的方法是使用流来写入大文件。

## 附加到文件
除了使用标志在文件末尾附加数据之外，`fs`模块还提供了`fs.appendFIle()`（和`fs.appendFIleSync()`用于同步）方法，该方法异步将数据附加到文件，如果尚未创建文件，则创建文件 存在：
```js
const fs = require('fs');

const data = "Some data to append";

fs.appendFile('file.txt', data, (err) => {
    if (err) {
        throw err;
    }
    console.log("File is updated.");
});
```

## 错误处理
如果在读取或写入文件时出现运行时错误，则以Error对象作为第一个参数调用回调方法。

处理运行时错误的最简单方法是将它们作为我们上面使用的Node.js异常抛出。 但是，这会使应用程序崩溃，因此，除非您没有其他选择，否则不建议这样做：
```js
const fs = require('fs');

fs.readFile('404.txt', 'utf-8', (err, data) => {
    if (err) {
        console.error(err);
        // log the error here
    }
    console.log(data);
});
```

现在，如果执行上述代码，您将在终端上看到类似以下内容的内容：

```js
{ [Error: ENOENT: no such file or directory, open '404.txt'] 
    errno: -2, 
    code: 'ENOENT', 
    syscall: 'open', 
    path: '404.txt' }
undefined
```

## 结论
这就是使用Node.js本机`fs`模块读写文件的全部内容。 希望本教程对您有所帮助。 如果您有任何疑问或意见，可以随时在·Twitter·上与我[联系](https://twitter.com/attacomsian)。

## 进一步阅读
如果您喜欢阅读本文，则可能还喜欢其他一些文章：
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Reading a file line by line in Node.js](https://attacomsian.com/blog/reading-a-file-line-by-line-in-nodejs)
- [How to write a JSON object to a file in Node.js](https://attacomsian.com/blog/nodejs-write-json-object-to-file)
- [Making HTTP Requests using Axios in Node.js](https://attacomsian.com/blog/http-requests-axios)
- [Uploading Files in Node.js and Express](https://attacomsian.com/blog/uploading-files-nodejs-express)
- [7 Ways to Make HTTP Requests in Node.js](https://attacomsian.com/blog/http-requests-in-nodejs)

再见，下次！

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

上次更新时间：2020年9月19日

Node.js

您可能还喜欢...
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)






