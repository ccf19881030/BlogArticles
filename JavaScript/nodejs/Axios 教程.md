# Axios 教程

> 原文： [http://zetcode.com/javascript/axios/](http://zetcode.com/javascript/axios/)

Axios 教程展示了如何使用 Axios 客户端库在 JavaScript 中生成请求。

## Axios

Axios 是用于浏览器和 Node.js 的基于 Promise 的 HTTP 客户端。 Axios 使向 REST 端点发送异步 HTTP 请求和执行 CRUD 操作变得容易。 它可以在普通 JavaScript 中使用，也可以与 Vue 或 React 之类的库一起使用。

在本教程中，我们将在 Node.js 应用中使用 Axios。

## 安装 Axios

首先，我们安装 Axios。

```js
$ node -v
v11.5.0

```

我们使用 Node.js 11.5 版。

```js
$ npm init -y

```

我们启动一个新的 Node.js 应用。

```js
$ npm i axios

```

我们使用`npm i axios`命令安装 Axios。

## Axios 响应对象

当我们向服务器发送请求时，它返回一个响应。 Axios 响应对象包括：

*   数据-服务器返回的有效负载
*   status-服务器返回的 HTTP 代码
*   statusText-服务器返回的 HTTP 状态消息
*   标头-服务器发送的标头
*   config-原始请求配置
*   request-请求对象

## 带回调的 Axios GET 请求

在第一个示例中，我们创建一个简单的 GET 请求。 我们使用回调。

`simple_get.js`

```js
const axios = require('axios');

axios.get('http://webcode.me').then(resp => {

    console.log(resp.data);
});

```

我们生成一个简单的 GET 请求并显示输出。

```js
const axios = require('axios');

```

包括 Axios 库。

```js
axios.get('http://webcode.me').then(resp => {

    console.log(resp.data);
});

```

使用`get()`，我们发送一个 GET 请求。 我们从响应中输出数据。 数据是 HTML 代码。

```js
$node simple_get.js
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>My html page</title>
</head>
<body>

    <p>
        Today is a beautiful day. We go swimming and fishing.
    </p>

    <p>
          Hello there. How are you?
    </p>

</body>
</html>

```

这是输出。

## 带有异步/等待的 Axios GET 请求

下面的示例创建相同的请求。 这次我们使用`async/await`语法。

`simple_get.js`

```js
const axios = require('axios');

async function makeGetRequest() {

  let res = await axios.get('http://webcode.me');

  let data = res.data;
  console.log(data);
}

makeGetRequest();

```

该示例使用`async/await`语法创建一个简单的 GET 请求。

## Axios HEAD 请求

HEAD 请求是没有消息正文的 GET 请求。 在 Axios 中，使用`head()`创建 HEAD 请求。

`head_request.js`

```js
const axios = require('axios');

async function makeHeadRequest() {

  let res = await axios.head('http://webcode.me');

  console.log(`Status: ${res.status}`)
  console.log(`Server: ${res.headers.server}`)
  console.log(`Date: ${res.headers.date}`)
}

makeHeadRequest();

```

该示例显示了通过 HEAD 请求生成的响应的状态，服务器名称，响应日期。

```js
$ node head_request.js
Status: 200
Server: nginx/1.6.2
Date: Mon, 04 Feb 2019 15:08:56 GMT

```

这是输出。

## Axios 基本 API

`get()`，`post()`或`delete()`方法是基本 axios API 的便捷方法：`axios(config)`和`axios(url, config)`。

`basic_api.js`

```js
const axios = require('axios');

async function makeRequest() {

    const config = {
        method: 'get',
        url: 'http://webcode.me'
    }

    let res = await axios(config)

    console.log(res.status);
}

makeRequest();

```

该示例向`webcode.me`创建 GET 请求。

```js
const config = {
    method: 'get',
    url: 'http://webcode.me'
}

```

我们在配置对象中指定请求的详细信息。

## Axios 自定义标头

在下面的示例中，我们发送一个自定义标头。

`custom_header.js`

```js
const axios = require('axios');

async function makeRequest() {

    const config = {
        method: 'get',
        url: 'http://webcode.me',
        headers: { 'User-Agent': 'Console app' }
    }

    let res = await axios(config)

    console.log(res.request._header);
}

makeRequest();

```

该示例发送一个自定义的标头。

```js
const config = {
    method: 'get',
    url: 'http://webcode.me',
    headers: { 'User-Agent': 'Console app' }
}

```

自定义数据将添加到配置对象的`headers`属性中。

```js
console.log(res.request._header);

```

我们验证发送的数据。

```js
$ node custom_header.js
GET / HTTP/1.1
Accept: application/json, text/plain, */*
User-Agent: Console app
Host: webcode.me
Connection: close

```

这是输出。

## 获取 Github 信息

许多在线服务包含公共 API。 在以下示例中，我们生成对 Github API 的请求。

`github.js`

```js
const axios = require('axios');

async function getNumberOfFollowers() {

  let res = await axios.get('https://api.github.com/users/janbodnar');

  let nOfFollowers = res.data.followers;
  let location = res.data.location;

  console.log(`# of followers: ${nOfFollowers}`)
  console.log(`Location: ${location}`)
}

