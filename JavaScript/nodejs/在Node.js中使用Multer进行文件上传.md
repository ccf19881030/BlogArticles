几个月前，我写了一篇有关如何使用`express-fileupload`中间件在Node.js和Express中上传文件的[文章](https://attacomsian.com/blog/uploading-files-nodejs-express)。
# 什么是Multer？
如前所述，Multer是用于处理`multipart/form-data`请求的Express中间件。 当用户将文件上传到服务器时，浏览器会自动将请求编码为`multipart/form-data`。 Multer使在服务器上轻松处理此类请求变得容易。

## 项目设置
让我们为演示项目创建一个新目录，并通过键入以下命令切换到该目录：
```shell
$mkdir express-multer && cd express-multer
```
接下来，通过运行以下命令来创建`package.json`文件：
```shell
$ npm init -y
```

现在安装Multer，Express和其他必需的依赖项：
```shell
$ npm install express multer body-parser cors morgan --save
```

## 基本的Express服务器
现在让我们创建一个基本的Express服务器。 首先，创建一个index.js文件：
```shell
$ touch index.js
```

将以下代码复制并粘贴到其中，以初始化所有模块并启动Express应用程序：
`index.js`
```index.js
const express = require('express');
const multer = require('multer');
const cors = require('cors');
const bodyParser = require('body-parser');
const morgan = require('morgan');

// create express app
const app = express();

// upload file path
const FILE_PATH = 'uploads';

// configure multer
const upload = multer({
    dest: `${FILE_PATH}/`
});

// enable CORS
app.use(cors());

// add other middleware
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(morgan('dev'));

// start the app 
const port = process.env.PORT || 3000;

app.listen(port, () =>
    console.log(`App is listening on port ${port}.`)
);
```

上面的代码将Multer配置为接受`multipart/form-data`文件的上传请求并将其保存到`uploads`文件夹，启用跨域原始资源共享（CORS），并在端口`3000`上启动Express服务器。

## 上传单文件
让我们在Express应用程序中创建第一个路由，以允许用户上传其个人资料图片：

```js
app.post('/upload-avatar', upload.single('avatar'), async (req, res) => {
    try {
        const avatar = req.file;

        // make sure file is available
        if (!avatar) {
            res.status(400).send({
                status: false,
                data: 'No file is selected.'
            });
        } else {
            // send response
            res.send({
                status: true,
                message: 'File is uploaded.',
                data: {
                    name: avatar.originalname,
                    mimetype: avatar.mimetype,
                    size: avatar.size
                }
            });
        }

    } catch (err) {
        res.status(500).send(err);
    }
});
```

上面的函数接收一个HTTP POST请求。 `upload.single('avatar')`是Multer中间件，它接受字段名称为`avatar`的单个文件，将其上传到目标文件夹，并将`file`属性添加到`req`对象。
我们可以使用`req.file`属性访问上传的文件。 它具有以下重要信息：
- `fieldname` —表单中使用的字段名称
- `originalname`-用户计算机上文件的名称
- `encoding` —文件的编码类型
- `mimetype`—文件的Mime类型
- `size` —文件大小，以字节为单位

在单个文件上传路由中，我们仅使用这些属性即可返回上传文件的详细信息。

## 上传多个文件
让我们添加另一条路由。 这次一次上传多个文件：
```js
app.post('/upload-photos', upload.array('photos', 8), async (req, res) => {
    try {
        const photos = req.files;

        // check if photos are available
        if (!photos) {
            res.status(400).send({
                status: false,
                data: 'No photo is selected.'
            });
        } else {
            let data = [];

            // iterate over all photos
            photos.map(p => data.push({
                name: p.originalname,
                mimetype: p.mimetype,
                size: p.size
            }));

            // send response
            res.send({
                status: true,
                message: 'Photos are uploaded.',
                data: data
            });
        }

    } catch (err) {
        res.status(500).send(err);
    }
});
```

使用Multer上传多个文件类似于对单个文件上传但有一些更改。 Multer中间件现在接受一个文件数组作为输入，一次最多8个文件。 字段名称也更改为`photos`。

## 测试应用程序
通过在终端的项目根目录中运行以下命令来启动Express应用程序：
```shell
$ node index.js
```

它将在端口`3000`上启动应用程序。让我们使用[Postman](https://www.getpostman.com/)发送HTTP `multipart/form-data`请求：

## 单文件
![Single File](https://img-blog.csdnimg.cn/20201015203025236.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 多个文件
![Multiple Files](https://img-blog.csdnimg.cn/20201015203050944.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 文件大小限制
如果要限制文件大小，请将`limits`属性添加到传递给`multer()`的对象中：
```js
const upload = multer({
    dest: `${FILE_PATH}/`,
    limits: {
        files: 5, // allow up to 5 files per request,
        fieldSize: 2 * 1024 * 1024 // 2 MB (max file size)
    }
});
```

## 过滤文件类型
有时我们只允许用户上传图像。 您可以使用`fileFilter`属性轻松限制文件类型：
```js
const upload = multer({
    dest: `${FILE_PATH}/`,
    limits: {
        files: 5, // allow up to 5 files per request,
        fieldSize: 2 * 1024 * 1024 // 2 MB (max file size)
    },
    fileFilter: (req, file, cb) => {
        // allow images only
        if (!file.originalname.match(/\.(jpg|jpeg|png|gif)$/)) {
            return cb(new Error('Only image are allowed.'), false);
        }
        cb(null, true);
    }
});
```
源代码：在MIT许可下从[GitHub](https://github.com/attacomsian/code-examples/tree/master/nodejs/express-multer)下载完整的源代码。

## 结论
今天就这些。 您已经了解了如何在Node.js中使用Express和Multer上传文件。 Multer是一种易于使用的Express中间件，用于处理`multipart/form-data`请求。

查看[官方文档](https://github.com/expressjs/multer)以获取更多配置选项。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

## 相关博客
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
