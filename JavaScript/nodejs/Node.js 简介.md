# Node.js 简介

> 原文： [http://zetcode.com/javascript/nodejs/](http://zetcode.com/javascript/nodejs/)

Node.js 教程是 Node.js 的入门教程。 我们描述 Node.js 并提供一些 Node.js 代码示例。

## Nojde.js

Node.js 是一个开源，跨平台的 JavaScript 运行时环境。 它基于 Chrome 的 V8 JavaScript 引擎构建。 Node.js 使用事件驱动的非阻塞 I / O 模型，从而使其轻巧高效。 Node.js 最初由 Ryan Dahl 在 2009 年编写。

Node.js 提供了各种 JavaScript 模块的丰富库，例如用于文件系统的`fs`或用于 HTTP 请求和响应的`http`。

Node.js 应用是用 JavaScript 编写的，可以在 OS X，Microsoft Windows 和 Linux 上的 Node.js 运行时中运行。

Node.js 有一个名为`npm`的程序包管理器，它是一个庞大的开源 JavaScript 库生态系统。

## Node.js 安装

我们安装了最新版本的 Node.js。 Node.js 版本 9 实现了大多数 ECMAScript 6 规范。 请遵循适用于您平台的 Node.js 网站上提供的安装说明。

```js
$ curl -sL https://deb.nodesource.com/setup_9.x | sudo -E bash -
$ sudo apt-get install -y nodejs

```

这就是我们在 Debian Linux 上安装 Node.js 的方式。

```js
$ nodejs -v
v9.11.1

```

我们显示 Node.js 的版本。

## Node.js 第一个示例

我们创建一个简单的控制台应用。

`first.js`

```js
console.log("This is our first application");

```

该程序将消息打印到控制台。

```js
$ node first.js 
This is our first application

```

这是输出。

## Node.js 读取文件内容

Node.js 包含用于处理文件的`fs`模块。

`words.txt`

```js
blue
book
pen
dog
computer
screen

```

我们有一个文本文件。

Node.js 中的大多数功能都是异步的。 是非阻塞的； 也就是说，它们不会阻止脚本的执行。

`read_file.js`

```js
const fs = require('fs')

fs.readFile('words.txt', 'utf-8', (err, data) => {
    if (err) throw err;
    console.log(data);
});

console.log("Script continues...")

```

该示例读取`words.txt`文件的内容。

```js
const fs = require('fs');

```

我们加载`fs`模块。

```js
fs.readFile('words.txt', 'utf-8', (err, data) => {

```

`readFile()`异步读取文件的全部内容。 我们在方法的第二个参数中指定编码。

```js
$ node read_file.js 
Script continues
blue
book
pen
dog
computer
screen

```

这是输出。 文件内容之前显示“脚本继续”。

## Node.js 同步读取目录

现在，我们将读取目录的内容。

`readdir_syn.js`

```js
const fs = require('fs');

readDirContentSync('.');

console.log("Ready.");

function readDirContentSync(mydir) {

    const filenames = fs.readdirSync(mydir);

    for (var i = 0; i < filenames.length; i++) {
        console.log(filenames[i]);
    }
}

```

该代码示例同步读取目录的内容。

```js
const filenames = fs.readdirSync(mydir);

```

我们与`readdirSync()`同步读取目录。

```js
for (var i = 0; i < filenames.length; i++) {
    console.log(filenames[i]);
}

```

我们遍历文件名数组，并将它们打印到控制台。

```js
$ node readdir_syn.js 
builtins.js
first.js
links
read_file.js
readdir_asyn.js
readdir_syn.js
server.js
todo
words.txt
Ready.    

```

通过同步功能调用，“就绪”。 函数完成执行后，显示消息。

## Node.js 异步读取目录

在下一个示例中，我们异步读取目录。

`readdir_async.js`

```js
var fs = require('fs');

fs.readdir(".", (err, filenames) => {

    for (var i = 0; i < filenames.length; i++) {
        console.log(filenames[i]);
    }

    console.log("Ready.");
});

```

`readdir()`异步读取当前工作目录的内容。 它用目录中文件的名称（不包括“。”）填充数组。 和“ ..”。

## Node.js 读取网页

在下面的示例中，我们使用内置的`http`模块读取网页。

`read_page.js`

```js
const http = require('http');

const request = http.request({ hostname: 'www.something.com' }, (res) => {

    res.setEncoding('utf8');
    res.on('data', (chunk) => {

        console.log(chunk);
    });
});

request.end();

request.on('error', (err) => {

    console.log("Error occured\n");
    console.error(err);
});

```

在示例中，我们使用`http`模块创建对小型网页的请求。 返回的 HTML 页面将打印到控制台。

```js
$ node read_site.js 
<html><head><title>Something.</title></head>
<body>Something.</body>
</html>

```

我们已经收到了这个小的 HTML 页面。

## 使用`npm`安装 Node.js 模块

可以使用`npm`（节点软件包管理器）安装其他模块。 现在，我们将安装一个名为`builtin-modules`的新模块。 通过此模块，我们将列出所有可用的 Node.js 内置模块。

```js
$ mkdir builtmodtest
$ cd builtmodtest/
$ npm init

```

我们创建一个新的项目目录。 使用`npm init`命令创建一个`package.json`文件。 它包含与项目相关的元数据，例如应用名称，作者或依赖项。

```js
$ cat package.json    
{
    "name": "builtmodtest",
    "version": "1.0.0",
    "description": "Testing builtin modules",
    "main": "main.js",
    "scripts": {
        "start": "node main.js"
    },
    "author": "Jan Bodnar",
    "license": "ISC"
}

```

这是初始的`package.json`文件。 我们选择了`main.js`作为主文件。

```js
$ npm install builtin-modules
$ tree -L 1
.
├── main.js
├── node_modules
├── package.json
└── package-lock.json

```

使用`npm install builtin-modules`，我们可以在本地安装`builtin-modules`模块。 创建一个新的`node_modules`目录，在其中存储模块及其依赖项。 npm 自动创建了一个`package-lock.json`文件。 它用于确保队友，部署和持续集成的依赖性安装的一致性。 该文件必须提交到源存储库。

```js
$ cat package.json 
{
  "name": "builtmodtest",
  "version": "1.0.0",
  "description": "Testing builtin modules",
  "main": "main.js",
  "scripts": {
    "start": "node main.js"
  },
  "author": "Jan Bodnar",
  "license": "ISC",
  "dependencies": {
    "builtin-modules": "^2.0.0"
  }
}

```

`builtin-modules`也被写入`package.json`文件。

`main.js`

```js
const builtmods = require('builtin-modules');

console.log(builtmods);

```

这是`main.js`文件。 它将所有内置模块打印到控制台。

```js
$ npm start

> builtmod@1.0.0 start /home/janbodnar/prog/nodejs/builtmod
> node main.js

[ 'assert',
  'async_hooks',
  'buffer',
  'child_process',
  'cluster',
  'config',
  'console',
  'constants',
...
]

```

这是程序的输出。

## Node.js 服务器

我们使用 Node.js `http`模块创建一个简单的服务器。

`server.js`

```js
const http = require('http');

const server = http.createServer((req, res) => {

    res.writeHead(200, {"Content-Type": "text/plain"});
    res.end("Hello there\n");
});

server.listen(8000);

console.log("Server running at http://127.0.0.1:8000/");

```

服务器向客户端发送一条简单的文本消息。

```js
const http = require('http');

```

我们加载`http`模块以创建 http 服务器。

```js
const server = http.createServer((req, res) => {

    res.writeHead(200, {"Content-Type": "text/plain"});
    res.end("Hello there\n");
});

```

服务器已创建。 它向客户端发送一条短信。

```js
server.listen(8000);

```

服务器侦听 localhost 上的端口 8000。

```js
$ node server.js &
$ curl localhost:8000
Hello there

```

我们运行服务器并使用`curl`创建一个请求。

在本教程中，我们介绍了 Node.js。 我们已经使用 Node.js 创建了一些代码示例。

您可能也对以下相关教程感兴趣： [JSON 服务器教程](/javascript/jsonserver/)， [Liquid.js 教程](/javascript/liquidjs/)，[从 JavaScript 中的 URL 读取 JSON](/articles/javascriptjsonurl/) ， [JavaScript Snake 教程](/javascript/snake/)， [jQuery 教程](/web/jquery/)， [Lodash 教程](/javascript/lodash/)， [jQuery Autocomplete 教程](/articles/jqueryautocomplete/)或[使用 jQuery DatePicker](/articles/jquerydatepicker/) 。
