# Apache Thrift-Node.js教程

## 介绍
所有Apache Thrift教程都要求您具备：
1.Apache Thrift编译器和库，请参阅[下载](https://thrift.apache.org/download)和[从源代码构建](https://thrift.apache.org/docs/BuildingFromSource)以获取更多详细信息。
2.生成了[tutorial.thrift](https://github.com/apache/thrift/blob/master/tutorial/tutorial.thrift)和[shared.thrift](https://github.com/apache/thrift/blob/master/tutorial/shared.thrift)文件
3.遵循以下所有先决条件。

## 先决条件
### 客户端
```nodejs
var Calculator = require('./gen-nodejs/Calculator');
var ttypes = require('./gen-nodejs/tutorial_types');
const assert = require('assert');

var transport = thrift.TBufferedTransport;
var protocol = thrift.TBinaryProtocol;

var connection = thrift.createConnection("localhost", 9090, {
  transport : transport,
  protocol : protocol
});

connection.on('error', function(err) {
  assert(false, err);
});

// Create a Calculator client with the connection
var client = thrift.createClient(Calculator, connection);


client.ping(function(err, response) {
  console.log('ping()');
});


client.add(1,1, function(err, response) {
  console.log("1+1=" + response);
});


work = new ttypes.Work();
work.op = ttypes.Operation.DIVIDE;
work.num1 = 1;
work.num2 = 0;

client.calculate(1, work, function(err, message) {
  if (err) {
    console.log("InvalidOperation " + err);
  } else {
    console.log('Whoa? You know how to divide by zero?');
  }
});

work.op = ttypes.Operation.SUBTRACT;
work.num1 = 15;
work.num2 = 10;

client.calculate(1, work, function(err, message) {
  console.log('15-10=' + message);

  client.getStruct(1, function(err, message){
    console.log('Check log: ' + message.value);

    //close the connection once we're done
    connection.end();
  });
});
```

该代码段是由Apache Thrift的源代码树文档生成的：[tutorial/nodejs/NodeClient.js](https://gitbox.apache.org/repos/asf?p=thrift.git;a=blob;hb=HEAD;f=tutorial/nodejs/NodeClient.js)

### 服务端
```nodejs
var Calculator = require("./gen-nodejs/Calculator");
var ttypes = require("./gen-nodejs/tutorial_types");
var SharedStruct = require("./gen-nodejs/shared_types").SharedStruct;

var data = {};

var server = thrift.createServer(Calculator, {
  ping: function(result) {
    console.log("ping()");
    result(null);
  },

  add: function(n1, n2, result) {
    console.log("add(", n1, ",", n2, ")");
    result(null, n1 + n2);
  },

  calculate: function(logid, work, result) {
    console.log("calculate(", logid, ",", work, ")");

    var val = 0;
    if (work.op == ttypes.Operation.ADD) {
      val = work.num1 + work.num2;
    } else if (work.op === ttypes.Operation.SUBTRACT) {
      val = work.num1 - work.num2;
    } else if (work.op === ttypes.Operation.MULTIPLY) {
      val = work.num1 * work.num2;
    } else if (work.op === ttypes.Operation.DIVIDE) {
      if (work.num2 === 0) {
        var x = new ttypes.InvalidOperation();
        x.whatOp = work.op;
        x.why = 'Cannot divide by 0';
        result(x);
        return;
      }
      val = work.num1 / work.num2;
    } else {
      var x = new ttypes.InvalidOperation();
      x.whatOp = work.op;
      x.why = 'Invalid operation';
      result(x);
      return;
    }

    var entry = new SharedStruct();
    entry.key = logid;
    entry.value = ""+val;
    data[logid] = entry;

    result(null, val);
  },

  getStruct: function(key, result) {
    console.log("getStruct(", key, ")");
    result(null, data[key]);
  },

  zip: function() {
    console.log("zip()");
  }

});

server.listen(9090);
```

此代码段由Apache Thrift的源代码树文档生成：[tutorial/nodejs/NodeServer.js](https://gitbox.apache.org/repos/asf?p=thrift.git;a=blob;hb=HEAD;f=tutorial/nodejs/NodeServer.js)

# 附加信息
## 链接
- [下载](https://thrift.apache.org/download)
- [开发者](https://thrift.apache.org/developers)
- [讲解](https://thrift.apache.org/tutorial)
- [网站地图](https://thrift.apache.org/sitemap)
## 参与其中
- [邮件列表](https://thrift.apache.org/mailing)
- [问题跟踪](http://issues.apache.org/jira/browse/THRIFT)
- [如何贡献](https://thrift.apache.org/docs/HowToContribute)

# 使用Apache Thrift的Nodejs示例
![Download](https://img-blog.csdnimg.cn/20201117231802578.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)


从[Thrift官网下载页面](https://thrift.apache.org/download)下载[Thrift compiler for Windows (thrift-0.13.0.exe)](http://www.apache.org/dyn/closer.cgi?path=/thrift/0.13.0/thrift-0.13.0.exe)，即下载Windows下的thrift-0.13.0.exe可执行文件，用于将前面说到的[tutorial.thrift](https://github.com/apache/thrift/blob/master/tutorial/tutorial.thrift)和[shared.thrift](https://github.com/apache/thrift/blob/master/tutorial/shared.thrift)接口定义文件转换为某种语言比如说Node.js的代码。
`shared.thrift`文件内容如下所示：
```thrift
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * This Thrift file can be included by other Thrift files that want to share
 * these definitions.
 */

namespace cl shared
namespace cpp shared
namespace d share // "shared" would collide with the eponymous D keyword.
namespace dart shared
namespace java shared
namespace perl shared
namespace php shared
namespace haxe shared
namespace netstd shared


struct SharedStruct {
  1: i32 key
  2: string value
}

service SharedService {
  SharedStruct getStruct(1: i32 key)
}
```
`tutorial.thrift`文件如下所示：
```thrift
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

# Thrift Tutorial
# Mark Slee (mcslee@facebook.com)
#
# This file aims to teach you how to use Thrift, in a .thrift file. Neato. The
# first thing to notice is that .thrift files support standard shell comments.
# This lets you make your thrift file executable and include your Thrift build
# step on the top line. And you can place comments like this anywhere you like.
#
# Before running this file, you will need to have installed the thrift compiler
# into /usr/local/bin.

/**
 * The first thing to know about are types. The available types in Thrift are:
 *
 *  bool        Boolean, one byte
 *  i8 (byte)   Signed 8-bit integer
 *  i16         Signed 16-bit integer
 *  i32         Signed 32-bit integer
 *  i64         Signed 64-bit integer
 *  double      64-bit floating point value
 *  string      String
 *  binary      Blob (byte array)
 *  map<t1,t2>  Map from one type to another
 *  list<t1>    Ordered list of one type
 *  set<t1>     Set of unique elements of one type
 *
 * Did you also notice that Thrift supports C style comments?
 */

// Just in case you were wondering... yes. We support simple C comments too.

/**
 * Thrift files can reference other Thrift files to include common struct
 * and service definitions. These are found using the current path, or by
 * searching relative to any paths specified with the -I compiler flag.
 *
 * Included objects are accessed using the name of the .thrift file as a
 * prefix. i.e. shared.SharedObject
 */
include "shared.thrift"

/**
 * Thrift files can namespace, package, or prefix their output in various
 * target languages.
 */

namespace cl tutorial
namespace cpp tutorial
namespace d tutorial
namespace dart tutorial
namespace java tutorial
namespace php tutorial
namespace perl tutorial
namespace haxe tutorial
namespace netstd tutorial

/**
 * Thrift lets you do typedefs to get pretty names for your types. Standard
 * C style here.
 */
typedef i32 MyInteger

/**
 * Thrift also lets you define constants for use across languages. Complex
 * types and structs are specified using JSON notation.
 */
const i32 INT32CONSTANT = 9853
const map<string,string> MAPCONSTANT = {'hello':'world', 'goodnight':'moon'}

/**
 * You can define enums, which are just 32 bit integers. Values are optional
 * and start at 1 if not supplied, C style again.
 */
enum Operation {
  ADD = 1,
  SUBTRACT = 2,
  MULTIPLY = 3,
  DIVIDE = 4
}

/**
 * Structs are the basic complex data structures. They are comprised of fields
 * which each have an integer identifier, a type, a symbolic name, and an
 * optional default value.
 *
 * Fields can be declared "optional", which ensures they will not be included
 * in the serialized output if they aren't set.  Note that this requires some
 * manual management in some languages.
 */
struct Work {
  1: i32 num1 = 0,
  2: i32 num2,
  3: Operation op,
  4: optional string comment,
}

/**
 * Structs can also be exceptions, if they are nasty.
 */
exception InvalidOperation {
  1: i32 whatOp,
  2: string why
}

/**
 * Ahh, now onto the cool part, defining a service. Services just need a name
 * and can optionally inherit from another service using the extends keyword.
 */
service Calculator extends shared.SharedService {

  /**
   * A method definition looks like C code. It has a return type, arguments,
   * and optionally a list of exceptions that it may throw. Note that argument
   * lists and exception lists are specified using the exact same syntax as
   * field lists in struct or exception definitions.
   */

   void ping(),

   i32 add(1:i32 num1, 2:i32 num2),

   i32 calculate(1:i32 logid, 2:Work w) throws (1:InvalidOperation ouch),

   /**
    * This method has a oneway modifier. That means the client only makes
    * a request and does not listen for any response at all. Oneway methods
    * must be void.
    */
   oneway void zip()

}

/**
 * That just about covers the basics. Take a look in the test/ folder for more
 * detailed examples. After you run this file, your generated code shows up
 * in folders with names gen-<language>. The generated code isn't too scary
 * to look at. It even has pretty indentation.
 */
```
然后使用刚刚下载的`thrift-0.13.0.exe`采用`thrift -r --gen js:node tutorial.thrift`命令将`tutorial.thrift`和`shared.thrift`生成对应的Node.js文件
```shell
thrift -r --gen js:node tutorial.thrift
```
![thrift命令](https://img-blog.csdnimg.cn/20201117232517530.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
可以看到`tutorial.thrift`和`shared.thrift`当前所在目录下生成了`gen-nodejs`目录，如下图所示：

![gen-nodejs目录](https://img-blog.csdnimg.cn/20201117232640689.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
创建一个tutorial目录，再其下再创建一个nodejs目录，分别创建一个`NodejsServer.js`和`NodejsClient.js`文件，其内容如下所示：

### NodejsServer.js
```js
var Calculator = require('./gen-nodejs/Calculator');
var ttypes = require('./gen-nodejs/tutorial_types');
var SharedStruct = require('./gen-nodejs/shared_types').SharedStruct;

var thrift = require('thrift');

var data = {};

var server = thrift.createServer(Calculator, {
  ping: function(result) {
    console.log("ping()");
    result(null);
  },
  add: function(n1, n2, result) {
    console.log("add(", n1, ",", n2, ")");
    result(null, n1+n2);
  },

  calculate: function(logid, work, result) {
    console.log("calculate(", logid, ",", work, ")");

    var val = 0;
    if (work.op == ttypes.Operation.ADD) {
      val = work.num1 + work.num2;
    } else if (work.op === ttypes.Operation.SUBTRACT) {
      val = work.num1 - work.num2;
    } else if (work.op === ttypes.Operation.MULTIPLY) {
      val = work.num1 * work.num2;
    } else if (work.op === ttypes.Operation.DIVIDE) {
      if (work.num2 == 0) {
        var x = new ttypes.InvalidOperation();
        x.whatOp = work.op;
        x.why = 'Cannot divide by 0';
        result(x);
        return;
      }
      val = work.num1 / work.num2;
    } else {
      var y = ttypes.InvalidOperation();
      y.whatOp = work.op;
      y.why = 'Invalid operation';
      result(y);
      return;
    }
    var entry = new SharedStruct();
    entry.key = logid;
    entry.value = "" + val;
    data[logid] = entry;

    result(null, val);
  },

  getStruct: function(key, result) {
    console.log("getStruct(", key, ")");
    result(null, data[key]);
  },

  zip: function() {
    console.log("zip()");
  }
});

server.listen(9090);
```

### NodejsClient.js
```js
var Calculator = require('./gen-nodejs/Calculator');
var ttypes = require('./gen-nodejs/tutorial_types');
const assert = require('assert');

var thrift = require('thrift');

var transport = thrift.TBufferedTransport;
var protocol = thrift.TBinaryProtocol;

var connection = thrift.createConnection("localhost", 9090, {
  transport: transport,
  protocol: protocol
});

connection.on('error', function(err) {
  assert(false, err);
});

// Create a Calculator client with the connection
var client = thrift.createClient(Calculator, connection);

client.ping(function(err, response) {
  console.log('ping()');
});

client.add(1, 1, function(err, response) {
  console.log("1+1=" + response);
});

work = new ttypes.Work();
work.op = ttypes.Operation.DIVIDE;
work.num1 = 1;
work.num2 = 0;

client.calculate(1, work, function(err, message) {
  if (err) {
    console.log("InvalidOperation " + err);
  } else {
    console.log('Whoa? You know how to divide by zero?');
  }
});

work.op = ttypes.Operation.SUBTRACT;
work.num1 = 15;
work.num2 = 10;

client.calculate(1, work, function(err, message) {
  console.log('15-10=' + message);

  client.getStruct(1, function(err, message) {
    console.log('Check log: ' + message.value);

    // close the connection once we're done
    connection.end();
  });
});
```

## 在Windows下运行Node.js示例代码
在项目源代码目录即nodejs所在目录使用`npm`或'cnpm`或'yarn`安装`thrift`库，在国内由于墙的原因`npm`下载和安装依赖库比较慢，所以建议使用'cnpm`或者`yarn`进行安装依赖库，最近发现使用`yarn`比较方便：
```shell
yarn init -y
yarn add thrift
```
我使用的是Windows下的VSCode作为开发环境，
### 使用`node NodeServer.js`运行RPC服务端：
![node NodeServer.js](https://img-blog.csdnimg.cn/20201117234228613.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
### 使用`node NodeClient.js`运行RPC客户端：
![使用node NodeClient.js运行RPC客户端](https://img-blog.csdnimg.cn/20201117234355446.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 在CentOS7下运行Node.js示例代码
### 运行Nodejs服务端
![运行Nodejs服务端](https://img-blog.csdnimg.cn/20201117235156224.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
### 运行Node.js客户端
![运行Node.js客户端](https://img-blog.csdnimg.cn/20201117235501953.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
