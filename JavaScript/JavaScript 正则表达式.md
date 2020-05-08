# JavaScript 正则表达式

> 原文： [http://zetcode.com/javascript/regularexpressions/](http://zetcode.com/javascript/regularexpressions/)

JavaScript 正则表达式教程展示了如何在 JavaScript 中使用正则表达式。

正则表达式用于文本搜索和更高级的文本操作。 正则表达式是内置工具，如 grep，sed，文本编辑器（如 vi，emacs），编程语言（如 JavaScript，Perl 和 Python）。

## JavaScript 正则表达式

在 JavaScript 中，我们使用斜线`//`或`RegExp`对象构建正则表达式。

模式是一个正则表达式，用于定义我们正在搜索或操纵的文本。 它由文本文字和元字符组成。 元字符是控制正则表达式计算方式的特殊字符。 例如，使用`\s`，我们搜索空白。

创建模式后，可以使用其中一个函数将模式应用于文本字符串。 函数包括`test()`，`match()`，`search()`和`replace()`。

下表显示了一些正则表达式：

| 正则表达式 | 含义 |
| --- | --- |
| `.` | 匹配任何单个字符。 |
| `?` | 一次匹配或根本不匹配前面的元素。 |
| `+` | 与前面的元素匹配一次或多次。 |
| `*` | 与前面的元素匹配零次或多次。 |
| `^` | 匹配字符串中的起始位置。 |
| `$` | 匹配字符串中的结束位置。 |
| <code>&#124;</code> | 备用运算符。 |
| `[abc]` | 匹配 a 或 b 或 c。 |
| `[a-c]` | 范围; 匹配 a 或 b 或 c。 |
| `[^abc]` | 否定，匹配除 a 或 b 或 c 之外的所有内容。 |
| `\s` | 匹配空白字符。 |
| `\w` | 匹配单词字符； 等同于`[a-zA-Z_0-9]` |

## 测试函数

`test()`方法执行搜索以查找正则表达式和指定字符串之间的匹配项。 它返回 true 或 false。

`test_fun.js`

```js
let words = ['book', 'bookworm', 'Bible', 
    'bookish','cookbook', 'bookstore', 'pocketbook'];

let pattern = /book/;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

在示例中，我们有一个单词数组。 模式将在每个单词中寻找一个“ book”字符串。

```js
let pattern = /book/;

```

我们使用斜线创建一个模式。 正则表达式由四个普通字符组成。

```js
words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

我们遍历数组并调用`test()`函数。 如果模式与单词匹配，则返回 true。

```js
$ node test_fun.js 
the book matches
the bookworm matches
the bookish matches
the cookbook matches
the bookstore matches
the pocketbook matches

```

这些单词与模式匹配。

## `search()`函数

`search()`函数返回正则表达式与给定字符串之间的第一个匹配项的索引。 如果找不到匹配项，则返回-1。

`search_fun.js`

```js
let text = 'I saw a fox in the wood. The fox had red fur.';

let pattern = /fox/;

let idx = text.search(pattern);
console.log(`the term was found at index: ${idx}`);

```

在该示例中，我们找出“ fox”项的第一个匹配项的索引。

```js
$ node search_fun.js
the term was found at index: 8

```

这是输出。

## `exec`函数

`exec()`执行搜索以查找指定字符串中的匹配项。 它返回一个带有匹配信息的对象。

`exec_fun.js`

```js
let words = ['book', 'bookworm', 'Bible',
    'bookish', 'cookbook', 'bookstore', 'pocketbook'];

let pattern = /book/;

words.forEach(word => {

    let res = pattern.exec(word);

    if (res) {
        console.log(`${res} matches ${res.input} at index: ${res.index}`);
    }
});

```

在示例中，我们使用`exec()`将模式应用于输入字符串。

```js
if (res) {
    console.log(`${res} matches ${res.input} at index: ${res.index}`);
}

```

我们打印有关比赛的信息。 它包括比赛开始的索引。

```js
$ node exec_fun.js
book matches book at index: 0
book matches bookworm at index: 0
book matches bookish at index: 0
book matches cookbook at index: 4
book matches bookstore at index: 0
book matches pocketbook at index: 6

```

这是输出。

## `match()`函数

当将模式与输入字符串进行匹配时，`match()`函数将检索匹配项。

`match_fun.js`

```js
let text = 'I saw a fox in the wood. The fox had red fur.';

let pattern = /fox/g;

let found = text.match(pattern);

console.log(`There are ${found.length} matches`);

```

在该示例中，我们找出“ fox”项的出现次数。

```js
let pattern = /fox/g;

```

`g`字符是一个标志，可查找所有出现的术语。 通常，当找到第一个匹配项时，搜索结束。

```js
$ node match_fun.js
There are 2 matches

```

我们在字符串中找到了两个“ fox”术语。

## `replace()`函数

`replace()`函数返回一个新字符串，该字符串的部分或全部匹配都由替换字符串替换。

`replace_fun.js`

```js
let text = 'He has gray hair; gray clouds gathered above us.'

let pattern = /gray/g;

let new_text = text.replace(pattern, 'grey');

console.log(new_text);

```

在示例中，我们从输入字符串中创建了一个新字符串，在此我们将“灰色”单词替换为“灰色”。

```js
let pattern = /gray/g;

```

`g`字符是一个标志，可查找所有出现的术语。

```js
$ node replacing.js 
He has grey hair; grey clouds gathered above us.

```

这是输出。

## 不区分大小写的匹配

要启用不区分大小写的搜索，我们使用`i`标志。

`case_insensitive.js`

```js
let words = ['dog', 'Dog', 'DOG', 'Doggy'];

let pattern = /dog/i;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

在示例中，无论大小写如何，我们都将模式应用于单词。

```js
let pattern = /dog/i;

```

附加`i`标志，我们进行不区分大小写的搜索。

```js
$ node case_insensitive.js
the dog matches
the Dog matches
the DOG matches
the Doggy matches

```

执行不区分大小写的搜索时，所有四个单词都与模式匹配。

## 点元字符

点（。）元字符代表文本中的任何单个字符。

`dot_meta.js`

```js
let words = ['seven', 'even', 'prevent', 'revenge', 'maven', 
    'eleven', 'amen', 'event'];

let pattern = /..even/;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

在示例中，我们在一个数组中有八个单词。 我们在每个单词上应用一个包含两个点元字符的模式。

```js
$ node dot_meta.js
the prevent matches
the eleven matches

```

有两个与模式匹配的单词。

## 问号元字符

问号（？）元字符是与上一个元素零或一次匹配的量词。

`question_mark_meta.js`

```js
let words = ['seven', 'even', 'prevent', 'revenge', 'maven', 
    'eleven', 'amen', 'event'];

let pattern = /.?even/;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

在示例中，我们在点字符后添加问号。 这意味着在模式中我们可以有一个任意字符，也可以在那里没有任何字符。

```js
$ node question_mark_meta.js 
the seven matches
the even matches
the prevent matches
the revenge matches
the eleven matches
the event matches

```

这次，没有前一个字符的偶数和事件字也匹配。

## 锚点

锚点匹配给定文本内字符的位置。 当使用^锚时，匹配必须发生在字符串的开头，而当使用$锚时，匹配必须发生在字符串的结尾。

`anchors.js`

```js
let sentences = ['I am looking for Jane.',
    'Jane was walking along the river.',
    'Kate and Jane are close friends.'];

let pattern = /^Jane/;

sentences.forEach(sentence => {

    if (pattern.test(sentence)) {

        console.log(`${sentence}`);
    }
});

```

在示例中，我们有三个句子。 搜索模式为`^Jane`。 该模式检查“ Jane”字符串是否位于文本的开头。 `Jane\.`将在句子结尾处查找“ Jane”。

## 精确匹配

可以通过在锚点^和$之间放置术语来进行精确匹配。

`exact_match.js`

```js
let words = ['seven', 'even', 'prevent', 'revenge', 'maven', 
    'eleven', 'amen', 'event']

let pattern = /^even$/;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

在示例中，我们寻找“偶数”项的精确匹配。

```js
$ node exact_match.js
the even matches

```

这是输出。

## 字符类

字符类定义了一组字符，任何字符都可以出现在输入字符串中以使匹配成功。

`character_class.js`

```js
let words = ['a gray bird', 'grey hair', 'great look'];

let pattern = /gr[ea]y/;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`${word}`);
    }
});  

```

在该示例中，我们使用字符类同时包含灰色和灰色单词。

```js
let pattern = /gr[ea]y/;

```

`[ea]`类允许在模式中使用'e'或'a'字符。

## 命名字符类

有一些预定义的字符类。 `\s`与空白字符`[\t\n\t\f\v]`匹配，`\d`与数字`[0-9]`匹配，`\w`与单词字符`[a-zA-Z0-9_]`匹配。

`named_character_class.js`

```js
let text = 'We met in 2013\. She must be now about 27 years old.';

let pattern = /\d+/g;

while ((found = pattern.exec(text)) !== null) {

    console.log(`found ${found} at index ${found.index}`);
}  

```

在示例中，我们在文本中搜索数字。

```js
let pattern = /\d+/g;

```

`\d+`模式在文本中查找任意数量的数字集。 `g`标志使搜索在第一次出现时不会停止。

```js
while ((found = pattern.exec(text)) !== null) {

    console.log(`found ${found} at index ${found.index}`);
}  

```

要查找所有匹配项，我们在 while 循环中使用`exec()`函数。

```js
$ node named_character_class.js 
found 2013 at index 10
found 27 at index 38

```

这是输出。

在下面的示例中，我们有使用`match()`函数的替代解决方案。

`count_numbers.js`

```js
let text = 'I met her in 2012\. She must be now about 27 years old.'

let pattern = /\d+/g;

var found = text.match(pattern);

console.log(`There are ${found.length} numbers`);

found.forEach((num, i) => {
    console.log(`match ${++i}: ${num}`);
});

```

要计算数字，我们使用`\d`命名类。

```js
$ node count_numbers.js 
There are 2 numbers
match 1: 2012
match 2: 27

```

这是输出。

## 数词

在下一个示例中，我们计算文本中的单词数。

`count_words.js`

```js
let text = 'The Sun was shining; I went for a walk.';

let pattern = /\w+/g;

let found = text.match(pattern);

console.log(`There are ${found.length} words`);

```

`\w`名称集代表一个字字符。

```js
let pattern = /\w+/g;

```

该模式使用量词（+）搜索一个或多个单词字符。 全局标志使搜索查找字符串中的所有单词。

```js
console.log(`There are ${found.length} words`);

```

我们将单词数打印到控制台。

```js
$ node count_words.js 
There are 9 words

```

这是输出。

## 交替

交替运算符| 创建具有多种选择的正则表达式。

`alternations.js`

```js
let words = ["Jane", "Thomas", "Robert",
    "Lucy", "Beky", "John", "Peter", "Andy"];

let pattern = /Jane|Beky|Robert/;

words.forEach(word => {

    if (pattern.test(word)) {

        console.log(`the ${word} matches`);
    }
});

```

列表中有八个名称。

```js
let pattern = /Jane|Beky|Robert/;

```

此正则表达式查找“​​ Jane”，“ Beky”或“ Robert”字符串。

## 捕获组

捕获组是一种将多个字符视为一个单元的方法。 通过将字符放置在一组圆括号内来创建它们。 例如，（book）是包含'b'，'o'，'o'，'k'，字符的单个组。

捕获组技术使我们能够找出字符串中与正则表达式模式匹配的那些部分。

`capturing_groups.js`

```js
content = `<p>The <code>Pattern</code> is a compiled
representation of a regular expression.</p>`;

let pattern = /(<\/?[a-z]*>)/g;

let found = content.match(pattern);

found.forEach(tag => {

    console.log(tag);
});

```

该代码示例通过捕获一组字符来打印提供的字符串中的所有 HTML 标签。

```js
let found = content.match(pattern);

```

为了找到所有标签，我们使用`match()`方法。

```js
$ ./capturing_groups.js
<p>
<code>
</code>
</p>

```

我们找到了四个 HTML 标签。

## JavaScript 正则表达式电子邮件示例

在以下示例中，我们创建一个用于检查电子邮件地址的正则表达式模式。

`emails.js`

```js
let emails = ["luke@gmail.com", "andy@yahoocom",
    "34234sdfa#2345", "f344@gmail.com"];

let pattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,18}$/;

emails.forEach(email => {
    if (pattern.test(email)) {

        console.log(`${email} matches`);
    } else {

        console.log(`${email} does not match`);
    }
})

```

本示例提供了一种可能的解决方案。

```js
let pattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,18}$/;

```

前`^`和后`$`个字符提供精确的模式匹配。 模式前后不允许有字符。 电子邮件分为五个部分。 第一部分是本地部分。 这通常是公司，个人或昵称的名称。 `[a-zA-Z0-9._-]+`列出了我们可以在本地部分使用的所有可能字符。 它们可以使用一次或多次。

第二部分由文字`@`字符组成。 第三部分是领域部分。 通常是电子邮件提供商的域名，例如 yahoo 或 gmail。 `[a-zA-Z0-9-]+`是一个字符类，提供可在域名中使用的所有字符。 `+`量词允许使用这些字符中的一个或多个。

第四部分是点字符。 它前面带有转义字符（\），以获取文字点。

最后一部分是顶级域名：`[a-zA-Z.]{2,18}`。 顶级域可以包含 2 到 18 个字符，例如 sk，net，信息，旅行，清洁，旅行保险。 最大长度可以为 63 个字符，但是今天大多数域都少于 18 个字符。 还有一个点字符。 这是因为某些顶级域包含两个部分： 例如 co.uk。

```js
$ node emails.js 
luke@gmail.com matches
andy@yahoocom does not match
34234sdfa#2345 does not match
f344@gmail.com matches

```

这是输出。

在本章中，我们介绍了 JavaScript 中的正则表达式。

您可能也对以下相关教程感兴趣： [JavaScript 数组教程](/javascript/arrays/)和 [Big.js 教程](/javascript/bigjs/)。
