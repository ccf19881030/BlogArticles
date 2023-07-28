# [golang正则验证邮箱格式](https://www.cnblogs.com/chaselogs/p/10072430.html)
```go
func VerifyEmailFormat(email string) bool {
    pattern := `\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*` //匹配电子邮箱
    reg := regexp.MustCompile(pattern)
    return reg.MatchString(email)
}

func main() {
    fmt.Println(VerifyEmailFormat("12345@126.com")) //true
    fmt.Println(VerifyEmailFormat("12345126.com"))  //false
}
```
