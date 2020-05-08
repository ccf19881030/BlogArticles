# MongoDB JavaScript 教程

> 原文： [http://zetcode.com/javascript/mongodb/](http://zetcode.com/javascript/mongodb/)

MongoDB JavaScript 教程展示了如何在 JavaScript 中创建与 MongoDB 一起使用的程序。 本教程使用本地 mongodb 驱动程序。 （还有其他解决方案，例如 Mongoose 或 Monk。）

## MongoDB

MongoDB 是 NoSQL 跨平台的面向文档的数据库。 它是可用的最受欢迎的数据库之一。 MongoDB 由 MongoDB Inc.开发，并作为免费和开源软件发布。

MongoDB 中的记录是一个文档，它是由字段和值对组成的数据结构。 MongoDB 文档与 JSON 对象相似。 字段的值可以包括其他文档，数组和文档数组。 MongoDB 将文档存储在集合中。 集合类似于关系数据库中的表以及行中的文档。

## 安装 MongoDB 服务器

以下命令可用于在基于 Debian 的 Linux 上安装 MongoDB。

```js
$ sudo apt-get install mongodb

```

该命令将安装 MongoDB 随附的必要软件包。

```js
$ sudo service mongodb status
mongodb start/running, process 975

```

使用`sudo service mongodb status`命令，我们检查`mongodb`服务器的状态。

```js
$ sudo service mongodb start
mongodb start/running, process 6448

```

`mongodb`服务器由`sudo service mongodb start`命令启动。

## MongoDB 驱动程序安装

我们设置了项目。

```js
$ node -v
v11.5.0

```

我们使用 Node.js 版本 11.5.0。

```js
$ npm i mongodb

```

我们安装`mongodb`本机 JavaScript 驱动程序。 `npm`是 Node.js 程序包管理器。 MongoDB Node.js 驱动程序提供基于回调和基于 Promise 的交互。

## MongoDB 创建数据库

`mongo`工具是 MongoDB 的交互式 JavaScript Shell 界面，它为系统管理员提供了一个界面，并为开发人员提供了一种直接测试数据库查询和操作的方法。

```js
$ mongo testdb
MongoDB shell version v4.0.7
...
> db
testdb
> db.cars.insert({name: "Audi", price: 52642})
> db.cars.insert({name: "Mercedes", price: 57127})
> db.cars.insert({name: "Skoda", price: 9000})
> db.cars.insert({name: "Volvo", price: 29000})
> db.cars.insert({name: "Bentley", price: 350000})
> db.cars.insert({name: "Citroen", price: 21000})
> db.cars.insert({name: "Hummer", price: 41400})
> db.cars.insert({name: "Volkswagen", price: 21600})

```

我们创建一个`testdb`数据库，并在`cars`集合中插入八个文档。

## MongoDB  Promise 

Promise 是用于延迟和异步计算的对象。 它表示尚未完成的操作，但有望在将来进行。

```js
asyncFunc()
  .then(value => { /* success */ })
  .catch(error => { /* failure */ })
  .finally( => { /* cleanup */};

```

`then()`方法始终返回 Promise，这使我们能够链接方法调用。

**Note:** the `MongoClient's` connect returns a promise if no callback is passed.

我们也可以使用`async/await`语法来处理诺言。

## MongoDB JS 驱动程序

在第一个示例中，我们打印 Node.js 驱动程序的版本。

`driver_version.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    console.log(client.topology.clientInfo);

    client.close();
});

```

在该示例中，我们连接到服务器并找到客户端信息。

```js
const mongo = require('mongodb');

```

我们使用`mongodb`模块。

```js
const client = mongo.MongoClient;

```

`MongoClient`用于连接到 MongoDB 服务器。

```js
const url = 'mongodb://localhost:27017';

```

这是数据库的 URL。 27017 是 MongoDB 服务器侦听的默认端口。

```js
MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

```

使用`connect()`创建到数据库的连接。

```js
$ node driver_version.js
{ driver: { name: 'nodejs', version: '3.2.2' },
    os:
    { type: 'Windows_NT',
        name: 'win32',
        architecture: 'x64',
        version: '10.0.17134' },
    platform: 'Node.js v11.5.0, LE' }

```

驱动程序版本为 3.2.2。

## MongoDB 列出数据库集合

`listCollections()`方法列出了数据库中的可用集合。

`list_collections.js`

```js
const mongo = require('mongodb');

const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    db.listCollections().toArray().then((docs) => {

        console.log('Available collections:');
        docs.forEach((doc, idx, array) => { console.log(doc.name) });

    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例连接到`testdb`数据库并检索其所有集合。

```js
db.listCollections().toArray().then((docs) => {

    console.log('Available collections:');
    docs.forEach((doc, idx, array) => { console.log(doc.name) });
...

```

`listCollection()`方法在`testdb`数据库中找到所有集合； 它们被打印到控制台。

**Note:** that we should be careful about using `toArray()` method because it can cause a lot of memory usage.

```js
}).catch((err) => {

    console.log(err);
}).finally(() => {

    client.close();
});

```

在`catch`块中，我们捕获了任何潜在的异常，并在`finally`块中关闭了与数据库的连接。

**Note:** our applications are console programs; therefore, we close the connection at the end of the program. In web applications, the connections should be reused.

```js
$ node list_collections.js
Available collections:
continents
cars
cities

```

在我们的数据库中，我们有这三个集合。

## MongoDB 数据库统计

`dbstats()`方法获取数据库的统计信息。

`dbstats.js`

```js
const mongo = require('mongodb');

const MongoClient = mongo.MongoClient;
const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    db.stats((err, stats) => {

        if (err) throw err;

        console.log(stats);

        client.close();
    })
});