getNumberOfFollowers();

```

在示例中，我们获得关注者的数量和用户的位置。

```js
$ node github.js
# of followers: 44
Location: Bratislava

```

这是输出。

## Axios POST 请求

使用`post()`方法创建 POST 请求。

`post_request.php`

```js
const axios = require('axios');

async function makePostRequest() {

    let res = await axios.post('https://jsonplaceholder.typicode.com/posts');

    console.log(`Status code: ${res.status}`);
    console.log(`Status text: ${res.statusText}`);
    console.log(`Request method: ${res.request.method}`);
    console.log(`Path: ${res.request.path}`);

    console.log(`Date: ${res.headers.date}`);
    console.log(`Data: ${res.data}`);
}

makePostRequest();

```

该示例创建对在线测试服务的 POST 请求。

```js
$ node post_request.js
Status code: 201
Status text: Created
Request method: POST
Path: /posts
Date: Mon, 04 Feb 2019 16:54:36 GMT
Data: [object Object]

```

这是输出。

## Axios 下载图像

以下示例显示了如何使用 Axios 下载图像。

`get_image.js`

```js
const axios = require('axios');
const fs = require('fs');

var config = {
    responseType: 'stream'
};

let url = 'httpsimg.dog.ceo/breeds/setter-english/n02100735_4870.jpg';

async function getImage() {

    let resp = await axios.get(url, config);
    resp.data.pipe(fs.createWriteStream('image.jpg'));
}

getImage();

```

该示例从在线服务中检索图像，该服务保留了狗的图像。

```js
const axios = require('axios');
const fs = require('fs');

```

我们包括`axios`和`fs`模块。

```js
var config = {
    responseType: 'stream'
};

```

我们在配置对象中指定响应类型。

```js
let resp = await axios.get(url, config);

```

我们得到图像。

```js
resp.data.pipe(fs.createWriteStream('image.jpg'));

```

借助`fs`模块，我们将图像保存到磁盘。

## Axios 多个请求

我们可以使用 Axios 一次创建多个请求。

`multiple_requests.js`

```js
const axios = require('axios');

async function makeRequests() {

    let [u1, u2] = await Promise.all([
        axios.get('https://api.github.com/users/janbodnar'),
        axios.get('https://api.github.com/users/symfony')
    ]);

    console.log(`Jan Bodnar: ${u1.data.created_at}`);
    console.log(`Symfony: ${u2.data.created_at}`);
}

makeRequests();

```

要发送多个请求，我们使用`Promise.all()`方法。

```js
$ node multiple_requests.js
Jan Bodnar: 2016-01-31T12:12:28Z
Symfony: 2009-10-24T04:05:23Z

```

这是输出。

## 将 Axios 与 JSON 服务器一起使用

JSON Server 是一个很棒的工具，它使我们能够轻松创建伪造的 REST API。

```js
$ npm i -g json-server

