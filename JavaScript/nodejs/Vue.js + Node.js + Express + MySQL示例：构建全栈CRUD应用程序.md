本文翻译自[Vue.js + Node.js + Express + MySQL example: Build a full-stack CRUD Application](https://bezkoder.com/vue-js-node-js-express-mysql-crud-example/)

# Vue.js + Node.js + Express + MySQL example: Build a full-stack CRUD Application
上次修改时间：2020年10月16日 bezkoder Full Stack，Node.js，Vue.js

在本教程中，我将向您展示如何构建一个全栈（Vue.js + Node.js + Express + MySQL）的CRUD应用程序示例。 后端服务器将Node.js + Express用于REST API，前端是带有Vue Router和axios的Vue客户端。

更过实践：[Node.js Express + Vue.js: JWT Authentication & Authorization example](https://bezkoder.com/node-express-vue-jwt-auth/)

Serverless with Firebase:
- [Vue Firebase Realtime Database: CRUD example](https://bezkoder.com/vue-firebase-realtime-database/)
- [Vue Firestore: Build a CRUD App example](https://bezkoder.com/vue-firestore-crud/)

## Vue.js + Node.js + Express + MySQL示例概述
我们将构建一个全栈教程的应用程序包括如下几点：
- 教程具有ID，标题，描述，发布状态。
- 用户可以创建，检索，更新，删除教程。
- 有一个搜索框，用于按标题查找教程。
下面是示例的截图：
- 添加一个对象：
![Add an object](https://img-blog.csdnimg.cn/20201108122308910.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
- 显示所有的对象：
![Show all objects](https://img-blog.csdnimg.cn/20201108122349284.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
- 点击`Edit`按钮更新对象：
![update an object](https://img-blog.csdnimg.cn/20201108122434172.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
在这个页面中，你可以：
	- 使用`Publish/UnPublished`按钮将状态更改成`Published/Pending`	
	- 使用`Delete`按钮从MySQL数据库中删除对象
	- 使用`Update`按钮更新数据库中对象的详细信息

- 根据`title`字段查找对象
![Search objects by field ‘title’](https://img-blog.csdnimg.cn/20201108122904263.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

## 全栈CRUD应用程序架构
我们将构建一个如下体系结构的应用程序:
![Full-stack CRUD App Architecture](https://img-blog.csdnimg.cn/2020110812301166.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
- Node.js Express导出REST API，并使用Sequelize ORM与MySQL数据库进行交互。
- Vue客户端使用axios发送HTTP请求并获取HTTP响应，在组件中使用数据。 Vue路由器用于页面间的导航。

## Node.js Express后端

### 总览
下面是Nodejs Express应用导出的一些APIs：
Methods     | Urls | Actions
-------- | ----- | ----- 
GET	|  api/tutorials	|  get all Tutorials
GET	|  api/tutorials/:id	 |  get Tutorial by id
POST	|  api/tutorials 	|  add new Tutorial
PUT	|  api/tutorials/:id	 | update Tutorial by id
DELETE	| api/tutorials/:id	| remove Tutorial by id
DELETE	|  api/tutorials	| remove all Tutorials
GET	 |  api/tutorials?title=[kw]	|  find all Tutorials which title contains 'kw'

### 项目结构
![Project Structure](https://img-blog.csdnimg.cn/20201108123804993.png#pic_center)
- db.config.js导出MySQL连接和Sequelize的配置参数。
-  在server.js的`Express` Web服务器中，我们配置CORS，初始化并运行Express REST API。
- 接下来，我们在`models/index.js`中添加MySQL数据库的配置，在`models/tutorial.model.js`中创建`Sequelize`数据模型。
- `controller`中的教程控制器。
- 在tutorial.routes.js中处理所有CRUD操作（包括自定义查找器）的路由。

### 实现
您可以在文章中逐步找到实现此Node.js Express应用程序的步骤：
[Node.js Rest APIs example with Express, Sequelize & MySQL](https://bezkoder.com/node-js-express-sequelize-mysql/)

## Vue.js前端
### 总览
![Overview](https://img-blog.csdnimg.cn/20201108124323976.png#pic_center)

- `App`组件是具有`route_view`的容器。 它具有链接到routes路径的导航栏。
- `TutorialsList`组件获取并显示Tutorials。
- `Tutorial`组件具有用于根据`:id'编辑教程详细信息的表单。
- `AddTutorial`组件具有用于提交新教程的表单。
- 这些组件调用`TutorialDataService`方法，这些方法使用`axios`发出HTTP请求并接收响应。

### 技术
- vue: 2.6.10
- vue-router: 3.1.3
- axios: 0.19.0

### 项目结构
![Project Structure](https://img-blog.csdnimg.cn/20201108131017828.png#pic_center)
- `package.json`包含3个主要的模块: `vue,` `vue-router`, `axios`。
- 有三个组件: `TutorialsList`, `Tutorial`, `AddTutorial`。
- `router.js`为每个组件定义了路由。
- `http-common.js`使用HTTP基准Url和请求头初始化axios.
- `TutorialDataService`中有用于发送HTTP请求的Apis的方法。
- `vue.config.js`为Vue客户端配置端口。

### 实现
您可以在文章中逐步找到实现此Vue App的步骤：
[Vue.js CRUD App with Vue Router & Axios](https://bezkoder.com/vue-js-crud-app/)
或者使用Vuetify：[Vuetify data-table example with a CRUD App](https://bezkoder.com/vuetify-data-table-example/)

![ Vuetify data-table example with a CRUD App](https://img-blog.csdnimg.cn/20201108132007463.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

## 结论
现在，我们在构建全栈CRUD应用程序时概述了Vue.js + Node.js Express + MySQL示例。

我们还介绍使用Express＆Sequelize ORM的REST API的客户端-服务器体系结构，以及用于构建前端应用程序以发出HTTP请求和使用响应的Vue.js项目结构。

接下来的教程向您展示有关如何实现系统的更多详细信息：
- [后端](https://bezkoder.com/node-js-express-sequelize-mysql/)
- [前端](https://bezkoder.com/vue-js-crud-app/)

如果你想要一个TypeScript版本的Vue App，可以参考如下文章:
[Vue Typescript CRUD Application to consume Web API example](https://bezkoder.com/vue-typescript-crud/)

分页:
- [Server side Pagination in Node.js with Sequelize & MySQL](https://bezkoder.com/node-js-sequelize-pagination-mysql/)
- [Vue Pagination with Axios and API (Server Side pagination) example](https://bezkoder.com/vue-pagination-axios/)

Serverless with Firebase:
- [Vue Firebase Realtime Database: CRUD example](https://bezkoder.com/vue-firebase-realtime-database/)
- [Vue Firestore: Build a CRUD App example](https://bezkoder.com/vue-firestore-crud/)

祝您学习愉快，再见！
