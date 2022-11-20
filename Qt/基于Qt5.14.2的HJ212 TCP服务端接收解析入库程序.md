# 基于Qt5.14.2的HJ212 TCP服务端接收解析入库程序
   之前写过一篇关于[环保 HJ212协议解析](https://ccf19881030.blog.csdn.net/article/details/108621406)的博文，有不少做环保行业的人咨询我关于HJ212-2017协议怎么解析，由于我主要是做C++开发的，之前采用C++ Boost asio库编写了一个TCP接收服务端，并解析HJ212-2017协议数据，上传到我的GitHub上面，仓库地址为：[https://github.com/ccf19881030/HJ212Receiver](https://github.com/ccf19881030/HJ212Receiver)，已经在Windows10系统下使用VS2017进行测试过，并且在CentOS8系统下使用Cmake进行编译测试。有需要的话可以自行下载：
```
git clone https://github.com/ccf19881030/HJ212Receiver.git
```

由于Qt自带了很多库，比如说网络库，SQL数据库接口等，使用起来比Boost库方便很多，于是使用Qt写了一个TCP服务端用于接收和解析HJ212-2017报文，然后入库到MySQL数据库中。最终的程序效果如下图所示：
![TCP服务端](https://img-blog.csdnimg.cn/20210429192423887.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
相关源代码我已经上传到Github上面，仓库地址为：[https://github.com/ccf19881030/GB212ReceiverApp](https://github.com/ccf19881030/GB212ReceiverApp)
需要的话可以自行下载：
```
git clone https://github.com/ccf19881030/GB212ReceiverApp
```
![GB212ReceiverApp仓库](https://img-blog.csdnimg.cn/20210429194341729.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

该程序是基于Qt5.14.2的HJ212-2017 TCP接收服务端，解析入库程序。数据库采用MySQL ODBC，使用Qt库编写TCP服务器，接收到HJ212-2017报文后解析入库到MySQL数据库中。

## 注意事项
一、开发环境：
- 1、使用VS2017+QT5.14.2作为开发环境，已经测试过基于X64位的Debug和Relase版本
- 2、使用到的技术有Qt、ODBC连接库mysql-connector-odbc-8.0.24-winx64.msi，关于在Windows10中使用Qt连接MySQL数据库，可以参考CSDN上的一篇博客：[连接MySQL数据库(通过ODBC方式连接)](https://blog.csdn.net/joey_ro/article/details/105411135)
- 3、需要将 MySQL数据库脚本 目录下的test_hj212_db.sql导入到你本地的MySQL数据库中，可以直接使用Navicat Premium 12等客户端工具，或者其他的数据库客户端工具，为了简便，目前数据库连接信息没有写入到配置文件中，直接硬编码到hj212dialog.cpp文件中，需要根据自己MySQL数据库中的连接情况相应修改第31行代码：dbprocess_.setDBInfo("127.0.0.1", 3306, "root", "1030", "test_hj212_db");
- 4、可以使用windeployqt.exe和Inno Setup Compiler对编译好的release x64位的Qt C++程序进行打包。


二、前提条件：
- 1、安装Qt5.14.2等版本
- 2、安装MySQL数据库
- 3、将MySQL数据库脚本 目录下的test_hj212_db.sql导入到你本地的MySQL数据库中
- 4、安装mysql-connector-odbc-8.0.24-winx64.msi，并配置mysql ODBC数据源，具体方法参考[https://blog.csdn.net/joey_ro/article/details/105411135](https://blog.csdn.net/joey_ro/article/details/105411135)这篇博客
- 5、修改hj212dialog.cpp文件中第31行代码：dbprocess_.setDBInfo("127.0.0.1", 3306, "root", "1030", "test_hj212_db");
改成自己的MySQL数据库配置
- 6、编译打包，可以先使用Qt5.14.2的windeployqt工具将相应的Qt5的dll库拷贝到exe可执行程序目录，然后再使用innosetup-6.1.2.exe工具进行打包。


## MySQL数据库
数据库采用的是MySQL，SQL数据库脚本如下：
```
/*
 Navicat Premium Data Transfer

 Source Server         : 本地MySQL数据库
 Source Server Type    : MySQL
 Source Server Version : 80016
 Source Host           : localhost:3306
 Source Schema         : test_hj212_db

 Target Server Type    : MySQL
 Target Server Version : 80016
 File Encoding         : 65001

 Date: 22/04/2021 21:15:56
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for monitordata
-- ----------------------------
DROP TABLE IF EXISTS `monitordata`;
CREATE TABLE `monitordata`  (
  `mn` varchar(255) CHARACTER SET utf8 COLLATE utf8_croatian_ci NOT NULL COMMENT '站点编码',
  `datatime` datetime(0) NOT NULL COMMENT '数据时间',
  `paramCode` varchar(255) CHARACTER SET utf8 COLLATE utf8_croatian_ci NOT NULL COMMENT '监测因子编码',
  `val` double(255, 0) NULL DEFAULT NULL COMMENT '监测数值',
  `mark` varchar(255) CHARACTER SET utf8 COLLATE utf8_croatian_ci NULL DEFAULT NULL COMMENT '监测数据标记',
  PRIMARY KEY (`mn`, `datatime`, `paramCode`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_croatian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of monitordata
-- ----------------------------
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a01001', -1, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a01002', 22, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a01006', 1032, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a01007', 4, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a01008', 353, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a05002', 34, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a05024', 6, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a21002', 18, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a21003', 5, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a21004', 9, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a21005', 1, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a21026', 2, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a24088', 35, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a34002', 124, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a34004', 25, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a34006', 874, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a34007', 2679, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a34049', 3553, 'N');
INSERT INTO `monitordata` VALUES ('LB4200001', '2021-01-07 14:38:00', 'a99999', 69, 'N');

-- ----------------------------
-- Table structure for station
-- ----------------------------
DROP TABLE IF EXISTS `station`;
CREATE TABLE `station`  (
  `mn` varchar(255) CHARACTER SET utf8 COLLATE utf8_croatian_ci NULL DEFAULT NULL COMMENT '站点编码',
  `stationname` varchar(255) CHARACTER SET utf8 COLLATE utf8_croatian_ci NULL DEFAULT NULL COMMENT '站点名称'
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_croatian_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```
![MySQL数据库](https://img-blog.csdnimg.cn/2021042919595653.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
## 程序运行
在环保项目中一般一个空气自动站、水站或者土壤站点一般涉及到的表比较多，其中有监测数据表、站点表、因子编码表等等。
首先看一下MySQL数据库中的`monitordata`表结构：
![monitordata表结构](https://img-blog.csdnimg.cn/20210503081222499.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
`monitordata`表中的数据刚开始把它清空：
![monitordata表的数据](https://img-blog.csdnimg.cn/20210503081311361.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)



再运行程序，
![HJ212-2017服务端接收和解析入库程序](https://img-blog.csdnimg.cn/20210429200916568.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
首先设置好TCP服务端的监听端口号，然后再点击上面程序界面的【监听】按钮；然后使用网络调试助手开一个TCP客户端，连接上面的TCP服务端，
![TCP客户端](https://img-blog.csdnimg.cn/20210429201122926.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
输入HJ212-2017报文，然后点击发送。可以看到TCP服务端接收并解析数据显示的效果，如下图所示：
![程序接收示例](https://img-blog.csdnimg.cn/20210429201239311.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
可以看到MySQL数据库`test_hj212_db`的表`monitordata`表`中插入了几条监测数据记录，如下图所示：
![monitordata表](https://img-blog.csdnimg.cn/20210503083347925.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
