本文翻译自[How to pretty-print a JSON object with JavaScript](https://attacomsian.com/blog/javascript-pretty-print-json)

## 如何使用JavaScript漂亮地打印JSON对象
在[之前的文章](https://attacomsian.com/blog/json-parse-stringify#jsonstringify)中，我们研究了如何使用`JSON.stringify()`方法将[JSON](https://attacomsian.com/blog/what-is-json)对象序列化为JSON字符串。 当从客户端向服务器发送JON数据时，这非常有用。

在本文中，您将学习如何使用JSON.stringify（）方法在JavaScript中漂亮地打印JSON[对象](https://attacomsian.com/blog/objects-prototypes-classes-javascript#objects)。

`JSON.stringify()`方法最多接受三个参数：JSON对象，替换器和空格。 只有JSON对象是必需的，其余两个参数是可选的。

如果在调用`JSON.stringify()`时跳过可选参数，则输出JSON字符串将不包含任何空格或换行符。 这使得很难读取序列化的JSON字符串，尤其是当您将其写入文件时。

为了提高可读性，您可以做的是传入一个数字作为第三个参数，表示要插入的总空格。 空格数必须在0到10之间：
```js
const obj = {
    name: 'Atta',
    profession: 'Software Engineer',
    country: 'PK',
    skills: ['Java', 'Spring Boot', 'Node.js', 'JavaScript']
};

// serialize JSON object
const str = JSON.stringify(obj, null, 4);

// print JSON string
console.log(str);
```
上面的示例将JSON对象序列化为以下字符串：
```json
{
    "name": "Atta",
    "profession": "Software Engineer",
    "country": "PK",
    "skills": [
        "Java",
        "Spring Boot",
        "Node.js",
        "JavaScript"
    ]
}
```
正如您在上面看到的那样，序列化的JSON字符串格式正确，并且比默认行为更具可读性。 省略space参数时，输出JSON字符串如下所示：
```json
{"name":"Atta","profession":"Software Engineer","country":"PK","skills":["Java","Spring Boot","Node.js","JavaScript"]}
```
仅此而已。 查看[本指南](https://attacomsian.com/blog/json-parse-stringify)，以了解有关JavaScript中JSON数据解析和序列化的更多信息。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

## 其他博客
- [JavaScript DOM — Detect Internet Explorer Browser](https://attacomsian.com/blog/javascript-dom-detect-internet-explorer-browser)
- [JavaScript DOM — Toggle password visibility](https://attacomsian.com/blog/javascript-dom-toggle-password-visibility)
- [JavaScript DOM — Append to an element](https://attacomsian.com/blog/javascript-dom-append-to-an-element)
- [JavaScript DOM — Detect if caps lock is on](https://attacomsian.com/blog/javascript-dom-detect-if-caps-lock-is-on)
- [JavaScript DOM — Detect if an element has focus](https://attacomsian.com/blog/javascript-dom-detect-if-an-element-has-focus)
