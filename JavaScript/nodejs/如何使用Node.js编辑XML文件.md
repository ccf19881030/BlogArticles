由于XML仍然继续用作数据交换格式（主要是在企业应用程序中），因此了解如何以编程方式操纵XML文件的内容可能非常有用。 您可以轻松地在Node.js中编写一个小的脚本来立即进行更改，而不必手动编辑数百行XML。
在[之前的文章](https://attacomsian.com/blog/nodejs-convert-xml-to-json)中，我们研究了如何通过使用开源`xml2js`模块将XML文件转换为Node.js中的JSON对象。 今天，您将学习如何使用Node.js编辑XML文件。

# 基本设置
首先，通过在终端中键入以下命令，将`xml2js`模块添加到您的Node.js应用程序中：
```shell
$ node install xml2js --save
```
接下来，创建一个名为`index.js`的新JavaScript文件，其内容如下：
```index.js
const fs = require("fs");

// read XML file
fs.readFile("databases.xml", "utf-8", (err, data) => {
    if (err) {
        throw err;
    }
    console.log(data);
});
```
上面的代码从磁盘[读取XML文件](https://attacomsian.com/blog/reading-writing-files-nodejs#reading-from-files)并将其打印在控制台上。 这是一个需要更新的XML文件的示例：
`databases.xml`
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<databases>
    <database>
        <name>MySQL</name>
        <type>RDBMS</type>
    </database>
    <database>
        <name>MongoDB</name>
        <type>NoSQL</type>
    </database>
    <database>
        <name>Neo4j</name>
        <type>Graph DB</type>
    </database>
</databases>
```
# 将XML转换成JSON
由于我们现在能够将XML文件读取为字符串，因此可以使用`xml2js.parseString()`方法轻松地将其转换为JSON对象。

让我们更新上面的示例代码，以将XML解析包括到JSON：
```js
const fs = require("fs");
const xml2js = require('xml2js');

// read XML file
fs.readFile("databases.xml", "utf-8", (err, data) => {
    if (err) {
        throw err;
    }

    // convert XML data to JSON object
    xml2js.parseString(data, (err, result) => {
        if (err) {
            throw err;
        }

        // print JSON object
        console.log(JSON.stringify(result, null, 4));

    });
});
```
如果运行上面的代码，则应该在控制台上看到打印出以下JSON对象：
```json
{
    "databases": {
        "database": [
            {
                "name": [
                    "MySQL"
                ],
                "type": [
                    "RDBMS"
                ]
            },
            {
                "name": [
                    "MongoDB"
                ],
                "type": [
                    "NoSQL"
                ]
            },
            {
                "name": [
                    "Neo4j"
                ],
                "type": [
                    "Graph DB"
                ]
            }
        ]
    }
}
```

# 编辑XML
用JavaScript编辑JSON对象非常简单。 让我们用另一个称为`ArangoDB`的图形数据库替换`Neo4j`数据库：
```js
// replace `Neo4j` with `ArangoDB`
result.databases.database[2].name = 'ArangoDB';
```
您还可以将新数据库添加到现有数据库列表中：
```js
// add a new database to list
const postgres = {
    name: 'PostgreSQL',
    type: 'RDBMS'
};

result.databases.database.push(postgres);
```

经过以上修改，我们更新后的示例代码如下所示：
```js
const fs = require("fs");
const xml2js = require('xml2js');

// read XML file
fs.readFile("databases.xml", "utf-8", (err, data) => {
    if (err) {
        throw err;
    }

    // convert XML data to JSON object
    xml2js.parseString(data, (err, result) => {
        if (err) {
            throw err;
        }

        // replace `Neo4j` with `ArangoDB`
        result.databases.database[2].name = 'ArangoDB';

        // add a new database to list
        const postgres = {
            name: 'PostgreSQL',
            type: 'RDBMS'
        };

        result.databases.database.push(postgres);

        // print JSON object
        console.log(JSON.stringify(result, null, 4));

    });
});
```

# 将JSON转换成XML
现在，我们已经成功修改了JSON对象，我们可以将其转换回XML字符串，最后将其写入文件：
```xml
const fs = require("fs");
const xml2js = require('xml2js');

// read XML file
fs.readFile("databases.xml", "utf-8", (err, data) => {
    if (err) {
        throw err;
    }

    // convert XML data to JSON object
    xml2js.parseString(data, (err, result) => {
        if (err) {
            throw err;
        }

        // replace `Neo4j` with `ArangoDB`
        result.databases.database[2].name = 'ArangoDB';

        // add a new database to list
        const postgres = {
            name: 'PostgreSQL',
            type: 'RDBMS'
        };

        result.databases.database.push(postgres);

        // convert JSON objec to XML
        const builder = new xml2js.Builder();
        const xml = builder.buildObject(result);

        // write updated XML string to a file
        fs.writeFile('new-databases.xml', xml, (err) => {
            if (err) {
                throw err;
            }

            console.log(`Updated XML is written to a new file.`);
        });

    });
});
```

仅此而已。 运行上面的代码，您应该在与Node.js脚本文件相同的目录中看到一个由更新的XML生成的新XML文件。

阅读下一篇：[如何在Node.js中将XML转换为JSON](https://attacomsian.com/blog/nodejs-convert-xml-to-json)

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

# 相关博客
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
