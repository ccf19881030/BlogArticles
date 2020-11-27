# go rpc示例

最近在Youtube上面看到一个关于`golang rpc包的示例视频`：youtube视频地址：[Building a Basic RPC Server and Client with Go](https://www.youtube.com/watch?v=1MPWPq2N768)，其相应源代码的Github仓库地址为：[https://github.com/tensor-programming/go-basic-rpc](https://github.com/tensor-programming/go-basic-rpc)，需要的话可以自行获取：
```git
git clone https://github.com/tensor-programming/go-basic-rpc.git
```
## golang rpc包
关于golang中的rpc库，可以查看官方文档：[https://golang.org/pkg/net/rpc/](https://golang.org/pkg/net/rpc/)和[https://pkg.go.dev/net/rpc](https://pkg.go.dev/net/rpc)，如下图所示：
![golang rpc](https://img-blog.csdnimg.cn/20201124100032330.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 简单的示例(不使用rpc)
下面对一个带有Title和Body的Item数组对象database，编写增删改查的方法，并进行简单的测试，相应的Go代码示例如下：
```go
package main

import (
	"fmt"
)

type Item struct {
	Title string
	Body  string
}

var database []Item

// 根据title名称从database数组中获取对应的Item对象
func GetByName(title string) Item {
	var getItem Item

	for _, val := range database {
		if val.Title == title {
			getItem = val
		}
	}

	return getItem
}

// 添加一个新的Item对象
func AddItem(item Item) Item {
	database = append(database, item)
	return item
}

// 根据title在database中查询对应的Item对象，如果存在则进行更新
func EditItem(title string, edit Item) Item {
	var changed Item

	for idx, val := range database {
		if val.Title == title {
			database[idx] = edit
			changed = edit
		}
	}

	return changed
}

// 删除某个item对象
func DeleteItem(item Item) Item {
	var del Item

	for idx, val := range database {
		if val.Title == item.Title && val.Body == item.Body {
			database = append(database[:idx], database[idx+1:]...)
			del = val
			break
		}
	}

	return del
}

func main() {
	fmt.Println("initial database: ", database)
	a := Item{"first", "a test item"}
	b := Item{"second", "a second item"}
	c := Item{"third", "a third item"}

	AddItem(a)
	AddItem(b)
	AddItem(c)

	fmt.Println("second database: ", database)

	DeleteItem(b)
	fmt.Println("third database: ", database)

	EditItem("third", Item{"fourth", "a new item"})
	fmt.Println("fourth database: ", database)

	x := GetByName("fourth")
	y := GetByName("first")
	fmt.Println(x, y)
}

```
执行命令`go run main,go`得出如下的输出：
![test main.go](https://img-blog.csdnimg.cn/20201124101106726.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## go_basic_rpc示例（包括rpc服务端和rpc客户端）
首先创建一个`go-basic-rpc`的目录，在其下创建一个`server.go`用于编写go rpc服务端，再创建一个`client`目录，然后在`client`目录下创建一个`client.go`文件用于编写go rpc客户端。最终的目录结构如下所示：
![go_basic_rpc的目录结构](https://img-blog.csdnimg.cn/20201124101718104.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)


### go rpc服务端`server.go`代码如下：
```go
package main

import (
	"log"
	"net"
	"net/http"
	"net/rpc"
)

type Item struct {
	Title string
	Body  string
}

type API int

var database []Item

func (a *API) GetDB(empty string, reply *[]Item) error {
	*reply = database
	return nil
}

func (a *API) GetByName(title string, reply *Item) error {
	var getItem Item

	for _, val := range database {
		if val.Title == title {
			getItem = val
		}
	}

	*reply = getItem

	return nil
}

func (a *API) AddItem(item Item, reply *Item) error {
	database = append(database, item)
	*reply = item
	return nil
}

func (a *API) EditItem(item Item, reply *Item) error {
	var changed Item

	for idx, val := range database {
		if val.Title == item.Title {
			database[idx] = Item{item.Title, item.Body}
			changed = database[idx]
		}
	}

	*reply = changed
	return nil
}

func (a *API) DeleteItem(item Item, reply *Item) error {
	var del Item

	for idx, val := range database {
		if val.Title == item.Title && val.Body == item.Body {
			database = append(database[:idx], database[idx+1:]...)
			del = item
			break
		}
	}

	*reply = del
	return nil
}

func main() {
	api := new(API)
	err := rpc.Register(api)
	if err != nil {
		log.Fatal("error registering API", err)
	}

	rpc.HandleHTTP()

	listener, err := net.Listen("tcp", ":4040")

	if err != nil {
		log.Fatal("Listener error", err)
	}
	log.Printf("serving rpc on port %d", 4040)
	http.Serve(listener, nil)

	if err != nil {
		log.Fatal("error serving: ", err)
	}

	// fmt.Println("initial database: ", database)
	// a := Item{"first", "a test item"}
	// b := Item{"second", "a second item"}
	// c := Item{"third", "a third item"}

	// AddItem(a)
	// AddItem(b)
	// AddItem(c)
	// fmt.Println("second database: ", database)

	// DeleteItem(b)
	// fmt.Println("third database: ", database)

	// EditItem("third", Item{"fourth", "a new item"})
	// fmt.Println("fourth database: ", database)

	// x := GetByName("fourth")
	// y := GetByName("first")
	// fmt.Println(x, y)

}
```


### go rpc客户端`client/client.go`代码如下：
```go
package main

import (
	"fmt"
	"log"
	"net/rpc"
)

type Item struct {
	Title string
	Body  string
}

func main() {
	var reply Item
	var db []Item

	client, err := rpc.DialHTTP("tcp", "localhost:4040")

	if err != nil {
		log.Fatal("Connection error: ", err)
	}

	a := Item{"First", "A first item"}
	b := Item{"Second", "A second item"}
	c := Item{"Third", "A third item"}

	client.Call("API.AddItem", a, &reply)
	client.Call("API.AddItem", b, &reply)
	client.Call("API.AddItem", c, &reply)
	client.Call("API.GetDB", "", &db)

	fmt.Println("Database: ", db)

	client.Call("API.EditItem", Item{"Second", "A new second item"}, &reply)

	client.Call("API.DeleteItem", c, &reply)
	client.Call("API.GetDB", "", &db)
	fmt.Println("Database: ", db)

	client.Call("API.GetByName", "First", &reply)
	fmt.Println("first item: ", reply)

}

```

### 运行rpc服务端和客户端
- 运行rpc服务端
```shell
cd /root/Programming/GoPro/go-basic-rpc
go run server.go
```

- 运行rpc客户端
```shell
cd /root/Programming/GoPro/go-basic-rpc/client
go run client.go
```

![运行go_basic_rpc服务端和客户端](https://img-blog.csdnimg.cn/20201124102107500.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)




## 参考资料
- youtube视频地址：[Building a Basic RPC Server and Client with Go](https://www.youtube.com/watch?v=1MPWPq2N768)
- Github代码：[https://github.com/tensor-programming/go-basic-rpc](https://github.com/tensor-programming/go-basic-rpc)
- [https://github.com/grpc/grpc-go](https://github.com/grpc/grpc-go)
- [https://golang.org/pkg/net/rpc/](https://golang.org/pkg/net/rpc/)
- [https://pkg.go.dev/net/rpc](https://pkg.go.dev/net/rpc)
