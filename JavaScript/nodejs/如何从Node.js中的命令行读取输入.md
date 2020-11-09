本文翻译自[How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)

## readline内置模块

您是否正在使用Node.js中开发一个小的CLI工具，并希望能够提示用户从命令行输入输入？ Node.js正是为此目的提供了[readline](https://nodejs.org/api/readline.html)模块。 它提供了一个接口，用于从可读流（例如`process.stdin`）中一次读取一行数据。

这是一个简单的示例，提示用户输入其姓名和国籍，然后在控制台上打印这些详细信息：
```js
const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// ask user for the anme input
rl.question(`What's your name? `, (name) => {

    // ask for nationality
    rl.question(`What are you from? `, (country) => {

        // log user details
        console.log(`${name} is from ${country}`);

        // close the stream
        rl.close();
    });

});
```
在上面的示例中，`readline.createInterface()`方法用于通过定义可读和可写流来创建readline的实例。

`rl.question()`方法显示查询（问题），并等待用户输入答案。 输入数据可用后，它将调用回调方法，并将用户输入作为第一个参数。

最后，我们在最终的回调中调用`rl.close()`方法以关闭`readline`接口。 您还可以侦听在关闭流时调用的`close`事件。 进行一些后期提问可能会很有用：
```js
// listen for close event
rl.on('close', () => {
    console.log("Goodbye 👋");

    // exit the process
    process.exit(0);
    
});
```
查看`readline`[文档](https://nodejs.org/api/readline.html)以了解有关所有可用方法和事件的更多信息。


## 第三方模块-prompt 
`readline`模块是一个低级Node.js软件包，对于复杂的用例，您可能会认为它太复杂了。 如果要使用更高级别的界面来处理用户输入，只需使用Node Package Manager（NPM）中的[`prompt`](https://www.npmjs.com/package/prompt)模块。 您可以通过执行以下命令将其添加到您的项目中：
```shell
$ npm install prompt --save
```
如果使用`yarn`作为包管理工具，可以执行如下命令添加`prompt`模块:
```shell
$ yarn add prompt --dev
```
与`readline模块相比，使用`prompt` 相对容易。 您无需显式配置可读和可写流。

让我们使用提示模块重写以上示例：
```js
const prompt = require('prompt');

// start the prompt
prompt.start();

// ask user for the input
prompt.get(['name', 'country'], (err, result) => {
    if (err) {
        throw err;
    }

    // print user details
    console.log(`${result.name} is from ${result.country}`);

});
```
### 处理密码
提示模块可以更轻松地安全地要求用户输入密码。 它将屏蔽输入，而不显示密码的实际字符：
```js
const prompt = require('prompt');

// start the prompt
prompt.start();

// define properties schema
var schema = {
    properties: {
        name: {
            pattern: /^[a-zA-Z\s\-]+$/,
            message: 'Name must be only letters, spaces, or dashes',
            required: true
        },
        password: {
            hidden: true
        }
    }
};


// ask user for the input
prompt.get(schema, (err, result) => {
    if (err) {
        throw err;
    }

    // print user credentials
    console.log(`${result.name} / ${result.password}`);

});
```
注意上例中的pattern`属性。 它确保在移至下一个属性输入之前，正确验证了我们从用户那里收到的`name`属性输入。

### 向对象添加属性
提示模块提供了另一个名为`addProperties()`的便捷方法，可通过从命令行添加属性数据来扩展现有对象：
```js
const prompt = require('prompt');

// start the prompt
prompt.start();

// create an object
const user = {
    name: 'John Doe',
    country: 'USA'
};

// extend `user` object
prompt.addProperties(user, ['email', 'age'], (err) => {
    if (err) {
        throw err;
    }

    // print modified object
    console.dir(user);

});
```

现在，如果您运行上述程序，您应该会看到类似于以下内容的输出：
```BASH
$ node index.js
prompt: email:  john.doe@example.com
prompt: age:  23
{ name: 'John Doe',
  country: 'USA',
  email: 'john.doe@example.com',
  age: '23' }
  ```
  如上所示，`prompt`是高度可定制的。 请查阅官方[文档](https://www.npmjs.com/package/prompt)以获取更多信息。 如果您打算在Node.js中构建可靠的CLI工具，则`prompt`可能是一个很好的选择。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

## 其他资料
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
- [nodejs的readline模块](https://nodejs.org/api/readline.html)
- [nodejs命令行提示第三方库-prompt](https://www.npmjs.com/package/prompt)
A beautiful command-line prompt for node.js
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)

