## [重构 - WebSocket Session共享](https://blog.csdn.net/u011692924/article/details/81076263)
最近在做消息中心模块，想要实现消息实时推送到前端页面展示，直接摒弃了前端定时轮训调用接口来获取消息数据的方式，采用了WebSocket服务端推送。

流程是首先前端跟后端应用新建一个连接，并携带当前登录的用户ID，此时WebSocket会创建一个WebsocketSession来唯一绑定该连接，我们会在后端用Map建立用户ID与Session的映射关系：
```java
Map<String userId, WebsocketSession session>
```

由于项目目前用到了Redis，所以可以采用Redis的发布/订阅功能来实现WebsocketSession共享问题。

-1、新建一个对象，属性有userId, message，用于发送消息
```java
Object(String userId, String message)
```

-2、当新消息到达时，将消息注册到redis指定topic的频道上
```java
convertAndSent("topicName", new Object(userId, message))
```

-3、每个应用节点都订阅该topic的频道，这样新消息一注册，每个节点都能接收到Object，然后从Object中获取userId，再从映射Map中获取userId对应的WebsocketSession（在哪个节点建立的连接和Map映射关系，就会在哪个节点找到对应的session），进行消息推送。

就这样通过Redis的发布/订阅功能实现session共享。当然在步骤2，新消息到达时，可以先在本节点的Map映射中查找是否有userId对应的session，如果有，直接推送消息，而且不必要再将消息注册到redis中。
