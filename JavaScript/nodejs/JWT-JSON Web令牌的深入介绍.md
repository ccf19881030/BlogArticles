![in-depth-introduction-jwt-feature-image](https://img-blog.csdnimg.cn/20200625143006180.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
## [JWT-JSON Web令牌的深入介绍](https://bezkoder.com/jwt-json-web-token/)
从桌面应用程序到Web应用程序或移动应用程序，身份验证是几乎所有应用程序中最重要的部分之一。 本教程是JWT（JSON Web令牌）的深入介绍，可帮助您了解：

- 基于会话的身份验证与基于令牌的身份验证（为什么JWT诞生了）
- JWT是如何工作的。
- 如何创建JWT。
- 我们如何保护我们的应用程序并验证JWT。
更多实践：
– [使用Spring Security和JWT身份验证的安全Spring Boot应用程序](https://bezkoder.com/spring-boot-jwt-authentication/)
–  [Node.js –使用JSONWebToken示例（JWT）的基于令牌的身份验证](https://bezkoder.com/node-js-jwt-authentication-mysql/)
– [Spring Boot，MongoDB：基于Spring Security的JWT身份验证](https://bezkoder.com/spring-boot-jwt-auth-mongodb/)

– [使用Vuex和Vue路由器进行Vue.js JWT身份验证](https://bezkoder.com/jwt-vue-vuex-authentication/)
– [使用HttpInterceptor和路由器进行Angular 8 JWT身份验证](https://bezkoder.com/angular-jwt-authentication/)
–  [React JWT身份验证（无Redux）示例](https://bezkoder.com/react-jwt-auth/)

使用JWT的Spring Security概述：
[按体系结构使用了 MySQL，Spring Security示例的Spring Boot JWT Auth[(https://bezkoder.com/spring-boot-jwt-mysql-spring-security-architecture/)

### 内容
- 基于会话的身份验证和基于令牌的身份验证
- JWT是如何工作的
- 如何创建JWT
   - 标头
   - 有效载荷
   - 签名
   - 结合一切
 - JWT如何保护我们的数据
 - 服务端如何校验从客户端过来的JWT
 - 结论
 - 进一步阅读

### 基于会话的身份验证和基于令牌的身份验证
对于使用任何网站，移动应用程序或桌面应用程序……您几乎需要创建一个帐户，然后使用该帐户登录以访问该应用程序的功能。 我们称该行为为**身份验证**。

那么，如何验证帐户？
首先，我们来看看过去流行的网站使用的一种简单方法：**基于会话的身份验证**。

  ![in-depth-introduction-jwt-session-based-authentication](https://img-blog.csdnimg.cn/20200625181959161.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
  在上图中，当用户登录网站时，**服务器**将为该用户生成一个会话并将其存储（在内存或数据库中）。服务器还会为**客户端**返回一个SessionId，以将其保存在浏览器**Cookie**中。

服务器上的会话具有到期时间。在此时间之后，该会话已过期，用户必须重新登录才能创建另一个会话。

如果用户已登录并且会话尚未到期，则Cookie（包括SessionId）将始终与所有向服务器的HTTP请求一起使用。服务器将比较此SessionId与存储的会话以进行身份​​验证并返回相应的响应。

没关系。但是为什么我们需要基于令牌的身份验证？
答案是我们不仅有网站，而且那里有很多平台。

假设我们有一个与Session配合良好的网站。有一天，我们想为移动（本地应用程序）实现系统，并与当前的Web应用程序使用同一数据库。我们应该做什么？我们无法使用基于会话的身份验证对使用Native App的用户进行身份验证，因为这些类型没有Cookie。

我们是否应该构建另一个支持Native Apps的后端项目？
还是应该为Native App用户编写一个身份验证模块？

这就是**基于令牌的身份验证**诞生的原因。
使用此方法，服务器会将用户登录状态编码为JSON Web令牌（JWT），并将其发送给客户端。 如今，许多RESTful API都在使用它。 让我们转到下一部分，我们将知道它是如何工作的。
### JWT是如何工作的
现在看下面的流程：
![in-depth-introduction-jwt-token-based-authentication](https://img-blog.csdnimg.cn/20200625182554815.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
您会发现它很容易理解。 服务器没有创建会话，而是从用户登录数据生成了JWT，并将其发送给客户端。 客户端保存JWT，从现在开始，来自客户端的每个请求都应附加到该JWT（通常在标头处）。 服务器将验证JWT并返回响应。

要在客户端存储JWT，取决于您使用的平台：
	- 浏览器：[Local Storage](https://developer.mozilla.org/en-US/docs/Web/API/Web_Storage_API/Local_storage)
	- IOS： [Keychain](https://developer.apple.com/documentation/security/keychain_services)
	- Android: [SharedPreferences](https://developer.android.com/reference/android/content/SharedPreferences)
这是**基于令牌的身份验证**流程的概述。 在下一节中，您将更深入地了解它。

### 如何创建JWT
首先，您应该了解JWT的三个重要部分：
- 标头
- 有效载荷
- 签名

### 标头
标头回答了这个问题：我们将如何计算JWT？
现在来看一个标头示例，它是一个JSON对象，如下所示：
```json
{
  "typ": "JWT",
  "alg": "HS256"
}
```
– typ是“ type”，表示此处的令牌类型是JWT。
– alg代表“算法”，它是一种用于生成令牌签名的哈希算法。 在上面的代码中，HS256是HMAC-SHA256 –使用密钥的算法。

### 有效载荷
有效负载可帮助我们回答：我们想在JWT中存储什么？
这是有效负载示例：
```json
{
  "userId": "abcd12345ghijk",
  "username": "bezkoder",
  "email": "contact@bezkoder.com",
  // standard fields
  "iss": "zKoder, author of bezkoder.com",
  "iat": 1570238918,
  "exp": 1570238992
}
```
在上面的JSON对象中，我们存储3个用户字段：userId，username, email。 您可以保存所需的任何字段。

我们也有一些**Standard Fields**。 它们是可选的。
   - iss（Issuer）：谁发行JWT
   - iat（发布于）：JWT的发布时间：
   - exp（到期时间）：JWT到期时间
我们可以在[https://en.wikipedia.org/wiki/JSON_Web_Token#Standard_fields](https://en.wikipedia.org/wiki/JSON_Web_Token#Standard_fields]查看更多的Standard Fields

### 签名
这部分是我们使用上面我告诉过您的哈希算法的地方。
查看下面获得签名的代码：
```js
const data = Base64UrlEncode(header) + '.' + Base64UrlEncode(payload);
const hashedData = Hash(data, secret);
const signature = Base64UrlEncode(hashedData);
```
让我们解释一下。
–首先，我们对Header和Payload进行编码，并用点将它们连接起来。
```js
data = '[encodedHeader].[encodedPayload]'
```
–接下来，我们使用带有秘钥字符串的Hash算法（在Header中定义）对数据进行哈希处理。
–最后，我们对哈希结果进行编码以获得**签名**。

### 结合一切
在拥有Header，Payload，Signature之后，我们将它们组合成JWT标准结构：header.payload.signature。
以下代码将说明我们如何做到这一点。
```js
const encodedHeader = base64urlEncode(header);
/* Result */
"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9"

const encodedPayload = base64urlEncode(payload);
/* Result */
"eyJ1c2VySWQiOiJhYmNkMTIzNDVnaGlqayIsInVzZXJuYW1lIjoiYmV6a29kZXIiLCJlbWFpbCI6ImNvbnRhY3RAYmV6a29kZXIuY29tIn0"

const data = encodedHeader + "." + encodedPayload;
const hashedData = Hash(data, secret);
const signature = base64urlEncode(hashedData);
/* Result */
"crrCKWNGay10ZYbzNG3e0hfLKbL7ktolT7GqjUMwi3k"

// header.payload.signature
const JWT = encodedHeader + "." + encodedPayload + "." + signature;
/* Result */
"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VySWQiOiJhYmNkMTIzNDVnaGlqayIsInVzZXJuYW1lIjoiYmV6a29kZXIiLCJlbWFpbCI6ImNvbnRhY3RAYmV6a29kZXIuY29tIn0.5IN4qmZTS3LEaXCisfJQhrSyhSPXEgM1ux-qXsGKacQ"
```
### JWT如何保护我们的数据
```important
JWT不保护您的数据
```
JWT完全不会隐藏，掩盖和保护数据。 您可以看到，生成JWT（标头，有效负载，签名）的过程仅对数据进行哈希处理，而不对数据进行加密。

JWT的目的是证明数据是由真实来源生成的。

那么，如果有[中间人攻击](https://en.wikipedia.org/wiki/Man-in-the-middle_attack)可以获取JWT，然后解码用户信息怎么办？ 是的，这是可能的，因此请始终确保您的应用程序具有HTTPS加密。

### 服务器如何从客户端验证JWT
在上一节中，我们使用**Secret**字符串创建**签名**。 此**Secret**字符串对于每个应用都是唯一的，并且必须安全地存储在服务器端。

从客户端接收JWT时，服务器获取签名，并验证签名是否已通过与上述相同的算法和Secret字符串正确地进行了哈希处理。 如果它与服务器的签名匹配，则JWT有效。
```note
重要！
```
当发送给服务端时，有经验的程序猿仍然可以添加或编辑**有效载荷**信息。 在这种情况下我们该怎么办？
我们先存储令牌，然后再将其发送给客户端。 它可以确保客户端稍后发送的JWT有效。

此外，将用户的令牌保存在服务器上还将使系统的**强制注销**功能受益。

### 结论
永远不会有最佳的身份验证方法。 这取决于用例和实现方式。

但是，对于要在许多平台上扩展为大量用户的应用程序，首选JWT身份验证，因为令牌将存储在客户端。

祝您学习愉快，再见！

### 进一步学习
- [RFC7519 – JSON Web Token (JWT)](https://tools.ietf.org/html/rfc7519)
- [JWT Standard fields](https://en.wikipedia.org/wiki/JSON_Web_Token#Standard_fields)
