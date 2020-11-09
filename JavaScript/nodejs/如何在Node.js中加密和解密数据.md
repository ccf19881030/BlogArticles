本文翻译自[How to encrypt and decrypt data in Node.js](https://attacomsian.com/blog/nodejs-encrypt-decrypt-data)

Node.js提供了一个名为`crypto`的内置模块，可用于加密和解密字符串，数字，缓冲区，流等。 该模块提供了加密功能，其中包括用于OpenSSL哈希，HMAC，密码，解密，签名和验证功能的一组包装器。

在本文中，您将学习如何使用Node.js的`crypto`模块对数据执行加密操作。 我将向您展示如何使用秘钥加密数据，然后在需要时使用相同的秘钥解密数据。

为了简单起见，我将使用AES（高级加密系统）算法CTR加密模式。 这是有关选择正确的AES加密模式的[StackOverflow](https://stackoverflow.com/questions/1220751/how-to-choose-an-aes-encryption-mode-cbc-ecb-ctr-ocb-cfb)的很好的讨论。

## 创建一个新项目
在本地文件系统中创建一个新目录，并通过键入以下命令切换到该目录：
```
$ mkdir crypto && cd crypto
```

现在执行以下命令来初始化一个新的Node.js项目：
```
$npm init -y
```
上面的命令将在根目录中创建一个新的`package.json文件。 发出上述命令之前，请确保已在计算机上[安装了Node.js](https://attacomsian.com/blog/install-nodejs-npm-ubuntu)。`

默认情况下，`crypto`模块已包含在预构建的Node.js二进制文件中。 但是，如果您手动安装了Node.js，则可能未附带`crypto`模块。 但是，您可以通过执行以下命令来安装它：
```
$ npm install crypto --save
```

## 加密和解密文本
让我们在项目的根目录中创建`crypto.js`文件，并定义我们的加密和解密功能，如下所示：
`crypto.js`
```js
const crypto = require('crypto');

const algorithm = 'aes-256-ctr';
const secretKey = 'vOVH6sdmpNWjRRIqCc7rdxs01lwHzfr3';
const iv = crypto.randomBytes(16);

const encrypt = (text) => {

    const cipher = crypto.createCipheriv(algorithm, secretKey, iv);

    const encrypted = Buffer.concat([cipher.update(text), cipher.final()]);

    return {
        iv: iv.toString('hex'),
        content: encrypted.toString('hex')
    };
};

const decrypt = (hash) => {

    const decipher = crypto.createDecipheriv(algorithm, secretKey, Buffer.from(hash.iv, 'hex'));

    const decrpyted = Buffer.concat([decipher.update(Buffer.from(hash.content, 'hex')), decipher.final()]);

    return decrpyted.toString();
};

module.exports = {
    encrypt,
    decrypt
};
```
下面的示例演示如何使用上述功能来加密和解密文本数据（字符串，数字等）：
`crypto-text.js`
```js
const { encrypt, decrypt } = require('./crypto');

const hash = encrypt('Hello World!');

console.log(hash);

// {
//     iv: '237f306841bd23a418878792252ff6c8',
//     content: 'e2da5c6073dd978991d8c7cd'
// }

const text = decrypt(hash);

console.log(text); // Hello World!
```

## 加密和解密缓冲区
您也可以使用上面定义的功能对缓冲区进行加密和解密。 只需传递缓冲区代替字符串，它应该可以工作：
`crypto-buffer.js`
```js
const { encrypt, decrypt } = require('./crypto');

const hash = encrypt(Buffer.from('Hello World!', 'utf8'));

console.log(hash);

// {
//     iv: '692e44dbbea073fc1a8d1c37ea68dffa',
//     content: 'bbffd902d55d7a00f3a0504e'
// }

const text = decrypt(hash);

console.log(text); // Hello World!
```

## 加密和解密流
您还可以使用加密模块对流进行加密和解密，如以下示例所示：
`crypto-stream.js`
```js
const crypto = require('crypto');
const fs = require('fs');

const algorithm = 'aes-256-ctr';
const secretKey = 'vOVH6sdmpNWjRRIqCc7rdxs01lwHzfr3';
const iv = crypto.randomBytes(16);

// input file
const r = fs.createReadStream('file.txt');

// encrypt content
const encrypt = crypto.createCipheriv(algorithm, secretKey, iv);

// decrypt content
const decrypt = crypto.createDecipheriv(algorithm, secretKey, iv);

// write file
const w = fs.createWriteStream('file.out.txt');

// start pipe
r.pipe(encrypt)
    .pipe(decrypt)
    .pipe(w);
````

源代码：在MIT许可下可从[GitHub](https://github.com/attacomsian/code-examples/tree/master/nodejs/crypto)下载此项目的完整源代码。

## 结论
在本文中，我们研究了如何使用Node.js内置的`crypto`模块对文本，缓冲区和流执行加密操作。 如果在将敏感数据（例如密钥）存储到数据库之前需要对其进行加密，这将非常有用。

喜欢这篇文章吗？ 在[Twitter](https://twitter.com/attacomsian)和[LinkedIn](https://linkedin.com/in/attacomsian)上关注我。 您也可以订阅[RSS Feed](https://feeds.feedburner.com/attacomsian)。

您可能还喜欢
- [How to read and write JSON files in Node.js](https://attacomsian.com/blog/nodejs-read-write-json-files)
- [Monitoring Your Node.js App with Scout APM](https://attacomsian.com/blog/monitoring-nodejs-app-with-scout-apm)
- [How to edit an XML file with Node.js](https://attacomsian.com/blog/nodjs-edit-xml-file)
- [How to read input from the command line in Node.js](https://attacomsian.com/blog/nodejs-read-input-from-cli)