```

该示例连接到`testdb`数据库并显示其统计信息。

```js
$ node dbstats.js
{ db: 'testdb',
  collections: 3,
  views: 0,
  objects: 18,
  avgObjSize: 57.888888888888886,
  dataSize: 1042,
  storageSize: 69632,
  numExtents: 0,
  indexes: 3,
  indexSize: 69632,
  fsUsedSize: 136856346624,
  fsTotalSize: 254721126400,
  ok: 1 }

```

这是一个示例输出。

## MongoDB 查找

`find()`函数为查询创建一个游标，该游标可用于遍历 MongoDB 的结果。

`find_all.js`

```js
const mongo = require('mongodb');

const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    db.collection('cars').find({}).toArray().then((docs) => {

        console.log(docs);

    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

在示例中，我们从`cars`集合中检索所有文档。

```js
db.collection('cars').find({}).toArray().then((docs) => {

```

传递空查询将返回所有文档。

```js
$ node find_all.js
[ { _id: 5cfcfc3438f62aaa09b52175, name: 'Audi', price: 52642 },
  { _id: 5cfcfc3a38f62aaa09b52176, name: 'Mercedes', price: 57127 },
  { _id: 5cfcfc3f38f62aaa09b52177, name: 'Skoda', price: 9000 },
  { _id: 5cfcfc4338f62aaa09b52178, name: 'Volvo', price: 29000 },
  { _id: 5cfcfc4838f62aaa09b52179, name: 'Bentley', price: 350000 },
  { _id: 5cfcfc4b38f62aaa09b5217a, name: 'Citroen', price: 21000 },
  { _id: 5cfcfc4f38f62aaa09b5217b, name: 'Hummer', price: 41400 },
  { _id: 5cfcfc5438f62aaa09b5217c,
    name: 'Volkswagen',
    price: 21600 } ]

```

这是输出。

## MongoDB 计数文件

`count()`函数返回集合中匹配文档的数量。

`count_documents.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    db.collection('cars').find({}).count().then((n) => {

        console.log(`There are ${n} documents`);

    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例计算`cars`集合中的文档数。

```js
$ node count_documents.js
There are 8 documents

```

现在，汽车收藏集中有八个文件。

## MongoDB `findOne`

`findOne()`方法返回一个满足指定查询条件的文档。 如果多个文档满足查询条件，则此方法将根据反映磁盘上文档顺序的自然顺序返回第一个文档。

`find_one.js`

```js
const MongoClient = require('mongodb').MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let collection = db.collection('cars');
    let query = { name: 'Volkswagen' }

    collection.findOne(query).then(doc => {

        console.log(doc);

    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例从`cars`集合中读取一个文档。

```js
let query = { name: 'Volkswagen' }

```

该查询包含汽车的名称-大众汽车。

```js
collection.findOne(query).then(doc => {

```

该查询将传递给`findOne()`方法。

```js
$ node find_one.js
{ _id: 8, name: 'Volkswagen', price: 21600 }

```

这是示例的输出。

## MongoDB 异步/等待示例

使用`async/await`，我们可以轻松地以同步方式处理 Promise 。

`async_await.js`

```js
const MongoClient = require('mongodb').MongoClient;

const url = 'mongodb://localhost:27017';

async function findCar() {

    const client = await MongoClient.connect(url, { useNewUrlParser: true })
        .catch(err => { console.log(err); });

    if (!client) {
        return;
    }

    try {

        const db = client.db("testdb");

        let collection = db.collection('cars');

        let query = { name: 'Volkswagen' }

        let res = await collection.findOne(query);

        console.log(res);

    } catch (err) {

        console.log(err);
    } finally {

        client.close();
    }
}

findCar();

```

该示例使用`async/await`读取一个文档。

```js
async function findCar() {

```

该函数具有`async`关键字。

```js
let res = await collection.findOne(query);

```

使用`await`，我们等待`findOne()`函数的结果。

## MongoDB 查询运算符

可以使用 MongoDB 查询运算符（例如`$gt`，`$lt`或`$ne`）过滤数据。

`read_gt.js`

```js
const mongo = require('mongodb');

const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let query = { price: { $gt: 30000 } };

    db.collection('cars').find(query).toArray().then((docs) => {

        console.log(docs);

    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例打印汽车价格大于 30,000 的所有文档。

```js
let query = { price: { $gts: 30000 } };

```

`$gt`运算符用于获取价格大于 30,000 的汽车。

```js
$ node read_gt.js
[ { _id: 5d03e40536943362cffc84a7, name: 'Audi', price: 52642 },
  { _id: 5d03e40a36943362cffc84a8, name: 'Mercedes', price: 57127 },
  { _id: 5d03e41936943362cffc84ab, name: 'Bentley', price: 350000 },
  { _id: 5d03e42236943362cffc84ad, name: 'Hummer', price: 41400 } ]

```

这是示例的输出。 仅包括价格超过 30,000 的汽车。

`$and`逻辑运算符可用于组合多个表达式。

`read_gt_lt.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

   if (err) throw err;

   const db = client.db("testdb");

   let query = { $and: [{ price: { $gt: 20000 } }, { price: { $lt: 50000 } }] };

   db.collection('cars').find(query).toArray().then((docs) => {

      console.log(docs);
   }).catch((err) => {

      console.log(err);
   }).finally(() => {

      client.close();
   });
});

```

在示例中，我们检索价格在 20,000 到 50,000 之间的汽车。

```js
let query = { $and: [{ price: { $gt: 20000 } }, { price: { $lt: 50000 } }] };

```

`$and`运算符将`$gt`和`$lt`组合在一起以获得结果。

```js
$ node read_gt_lt.js
[ { _id: 5d03e41336943362cffc84aa, name: 'Volvo', price: 29000 },
  { _id: 5d03e41e36943362cffc84ac, name: 'Citroen', price: 21000 },
  { _id: 5d03e42236943362cffc84ad, name: 'Hummer', price: 41400 },
  { _id: 5d03e42636943362cffc84ae,
    name: 'Volkswagen',
    price: 21600 } ]

```

这是示例的输出。

## MongoDB 预测

投影确定从数据库传递哪些字段。

`projections.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

   if (err) throw err;

   const db = client.db("testdb");

   db.collection('cars').find({}).project({_id: 0}).toArray().then((docs) => {

      console.log(docs);
   }).catch((err) => {

      console.log(err);
   }).finally(() => {

      client.close();
   });
});