```

我们安装`json-server`。

`users.json`

```js
{
  "users": [
    {
      "id": 1,
      "first_name": "Robert",
      "last_name": "Schwartz",
      "email": "rob23@gmail.com"
    },
    {
      "id": 2,
      "first_name": "Lucy",
      "last_name": "Ballmer",
      "email": "lucyb56@gmail.com"
    },
    {
      "id": 3,
      "first_name": "Anna",
      "last_name": "Smith",
      "email": "annasmith23@gmail.com"
    },
    {
      "id": 4,
      "first_name": "Robert",
      "last_name": "Brown",
      "email": "bobbrown432@yahoo.com"
    },
    {
      "id": 5,
      "first_name": "Roger",
      "last_name": "Bacon",
      "email": "rogerbacon12@yahoo.com"
    }
  ]
}  

```

这是我们的测试数据。

### 启动 JSON 服务器

JSON 服务器从我们已全局安装的 json-server 启动。

```js
$ json-server --watch data.json    

```

`--watch`选项用于指定服务器的数据。

```js
$ curl localhost:3000/users/2/
{
  "id": 2,
  "first_name": "Lucy",
  "last_name": "Ballmer",
  "email": "lucyb56@gmail.com"
}

```

使用 curl 命令，使用户获得 ID 2。

## 发布用户

我们发布了一个新用户。

`post_user.js`

```js
const axios = require('axios');

async function makePostRequest() {

    params = {
        id: 6,
        first_name: 'Fred',
        last_name: 'Blair',
        email: 'freddyb34@gmail.com'
      }

    let res = await axios.post('http://localhost:3000/users/', params);

    console.log(res.data);
}

makePostRequest();

```

该示例发布了一个新用户。

```js
let res = await axios.post('http://localhost:3000/users/', params);

```

将 post 参数作为第二个参数传递给`post()`方法。

### 获取用户

我们从测试服务器获取用户。

`get_users.js`

```js
const axios = require('axios');

async function makeGetRequest() {

  let res = await axios.get('http://localhost:3000/users/');

  let data = res.data;
  console.log(data);
}

makeGetRequest();

```

该程序从我们的测试服务器检索所有用户。

```js
$ node get_users.js
[ { id: 1,
    first_name: 'Robert',
    last_name: 'Schwartz',
    email: 'rob23@gmail.com' },
  { id: 2,
    first_name: 'Lucy',
    last_name: 'Ballmer',
    email: 'lucyb56@gmail.com' },
  { id: 3,
    first_name: 'Anna',
    last_name: 'Smith',
    email: 'annasmith23@gmail.com' },
  { id: 4,
    first_name: 'Robert',
    last_name: 'Brown',
    email: 'bobbrown432@yahoo.com' },
  { id: 5,
    first_name: 'Roger',
    last_name: 'Bacon',
    email: 'rogerbacon12@yahoo.com' },
  { id: 6,
    first_name: 'Fred',
    last_name: 'Blair',
    email: 'freddyb34@gmail.com' } ]

```

这是输出。

## 删除用户

使用`delete()`删除资源。

`delete_user.js`

```js
const axios = require('axios');

async function makePostRequest() {

    let res = await axios.delete('http://localhost:3000/users/2/');

    console.log(res.status);
}

makePostRequest();

```

该示例删除具有 ID 2 的用户。

在本教程中，我们使用了 JavaScript Axios 模块。

您可能也对以下相关教程感兴趣： [JSON 服务器教程](/javascript/jsonserver/)，[笑话教程](/javascript/jest/)， [Moment.js 教程](/javascript/momentjs/)，[从 JavaScript 中的 URL 读取 JSON](/articles/javascriptjsonurl/) ， [JavaScript Snake 教程](/javascript/snake/)， [JQuery 教程](/web/jquery/)， [Node Sass 教程](/javascript/nodesass/)， [Lodash 教程](/javascript/lodash/)。
