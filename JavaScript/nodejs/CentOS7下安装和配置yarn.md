[Yarn](https://github.com/yarnpkg/yarn)和[npm](https://www.npmjs.com/)一样是Node.js的包依赖管理工具。

## CentOS7下安装和配置yarn
### 1 准备工作
#### 1.1 浏览器访问安装包下载地址：
[https://github.com/yarnpkg/yarn/releases/](https://github.com/yarnpkg/yarn/releases/)
![yarn](https://img-blog.csdnimg.cn/20201015170257622.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

找到需要安装的版本，以v1.22.10为例，地址为：
- [yarn-1.22.10.tar.gz](https://github.com/yarnpkg/yarn/releases/download/v1.22.10/yarn-v1.22.10.tar.gz)
- [yarn-1.22.10.zip](https://github.com/yarnpkg/yarn/archive/v1.22.10.zip)

#### 1.2 下载源码
$ mkdir -p /usr/local/yarn
$ wget https://github.com/yarnpkg/yarn/releases/download/v1.22.10/yarn-v1.22.10.tar.gz
$ tar -zxvf yarn-v1.22.10.tar.gz -C /usr/local/yarn

### 2 安装
yarn不需要安装过程，直接下载后配置profile即可使用。

#### 2.1 配置yarn的环境变量
修改`/etc/profile`配置文件，配置yarn的环境变量，让`/usr/local/yarn/yarn-v1.22.10/bin`目录下的`yarn`命令可以在任何终端窗口中使用。
$ vim /etc/profile
 在文件结尾加入以下内容
```shell
export PATH=$PATH:/usr/local/yarn/yarn-1.22.10/bin
```
或者
```shell
 export YARN_HOME=/usr/local/yarn/yarn-v1.22.10
 export PATH=$PATH:$YARN_HOME/bin
```

如下图所示：
![配置yarn环境变量](https://img-blog.csdnimg.cn/20201015180816456.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)


#### 2.2 即时生效
```shell
source /etc/profile
```

2.3 查看安装情况
$ yarn -v
如果安装成功，会显示：
```shell
1.22.10
```
## 参考资料
- [centos7 安装 Yarn](https://www.cnblogs.com/dousnl/p/12052834.html)
- [https://github.com/yarnpkg/yarn](https://github.com/yarnpkg/yarn)
- [https://classic.yarnpkg.com/en/docs/install](https://classic.yarnpkg.com/en/docs/install)
- [https://classic.yarnpkg.com/en/docs/usage](https://classic.yarnpkg.com/en/docs/usage)