```

该示例从输出中排除`_id`字段。

```js
db.collection('cars').find({}).project({_id: 0}).toArray().then((docs) => {

```

`project()`方法设置查询的投影； 它不包括`_id`字段。

```js
$ node projections.js
[ { name: 'Audi', price: 52642 },
  { name: 'Mercedes', price: 57127 },
  { name: 'Skoda', price: 9000 },
  { name: 'Volvo', price: 29000 },
  { name: 'Bentley', price: 350000 },
  { name: 'Citroen', price: 21000 },
  { name: 'Hummer', price: 41400 },
  { name: 'Volkswagen', price: 21600 } ]

```

这是示例的输出。

## MongoDB 限制数据输出

`limit()`方法指定要返回的文档数，`skip()`方法指定要跳过的文档数。

`skip_limit.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

   if (err) throw err;

   const db = client.db("testdb");

   db.collection('cars').find({}).skip(2).limit(5).toArray().then((docs) => {

      console.log(docs);
   }).catch((err) => {

      console.log(err);
   }).finally(() => {

      client.close();
   });
});

```

该示例从`cars`集合中读取，跳过前两个文档，并将输出限制为五个文档。

```js
db.collection('cars').find({}).skip(2).limit(5).toArray().then((docs) => {

```

`skip()`方法跳过前两个文档，`limit()`方法将输出限制为五个文档。

```js
$ node skip_limit.js
[ { _id: 5d03e40f36943362cffc84a9, name: 'Skoda', price: 9000 },
  { _id: 5d03e41336943362cffc84aa, name: 'Volvo', price: 29000 },
  { _id: 5d03e41936943362cffc84ab, name: 'Bentley', price: 350000 },
  { _id: 5d03e41e36943362cffc84ac, name: 'Citroen', price: 21000 },
  { _id: 5d03e42236943362cffc84ad, name: 'Hummer', price: 41400 } ]

```

这是示例的输出。

## MongoDB 聚合

聚合计算集合中数据的聚合值。

`sum_all_cars.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

   if (err) throw err;

   const db = client.db("testdb");

   let myagr = [{$group: {_id: 1, all: { $sum: "$price" } }}];

   db.collection('cars').aggregate(myagr).toArray().then((sum) => {

      console.log(sum);
   }).catch((err) => {

      console.log(err);
   }).finally(() => {

      client.close();
   });
});

