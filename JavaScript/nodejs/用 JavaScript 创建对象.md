# 用 JavaScript 创建对象

> 原文： [http://zetcode.com/javascript/createobject/](http://zetcode.com/javascript/createobject/)

JavaScript 创建对象教程展示了如何在 JavaScript 中创建对象。 可以使用对象字面值，函数构造函数或类定义来创建对象。 通常使用创建性生成器和工厂设计模式来创建对象。

在本教程中，我们使用 Node.js 执行示例。

## 对象字面值

在对象字面值表示法中，我们将用逗号分隔的对象属性放在大括号`{}`中。

属性名称和值用冒号分隔。

`object_literal.js`

```js
const person = {
    firstName: 'John',
    lastName: 'Doe',
    email: 'jdoe@example.com',
    info: function() {
        return `${this.firstName} ${this.lastName}, ${this.email}`
    }
};

console.log(person.info());

```

该示例使用字面值表示法创建一个对象。

```js
$ node object_literal.js
John Doe, jdoe@example.com

```

这是输出。

## 对象构造函数

可以使用`new Object()`构造函数创建对象。 然后使用点运算符动态添加属性。

`object_constructor.js`

```js
let person = new Object();

person.firstName = "John";
person.lastName = "Doe";
person.email = 'jdoe@example.com';

person.info = function(){
    return `${this.firstName} ${this.lastName}, ${this.email}`;
};

console.log(person.info());

```

该示例使用 Object 构造函数创建一个对象。

## 函数构造函数

使用`function`关键字创建函数构造函数。 它以值作为参数。 使用`this`关键字设置属性。 使用`this`和`function`关键字创建方法。 使用`new`关键字创建新对象。

`function_constructor.js`

```js
function Person(firstName, lastName, email) {

    this.firstName = firstName;
    this.lastName = lastName;
    this.email = email;

    this.info = function() {
        return `${this.firstName} ${this.lastName}, ${this.email}`;
    }
}

let person = new Person('John', 'Doe', 'jdoe@example.com');
console.log(person.info());

```

该示例使用函数构造函数创建一个对象。

## 类定义

对象用`class`关键字定义，并用`new`关键字生成。 这是创建从诸如 C# 或 Java 之类的语言已知的对象的经典方法。 JavaScript 使用`constructor`关键字定义对象构造函数。 使用`this`关键字设置属性。

`class_definition.js`

```js
class Person {

    constructor(firstName, lastName, email) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
    }

    info() {
        return `${this.firstName} ${this.lastName}, ${this.email}`;
    }
}

let person = new Person('John', 'Doe', 'jdoe@example.com');
console.log(person.info());

```

该示例使用类定义创建对象。

## 构建器模式

构建器模式是一种用于创建对象的创新性设计模式。 它通过提供逐步的方法，使用简单的对象来构建复杂的对象。 Builder 模式使用流利的 API 创建对象。

`builder_pattern.js`

```js
let Person = function (firstName, lastName, email) {

    this.firstName = firstName;
    this.lastName = lastName;
    this.email = email;
}

let PersonBuilder = function () {

    let firstName;
    let lastName;
    let email;

    return {
        setFirstName: function (firstName) {
            this.firstName = firstName;
            return this;
        },
        setLastName: function (lastName) {
            this.lastName = lastName;
            return this;
        },
        setEmail: function (email) {
            this.email = email;
            return this;
        },
        info: function () {
            return `${this.firstName} ${this.lastName}, ${this.email}`;
        },
        build: function () {
            return new Person(firstName, lastName, email);
        }
    };
};

var person = new PersonBuilder().setFirstName('John').setLastName('Doe')
    .setEmail('jdoe@example.com');
console.log(person.info());

```

该示例使用构建器设计模式创建一个对象。

## 工厂模式

使用 Factory 模式，我们可以在不将创建逻辑暴露给客户端的情况下创建对象。

`factory_pattern.js`

```js
const personFactory = (firstName, lastName, email) => {
    return {
        firstName: firstName,
        lastName: lastName,
        email: email,
        info() {
            return `${this.firstName} ${this.lastName}, ${this.email}`;
        }
    };
};

let person = personFactory('John', 'Doe', 'jdoe@example.com');

console.log(person.info());

```

该示例使用工厂模式创建一个对象。

在本教程中，我们使用不同的语法创建了 JavaScript 对象。 我们还介绍了两种创新的设计模式，即构建器模式和工厂模式。

您可能也对以下相关教程感兴趣： [JavaScript 构建器模式教程](/javascript/builderpattern/)，或列出[所有 JavaScript 教程](/all/#js)。
