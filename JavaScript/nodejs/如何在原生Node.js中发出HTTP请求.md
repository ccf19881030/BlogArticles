本文翻译自[How to make HTTP Requests in native Node.js](https://attacomsian.com/blog/node-make-http-requests)

在较早的文章中，我们了解了使用各种流行的库（例如[Axios](https://attacomsian.com/blog/http-requests-axios)，[Needle](https://attacomsian.com/blog/http-requests-needle)等）在Node.js中[发出HTTP请求的7种不同方法](https://attacomsian.com/blog/http-requests-in-nodejs)。 无疑，这些库很简单，并且隐藏了在本机Node.js中处理HTTP请求的潜在复杂性。 但这还需要添加外部依赖项。

在这篇简短的文章中，您将了解[Node.js本机HTTPS模块](https://nodejs.org/api/https.html)，该模块可以在没有任何外部依赖的情况下发出HTTP请求。

由于它是本机模块，因此不需要安装。 您可以通过以下代码访问它：
```js
const https = require('https');
```

## GET请求
是一个非常简单的示例，该示例使用HTTP模块的https.get（）方法发送GET请求：
```js
const https = require('https');

https.get('https://reqres.in/api/users', (res) => {
    let data = '';

    // called when a data chunk is received.
    res.on('data', (chunk) => {
        data += chunk;
    });

    // called when the complete response is received.
    res.on('end', () => {
        console.log(JSON.parse(data));
    });

}).on("error", (err) => {
    console.log("Error: ", err.message);
});
```

与其他流行的HTTP客户端收集响应并将其作为字符串或[JSON](https://attacomsian.com/blog/what-is-json)对象返回的方法不同，在这里，您需要将传入的数据流连接起来以供以后使用。 另一个值得注意的例外是HTTPS模块不支持[promise](https://attacomsian.com/blog/promises-javascript)，这是合理的，因为它是一个低级模块并且不是非常用户友好。

## POST请求
要发出POST请求，我们必须使用通用的`https.request()`方法。 没有可用的速记`https.post()`方法。

`https.request()`方法接受两个参数：

- options —它可以是对象文字，字符串或URL对象。
- callback —回调函数，用于捕获和处理响应。
让我们发出POST请求：
```js
const https = require('https');

const data = JSON.stringify({
    name: 'John Doe',
    job: 'DevOps Specialist'
});

const options = {
    protocol: 'https:',
    hostname: 'reqres.in',
    port: 443,
    path: '/api/users',
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Content-Length': data.length
    }
};


const req = https.request(options, (res) => {
    let data = '';

    res.on('data', (chunk) => {
        data += chunk;
    });

    res.on('end', () => {
        console.log(JSON.parse(data));
    });

}).on("error", (err) => {
    console.log("Error: ", err.message);
});

req.write(data);
req.end();

```

`options`对象中的`protocols`和`port'属性是可选的。


## PUT和DELETE请求
`PUT`和`DELETE`请求格式与`POST`请求类似。 只需将`options.method`值更改为`PUT`或`DELETE`。

这是`DELETE`请求的示例：
```js
const https = require('https');

const options = {
    hostname: 'reqres.in',
    path: '/api/users/2',
    method: 'DELETE'
};


const req = https.request(options, (res) => {

    // log the status
    console.log('Status Code:', res.statusCode);

}).on("error", (err) => {
    console.log("Error: ", err.message);
});

req.end();
```

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

上次更新时间：2020年10月03日

Node.js

您可能还喜欢...

- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