```

该示例计算集合中所有汽车的价格。

```js
let myagr = [{$group: {_id: 1, all: { $sum: "$price" } }}];

```

`$sum`运算符计算并返回数值的总和。 `$group`运算符通过指定的标识符表达式对输入文档进行分组，并将累加器表达式（如果指定）应用于每个组。

```js
db.collection('cars').aggregate(myagr).toArray().then((sum) => {

```

`aggregate()`函数将聚合操作应用于`cars`集合。

```js
$ node sum_all_cars.js
[ { _id: 1, all: 581769 } ]

```

所有价格的总和是 581,769。

我们可以使用`$match`运算符来选择要汇总的特定汽车。

`sum_two_cars.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let myagr = [
        { $match: { $or: [{ name: "Audi" }, { name: "Volvo" }] } },
        { $group: { _id: 1, sum2cars: { $sum: "$price" } } }
    ];

    db.collection('cars').aggregate(myagr).toArray().then((sum) => {

        console.log(sum);
    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例计算奥迪和沃尔沃汽车的价格总和。

```js
let myagr = [
    { $match: { $or: [{ name: "Audi" }, { name: "Volvo" }] } },
    { $group: { _id: 1, sum2cars: { $sum: "$price" } } }
];

```

该表达式使用`$match`，`$or`，`$group`和`$sum`运算符执行任务。

```js
$ node sum_two_cars.js
[ { _id: 1, sum2cars: 81642 } ]

```

两辆车的价格之和为 81,642。

## MongoDB `insertOne`

`insertOne()`方法将单个文档插入到集合中。

`insert_one.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;
const ObjectID = mongo.ObjectID;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let doc = {_id: new ObjectID(), name: "Toyota", price: 37600 };

    db.collection('cars').insertOne(doc).then((doc) => {

        console.log('Car inserted')
        console.log(doc);
    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例将一辆汽车插入 cars 集合。

```js
let doc = {_id: new ObjectID(), name: "Toyota", price: 37600 };

```

这是要插入的文档。 使用`ObjectID`生成一个新的 ID。

```js
db.collection('cars').insertOne(doc).then((doc) => {

```

`insertOne()`功能将文档插入到集合中。

```js
> db.cars.find({name:'Toyota'})
{ "_id" : ObjectId("5d03d4321f9c262a50e671ee"), "name" : "Toyota", "price" : 37600 }

```

我们用`mongo`工具确认插入。

## MongoDB `insertMany()`

`insertMany()`功能可将多个文档插入一个集合中。

`insert_many.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;
const ObjectID = mongo.ObjectID;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let collection = db.collection('continents');

    let continents = [
        { _id: new ObjectID(), name: "Africa" }, { _id: new ObjectID(), name: "America" },
        { _id: new ObjectID(), name: "Europe" }, { _id: new ObjectID(), name: "Asia" },
        { _id: new ObjectID(), name: "Australia" }, { _id: new ObjectID(), name: "Antarctica" }
    ];

    collection.insertMany(continents).then(result => {

        console.log("documents inserted into the collection");
    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例创建一个`continents`集合并将六个文档插入其中。

```js
let collection = db.collection('continents');

```

`collection()`方法检索集合； 如果集合不存在，则会创建它。

```js
let continents = [
    { _id: new ObjectID(), name: "Africa" }, { _id: new ObjectID(), name: "America" },
    { _id: new ObjectID(), name: "Europe" }, { _id: new ObjectID(), name: "Asia" },
    { _id: new ObjectID(), name: "Australia" }, { _id: new ObjectID(), name: "Antarctica" }
];

```

这是要插入新集合的六个记录的数组。 `ObjectID()`创建一个新的 ObjectID，这是用于标识文档的唯一值，而不是整数。

```js
collection.insertMany(continents).then(result => {

    console.log("documents inserted into the collection");
}).catch((err) => {

    console.log(err);
}).finally(() => {

    client.close();
});

```

`insertMany()`方法将文档数组插入`continents`集合。

```js
> db.continents.find()
{ "_id" : ObjectId("5cfcf97732fc4913748c9669"), "name" : "Africa" }
{ "_id" : ObjectId("5cfcf97732fc4913748c966a"), "name" : "America" }
{ "_id" : ObjectId("5cfcf97732fc4913748c966b"), "name" : "Europe" }
{ "_id" : ObjectId("5cfcf97732fc4913748c966c"), "name" : "Asia" }
{ "_id" : ObjectId("5cfcf97732fc4913748c966d"), "name" : "Australia" }
{ "_id" : ObjectId("5cfcf97732fc4913748c966e"), "name" : "Antarctica" }

```

`continents`集合已成功创建。

## MongoDB deleteOne

`deleteOne()`方法用于删除文档。

`delete_one.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let query = { name: "Volkswagen" };

    db.collection('cars').deleteOne(query).then((result) => {

        console.log('Car deleted');
        console.log(result);
    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例删除文档。

```js
let query = { name: "Volkswagen" };

db.collection('cars').deleteOne(query).then((result) => {
...

```

`deleteOne()`删除`Volkswagen`的文档。

## MongoDB `updateOne()`

`updateOne()`功能用于更新文档。

`update_one.js`

```js
const mongo = require('mongodb');
const MongoClient = mongo.MongoClient;

const url = 'mongodb://localhost:27017';

MongoClient.connect(url, { useNewUrlParser: true }, (err, client) => {

    if (err) throw err;

    const db = client.db("testdb");

    let filQuery = { name: "Audi" };
    let updateQuery = { $set: { "price": 52000 }};

    db.collection('cars').updateOne(filQuery, updateQuery).then(result => {

        console.log('Car updated');
        console.log(result);

    }).catch((err) => {

        console.log(err);
    }).finally(() => {

        client.close();
    });
});

```

该示例更新了汽车的价格。

```js
let filQuery = { name: "Audi" };
let updateQuery = { $set: { "price": 52000 }};

db.collection('cars').updateOne(filQuery, updateQuery).then(result => {

```

通过`updateOne()`方法将 Audi 的价格更改为 52,000。 `$set`运算符用于更改价格。

```js
> db.cars.find({name:'Audi'})
{ "_id" : ObjectId("5cfcfc3438f62aaa09b52175"), "name" : "Audi", "price" : 52000 }

```

我们使用`mongo`工具确认更改。

在本教程中，我们使用了 MongoDB 和 JavaScript。 列出[所有 JavaScript](/all/#js) 教程。
