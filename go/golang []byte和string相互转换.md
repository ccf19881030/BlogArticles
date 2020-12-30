string 不能直接和byte数组转换

string可以和byte的切片转换

## 1,string 转为[]byte

var str string = "test"

var data []byte = []byte(str)

 

## 2,byte转为string

var data [10]byte 

byte[0] = 'T'

byte[1] = 'E'

var str string = string(data[:])

```go
package main

import (
    "fmt"
)

func main() {
    str2 := "hello"
    data2 := []byte(str2)
    fmt.Println(data2)
    str2 = string(data2[:])
    fmt.Println(str2)
}
```


