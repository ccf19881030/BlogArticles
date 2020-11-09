本文翻译自[Node.js Rest APIs example with Express, Sequelize & MySQL](https://bezkoder.com/node-js-express-sequelize-mysql/)

最新修改：2020年9月29号 [bezkoder](https://bezkoder.com/author/bezkoder/)  [Node.js](https://bezkoder.com/category/node-js/)

[Express](https://expressjs.com/)是Node.js最受欢迎的Web框架之一，支持路由，中间件，视图系统...[Sequelize](https://sequelize.org/)是基于Promise的Node.js ORM，它支持Postgres，MySQL，SQL Server的方言。在本教程中，我将 向您展示如何使用Express，Sequelize和MySQL数据库来构建Node.js Restful CRUD API。

您应该首先在机器上安装MySQL。 可以在以下位置找到安装说明：
[Official MySQL installation manual](https://dev.mysql.com/doc/refman/5.7/en/installing.html)

相关文章：
- [Build Node.js Rest APIs with Express & MySQL (without Sequelize)](https://bezkoder.com/node-js-rest-api-express-mysql/)
- [Node.js: Upload/Import Excel file data into MySQL Database](https://bezkoder.com/node-js-upload-excel-file-database/)
- [Node.js: Upload CSV file data into MySQL Database](https://bezkoder.com/node-js-upload-csv-file-database/)

全栈：
- [Vue.js + Node.js + Express + MySQL example](https://bezkoder.com/vue-js-node-js-express-mysql-crud-example/)
- [Vue.js + Node.js + Express + MongoDB example](https://bezkoder.com/vue-node-express-mongodb-mevn-crud/)
- [Angular + Node.js Express + MySQL example](https://bezkoder.com/angular-node-express-mysql/)
- [React + Node.js + Express + MySQL example](https://bezkoder.com/react-node-express-mysql/)

安全性：[Node.js – JWT Authentication & Authorization example](https://bezkoder.com/node-js-jwt-authentication-mysql/)
部署：[Deploying/Hosting Node.js app on Heroku with MySQL database](https://bezkoder.com/deploy-node-js-app-heroku-cleardb-mysql/)

# Node.js Rest CRUD API概述
我们将构建Rest Apis，它可以创建，检索，更新，删除和按标题查找教程。
首先，我们从Express Web服务器开始。 接下来，我们为MySQL数据库添加配置，使用Sequelize创建`Tutorial`模型，编写控制器。 然后，我们定义用于处理所有CRUD操作（包括自定义查找程序）的路由。

下表概述了将要导出的Rest API：
Methods     | Urls  | Actions
-------- | -----  | -----
GET	|  api/tutorials	| get all Tutorials
GET	|  api/tutorials/:id	| get Tutorial by id
POST	|  api/tutorials	|  add new Tutorial
PUT	|  api/tutorials/:id	| update Tutorial by id
DELETE	| api/tutorials/:id	| remove Tutorial by id
DELETE	|  api/tutorials	|   remove all Tutorials
GET	|  api/tutorials/published	|  find all published Tutorials
GET	|  api/tutorials?title=[kw]	| find all Tutorials which title contains 'kw'

最后，我们将使用Postman测试Rest Apis。

这是我们的项目结构：
![project structure](https://img-blog.csdnimg.cn/20201108163017724.png#pic_center)

# 示例视频
这是我们的与MySQL数据库一起运行的Node.js Express Sequelize应用程序演示，并通过Postman测试Rest Apis。

# 创建Node.js应用
首先，我们创建目录：
```shell
$ mkdir nodejs-express-sequelize-mysql
$ cd nodejs-express-sequelize-mysql
```
接下来，我们使用package.json文件初始化Node.js App：
```shell
npm init

name: (nodejs-express-sequelize-mysql) 
version: (1.0.0) 
description: Node.js Rest Apis with Express, Sequelize & MySQL.
entry point: (index.js) server.js
test command: 
git repository: 
keywords: nodejs, express, sequelize, mysql, rest, api
author: bezkoder
license: (ISC)

Is this ok? (yes) yes
```
我们需要安装必要的模块：`express`，`sequelize`，`mysql2`和`body-parser`。
运行命令：
```shell
npm install express sequelize mysql2 body-parser cors --save
```
package.json文件应如下所示：
```json
{
  "name": "nodejs-express-sequelize-mysql",
  "version": "1.0.0",
  "description": "Node.js Rest Apis with Express, Sequelize & MySQL",
  "main": "server.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "keywords": [
    "nodejs",
    "express",
    "rest",
    "api",
    "sequelize",
    "mysql"
  ],
  "author": "bezkoder",
  "license": "ISC",
  "dependencies": {
    "body-parser": "^1.19.0",
    "cors": "^2.8.5",
    "express": "^4.17.1",
    "mysql2": "^2.0.2",
    "sequelize": "^5.21.2"
  }
}
```

# 建立Express Web服务器
在根目录下，创建一个新的`server.js`文件：
```js
const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");

const app = express();

var corsOptions = {
  origin: "http://localhost:8081"
};

app.use(cors(corsOptions));

// parse requests of content-type - application/json
app.use(bodyParser.json());

// parse requests of content-type - application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));

// simple route
app.get("/", (req, res) => {
  res.json({ message: "Welcome to bezkoder application." });
});

// set port, listen for requests
const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}.`);
});
```
我们要做的是：
- 导入`express`，`body-parser`和`cors`模块：

	- Express用于构建Rest API
	- `body-parser`有助于解析请求并创建`req.body`对象
	- `cors`提供了Express中间件，以使CORS具有多种选择。
- 创建一个Express应用，然后使用`app.use()`方法添加`body-parser`和`cors`中间件。 请注意，我们设置了origin：`http:// localhost:8081`。
- 定义一个易于测试的GET路由。
- 在端口8080上侦听传入请求。

现在，使用以下命令运行该应用：`node server.js`。
使用URL `http:// localhost:8080/`打开浏览器，您将看到：
![http://localhost:8080](https://img-blog.csdnimg.cn/20201108173311553.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

是的，第一步已经完成。 在下一节中，我们将与Sequelize一起协作。

# 配置MySQL数据库并进行序列化
在app文件夹中，我们创建一个单独的config文件夹，然后使用db.config.js文件进行配置，如下所示：
```js
module.exports = {
  HOST: "localhost",
  USER: "root",
  PASSWORD: "123456",
  DB: "testdb",
  dialect: "mysql",
  pool: {
    max: 5,
    min: 0,
    acquire: 30000,
    idle: 10000
  }
};
```
前面5个参数用于MySQL连接。

`pool`是可选的，它将用于Sequelize连接池配置：

	- max：池中的最大连接数
	- min：池中的最小连接数
	- idle：连接释放之前可以空闲的最长时间（以毫秒为单位）
	- acquire：该池将在抛出错误之前尝试获取连接的最长时间（以毫秒为单位）

有关更多详细信息，请访问[API Reference for the Sequelize constructor](https://sequelize.org/master/class/lib/sequelize.js~Sequelize.html#instance-constructor-constructor)。

# 初始化Sequelize
我们将在下一步包含模型的`app/models`文件夹中初始化Sequelize。

现在，使用以下代码创建`app/models/index.js`：

```js
const dbConfig = require("../config/db.config.js");

const Sequelize = require("sequelize");
const sequelize = new Sequelize(dbConfig.DB, dbConfig.USER, dbConfig.PASSWORD, {
  host: dbConfig.HOST,
  dialect: dbConfig.dialect,
  operatorsAliases: false,

  pool: {
    max: dbConfig.pool.max,
    min: dbConfig.pool.min,
    acquire: dbConfig.pool.acquire,
    idle: dbConfig.pool.idle
  }
});

const db = {};

db.Sequelize = Sequelize;
db.sequelize = sequelize;

db.tutorials = require("./tutorial.model.js")(sequelize, Sequelize);

module.exports = db;
```
不要忘记在`server.js`中调用`sync()`方法
```js
...
const app = express();
app.use(...);

const db = require("./app/models");
db.sequelize.sync();

...
```
在开发中，您可能需要删除现有表并重新同步数据库。 只需使用force：true即可，如下代码：
```js
db.sequelize.sync({ force: true }).then(() => {
  console.log("Drop and re-sync db.");
});
```


# 定义Sequelize模型
在models文件夹中，像这样创建tutorial.model.js文件：
```js
module.exports = (sequelize, Sequelize) => {
  const Tutorial = sequelize.define("tutorial", {
    title: {
      type: Sequelize.STRING
    },
    description: {
      type: Sequelize.STRING
    },
    published: {
      type: Sequelize.BOOLEAN
    }
  });

  return Tutorial;
};
```

该Sequelize模型表示MySQL数据库中的`tutorials`表。 这些列将自动生成：id, title, description, published, createdAt, updatedAt.

初始化Sequelize之后，我们无需编写CRUD函数，Sequelize支持所有这些功能：
- 创建一个新的教程：create(object)
- 通过id查找教程：findByPk(id)
- 获取所有教程：findAll()
- 通过id：update(data, where: { id: id })
- 删除教程：destroy(where: { id: id })
- 删除所有教程：destroy（where：{}）
- 按标题查找所有教程：findAll({ where: { title: ... } })

这些功能将在我们的控制器中使用。

我们可以通过为每个教程添加评论来改进示例。 这是一对多关系，我为此编写了一个教程：
[Sequelize Associations: One-to-Many example – Node.js, MySQL](https://bezkoder.com/sequelize-associate-one-to-many/)

或者，您可以为每个教程添加标签，并将教程添加到标签（多对多关系）：
[Sequelize Many-to-Many Association example with Node.js & MySQL](https://bezkoder.com/sequelize-associate-many-to-many/)

# 创建控制器
在`app/controllers`文件夹中，让我们使用以下CRUD函数创建tutorial.controller.js：
- create
- findAll
- findOne
- update
- delete
- deleteAll
- findAllPublised

```js
const db = require("../models");
const Tutorial = db.tutorials;
const Op = db.Sequelize.Op;

// Create and Save a new Tutorial
exports.create = (req, res) => {
  
};

// Retrieve all Tutorials from the database.
exports.findAll = (req, res) => {
  
};

// Find a single Tutorial with an id
exports.findOne = (req, res) => {
  
};

// Update a Tutorial by the id in the request
exports.update = (req, res) => {
  
};

// Delete a Tutorial with the specified id in the request
exports.delete = (req, res) => {
  
};

// Delete all Tutorials from the database.
exports.deleteAll = (req, res) => {
  
};

// Find all published Tutorials
exports.findAllPublished = (req, res) => {
  
};
```
让我们实现这些功能。

## 创建一个新对象
创建并保存一个新教程：
```js
exports.create = (req, res) => {
  // Validate request
  if (!req.body.title) {
    res.status(400).send({
      message: "Content can not be empty!"
    });
    return;
  }

  // Create a Tutorial
  const tutorial = {
    title: req.body.title,
    description: req.body.description,
    published: req.body.published ? req.body.published : false
  };

  // Save Tutorial in the database
  Tutorial.create(tutorial)
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Some error occurred while creating the Tutorial."
      });
    });
};
```

## 检索对象（有条件）
从数据库中检索所有教程/按标题查找：

```js
exports.findAll = (req, res) => {
  const title = req.query.title;
  var condition = title ? { title: { [Op.like]: `%${title}%` } } : null;

  Tutorial.findAll({ where: condition })
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Some error occurred while retrieving tutorials."
      });
    });
};
```

我们使用`req.query.title`从Request中获取查询字符串，并将其作为`findAll()`方法的条件。

## 检索单个对象
查找具有ID的单个教程：
```js
exports.findOne = (req, res) => {
  const id = req.params.id;

  Tutorial.findByPk(id)
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message: "Error retrieving Tutorial with id=" + id
      });
    });
};
```

## 更新对象
更新由请求中的`id`标识的教程：
```js
exports.update = (req, res) => {
  const id = req.params.id;

  Tutorial.update(req.body, {
    where: { id: id }
  })
    .then(num => {
      if (num == 1) {
        res.send({
          message: "Tutorial was updated successfully."
        });
      } else {
        res.send({
          message: `Cannot update Tutorial with id=${id}. Maybe Tutorial was not found or req.body is empty!`
        });
      }
    })
    .catch(err => {
      res.status(500).send({
        message: "Error updating Tutorial with id=" + id
      });
    });
};
```

## 删除对象
删除具有指定`id`的教程：
```js
exports.delete = (req, res) => {
  const id = req.params.id;

  Tutorial.destroy({
    where: { id: id }
  })
    .then(num => {
      if (num == 1) {
        res.send({
          message: "Tutorial was deleted successfully!"
        });
      } else {
        res.send({
          message: `Cannot delete Tutorial with id=${id}. Maybe Tutorial was not found!`
        });
      }
    })
    .catch(err => {
      res.status(500).send({
        message: "Could not delete Tutorial with id=" + id
      });
    });
};
```

## 删除所有对象
从数据库中删除所有教程：
```js
exports.deleteAll = (req, res) => {
  Tutorial.destroy({
    where: {},
    truncate: false
  })
    .then(nums => {
      res.send({ message: `${nums} Tutorials were deleted successfully!` });
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Some error occurred while removing all tutorials."
      });
    });
};
```

## 按条件查找所有对象
查找所有`published = true`的教程：
```js
exports.findAllPublished = (req, res) => {
  Tutorial.findAll({ where: { published: true } })
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Some error occurred while retrieving tutorials."
      });
    });
};
```

可以对该控制器进行一些修改以返回分页响应：
```js
{
    "totalItems": 8,
    "tutorials": [...],
    "totalPages": 3,
    "currentPage": 1
}
```

您可以在以下位置找到更多详细信息：
[Server side Pagination in Node.js with Sequelize and MySQL](https://bezkoder.com/node-js-sequelize-pagination-mysql/)

# 定义路由
当客户端使用HTTP请求（GET，POST，PUT，DELETE）发送对端点的请求时，我们需要通过设置路由来确定服务器的响应方式。

这些是我们的路由：

- `/api/tutorials`：GET，POST，DELETE
- `/api/tutorials/:id`：GET，PUT，DELETE
- `/api/tutorials/published`：GET
在`app/routes`文件夹中创建一个`turorial.routes.js`，其内容如下：
```js
module.exports = app => {
  const tutorials = require("../controllers/tutorial.controller.js");

  var router = require("express").Router();

  // Create a new Tutorial
  router.post("/", tutorials.create);

  // Retrieve all Tutorials
  router.get("/", tutorials.findAll);

  // Retrieve all published Tutorials
  router.get("/published", tutorials.findAllPublished);

  // Retrieve a single Tutorial with id
  router.get("/:id", tutorials.findOne);

  // Update a Tutorial with id
  router.put("/:id", tutorials.update);

  // Delete a Tutorial with id
  router.delete("/:id", tutorials.delete);

  // Delete all Tutorials
  router.delete("/", tutorials.deleteAll);

  app.use('/api/tutorials', router);
};
```

您可以看到我们使用了`/controllers/tutorial.controller.js`中的控制器。

我们还需要在`server.js`中包含路由（在`app.listen()`之前）：
```js
...

require("./app/routes/turorial.routes")(app);

// set port, listen for requests
const PORT = ...;
app.listen(...);
```

# 测试API
使用以下命令运行我们的Node.js应用程序：`node server.js`。
控制台显示：
```shell
Server is running on port 8080.
Executing (default): DROP TABLE IF EXISTS `tutorials`;
Executing (default): CREATE TABLE IF NOT EXISTS `tutorials` (`id` INTEGER NOT NULL auto_increment , `title` VARCHAR(255), `description` VARCHAR(255), `published` TINYINT(1), `createdAt` DATETIME NOT NULL, `updatedAt` DATETIME NOT NULL, PRIMARY KEY (`id`)) ENGINE=InnoDB;
Executing (default): SHOW INDEX FROM `tutorials`
Drop and re-sync db.
```

使用Postman，我们将测试以上所有的Apis。

1、使用`POST/tutorials` Api创建一个新教程
![Create a new Tutorial](https://img-blog.csdnimg.cn/20201108191929283.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
创建一些新教程后，您可以检查MySQL表：
```shell
mysql> select * from tutorials;
+----+-------------------+-------------------+-----------+---------------------+---------------------+
| id | title             | description       | published | createdAt           | updatedAt           |
+----+-------------------+-------------------+-----------+---------------------+---------------------+
|  1 | JS: Node Tut #1   | Tut#1 Description |         0 | 2019-12-13 01:13:57 | 2019-12-13 01:13:57 |
|  2 | JS: Node Tut #2   | Tut#2 Description |         0 | 2019-12-13 01:16:08 | 2019-12-13 01:16:08 |
|  3 | JS: Vue Tut #3    | Tut#3 Description |         0 | 2019-12-13 01:16:24 | 2019-12-13 01:16:24 |
|  4 | Vue Tut #4        | Tut#4 Description |         0 | 2019-12-13 01:16:48 | 2019-12-13 01:16:48 |
|  5 | Node & Vue Tut #5 | Tut#5 Description |         0 | 2019-12-13 01:16:58 | 2019-12-13 01:16:58 |
+----+-------------------+-------------------+-----------+---------------------+---------------------+
```

2、使用`GET /tutorials` Api检索所有的教程
![Retrieve all Tutorials](https://img-blog.csdnimg.cn/2020110819212040.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
3、使用`GET /tutorials/:id` Api根据id查询单个教程
![Retrieve a single Tutorial by id](https://img-blog.csdnimg.cn/20201108192218596.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
4、使用`PUT /tutorials/:id' Api更新教程
![Update a Tutorial](https://img-blog.csdnimg.cn/20201108192300535.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

在更新某些行后，请查看`tutorials`表：
```shell
mysql> select * from tutorials;
+----+-------------------+-------------------+-----------+---------------------+---------------------+
| id | title             | description       | published | createdAt           | updatedAt           |
+----+-------------------+-------------------+-----------+---------------------+---------------------+
|  1 | JS: Node Tut #1   | Tut#1 Description |         0 | 2019-12-13 01:13:57 | 2019-12-13 01:13:57 |
|  2 | JS: Node Tut #2   | Tut#2 Description |         0 | 2019-12-13 01:16:08 | 2019-12-13 01:16:08 |
|  3 | JS: Vue Tut #3    | Tut#3 Description |         1 | 2019-12-13 01:16:24 | 2019-12-13 01:22:51 |
|  4 | Vue Tut #4        | Tut#4 Description |         1 | 2019-12-13 01:16:48 | 2019-12-13 01:25:28 |
|  5 | Node & Vue Tut #5 | Tut#5 Description |         1 | 2019-12-13 01:16:58 | 2019-12-13 01:25:30 |
+----+-------------------+-------------------+-----------+---------------------+---------------------+
```

5、使用`GET /tutorials?title=node`查找标题包含'node'的所有教程
![Find all Tutorials which title contains ‘node’](https://img-blog.csdnimg.cn/20201108192501484.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
6、使用`GET /tutorials/published` Api查询所有已发布的教程
![Find all published Tutorials](https://img-blog.csdnimg.cn/20201108192556555.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
7、使用'DELETE /tutorials/:id` Api删除一个教程
![Delete a Tutorial](https://img-blog.csdnimg.cn/20201108192646838.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
id = 2的教程已从`tutorials`表中删除：

```shell
mysql> select * from tutorials;
+----+-------------------+-------------------+-----------+---------------------+---------------------+
| id | title             | description       | published | createdAt           | updatedAt           |
+----+-------------------+-------------------+-----------+---------------------+---------------------+
|  1 | JS: Node Tut #1   | Tut#1 Description |         0 | 2019-12-13 01:13:57 | 2019-12-13 01:13:57 |
|  3 | JS: Vue Tut #3    | Tut#3 Description |         1 | 2019-12-13 01:16:24 | 2019-12-13 01:22:51 |
|  4 | Vue Tut #4        | Tut#4 Description |         1 | 2019-12-13 01:16:48 | 2019-12-13 01:25:28 |
|  5 | Node & Vue Tut #5 | Tut#5 Description |         1 | 2019-12-13 01:16:58 | 2019-12-13 01:25:30 |
+----+-------------------+-------------------+-----------+---------------------+---------------------+
```

8、使用'DELETE /tutorials` Api删除所有的教程
![Delete all Tutorials](https://img-blog.csdnimg.cn/20201108192823367.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
现在在`tutorials`表中没有一行数据了：
```shell
mysql> SELECT * FROM tutorials;
Empty set (0.00 sec)
```

# 结论
今天，我们已经学习了如何使用Express Web服务器创建Node.js Rest Apis。 我们还知道添加MySQL数据库和Sequelize配置，创建Sequelize模型，编写控制器以及定义用于处理所有CRUD操作的路由的方法。

您可以在下一个教程中找到更多有趣的东西：
- [Server side Pagination in Node.js with Sequelize and MySQL](https://bezkoder.com/node-js-sequelize-pagination-mysql/)
返回分页数据作为响应：
```js
{
    "totalItems": 8,
    "tutorials": [...],
    "totalPages": 3,
    "currentPage": 1
}
```
- [Deploying/Hosting Node.js app on Heroku with MySQL database](https://bezkoder.com/deploy-node-js-app-heroku-cleardb-mysql/)
或者您可以将图像保存到MySQL数据库：
- [Upload/store images in MySQL using Node.js, Express & Multer](https://bezkoder.com/node-js-upload-image-mysql/)

学习愉快！ 再见。

# 进一步阅读
- [Express.js Routing]()
- [https://www.npmjs.com/package/express](http://expressjs.com/en/guide/routing.html)
- [https://www.npmjs.com/package/body-parser](https://www.npmjs.com/package/express)
- [https://www.npmjs.com/package/mysql2](https://www.npmjs.com/package/mysql2)
- [Tutorials and Guides for Sequelize v5](https://sequelize.org/master/)

将教程数据从文件上传到MySQL数据库表：
	- [Node.js: Upload Excel file data into MySQL Database](https://bezkoder.com/node-js-upload-excel-file-database/)
	- [Node.js: Upload CSV file data into MySQL Database](https://bezkoder.com/node-js-upload-csv-file-database/)

# 源代码
您可以在[Github](https://github.com/bezkoder/nodejs-express-sequelize-mysql)上找到此示例的完整源代码。

如果要为每个教程添加评论。 它是一对多关联，有一个有关该关系的教程：[Sequelize Associations: One-to-Many example – Node.js, MySQL](https://bezkoder.com/sequelize-associate-one-to-many/)

或者，您可以为每个教程添加标签，并将教程添加到标签（多对多关系）：
[Sequelize Many-to-Many Association example with Node.js & MySQL](https://bezkoder.com/sequelize-associate-many-to-many/)


