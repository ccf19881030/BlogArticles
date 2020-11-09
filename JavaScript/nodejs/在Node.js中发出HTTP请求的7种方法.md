本文翻译自[7 Ways to Make HTTP Requests in Node.js](https://attacomsian.com/blog/http-requests-in-nodejs)

HTTP请求是大多数现代语言的核心部分。 对于新开发人员而言，学习如何发出HTTP请求以交换数据可能是具有挑战性的。 幸运的是，对于Node.js开发人员而言并非如此。 有许多经过考验的解决方案可用于发出任何种类的HTTP请求。 让我们看一下一些支持HTTP请求的最受欢迎的Node.js库。

出于测试目的，我们将为所有示例使用`JSONPlaceholder`假的todo REST API。 我们的REST API返回以下JSON响应：
```json
{
  "userId": 1,
  "id": 1,
  "title": "delectus aut autem",
  "completed": false
}
```

在继续之前，请确保已在计算机上安装了最新的LTS版本的[Node.js和npm](https://attacomsian.com/blog/install-nodejs-npm-ubuntu)。

## 1.HTTP —标准HTTP库
`HTTP`和`HTTPS`模块都打包在标准库中。 使用这些模块，您可以轻松地发出HTTP请求，而无需安装外部软件包。 但是，不幸的是，这些是低级模块，与其他解决方案相比，它们不是很友好。
```js
const https = require('https');

https.get('https://jsonplaceholder.typicode.com/todos/1', (response) => {
  let todo = '';

  // called when a data chunk is received.
  response.on('data', (chunk) => {
    todo += chunk;
  });

  // called when the complete response is received.
  response.on('end', () => {
    console.log(JSON.parse(todo).title);
  });

}).on("error", (error) => {
  console.log("Error: " + error.message);
});
```

`注意`：
有关更多HTTPS模块示例，请查看教程中的[本机Node.js发出HTTP请求](https://attacomsian.com/blog/node-make-http-requests)。

## 2.Request
[Request](https://github.com/request/request)是简化的HTTP客户端，与默认的HTTP模块相比，它更加用户友好。 它在社区中非常流行，并且被认为是Node.js项目的HTTP客户端。

与`HTTP`模块不同，您需要使用以下命令从Node Package Manager（npm）将其安装为依赖项：
```shell
$ npm install request --save
```
以下是使用`request` HTTP客户端调用我们伪造的REST API的示例代码片段：
```js
const request = require('request');

request('https://jsonplaceholder.typicode.com/todos/1', { json: true }, (err, res, body) => {
  if (err) { 
      return console.log(err); 
  }
  console.log(body.id);
  console.log(body.title);
});
```

`注意`:
有关更多请求模块示例，请参阅[使用Request模块发出HTTP请求](https://attacomsian.com/blog/node-http-requests-using-request-module)指南。

## 3.Needle
[Needle](https://github.com/tomas/needle)是Node.js的可流HTTP客户端，它支持`proxy,` `iconv`, `cookie`, `deflate` and `multi-part`。 要从`npm`安装`Needle`，请在终端中运行以下命令：
```npm
$ npm install needle --save
```

以下代码段将执行调用伪造的REST API并打印详细信息的相同任务：
```js
const needle = require('needle');

needle.get('https://jsonplaceholder.typicode.com/todos/1', {json: true}, (err, res) => {
    if (err) { 
          return console.log(err); 
      }
    let todo = res.body;
    console.log(todo.id);
    console.log(todo.title);
});
```

从`2.0.x`版开始，`Needle`还支持`Promises`。 对于编写涉及一系列事件的更复杂的代码，[Promises](https://www.promisejs.org/)是很好的。 上面的代码片段可以使用`Promises`编写，如下所示：
```js
const needle = require('needle');

needle('get', 'https://jsonplaceholder.typicode.com/todos/1', { json: true })
    .then(res => {
        let todo = res.body;
        console.log(todo.id);
        console.log(todo.title);
    }).catch(err => {
        console.log(err);
    });
```
    
您还可以在上面的代码片段中发现差异，因为我们现在正在使用`Promises`，所以使用`.catch()`进行错误处理。

`注意`:
有关更多`Needle`示例，请签出[使用Needle进行HTTP请求](https://attacomsian.com/blog/http-requests-needle)教程。


## 4.Axios
[Axios](https://github.com/axios/axios)是用于浏览器和Node.js的基于`Promise`的HTTP客户端。 与上述HTTP客户端不同，Axios自动将响应数据转换为JSON对象。 在终端的项目根目录中运行以下命令：
```npm
$ npm install axios --save
```

由于它支持`Promises`，因此我们需要像上面对`HTTP`客户端所做的那样，编写更少的代码来调用伪造的REST API：
```js
const axios = require('axios');

axios.get('https://jsonplaceholder.typicode.com/todos/1')
  .then(res => {
    console.log(res.data.id);
    console.log(res.data.title);
  })
  .catch(err => {
    console.log(err);
  });
```

Axios的另一个好处是，它通过`axios.all`支持多个并发请求。 例如，我们可以同时调用伪造的REST API来一次获取两个待办事项信息：
```js
const axios = require('axios');

axios.all([
      axios.get('https://jsonplaceholder.typicode.com/todos/1'),
      axios.get('https://jsonplaceholder.typicode.com/todos/2')
    ]).then(axios.spread((res1, res2) => {
      console.log(res1.data.title);
      console.log(res2.data.title);
    })).catch(err => {
      console.log(err);
    });
```

有关更多`Axios`示例，请签出[使用Axios进行HTTP请求](https://attacomsian.com/blog/http-requests-axios)教程。

## 5.SuperAgent
[SuperAgent](https://github.com/visionmedia/superagent)是另一个类似于`Axios`的流行`HTTP`库，用于在Node.js和浏览器中发出`AJAX`请求。 就像`Axios`一样，它会将响应数据解析为JSON，这非常酷。 使用以下命令从`npm`安装`SuperAgent`：
```npm
$ npm install superagent --save
```
以下是使用SuperAgent调用伪造的REST API的代码段：
```js
const superagent = require('superagent');

superagent.get('https://jsonplaceholder.typicode.com/todos/1')
.end((err, res) => {
  if (err) { 
      return console.log(err); 
  }
  console.log(res.body.id);
  console.log(res.body.title);
});
```

SuperAgent可通过插件高度扩展。 SuperAgent有许多插件可以执行不同的任务，例如不进行缓存，URL前缀和后缀等。您可以轻松编写自己的插件来扩展SuperAgent的功能。

## 6.Got
[Got](https://github.com/sindresorhus/got)是Node.js的另一个用户友好的轻量级`HTTP`请求库。 使用以下命令从`npm`安装`Got`：
```npm
$ npm install got --save
```

就像`Axios`和`Needle`一样，`Got`也支持Promises`。 以下代码段将调用我们假的REST API以获取待办事项信息：

```js
const got = require('got');

got('https://jsonplaceholder.typicode.com/todos/1', { json: true })
    .then(res => {
      console.log(res.body.id);
      console.log(res.body.title);
    }).catch(err => {
      console.log(err.response.body);
    });
```

## 7.Node-fetch
[Node-fetch](https://github.com/bitinn/node-fetch)是一个轻量级的`HTTP`请求库，它将[浏览器的Fetch API](https://attacomsian.com/blog/javascript-fetch-api)功能引入Node.js。 您可以在终端中使用以下命令从`npm`安装`node-fetch`：
```npm
$ npm install node-fetch --save
```

与`Axios`相似，最新的`node-fetch`版本支持`Promises`。 以下是调用我们的假`REST API`来使用`Node-fetch`模块获取待办事项信息的代码段：

```js
const fetch = require('node-fetch');

fetch('https://jsonplaceholder.typicode.com/todos/1')
    .then(res => res.json()) // expecting a json response
    .then(json => {
        console.log(json.id);
        console.log(json.title);
    })
    .catch(err => {
        console.log(err);
    });
```

## 结论
这篇文章并不涵盖Node.js可用的`所有`HTTP请求库。 它仅说明HTTP功能在Node.js中某些最流行的HTTP客户端中如何工作。 Node.js还有[许多其他HTTP客户端](https://github.com/zeke/npm-collection-http-clients)可用，例如[simple-get](https://github.com/feross/simple-get)，它提供了最简单的方法来发出HTTP请求，并支持少于100行的HTTPS，重定向和流。

您最喜欢在Node.js中发出HTTP请求的HTTP客户端是什么？ 随时[发推文](https://twitter.com/attacomsian)，让我知道或提出任何其他问题。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

上次更新时间：2020年2月16日

Node.js
Express.js

## 您可能还喜欢...
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)



