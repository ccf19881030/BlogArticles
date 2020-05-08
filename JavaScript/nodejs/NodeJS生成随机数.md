## [NodeJS生成随机数](https://blog.csdn.net/watson2017/article/details/80945116)
crypto.randomBytes(size, [callback])

生成加密用的伪随机码，支持2种方法，当传递callback的话就是异步方法，不传callback就是同步方法：
```nodejs
var crypto = require('crypto');
 
// 异步
crypto.randomBytes(16, function(ex, buf) {
	if (ex) throw ex;
	var token = buf.toString('hex');
	console.log(‘randomcode: %s', token);
});
// 同步
try {
	var buf = crypto.randomBytes(16);
	var token = buf.toString('hex');
	console.log(‘randomcode: %s', token);
} catch (ex) {
	// handle error
}
```
