## 博客说明
本博客翻译自[Node.js - Role Based Authorization Tutorial with Example API](https://jasonwatmore.com/post/2018/11/28/nodejs-role-based-authorization-tutorial-with-example-api)，本人的CSDN博客为：[Node.js-具有示例API的基于角色的授权教程](https://blog.csdn.net/ccf19881030/article/details/107804978)
出版时间：2018年11月28日
最后更新：2020年7月2日

# Node.js-具有示例API的基于角色的授权教程
![Node.js-具有示例API的基于角色的授权教程](https://img-blog.csdnimg.cn/20200805002311215.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
## 使用Node.js构建的教程
## 其他可用版本：
- **ASP.NET**: [ASP.NET Core 3.1](https://jasonwatmore.com/post/2019/10/16/aspnet-core-3-role-based-authorization-tutorial-with-example-api), [ASP.NET Core 2.2](https://jasonwatmore.com/post/2019/01/08/aspnet-core-22-role-based-authorization-tutorial-with-example-api)
在本教程中，我们将通过一个简单的示例介绍如何在JavaScript中使用Node.js API实现基于角色的授权/访问控制。 该示例基于我最近发布的另一篇教程，该教程侧重于[Node.js中的JWT身份验证](https://jasonwatmore.com/post/2018/08/06/nodejs-jwt-authentication-tutorial-with-example-api)，此版本已扩展为在JWT身份验证的基础上包括基于角色的授权/访问控制。
示例API仅具有三个端点/路由来演示身份验证和基于角色的授权：
- /users/authenticate - 接受body中带有用户名和密码的HTTP POST请求的公共路由。 如果用户名和密码正确，则返回JWT身份验证令牌。
- /users - 仅限于“Admin”用户的安全路由，如果HTTP授权header包含有效的JWT令牌并且用户处于“Admin”角色，则它接受HTTP GET请求并返回所有用户的列表。 如果没有身份验证令牌，令牌无效或用户不具有“Admin”角色，则返回401未经授权的响应。
- /users/:id - 安全路由，无论以任何角色都限于经过身份验证的用户，它会接受HTTP GET请求，并在授权成功后返回指定“ id”参数的用户记录。 请注意，“Admin”用户可以访问所有用户记录，而其他角色（例如“User”）只能访问自己的用户记录。
该教程项目可在GitHub上找到：[https://github.com/cornflourblue/node-role-based-authorization-api](https://github.com/cornflourblue/node-role-based-authorization-api).

更新历史：
- 2020年7月2日-更新至express-jwt版本6.0.0以修复安全漏洞
- 2020年5月15日-添加了有关使用Angular 9客户端应用程序运行Node.js api的说明
- 2018年11月28日-使用Node.js构建

## 在本地运行Node.js基于角色的授权API
1.从[https://github.com/cornflourblue/node-role-based-authorization-api](https://github.com/cornflourblue/node-role-based-authorization-api)下载或克隆教程项目代码
2.通过从项目根文件夹（package.json所在的位置）中的命令行运行*npm install*来安装所有必需的npm软件包。
3.通过从项目根文件夹中的命令行运行npm start来启动api，您应该看到消息 *Server listening on port 4000*。您可以使用诸如[Postman](https://www.getpostman.com/)之类的应用程序直接测试api，也可以使用下面的单个页面的示例应用程序来测试它。 

## 使用基于Node.js角色的Auth API运行Angular 9客户端应用
有关示例Angular 9应用程序的完整详细信息，请参阅[Angular 9 - Role Based Authorization Tutorial with Example](https://jasonwatmore.com/post/2020/05/15/angular-9-role-based-authorization-tutorial-with-example)。 但是要快速启动并运行，请按照以下步骤操作。

1.从[https://github.com/cornflourblue/angular-9-role-based-authorization-example](https://github.com/cornflourblue/angular-9-role-based-authorization-example)下载或克隆Angular 9教程代码
2.通过从项目根文件夹（package.json所在的位置）中的命令行运行*npm install*来安装所有必需的npm软件包。
3.删除或注释掉*//src/app/app.module.ts*文件中提供程序下面的一行注释// provider used to create fake backend。
4通过从项目根文件夹中的命令行运行npm start来启动应用程序，这将启动显示Angular示例应用程序的浏览器，并且应与已经运行的基于Node.js基于角色的授权API挂钩。

## 使用基于Node.js角色的Auth API运行React客户端应用
有关示例React应用程序的完整详细信息，请参阅[React - Role Based Authorization Tutorial with Example](https://jasonwatmore.com/post/2019/02/01/react-role-based-authorization-tutorial-with-example)。 但是要快速启动并运行，请按照以下步骤操作。

1.从[https://github.com/cornflourblue/react-role-based-authorization-example](https://github.com/cornflourblue/react-role-based-authorization-example)下载或克隆React教程代码
2.通过从项目根文件夹（package.json所在的位置）中的命令行运行*npm install*来安装所有必需的npm软件包。
3.删除或注释掉*/src/index.jsx*文件中的注释// setup fake backend下面的两行。
4.通过从项目根文件夹中的命令行运行npm start来启动应用程序，这将启动一个显示React示例应用程序的浏览器，并且应该与已经运行的Node.js基于角色的授权API挂钩。

## 使用基于Node.js角色的Auth API运行Vue.js客户端应用
有关示例Vue.js应用程序的完整详细信息，请参见[Vue.js - Role Based Authorization Tutorial with Example](https://jasonwatmore.com/post/2019/03/08/vuejs-role-based-authorization-tutorial-with-example)。 但是要快速启动并运行，请按照以下步骤操作。
1.从[https://github.com/cornflourblue/vue-role-based-authorization-example](https://github.com/cornflourblue/vue-role-based-authorization-example)下载或克隆Vue.js教程代码
2.通过从项目根文件夹（package.json所在的位置）中的命令行运行*npm install*来安装所有必需的npm软件包。
3.删除或注释掉位于*/src/index.js*文件中的*// setup fake backend*的注释下面的两行。
4.通过从项目根文件夹中的命令行运行*npm start*来启动应用程序，这将启动显示Vue.js示例应用程序的浏览器，并且应与已经运行的基于Node.js基于角色的授权API挂钩。
## 基于Node.js角色的访问控制项目结构
该项目分为“功能文件夹”（users）和“非功能/共享组件文件夹”（_helpers）。 共享的组件文件夹包含可以供应用程序的多个功能和其他部分使用的代码，并带有下划线前缀，以将它们分组在一起，因此可以一目了然地轻松查看内容。

该示例仅包含一个用户功能，但是可以通过复制用户文件夹并遵循相同的模式来轻松添加其他功能。
- _helpers
	- authorize.js
	- error-handler.js
	- role.js
- users
	- user.service.js
	- users.controller.js
- config.js
- server.js

## Node.js Auth Helpers文件夹
路径：/_helpers
helpers文件夹包含所有不适合其他文件夹但没有理由拥有自己的文件夹的零碎内容。

## Node.js授权角色中间件
路径：/_helpers/authorize.js
可以将授权中间件添加到任何路由中，以限制对指定角色中经过身份验证的用户的访问。如果将角色参数留为空白，则路由将被限制到任何经过身份验证的用户，无论角色如何。在用户控制器中使用它来限制对“获取所有用户”和“按ID获取用户”路由的访问。

authorize函数实际上返回2个中间件函数，第一个（*jwt（{... ...）*））通过验证Authorization http请求头中的JWT令牌来认证请求。成功认证后，会将*user*对象附加到包含JWT令牌中数据的*req*对象，在这种情况下，该对象包括用户ID（*req.user.sub*）和用户角色（*req.user.role*）。 *sub*属性是subject的缩写，是用于在令牌中存储项目id的标准JWT属性。

第二个中间件功能根据其角色检查经过身份验证的用户是否有权访问请求的路由。如果验证或授权失败，则返回401未经授权响应。

```js
const jwt = require('express-jwt');
const { secret } = require('config.json');

module.exports = authorize;

function authorize(roles = []) {
    // roles param can be a single role string (e.g. Role.User or 'User') 
    // or an array of roles (e.g. [Role.Admin, Role.User] or ['Admin', 'User'])
    if (typeof roles === 'string') {
        roles = [roles];
    }

    return [
        // authenticate JWT token and attach user to request object (req.user)
        jwt({ secret, algorithms: ['HS256'] }),

        // authorize based on user role
        (req, res, next) => {
            if (roles.length && !roles.includes(req.user.role)) {
                // user's role is not authorized
                return res.status(401).json({ message: 'Unauthorized' });
            }

            // authentication and authorization successful
            next();
        }
    ];
}
```

## Node.js Auth全局错误处理程序中间件
路径：/_helpers/error-handler.js
The global error handler is used catch all errors and remove the need for redundant error handler code throughout the application. It's configured as middleware in the main **server.js** file.
```server.js
module.exports = errorHandler;

function errorHandler(err, req, res, next) {
    if (typeof (err) === 'string') {
        // custom application error
        return res.status(400).json({ message: err });
    }

    if (err.name === 'UnauthorizedError') {
        // jwt authentication error
        return res.status(401).json({ message: 'Invalid Token' });
    }

    // default to 500 server error
    return res.status(500).json({ message: err.message });
}
```

## Node.js Auth角色对象/枚举
路径：/_helpers/role.js
角色对象定义了示例应用程序中的所有角色，我将其创建为像*enum*一样使用，以避免将角色作为字符串传递，因此可以使用*Role.Admin*代替“ *Admin*”。
```role.js
module.exports = {
  Admin: 'Admin',
  User: 'User'
}
```

## Node.js Auth Users文件夹
路径：/users
users文件夹包含所有特定于基于角色的授权api的users功能的代码。

### Node.js Auth用户服务
路径：/users/user.service.js
用户服务包含用于验证用户凭据并返回JWT令牌的方法，用于在应用程序中获取所有用户的方法以及用于通过id获取单个用户的方法。

我在示例中对用户数组进行了硬编码，以使其始终专注于身份验证和基于角色的授权，但是在生产应用程序中，建议使用哈希密码将用户记录存储在数据库中。 我发布了另一个稍有不同的示例（包括注册，但不包括基于角色的授权），该示例将数据存储在MongoDB中，如果您有兴趣查看数据的配置方式，可以在[NodeJS + MongoDB上进行验证-用于身份验证，注册和验证的简单API 用户管理](https://jasonwatmore.com/post/2018/06/14/nodejs-mongodb-simple-api-for-authentication-registration-and-user-management)。

在文件顶部附近（在硬编码用户下方），我已经导出了服务方法的定义，因此可以一目了然地查看所有方法，在文件的其余部分包含该方法的实现。
```user.service.js
const config = require('config.json');
const jwt = require('jsonwebtoken');
const Role = require('_helpers/role');

// users hardcoded for simplicity, store in a db for production applications
const users = [
    { id: 1, username: 'admin', password: 'admin', firstName: 'Admin', lastName: 'User', role: Role.Admin },
    { id: 2, username: 'user', password: 'user', firstName: 'Normal', lastName: 'User', role: Role.User }
];

module.exports = {
    authenticate,
    getAll,
    getById
};

async function authenticate({ username, password }) {
    const user = users.find(u => u.username === username && u.password === password);
    if (user) {
        const token = jwt.sign({ sub: user.id, role: user.role }, config.secret);
        const { password, ...userWithoutPassword } = user;
        return {
            ...userWithoutPassword,
            token
        };
    }
}

async function getAll() {
    return users.map(u => {
        const { password, ...userWithoutPassword } = u;
        return userWithoutPassword;
    });
}

async function getById(id) {
    const user = users.find(u => u.id === parseInt(id));
    if (!user) return;
    const { password, ...userWithoutPassword } = user;
    return userWithoutPassword;
}
```

## Node.js Auth用户控制器
路径：/users/users.controller.js
用户控制器为api定义了所有用户路由，路由定义在文件顶部分组在一起，并且路由实现在下面。

使用授权中间件的路由仅限于经过身份验证的用户，如果包括角色（例如*authorize（Role.Admin*）），则该路由仅限于指定角色/角色的用户，否则，如果不包括角色（例如，*authorize()*），则该路由将限制为所有经过身份验证的用户，无论其角色如何。 不使用授权中间件的路由是可公开访问的。

*getById*路由在route函数中包含一些额外的自定义授权逻辑。 它允许管理员用户访问任何用户记录，但仅允许普通用户访问自己的记录。

Express是api使用的Web服务器，它是Node.js最受欢迎的Web应用程序框架之一。
```users.controller.js
const express = require('express');
const router = express.Router();
const userService = require('./user.service');
const authorize = require('_helpers/authorize')
const Role = require('_helpers/role');

// routes
router.post('/authenticate', authenticate);     // public route
router.get('/', authorize(Role.Admin), getAll); // admin only
router.get('/:id', authorize(), getById);       // all authenticated users
module.exports = router;

function authenticate(req, res, next) {
    userService.authenticate(req.body)
        .then(user => user ? res.json(user) : res.status(400).json({ message: 'Username or password is incorrect' }))
        .catch(err => next(err));
}

function getAll(req, res, next) {
    userService.getAll()
        .then(users => res.json(users))
        .catch(err => next(err));
}

function getById(req, res, next) {
    const currentUser = req.user;
    const id = parseInt(req.params.id);

    // only allow admins to access other user records
    if (id !== currentUser.sub && currentUser.role !== Role.Admin) {
        return res.status(401).json({ message: 'Unauthorized' });
    }

    userService.getById(req.params.id)
        .then(user => user ? res.json(user) : res.sendStatus(404))
        .catch(err => next(err));
}
```

## Node.js Auth应用程序配置
路径： /config.json
应用程序配置文件包含api的配置数据。

重要说明：api使用“"secret”属性来签名和验证用于身份验证的JWT令牌，并使用您自己的随机字符串对其进行更新，以确保没有其他人可以生成JWT来获得对应用程序的未授权访问。
```config.json
{
    "secret": "THIS IS USED TO SIGN AND VERIFY JWT TOKENS, REPLACE IT WITH YOUR OWN SECRET, IT CAN BE ANY STRING"
}
```

## Node.js Auth主服务器入口点
路径：/server.js
server.js文件是api的入口点，它配置应用程序中间件，将控制器绑定到路由并启动api的Express Web服务器。
```server.js
require('rootpath')();
const express = require('express');
const app = express();
const cors = require('cors');
const bodyParser = require('body-parser');
const errorHandler = require('_helpers/error-handler');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());

// api routes
app.use('/users', require('./users/users.controller'));

// global error handler
app.use(errorHandler);

// start server
const port = process.env.NODE_ENV === 'production' ? 80 : 4000;
const server = app.listen(port, function () {
    console.log('Server listening on port ' + port);
});
```

## 订阅或关注我以获取更新
订阅我的YouTube频道，或者在Twitter或GitHub上关注我，以便在我发布新内容时收到通知。
- 在[https://www.youtube.com/c/JasonWatmore](https://www.youtube.com/c/JasonWatmore?sub_confirmation=1)上在YouTube上订阅
- 在Twitter上关注我，网址为[https://twitter.com/jason_watmore](https://twitter.com/jason_watmore)
- 在GitHub上关注我，网址为[https://github.com/cornflourblue](https://github.com/cornflourblue)
- 供稿格式：[RSS](https://jasonwatmore.com/rss)，[Atom](https://jasonwatmore.com/atom)，[JSON](https://jasonwatmore.com/json)

## 更多NodeJS帖子
- [Node.js + Express API - Request Schema Validation with Joi](https://jasonwatmore.com/post/2020/07/22/nodejs-express-api-request-schema-validation-with-joi)
- [Node.js - Send Emails via SMTP with Nodemailer](https://jasonwatmore.com/post/2020/07/20/nodejs-send-emails-via-smtp-with-nodemailer)
- [Node.js - Hash and Verify Passwords with Bcrypt](https://jasonwatmore.com/post/2020/07/20/nodejs-hash-and-verify-passwords-with-bcrypt)
- [Node.js + MongoDB API - JWT Authentication with Refresh Tokens](https://jasonwatmore.com/post/2020/06/17/nodejs-mongodb-api-jwt-authentication-with-refresh-tokens)
- [Node + Mongo - Boilerplate API with Email Sign Up, Verification, Authentication & Forgot Password](https://jasonwatmore.com/post/2020/05/13/node-mongo-api-with-email-sign-up-verification-authentication-forgot-password)
- [Vue.js + Node.js on AWS - How to Deploy a MEVN Stack App to Amazon EC2](https://jasonwatmore.com/post/2019/12/14/vuejs-nodejs-on-aws-how-to-deploy-a-mevn-stack-app-to-amazon-ec2)
- [Angular + Node.js on AWS - How to Deploy a MEAN Stack App to Amazon EC2](https://jasonwatmore.com/post/2019/12/02/angular-nodejs-on-aws-how-to-deploy-a-mean-stack-app-to-amazon-ec2)
- [React + Node.js on AWS - How to Deploy a MERN Stack App to Amazon EC2](https://jasonwatmore.com/post/2019/11/18/react-nodejs-on-aws-how-to-deploy-a-mern-stack-app-to-amazon-ec2)
- [Vue.js + Node - Server Side Pagination Tutorial & Example](https://jasonwatmore.com/post/2019/08/12/vuejs-node-server-side-pagination-tutorial-example)
- [React + Node - Server Side Pagination Tutorial & Example](https://jasonwatmore.com/post/2019/07/18/react-node-server-side-pagination-tutorial-example)
- [Angular 8 + Node - Server Side Pagination Tutorial & Example](https://jasonwatmore.com/post/2019/06/28/angular-8-node-server-side-pagination-tutorial-example)
- [Deploy to Heroku - Node + Mongo API for Authentication, Registration and User Management](https://jasonwatmore.com/post/2018/12/06/deploy-to-heroku-node-mongo-api-for-authentication-registration-and-user-management)
- [Setup Node.js + MongoDB Production Server on Ubuntu 18.04 - Ubuntu 19.04](https://jasonwatmore.com/post/2018/09/26/setup-nodejs-mongodb-production-server-on-ubuntu-1804)
- [NodeJS - Basic Authentication Tutorial with Example API](https://jasonwatmore.com/post/2018/09/24/nodejs-basic-authentication-tutorial-with-example-api)
- [NodeJS - JWT Authentication Tutorial with Example API](https://jasonwatmore.com/post/2018/08/06/nodejs-jwt-authentication-tutorial-with-example-api)
- [NodeJS + MongoDB - Simple API for Authentication, Registration and User Management](https://jasonwatmore.com/post/2018/06/14/nodejs-mongodb-simple-api-for-authentication-registration-and-user-management)
- [Node - Get Public Key From Private Key with JavaScript](https://jasonwatmore.com/post/2018/05/23/node-get-public-key-from-private-key-with-javascript)
- [Angular 2 - Refresh Without 404 in Node & IIS](https://jasonwatmore.com/post/2017/02/24/angular-2-refresh-without-404-in-node-iis)
- [MEAN with Angular 2/5 - User Registration and Login Example & Tutorial](https://jasonwatmore.com/post/2017/02/22/mean-with-angular-2-user-registration-and-login-example-tutorial)
- [MEANie - Lightweight MEAN Stack CMS & Blogging Platform](https://jasonwatmore.com/post/2016/10/29/meanie-mean-stack-blogging-platform)
- [AngularJS - Enable HTML5 Mode Page Refresh Without 404 Errors in NodeJS and IIS](https://jasonwatmore.com/post/2016/07/26/angularjs-enable-html5-mode-page-refresh-without-404-errors-in-nodejs-and-iis)
- [NodeJS - Setup a Simple HTTP Server / Local Web Server](https://jasonwatmore.com/post/2016/06/22/nodejs-setup-simple-http-server-local-web-server)
- [Getting Foreman working on Windows 7 after installing the Heroku Toolbelt](https://jasonwatmore.com/post/2013/11/20/getting-foreman-working-on-windows-7-after-installing-the-heroku-toolbelt)
