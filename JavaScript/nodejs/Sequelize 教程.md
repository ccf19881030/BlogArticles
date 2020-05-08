# Sequelize 教程

> 原文： [http://zetcode.com/javascript/sequelize/](http://zetcode.com/javascript/sequelize/)

Sequelize 教程展示了如何使用 Sequelize ORM 在 JavaScript 中对数据库进行编程。

## Sequelize 

Sequelize 是 Node.js 的基于 Promise 的 ORM。 它可与 PostgreSQL，MySQL，SQLite 和 MSSQL 方言配合使用，并具有可靠的事务支持，关系，读取复制等功能。

对象关系映射（ORM）是一种从面向对象的语言访问关系数据库的技术。

在本教程中，我们使用 MySQL。

## 设置续集

我们初始化一个 Node 应用并安装 Sequelize 和 MySQL 适配器。

```js
$ nodejs -v
v10.12.0

```

我们使用 Node 版本 10.12.0。

```js
$ npm init

```

我们启动一个新的 Node 应用。

```js
$ npm i sequelize
$ nmp i mysql2 

```

我们安装 Seqelize 和 MySQL 驱动程序。 有两个驱动程序可用：`mysql`和`mysql2`; 我们选择了后者。

## Sequelize 认证

在第一个示例中，我们创建与 MySQL 数据库的连接。

`authenticate.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/testdb';
const sequelize = new Sequelize(path, { operatorsAliases: false });

sequelize.authenticate().then(() => {
  console.log('Connection established successfully.');
}).catch(err => {
  console.error('Unable to connect to the database:', err);
}).finally(() => {
  sequelize.close();
});

```

该示例在连接到 MySQL 数据库时显示一条消息。

```js
const Sequelize = require('sequelize');

```

我们加载 Sequelize 模块。

```js
const path = 'mysql://user12:12user@localhost:3306/testdb';

```

这是 MySQL 连接路径。 它包含用户名，密码，主机名，数据库端口和数据库名称。

```js
const sequelize = new Sequelize(path, { operatorsAliases: false });

```

我们实例化 Sequelize。

```js
sequelize.authenticate().then(() => {
  console.log('Connection established successfully.');
...  

```

`authenticate()`方法通过尝试向数据库进行身份验证来测试连接。 建立连接后，我们将打印一条消息。

```js
}).catch(err => {
  console.error('Unable to connect to the database:', err);
...  

```

如果发生错误，我们将打印一条错误消息。

```js
}).finally(() => {
  sequelize.close();
});

```

最后，我们关闭数据库连接。

```js
$ node authenticate.js
Executing (default): SELECT 1+1 AS result
Connection established successfully

```

这是输出。 输出也包括调试输出。

## Sequelize 模型定义

`Model`代表数据库中的表。 此类的实例代表数据库行。 Sequelize 的`define()`方法定义了一个新模型。

`define_model.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false
});

let Dummy = sequelize.define('dummy', {
    description: Sequelize.STRING
});

Dummy.sync().then(() => {
    console.log('New table created');
}).finally(() => {
    sequelize.close();
})

```

该示例创建一个简单的模型。 它将模型保存到数据库表中。

```js
let Dummy = sequelize.define('dummy', {
    description: Sequelize.STRING
});

```

创建了一个新模型`Dummy`。 第一个参数是型号名称。 第二个参数由属性组成，这些属性是表列。 在我们的例子中，我们有一个列名`description`，它是 String 类型。

```js
Dummy.sync().then(() => {
    console.log('New table created');
}).finally(() => {
    sequelize.close();
})

```

`sync()`方法将模型同步到数据库。 实际上，它将创建一个新的`dummies`表。 （表名是复数的。）

```js
$ node model_define.js
Executing (default): CREATE TABLE IF NOT EXISTS `dummies` (`id` INTEGER 
NOT NULL auto_increment , `description` VARCHAR(255), 
`createdAt` DATETIME NOT NULL, `updatedAt` DATETIME NOT NULL, 
PRIMARY KEY (`id`)) ENGINE=InnoDB;
Executing (default): SHOW INDEX FROM `dummies`
New table created

```

这是输出。 默认情况下，Sequelize 提供日志记录。 可以使用`logging`选项将其关闭。

```js
mysql> describe dummies;
+-------------+--------------+------+-----+---------+----------------+
| Field       | Type         | Null | Key | Default | Extra          |
+-------------+--------------+------+-----+---------+----------------+
| id          | int(11)      | NO   | PRI | NULL    | auto_increment |
| description | varchar(255) | YES  |     | NULL    |                |
| createdAt   | datetime     | NO   |     | NULL    |                |
| updatedAt   | datetime     | NO   |     | NULL    |                |
+-------------+--------------+------+-----+---------+----------------+
4 rows in set (0.00 sec)

```

我们检查在 MySQL 中创建的表。 Sequelize 还创建了另外两个列：`createdAt`和`updatedAt`。 可以使用`timestamps`选项将其关闭。

## Sequelize 删除表

用`drop()`方法删除一个表。

`drop_table.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Dummy = sequelize.define('dummy', {
    description: Sequelize.STRING
});

Dummy.drop().then(() => {
    console.log('table deleted');
}).finally(() => {
    sequelize.close();
});

```

该示例删除`dummies`表。

## Sequelize 时间戳

Sequelize 自动为模型添加时间戳。 我们可以使用`timestamps`控制此行为。

`timestamps.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false,
    define: {
        timestamps: false
    }
});

let Dummy = sequelize.define('dummy', {
    description: Sequelize.STRING
});

sequelize.sync({force: true}).then(() => {

    Dummy.create({ description: 'test 1' }).then(() => {
        console.log('table created');
    }).finally(() => {
        sequelize.close();
    });
});

```

该示例创建一个没有时间戳的表。

```js
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false,
    define: {
        timestamps: false
    }
});

```

在这里，我们关闭时间戳记。

```js
mysql> describe dummies;
+-------------+--------------+------+-----+---------+----------------+
| Field       | Type         | Null | Key | Default | Extra          |
+-------------+--------------+------+-----+---------+----------------+
| id          | int(11)      | NO   | PRI | NULL    | auto_increment |
| description | varchar(255) | YES  |     | NULL    |                |
+-------------+--------------+------+-----+---------+----------------+
2 rows in set (0.00 sec)

```

我们确认表中没有时间戳。

## Sequelize 批量创建

`bulkCreate()`方法创建并批量插入多个实例。 该方法采用对象数组。

`bulk_create_notes.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

let notes = [
    { description: 'Tai chi in the morning' },
    { description: 'Visited friend' },
    { description: 'Went to cinema' },
    { description: 'Listened to music' },
    { description: 'Watched TV all day' },
    { description: 'Walked for a hour' },
];

sequelize.sync({ force: true }).then(() => {
    Note.bulkCreate(notes, { validate: true }).then(() => {
        console.log('notes created');
    }).catch((err) => {
        console.log('failed to create notes');
        console.log(err);
    }).finally(() => {
        sequelize.close();
    });
});

```

表格示例记录了几行。

```js
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

```

我们禁用日志记录。

```js
sequelize.sync({ force: true }).then(() => {

```

`sqeuelize.syn()`同步所有型号。 在`force`选项丢弃的表，如果它的创建之前就存在。

```js
Note.bulkCreate(notes, { validate: true }).then(() => {
    console.log('notes created');
...    

```

`bulkCreate()`创建具有六行的表格。

```js
mysql> select * from notes;
+----+------------------------+---------------------+---------------------+
| id | description            | createdAt           | updatedAt           |
+----+------------------------+---------------------+---------------------+
|  1 | Tai chi in the morning | 2018-10-21 14:34:28 | 2018-10-21 14:34:28 |
|  2 | Visited friend         | 2018-10-21 14:34:28 | 2018-10-21 14:34:28 |
|  3 | Went to cinema         | 2018-10-21 14:34:28 | 2018-10-21 14:34:28 |
|  4 | Listened to music      | 2018-10-21 14:34:28 | 2018-10-21 14:34:28 |
|  5 | Watched TV all day     | 2018-10-21 14:34:28 | 2018-10-21 14:34:28 |
|  6 | Walked for a hour      | 2018-10-21 14:34:28 | 2018-10-21 14:34:28 |
+----+------------------------+---------------------+---------------------+
6 rows in set (0.00 sec)

```

这是在数据库中创建的表。

## Sequelize `build()`和`save()`

使用`build()`和`save()`分两步或使用`create()`一步创建新行。

`build_save.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

const note = Note.build({ description: 'Took a cold bath' });
note.save().then(() => {
    console.log('new task saved');
}).finally(() => {
    sequelize.close();
});

```

本示例使用`build()`和`save()`创建一个新的 not。

## Sequelize `findById`

使用`findById()`，我们通过其 ID 查找特定行。

`find_by_id.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';

const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

Note.findById(2).then((note) => {
    console.log(note.get({ plain: true }));
    console.log('********************')
    console.log(`id: ${note.id}, description: ${note.description}`);
}).finally(() => {
    sequelize.close();
});

```

该示例查找带有 ID 2 的注释。

```js
console.log(note.get({ plain: true }));

```

默认情况下，Sequelize 返回大量元数据。 要关闭数据，我们使用`plain: true`选项。

```js
$ node find_by_id.js
{ id: 2,
  description: 'Visited friend',
  createdAt: 2018-10-21T14:34:28.000Z,
  updatedAt: 2018-10-21T14:34:28.000Z }
********************
id: 2, description: Visited friend

```

我们将行打印两次。 在第一种情况下，我们返回所有数据。 在第二种情况下，我们仅选择两个字段。

## Sequelize `findOne`

`findOne()`方法搜索单个行。

`find_one.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';

const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

Note.findOne({ where: { id: 1 } }).then(note => {
    console.log(note.get({ plain: true }));
}).finally(() => {
    sequelize.close();
});

```

该示例使用`find_one()`返回表的第一行。 `where`选项指定要查找的 ID。

```js
$ node find_one.js
{ id: 1,
  description: 'Tai chi in the morning',
  createdAt: 2018-10-21T14:34:28.000Z,
  updatedAt: 2018-10-21T14:34:28.000Z }

```

这是输出。

## Sequelize `async`和`await`

在下一个示例中，我们使用`async`和`await`关键字。

`find_one2.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';

const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function getOneNote() {

    let user = await Note.findOne();

    console.log(user.get('description'));
    sequelize.close();
}

getOneNote();

```

我们使用`async`和`await`关键字返回带有`findOne()`的第一行。

## Sequelize 计数

`count()`方法计算表中的行数。

`count_rows.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function countRows() {

    let n = await Note.count();
    console.log(`There are ${n} rows`);

    sequelize.close();
}

countRows();

```

该示例计算`notes`表中的行数。

```js
$ node count_rows.js
There are 7 rows

```

目前，表格中有 7 行。

## Sequelize 删除行

使用`destroy()`方法删除一行。 它返回已删除的行数。

`delete_row.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function deleteRow() {

    let n = await Note.destroy({ where: { id: 2 } });
    console.log(`number of deleted rows: ${n}`);

    sequelize.close();
}

deleteRow();

```

该示例删除 ID 为 2 的行。

## Sequelize 更新行

用`update()`方法更新一行。

`update_row.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function updateRow() {

    let id = await Note.update(
        { description: 'Finished reading history book' },
        { where: { id: 1 } });
    sequelize.close();
}

updateRow();

```

该示例更新了第一行的描述。

## Sequelize `findAll`

`findAll()`方法搜索多个实例。

`find_all.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function findAllRows() {

    let notes = await Note.findAll({ raw: true });
    console.log(notes);

    sequelize.close();
}

findAllRows();

```

该示例使用`findAll()`从数据库表中检索所有行。

```js
let notes = await Note.findAll({ raw: true });

```

`raw: true`选项关闭元数据。

```js
$ node find_all.js
[ { id: 1,
    description: 'Finished reading history book',
    createdAt: 2018-10-21T14:34:28.000Z,
    updatedAt: 2018-10-21T16:00:22.000Z },
  { id: 2,
    description: 'Visited friend',
    createdAt: 2018-10-21T14:34:28.000Z,
    updatedAt: 2018-10-21T14:34:28.000Z },
  { id: 3,
    description: 'Went to cinema',
    createdAt: 2018-10-21T14:34:28.000Z,
    updatedAt: 2018-10-21T14:34:28.000Z },
  { id: 4,
    description: 'Listened to music',
    createdAt: 2018-10-21T14:34:28.000Z,
    updatedAt: 2018-10-21T14:34:28.000Z },
  { id: 5,
    description: 'Watched TV all day',
    createdAt: 2018-10-21T14:34:28.000Z,
    updatedAt: 2018-10-21T14:34:28.000Z },
  { id: 6,
    description: 'Walked for a hour',
    createdAt: 2018-10-21T14:34:28.000Z,
    updatedAt: 2018-10-21T14:34:28.000Z },
  { id: 7,
    description: 'Took a cold bath',
    createdAt: 2018-10-21T14:49:51.000Z,
    updatedAt: 2018-10-21T14:49:51.000Z } ]

```

该示例返回了七行。

## Seqelize 选择列

使用`attributes`选项，我们可以选择要包括在查询中的列。

`columns.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function getTwoColumns() {

    let notes = await Note.findAll({ attributes: ['id', 'description'], raw: true });
    console.log(notes);

    sequelize.close();
}

getTwoColumns();

```

在示例中，我们选择`id`和`description`列。

```js
$ node columns.js
Executing (default): SELECT `id`, `description` FROM `notes` AS `notes`;
[ { id: 1, description: 'Finished reading history book' },
  { id: 3, description: 'Went to cinema' },
  { id: 4, description: 'Listened to music' },
  { id: 5, description: 'Watched TV all day' },
  { id: 6, description: 'Walked for a hour' } ]

```

这是输出。

## Seqelize `offset`和`limit`

使用`offset`和`limit`属性，我们可以定义`findAll()`方法中要包括的行的初始跳过和行数。

`offset_limit.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function getRows() {

    let notes = await Note.findAll({ offset: 2, limit: 3, 
        attributes: ['id', 'description'], raw: true
    });

    console.log(notes);

    sequelize.close();
}

getRows();

```

该示例从第二行开始还原三行。

```js
$ node offset_limit.js
[ { id: 3, description: 'Went to cinema' },
  { id: 4, description: 'Listened to music' },
  { id: 5, description: 'Watched TV all day' } ]

```

这是输出。

## Seqelize 顺序排序

为了在查询中包含`ORDER BY`子句，我们使用`order`选项。

`order_by.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function getRows() {

    let notes = await Note.findAll({
        order: [['description', 'DESC']],
        attributes: ['id', 'description'], raw: true
    })

    console.log(notes);

    sequelize.close();
}

getRows();

```

在示例中，我们从表中选择所有行，并按描述以降序对其进行排序。

```js
$ node order_by.js
Executing (default): SELECT `id`, `description` FROM `notes` AS `notes` 
    ORDER BY `notes`.`description` DESC;
[ { id: 3, description: 'Went to cinema'}, { id: 5, description: 'Watched TV all day' },
  { id: 6, description: 'Walked for a hour'}, { id: 2, description: 'Visited friend' },
  { id: 1, description: 'Tai chi in the morning' },
  { id: 4, description: 'Listened to music' } ]

```

从输出中我们可以看到`ORDER BY`子句已添加到查询中。

## Seqelize `Op.IN`运算符

使用`Op.IN`运算符，我们可以确定指定的值是否与子查询或列表中的任何值匹配。

`operator_in.js`

```js
const Sequelize = require('sequelize');
const Op = Sequelize.Op;

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function getRows() {

    let notes = await Note.findAll({ where: { id: { [Op.in]: [3, 6] } } });

    notes.forEach(note => {
        console.log(`${note.id}: ${note.description}`);
    });

    sequelize.close();
}

getRows();

```

在示例中，我们选择与 ID 列表匹配的所有行。

```js
$ node operator_in.js
3: Went to cinema
6: Walked for a hour

```

输出显示两行：ID 为 3 和 6。

## Seqelize `Op.between`运算符

使用`Op.between`运算符，我们可以确定指定值是否与给定范围内的任何值匹配。

`operator_between.js`

```js
const Sequelize = require('sequelize');
const Op = Sequelize.Op;

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Note = sequelize.define('notes', {
    description: Sequelize.STRING
});

async function getRows() {

    let notes = await Note.findAll({ where: { id: { [Op.between]: [3, 6] } }});

    notes.forEach(note => {
        console.log(`${note.id}: ${note.description}`);
    });

    sequelize.close();
}

getRows();

```

该示例使用`Op.between`运算符显示行 3..6。

## Sequelize `belongsTo`

Sequelize `belongsTo`在源模型和提供的目标模型之间创建一对一的关联。 外键添加在源上。

`belongs_to.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Employee = sequelize.define('employees', {
    name: Sequelize.STRING
});

let Project = sequelize.define('projects', {
    name: Sequelize.STRING
});

Employee.belongsTo(Project);

let employees = [
    { name: 'Jane Brown' }, { name: 'Lucia Benner' }, { name: 'Peter Novak' }
];

sequelize.sync({ force: true }).then(() => {
    return Employee.bulkCreate(employees);
}).then((employees) => {

    let works = [];
    let i = 0;

    employees.forEach(employee => {

        let pname = 'Project ' + String.fromCharCode('A'.charCodeAt() + i);
        i++;

        let work = Project.create({ name: pname }).then(project => {

            employee.setProject(project);
        });

        works.push(work);

    });

    Promise.all(works).then(() => sequelize.close());
    console.log('finish');

});

```

在示例中，我们有两个模型：`Employee`和`Project`。 我们使用`belongsTo`在两个模型之间创建一对一关联。 我们将数据添加到模型中。

```js
let Employee = sequelize.define('employees', {
    name: Sequelize.STRING
});

let Project = sequelize.define('projects', {
    name: Sequelize.STRING
});

```

我们定义了两个模型。

```js
Employee.belongsTo(Project);

```

我们在`Employee`和`Project`模型之间创建一对一关联。 外键在`Employee`中生成。

```js
let employees = [
    { name: 'Jane Brown' }, { name: 'Lucia Benner' }, { name: 'Peter Novak' }
];

```

我们将创建三名员工。

```js
let works = [];

```

`works`数组用于存储生成的 Promise。

```js
employees.forEach(employee => {

    let pname = 'Project ' + String.fromCharCode('A'.charCodeAt() + i);
    i++;

    let work = Project.create({ name: pname }).then(project => {

        employee.setProject(project);
    });

    works.push(work);

});

```

我们遍历所有员工，并为每个员工生成一个新项目。 `setProject()`添加了一个新项目。 `Project.create()`生成一个新的 Promise，将其添加到`works`数组中。

```js
Promise.all(works).then(() => sequelize.close());

```

`Promise.all()`解析数组中的所有 promise。

接下来，我们检索联接的数据。 当我们生成还从其他表中获取关联数据的查询时，我们会渴望加载。 通过`include`选项启用了预先加载。

`belongs_to2.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Employee = sequelize.define('employees', {
    name: Sequelize.STRING
});

let Project = sequelize.define('projects', {
    name: Sequelize.STRING
});

Employee.belongsTo(Project);

Employee.findAll({include: [Project]}).then(employees => {

    employees.forEach(employee => {
        console.log(`${employee.name} is in project ${employee.project.name}`);
    });
}).finally(() => {
    sequelize.close();
});

```

该示例列出了员工及其项目。

```js
Employee.findAll({include: [Project]}).then(employees => {

```

在查询中，我们添加`include`选项，其中包括关联的模型。

```js
$ node belongs_to2.js 
Jane Brown is in project Project A
Lucia Benner is in project Project B
Peter Novak is in project Project C

```

这是输出。

## 双向化一对一关系

双向关系在两个方向上均有效。 我们可以从源模型参考目标模型，反之亦然。 为了在模型之间创建双向一对一关系，我们将其与`belongsTo()`和`hasOne()`映射。

`bidi_one2one.js`

```js
const Sequelize = require('sequelize');

const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let Employee = sequelize.define('employees', {
    name: Sequelize.STRING
});

let Project = sequelize.define('projects', {
    name: Sequelize.STRING
});

Employee.belongsTo(Project);
Project.hasOne(Employee);

Project.findAll({include: [Employee]}).then(projects => {

    projects.forEach(project => {
        console.log(`${project.name} belongs to user ${project.employee.name}`);
    });
}).finally(() => {
    sequelize.close();
});

```

在此示例中，我们从每个项目中检索一名员工。

```js
Employee.belongsTo(Project);
Project.hasOne(Employee);

```

为了实现双向关联，我们还使用`hasOne()`映射了模型。

```js
$ node bidi_one2one.js
Project A belongs to user Jane Brown
Project B belongs to user Lucia Benner
Project C belongs to user Peter Novak

```

这是输出。

## Sequelize `hasMany`

Sequelize `hasMany`在源和提供的目标之间创建多对一关联。 外键添加到目标上。

`one_to_many.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let User = sequelize.define('user', {
    name: Sequelize.STRING,
});

let Task = sequelize.define('task', {
    description: Sequelize.STRING,
});

User.hasMany(Task);

async function createTables() {

    await User.sync();
    await Task.sync();

    console.log('done');
    sequelize.close();
}

createTables();

```

首先，我们创建两个表：`users`和`tasks`。

在第二步中，我们用数据填充表。

`one_to_many2.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let User = sequelize.define('user', {
    name: Sequelize.STRING
});

let Task = sequelize.define('task', {
    description: Sequelize.STRING,
});

User.hasMany(Task);

let mytasks1 = [
    { description: 'write memo' }, { description: 'check accounts' }
];

let mytasks2 = [
    { description: 'make two phone calls' },
    { description: 'read new emails' },
    { description: 'arrange meeting' }
];

async function addUsersTasks() {

    let user1 = await User.create({ name: 'John Doe' });
    let tasks1 = await Task.bulkCreate(mytasks1);

    await user1.setTasks(tasks1);

    let user2 = await User.create({ name: 'Debbie Griffin' });
    let tasks2 = await Task.bulkCreate(mytasks2);

    await user2.setTasks(tasks2);

    console.log('done');
    sequelize.close();
}

addUsersTasks();

```

我们有两个执行某些任务的用户。

```js
let user1 = await User.create({ name: 'John Doe' });

```

使用`User.create()`创建一个新用户。

```js
let tasks1 = await Task.bulkCreate(mytasks1);

```

使用`Task.bulkCreate()`生成新任务。

```js
await user1.setTasks(tasks1);

```

使用`setTasks()`将任务添加到用户。

最后，我们检索数据。

`one_to_many3.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let User = sequelize.define('user', {
    name: Sequelize.STRING
});

let Task = sequelize.define('task', {
    description: Sequelize.STRING,
});

User.hasMany(Task);

async function showUsersTasks() {

    let users = await User.findAll({ include: [Task] });

    users.forEach(user => {

        console.log(`${user.name} has tasks: `);

        let tasks = user.tasks;

        tasks.forEach(task => {
            console.log(`  * ${task.description}`);
        })
    });

    console.log('done');
    sequelize.close();
}

showUsersTasks();

```

在示例中，我们显示了所有用户及其关联的任务。

```js
let users = await User.findAll({ include: [Task] });

```

要启用紧急加载，我们使用`include`选项。 急切的加载是在查询中也检索关联的数据时。

```js
$ node one_to_many3.js
John Doe has tasks:
  * write memo  * check accountsDebbie Griffin has tasks:
  * make two phone calls  * read new emails
  * arrange meeting
done

```

这是输出。

## 双向一对多关系

双向一对多关系在两个方向上均有效。 为了在模型之间建立双向的一对多关系，我们使用`hasMany()`和`belongsTo()`映射它们。

`bidi_one2many.js`

```js
const Sequelize = require('sequelize');
const path = 'mysql://user12:12user@localhost:3306/mydb';
const sequelize = new Sequelize(path, {
    operatorsAliases: false,
    logging: false
});

let User = sequelize.define('user', {
    name: Sequelize.STRING
});

let Task = sequelize.define('task', {
    description: Sequelize.STRING
});

User.hasMany(Task);
Task.belongsTo(User);

async function showTaskUser() {

    let task = await Task.findOne({ include: [User] });

    console.log(`${task.description} belongs to ${task.user.name}`);

    sequelize.close();
}

showTaskUser();

```

该示例从检索的任务中获取用户。

```js
User.hasMany(Task);
Task.belongsTo(User);

```

为了实现双向一对一关系，我们使用`hasMany()`和`belongsTo()`映射模型。

```js
$ node bidi_one2many.js
write memo belongs to John Doe

```

这是输出。

在本教程中，我们使用了`Seqeulize`库。 我们创建了一些与 MySQL 交互的命令行程序。

您可能也对以下相关教程感兴趣： [Knex.js 教程](/javascript/knex/)， [Node Postgres 教程](/javascript/nodepostgres/)， [Lodash 教程](/javascript/lodash/)，[书架教程](/javascript/bookshelf/)， 或列出[所有 JavaScript 教程](/all/#js)。
