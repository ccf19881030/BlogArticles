大量的移动应用程序和网站允许用户上传个人资料图片和其他文件。 因此，在使用Node.js和Express构建REST API时，通常需要处理文件上传。

在本教程中，我们将讨论如何使用Node.js和Express后端处理单个和多个文件上传，以及如何将上传的文件保存在服务器上。

## 安装
首先，让我们通过运行以下命令来创建一个新的Node.js应用程序。 我正在使用`npm`进行软件包管理。 如果愿意，可以使用`yarn`。
```shell
# creat a new directory & switch to it
$ mkdir files-upload && cd files-upload

# run this for npm to create a new app
$ npm init -y

# run this for yarn to create a new app
$ yarn init -y 
```

`-y`或`--yes`跳过交互会话，并根据默认设置生成`package.json`文件。 接下来，运行以下命令以安装必需的依赖项：
```shell
# run this for npm
$ npm install express body-parser cors express-fileupload morgan lodash --save

# or using yarn
$ yarn add express body-parser cors express-fileupload morgan lodash 
```

以下是上述每个软件包的功能：
- `express`-基于Node.js构建的流行Web框架。 我们将使用它来开发REST API。
- `body-parser`-Node.js请求主体解析中间件，该中间件在处理程序之前解析传入的请求主体，并使其在req.body属性下可用。 简而言之，它简化了传入请求。
- `cors`-另一种Express中间件，用于启用CORS（跨域资源共享）请求。
- `express-fileupload`-用于上传文件的Simple Express中间件。 它解析`multipart/form-data`请求，提取文件（如果有），并在`req.files`属性下使它们可用。
- `morgan`-用于记录HTTP请求的Node.js中间件。
- `lodash`-一个JavaScript库，为数组，数字，对象，字符串等提供实用程序功能。

## 创建Express服务器
安装所需的依赖项之后，让我们开始创建Express服务器。
`index.js`
```index.js
const express = require('express');
const fileUpload = require('express-fileupload');
const cors = require('cors');
const bodyParser = require('body-parser');
const morgan = require('morgan');
const _ = require('lodash');

const app = express();

// enable files upload
app.use(fileUpload({
    createParentPath: true
}));

//add other middleware
app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));
app.use(morgan('dev'));

//start app 
const port = process.env.PORT || 3000;

app.listen(port, () => 
  console.log(`App is listening on port ${port}.`)
);
```

上面的代码很容易理解。 它首先设置`express-fileupload`中间件以启用`multipart/form-data`请求。 之后，添加了其他Express中间件以允许跨域资源共享（CORS），请求正文解析和HTTP请求日志记录。 最后，它将在端口`3000`上启动服务器。

## 上传单个文件
让我们创建第一个路由，该路由允许用户上传其个人资料图片。
```index.js
app.post('/upload-avatar', async (req, res) => {
    try {
        if(!req.files) {
            res.send({
                status: false,
                message: 'No file uploaded'
            });
        } else {
            //Use the name of the input field (i.e. "avatar") to retrieve the uploaded file
            let avatar = req.files.avatar;
            
            //Use the mv() method to place the file in upload directory (i.e. "uploads")
            avatar.mv('./uploads/' + avatar.name);

            //send response
            res.send({
                status: true,
                message: 'File is uploaded',
                data: {
                    name: avatar.name,
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

上面的代码段是一个HTTP `POST`函数。 当您向`/upload-avatar`路由发送`multipart/form-data`请求以上传文件时，此功能会将文件保存到服务器上的`uploads`文件夹中。

## express-fileupload中间件如何工作？
它使上传的文件可从`req.files`属性访问。 例如，如果您上传名为`my-profile.jpg`的文件，并且您的字段名是`avatar`，则可以通过`req.files.avatar`访问它。 `avatar`对象将包含以下信息：

- `avatar.name`-上传文件的名称，即`my-profile.jpg`
- `avatar.mv`-将文件移动到服务器上其他位置的功能
- `avatar.mimetype`-文件的mime类型
- `avatar.size`-文件大小，以字节为单位
- `avatar.data`-上载文件的缓冲区表示

## 上传多个文件
让我们开始创建另一条路由，以允许用户一次上传多张照片。
```index.js
app.post('/upload-photos', async (req, res) => {
    try {
        if(!req.files) {
            res.send({
                status: false,
                message: 'No file uploaded'
            });
        } else {
            let data = []; 
    
            //loop all files
            _.forEach(_.keysIn(req.files.photos), (key) => {
                let photo = req.files.photos[key];
                
                //move photo to uploads directory
                photo.mv('./uploads/' + photo.name);

                //push file details
                data.push({
                    name: photo.name,
                    mimetype: photo.mimetype,
                    size: photo.size
                });
            });
    
            //return response
            res.send({
                status: true,
                message: 'Files are uploaded',
                data: data
            });
        }
    } catch (err) {
        res.status(500).send(err);
    }
});
```

上面的代码与单文件上传非常相似，除了我们现在收到的是`photos`字段而不是`avatar`。 我们使用`lodash`实用程序函数（`_.forEach()`和`_.keysIn()`）遍历`photos`字段，然后将每张照片保存到`uploads`目录。

## 测试应用程序
我们快完成了！ 在终端的项目根目录中运行以下命令以启动应用程序：
```shell
$ node index.js
```
它将在端口`3000`上启动应用程序。让我们使用Postman发送HTTP `multipart/form-data`请求：

### 1. 单文件
![Single File](https://img-blog.csdnimg.cn/20201015200004230.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)


### 2. 多个文件
![多个文件](https://img-blog.csdnimg.cn/202010152000309.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
如果您想使上传的文件可以从任何地方公开访问，只需将`uploads`目录设置为静态：
```js
app.use(express.static('uploads'));
```

现在，您可以直接在浏览器中打开上传的文件：
```shell
http://localhost:3000/icon.png
```

## 文件大小限制
如果要限制一次上传的文件的大小，请将`limits `选项直接传递给`express-fileupload`中间件：
```js
app.use(fileUpload({
    createParentPath: true,
    limits: { 
        fileSize: 2 * 1024 * 1024 * 1024 //2MB max file(s) size
    },
}));
```
源代码：在MIT许可下从[GitHub](https://github.com/attacomsian/code-examples/tree/master/nodejs/files-upload)下载完整的源代码。

## 结论
那是所有！ 我们学习了如何使用Node.js和Express框架上传单个和多个文件。 ·express-fileupload·是一种易于使用的Express中间件，用于处理文件上传。 查看其[文档](https://github.com/richardgirges/express-fileupload)以获取更多配置选项。

如果您有任何疑问或反馈，请随时给我发送[tweet](https://twitter.com/attacomsian)。

快乐学习Node.js😍


阅读下一篇：[使用Node.js中的Multer快速上传文件](https://attacomsian.com/blog/express-file-upload-multer)

## 相关博客链接
- [使用Node.js中的Multer快速上传文件](https://attacomsian.com/blog/express-file-upload-multer)
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
