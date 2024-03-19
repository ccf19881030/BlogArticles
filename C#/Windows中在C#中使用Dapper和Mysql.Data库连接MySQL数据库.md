# Windows中在C#中使用Dapper和Mysql.Data库连接MySQL数据库
在Windows中使用C#连接Mysql数据库比较简单，可以直接使用[MySql.Data](https://www.nuget.org/packages/MySql.Data/)库，目前最新版本为：8.3.0。
当然也可以结合[MySql.Data](https://www.nuget.org/packages/MySql.Data/)和[Dapper](https://www.nuget.org/packages/Dapper)库一起使用，目前Dapper的最新版本为：2.1.35。
[Dapper](https://github.com/DapperLib/Dapper)是一款轻量级ORM工具，是一个简单的.NET对象映射器，在速度上几乎与使用原始ADO.NET数据读取器的速度一样快。ORM是一个对象关系映射器，它负责数据库和编程语言之间的映射。Dapper通过扩展IDbConnection提供一些有用的扩展方法去查询数据库，提供了一种简单、高效的方式来执行数据库查询、插入、更新和删除操作。

# 一、使用Mysql.Data和Dapper来操作Mysql数据库
准备条件：
(1)、OS：Windows 10或Windows11
(2)、Visual Stuidio 2022
(3)、MySQL安装包，比如[mysql-installer-web-community-8.0.36.0.msi](https://dev.mysql.com/get/Downloads/MySQLInstaller/mysql-installer-web-community-8.0.36.0.msi)

本文使用的Visual Studio版本是VS2022，MySQL版本为：8.0.36，对应的下载地址为：[mysql-installer-web-community-8.0.36.0.msi](https://dev.mysql.com/get/Downloads/MySQLInstaller/mysql-installer-web-community-8.0.36.0.msi)，并采用C# .Net WinForm窗体程序作为演示示例，我们展示如何使用Mysql.Data和Dapper连接MySql数据库，并查询MySql数据库中对应的people表，然后在窗体程序中输入字段LastName来查询对应的数据，鼠标按下`search`按钮，在ListBox中展示从MySQL数据库中的查询结果；另外我们在下方的三个输入框中分别输入用户的FirstName、LastName、EmailAddress字段，然后鼠标点击`insert`按钮，往数据库表中插入一条记录。最终的程序界面如下图所示：
![MySQL数据库访问窗体示例程序](https://img-blog.csdnimg.cn/direct/32f08df05d464a2099ca40ec1be9f7a8.png)
(1)、根据LastName查询记录
我们首先在输入框中输入LastName如蒋（英文中LastName代表中文中的姓，FirstName代表中文中的名），然后鼠标点击【Seach】按钮，查询的结果展示在下方中的ListBox中，如下图所示：
![根据LastName查询数据](https://img-blog.csdnimg.cn/direct/963bea41bb5b4cbcb3b0db79fa16541e.png)

(2)、往数据库people表中插入一条记录
我们首先在下面的`FirstName`、`LastName`、`EmailAddress`三个文本框中输入对应的数据，然后鼠标点击`insert`按钮，即可插入一条记录。
注意：由于Id是主键自增的，所以不用管。
![插入一条记录](https://img-blog.csdnimg.cn/direct/9541fbafbc034598a8797f9cc9d07907.png)

执行插入记录后，原来输入的`FistName`、`LastName`、`EmailAddress`记录会被清空，如下图所示：
![执行插入记录后，原来的输入记录会被清空](https://img-blog.csdnimg.cn/direct/a867dcb3cfa646579e698d082b239b88.png)
接下来我们输入在最上方根据刚刚输入的`LastName`：蒋，看`FirstName`为青青，`LastName`为蒋，`EmailAddress`为jiangqingqing@china.com的那条记录是否入库，如下图所示：
![检查刚刚插入的数据是否入库](https://img-blog.csdnimg.cn/direct/2dff10d952d146129e75db7c45e4cb5e.png)


## 二、C#窗体程序源代码下载
完整的C#窗体程序代码我已经上传到github上面了：
![Github源代码](https://img-blog.csdnimg.cn/direct/8702aeb9c23c453b9a2b94bd91badd32.png)

```github
git clone https://github.com/ccf19881030/WindowsFormsMySqlDbApp.git
```
或者直接下载[https://github.com/ccf19881030/WindowsFormsMySqlDbApp/archive/refs/heads/main.zip](https://github.com/ccf19881030/WindowsFormsMySqlDbApp/archive/refs/heads/main.zip)源代码即可，
![下载源代码描述](https://img-blog.csdnimg.cn/direct/5be4e0b73e42432cb242749f3abbc0b9.png)

# 三、创建C# MySQL数据库窗体示例程序
## 1、创建一个基于C# .Net的WinForm窗体程序
基于VS2022，创建一个WinForm .Net窗体程序，如下图所示：
![WinForm .Net窗体程序](https://img-blog.csdnimg.cn/direct/8875a7ac55ba420899458005b40d6d47.png)

最终的程序代码结构如下图所示：
![最终的程序代码结构](https://img-blog.csdnimg.cn/direct/6e68de2e5ac64a379501868412632b4e.png)


## 2、通过NuGet包管理器安装Mysql.Data和Dapper库
创建项目名称为`WindowsFormsMySqlDbApp`的C#窗体程序之后，通过项目中的引用-》管理 NuGet 程序包(N)-》浏览，分别输入MySql.Data和Dapper，然后点击安装：
![MySql.Data库](https://img-blog.csdnimg.cn/direct/40b8236f20f24f3db5ef352f461eba27.png)
![Dapper](https://img-blog.csdnimg.cn/direct/7b4bb9a1c1eb42b187b6df0fe02d406b.png)

![安装了MySql.Data和Dapper库](https://img-blog.csdnimg.cn/direct/5796cabb559742f584f55673d0153b7d.png)

## 3、设计界面UI
WinForm界面如下图所示：
![WinForm窗体程序](https://img-blog.csdnimg.cn/direct/ea8cc4291d4246b98b81ab383bee8cd7.png)

WinForm界面和MFC一样很简单，只由`Label`、`TextBox`、`Button`、`ListBox`这四种控件组成。

## 4、安装MySQL数据库，并Navicat Premium 16或者MySQL命令行创建数据库ytdemo和people表
安装[mysql-installer-web-community-8.0.36.0.msi](https://dev.mysql.com/get/Downloads/MySQLInstaller/mysql-installer-web-community-8.0.36.0.msi)数据库安装包之后，我们`root`账号的初始密码设置为`123456`，然后使用Navicat Premium 16连接并登录本地MySQL数据库，然后先创建`ytdemo`数据库，然后在该数据库中创建`people`表，其字段结果如下图所示：
![people表结构](https://img-blog.csdnimg.cn/direct/6b82f7d516344f2989fc24351f608d85.png)
`people`表结构的脚本如下：
people.sql
```sql
/*
 Navicat Premium Data Transfer

 Source Server         : localhost_mysql_root
 Source Server Type    : MySQL
 Source Server Version : 80036
 Source Host           : localhost:3306
 Source Schema         : ytdemo

 Target Server Type    : MySQL
 Target Server Version : 80036
 File Encoding         : 65001

 Date: 09/03/2024 14:34:56
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for people
-- ----------------------------
DROP TABLE IF EXISTS `people`;
CREATE TABLE `people`  (
  `Id` int NOT NULL AUTO_INCREMENT,
  `FirstName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `LastName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `EmailAddress` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 33 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
```
然后往数据库表中插入一些测试数据，如下图所示：
![people表中的测试数据](https://img-blog.csdnimg.cn/direct/e7a40c03eb794f5ebb1e0eba367c4679.png)
`people`的测试数据如下：
```sql
-- ----------------------------
-- Records of people
-- ----------------------------
INSERT INTO `people` VALUES (1, 'Timothy', 'Corey', 'TimCorey@gmail.com');
INSERT INTO `people` VALUES (2, 'Jane', 'Simth', 'JSmith@apple.com');
INSERT INTO `people` VALUES (3, 'Sue', 'Storm', 'SueStorm@126.com');
INSERT INTO `people` VALUES (4, 'Bob', 'McClure', 'BobMClu@microsoft.com');
INSERT INTO `people` VALUES (5, 'Mary', 'Jones', 'maryJones@google.com');
INSERT INTO `people` VALUES (6, 'Ray', 'Stone', 'rayStone@163.com');
INSERT INTO `people` VALUES (7, '操', '曹', 'caocao@neusoft.com');
INSERT INTO `people` VALUES (8, '权', '孙', 'sunquan@huawei.com');
INSERT INTO `people` VALUES (9, '备', '刘', 'liubei@qq.com');
INSERT INTO `people` VALUES (10, '飞', '张', 'zhangfen@qq.com');
INSERT INTO `people` VALUES (11, '羽', '关', 'guanyu@qq.com');
INSERT INTO `people` VALUES (12, '亮', '诸葛', 'zhugeliang@qq.com');
INSERT INTO `people` VALUES (13, '郎', '王', 'wanglang@126.com');
INSERT INTO `people` VALUES (14, '肃', '鲁', 'lusu@163.com');
INSERT INTO `people` VALUES (15, '云', '赵', 'zhaoyun@qq.com');
INSERT INTO `people` VALUES (16, '超', '马', 'machao@qq.com');
INSERT INTO `people` VALUES (17, '纯', '马', 'machun@alibaba.com');
INSERT INTO `people` VALUES (18, '万翼', '马', 'mawanyi@qq.com');
INSERT INTO `people` VALUES (19, '禅', '刘', 'liushan@qq.com');
INSERT INTO `people` VALUES (20, '懿', '司马', 'simayi@neusoft.com');
INSERT INTO `people` VALUES (21, '昭', '司马', 'simazhao@neusoft.com');
INSERT INTO `people` VALUES (22, '炎', '司马', 'simayan@neusoft.com');
INSERT INTO `people` VALUES (23, '相如', '司马', 'simaxiangru@han.com');
INSERT INTO `people` VALUES (24, '德宗', '司马', 'simadezong@neusoft.com');
INSERT INTO `people` VALUES (25, '峰', '欧阳', 'ouyangfeng@qq.com');
INSERT INTO `people` VALUES (26, '克', '欧阳', 'ouyangke@qq.com');
INSERT INTO `people` VALUES (27, '超风', '梅', 'machaofeng@126.com');
INSERT INTO `people` VALUES (28, '志', '徐', 'xuzhi@gmail.com');
INSERT INTO `people` VALUES (29, '万宗', '毛', 'maowanzong@china.com');
INSERT INTO `people` VALUES (30, '人凤', '毛', 'maorenfeng@taiwan.com');
INSERT INTO `people` VALUES (31, '爱天', '毛', 'maaitian@china.com');
INSERT INTO `people` VALUES (32, '于铭', '毛', 'mayumin@china.com');
INSERT INTO `people` VALUES (33, '科', '孙', 'sunke@china.com');
INSERT INTO `people` VALUES (34, '中山', '孙', 'sunzhongshan@china.com');
INSERT INTO `people` VALUES (35, '世凯', '袁', 'yuanshikai@qing.com');
INSERT INTO `people` VALUES (36, '袁', '立', 'yuanli@gmail.com');
INSERT INTO `people` VALUES (37, '国西', '李', 'liguoxi@ybu.com');
INSERT INTO `people` VALUES (38, '二', '李', 'lier@dangdang.com');
INSERT INTO `people` VALUES (39, '丽丽', '叶', 'yeili@hongkong.com');
INSERT INTO `people` VALUES (40, '婷', '叶', 'yeting@qq.com');
INSERT INTO `people` VALUES (41, '耳父', '陈', 'chenerfu@china.com');
INSERT INTO `people` VALUES (42, '国富', '陈', 'chenguofu@taiwan.com');
INSERT INTO `people` VALUES (43, '立夫', '陈', 'chenlifu@taiwan.com');
INSERT INTO `people` VALUES (44, '诚', '陈', 'chenchen@taiwan.com');
INSERT INTO `people` VALUES (45, '崇禧', '白', 'baichongxi@taiwan.com');
INSERT INTO `people` VALUES (46, '果夫', '陈', 'chengefu@taiwan.com');
INSERT INTO `people` VALUES (47, '美龄', '宋', 'songmeiling@taiwan.com');
INSERT INTO `people` VALUES (48, '庆龄', '宋', 'songqinglin@china.com');
INSERT INTO `people` VALUES (49, '蔼龄', '宋', 'songailing@taiwan.com');
INSERT INTO `people` VALUES (50, '祥熙', '孔', 'kongxiangxi@gmail.com');
INSERT INTO `people` VALUES (51, '仕杰', '宋', 'songshijie@huawei.com');
INSERT INTO `people` VALUES (52, '天赐', '张', 'zhangtianci@huawei.com');
INSERT INTO `people` VALUES (53, '峰', '乔', 'qiaofeng@xiaomi.com');
INSERT INTO `people` VALUES (54, '誉', '段', 'duanyu@gmail.com');
INSERT INTO `people` VALUES (55, '竹', '虚', 'xuzhu@gmail.com');
INSERT INTO `people` VALUES (56, '容复', '慕', 'morongfu@gmail.com');
INSERT INTO `people` VALUES (57, '植', '曹', 'caozhi@neusoft.com');
INSERT INTO `people` VALUES (58, '丕', '曹', 'caopi@neusoft.com');
INSERT INTO `people` VALUES (59, '冲', '曹', 'caochong@neusoft.com');
INSERT INTO `people` VALUES (60, '爽', '曹', 'caoshuang@neusoft.com');
INSERT INTO `people` VALUES (61, '真', '曹', 'caozhen@neusoft.com');
INSERT INTO `people` VALUES (62, '睿', '曹', 'caorui@neusoft.com');
INSERT INTO `people` VALUES (63, '伟庭', '曹', 'caoweiting@neusoft.com');
INSERT INTO `people` VALUES (64, '值', '王', 'wangzhi@sony.com');
INSERT INTO `people` VALUES (65, '双双', '陈', 'chenshuangshuang@gmail.com');
INSERT INTO `people` VALUES (66, '介石', '蒋', 'jiangzhongzhen@taiwan.com');
INSERT INTO `people` VALUES (67, '经国', '蒋', 'jiangjingguo@taiwan.com');
INSERT INTO `people` VALUES (68, '纬国', '蒋', 'jiangweiguo@taiwan.com');
INSERT INTO `people` VALUES (69, '万安', '蒋', 'jiangwanan@taiwan.com');
INSERT INTO `people` VALUES (70, '方良', '蒋', 'jiangfangliang@taiwan.com');
INSERT INTO `people` VALUES (71, '英', '蒋', 'jiangying@china.com');
INSERT INTO `people` VALUES (72, '学森', '钱', 'qianxuesen@china.com');
INSERT INTO `people` VALUES (73, '雪', '林', 'linxue@gmail.com');
INSERT INTO `people` VALUES (74, '国栋', '林', 'linguodong@gmai.com');
INSERT INTO `people` VALUES (75, '万里', '蒋', 'jiangwanli@gmail.com');
INSERT INTO `people` VALUES (76, '勃', '周', 'zhoubo@han.com');
INSERT INTO `people` VALUES (77, '彬彬', '周', 'zhoubinbin@china.com');
INSERT INTO `people` VALUES (78, '德旺', '朱', 'zhudewang@china.com');
INSERT INTO `people` VALUES (79, '正田', '朱', 'zhuzhengtian@gmail.com');
INSERT INTO `people` VALUES (80, '元璋', '朱', 'zhuyuanzhang@ming.com');
INSERT INTO `people` VALUES (81, '允炆', '朱', 'zhuyunwen@ming,com');
INSERT INTO `people` VALUES (82, '标', '朱', 'zhubiao@ming.com');
INSERT INTO `people` VALUES (83, '棣', '朱', 'zhuli@ming.com');
INSERT INTO `people` VALUES (84, '高炽', '朱', 'zhugaochi@ming.com');
INSERT INTO `people` VALUES (85, '高煦', '朱', 'zhugaoxu@ming.com');
INSERT INTO `people` VALUES (86, '瞻基', '朱', 'zhuzhanji@ming.com');
INSERT INTO `people` VALUES (87, '厚照', '朱', 'zhuhouzhao@ming.com');
INSERT INTO `people` VALUES (88, '秀', '刘', 'liuxiu@han.com');
INSERT INTO `people` VALUES (89, '璋', '刘', 'liuzhang@han.com');
INSERT INTO `people` VALUES (90, '莉莉', '刘', 'liulili@han.com');
INSERT INTO `people` VALUES (91, '志', '刘', 'liuzhi@han.com');
INSERT INTO `people` VALUES (92, '屈氂', '刘', 'liuqumao@han.com');
INSERT INTO `people` VALUES (93, '梦', '刘', 'liumeng@han.com');
INSERT INTO `people` VALUES (94, '凤凤', '张', 'zhangfengfeng@126.com');
INSERT INTO `people` VALUES (95, '美丽', '刘', 'liumeili@126.com');
INSERT INTO `people` VALUES (96, '靖', '郭', 'guojing@163.com');
INSERT INTO `people` VALUES (97, '蓉', '黄', 'huangrong@163.com');
INSERT INTO `people` VALUES (98, '芙', '郭', 'guofu@163.com');
INSERT INTO `people` VALUES (99, '襄', '郭', 'guoxiang@163.com');
INSERT INTO `people` VALUES (100, '美美', '郭', 'guomeimei@163.com');
INSERT INTO `people` VALUES (101, '克', '欧阳', 'ouyangke@126.com');
INSERT INTO `people` VALUES (102, '康', '杨', 'yangkang@126.com');
INSERT INTO `people` VALUES (103, '佳伟', '沈', 'shenjiawei@126.com');
INSERT INTO `people` VALUES (104, '逍遥', '李', 'lixiaoyao@gmail.com');
INSERT INTO `people` VALUES (105, '正淳', '段', 'duanzhengchun@gmail.com');
INSERT INTO `people` VALUES (106, '星竹', '李', 'lixingzhu@gmail.com');
INSERT INTO `people` VALUES (107, '紫', '阿', 'azi@163.com');
INSERT INTO `people` VALUES (108, '朱', '阿', 'azhu@163.com');
INSERT INTO `people` VALUES (109, '延庆', '段', 'duanyanqing@gmail.com');
INSERT INTO `people` VALUES (110, '微微', '曹', 'caoweiwei@126.com');
INSERT INTO `people` VALUES (111, '乐天', '何', 'heletian@ybu.com');
INSERT INTO `people` VALUES (112, '晓婷', '何', 'hexiaoting@gmail.com');
```
## 5、创建Person实体对象
在C#窗体程序中创建一个`Person`实体类，对应数据库表中的`people`结构，具体代码如下图所示：
```C#
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsMySqlDbApp
{
    public class Person
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string EmailAddress { get; set; }
        public string FullInfo
        {
            get
            {
                return $" {FirstName} {LastName} ({EmailAddress})";
            }
        }

    }
}
```

## 6、MySQL连接字符串
我们的MySQL链接字符串为：`Server=127.0.0.1;Port=3306;database=ytdemo;user id=root;password=123456;`
如果在云环境中我们需要将Server对应的本地数据库IP地址`127.0.0.1`修改为对应的云服务器IP地址，`user id`对应用户名，`password`对应我们的用户密码。
为了方便，我们一般不要把MySQL数据库连接字符串硬编码在代码中写死，一般可以放在`App.Config`配置文件中，例如：
```config
<?xml version="1.0" encoding="utf-8" ?>
<configuration>
    <startup> 
        <supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.8" />
    </startup>
	<connectionStrings>
		<add name="SampleDB" connectionString="Server=127.0.0.1;Port=3306;database=ytdemo;user id=root;password=123456;" />
	</connectionStrings>
</configuration>
```

## 7、创建MySQL数据库字符串访问类以及查询people表数据的接口
对应的MySQL连接字符串访问类`Helper`如下：
```C#
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsMySqlDbApp
{
    public static class Helper
    {
        public static string ConnectVal(string name)
        {
            return ConfigurationManager.ConnectionStrings[name].ConnectionString;
        }
    }
}
```
另外，我们创建一个`MySQLDataAccess`类用于连接和访问MySQL数据库，具体的实现代码如下：
```C#
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Dapper;
using MySql.Data.MySqlClient;

namespace WindowsFormsMySqlDbApp
{
    public class MySQLDataAccess
    {
        //public static string connStr = "Server=127.0.0.1;Port=3306;database=ytdemo;user id=root;password=123456;"; 
        /// <summary>
        /// 根据lastName获取所有的人员信息列表
        /// </summary>
        /// <param name="lastName">姓</param>
        /// <returns></returns>
        public List<Person> GetPersonList(string lastName)
        {
            using (IDbConnection connection = new MySqlConnection(Helper.ConnectVal("SampleDB")))
            {
                //string searchSql = "select * from people where LastName=@LastName";
                //return connection.Query<Person>(searchSql, new { LastName = lastName }).ToList();

                var personList = connection.Query<Person>($"select * from people where LastName = '{lastName}'").ToList();

                return personList;
            }

        }
        /// <summary>
        /// 往数据库表people中插入一条记录
        /// </summary>
        /// <param name="firstName"></param>
        /// <param name="lastName"></param>
        /// <param name="emailAdress"></param>

        public void InsertPerson(string firstName, string lastName, string emailAddress)
        {
            using (IDbConnection connection = new MySqlConnection(Helper.ConnectVal("SampleDB")))
            {
                //string insertSql = $"INSERT INTO `people`(FirstName, LastName, emailAddress) VALUES ('{firstName}', '{lastName}', '{emailAdress}');";
                //connection.Execute(insertSql);

                Person newPerson = new Person { FirstName = firstName, LastName = lastName, EmailAddress = emailAddress };
                string insertSql = "INSERT INTO `people`(FirstName, LastName, emailAddress) VALUES (@FirstName, @LastName, @EmailAddress);";
                connection.Execute(insertSql, newPerson);
            }
        }
    }
}

```
## 8、在查询按钮实现函数中实现具体的查询逻辑
具体的界面和查询逻辑实现代码如下：
```C#
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsMySqlDbApp
{
    public partial class DashBoardForm : Form
    {
        List<Person> people = new List<Person>();   // 查询结果列表
        public DashBoardForm()
        {
            InitializeComponent();

            // 更新绑定内容
            UpdateBinding();
        }
        /// <summary>
        /// 刷新ListBox中的数据，将peopleFoundListBox和peopl列表数据进行绑定，并显示FullInfo字段内容
        /// </summary>

        public void UpdateBinding()
        {
            peopleFoundListBox.DataSource = people;
            peopleFoundListBox.DisplayMember = "FullInfo";
        }
        /// <summary>
        /// search按钮单击响应处理函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void searchButton_Click(object sender, EventArgs e)
        {
            // 创建MySQLDataAccess类对象
            MySQLDataAccess dataAccess = new MySQLDataAccess();
            // 根据UI窗体用户输入的LastName字段，调用dataAccess对象的GetPersonList接口从people表查询数据
            people = dataAccess.GetPersonList(lastNameTextBox.Text);

            // 更新绑定内容，将people查询结果展示在peopleFoundListBox中
            UpdateBinding();
        }

        /// <summary>
        /// insert按钮响应处理函数
        /// 功能：接收用户输入，往people数据表中插入记录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void insertDataButton_Click(object sender, EventArgs e)
        {
            MySQLDataAccess dataAccess = new MySQLDataAccess();
            // 插入一条数据记录到people表中
            dataAccess.InsertPerson(firstNameInsTextBox.Text, lastNameInsTextBox.Text, emailAddressInsTextBox.Text);

            // 插入数据之后将界面中的记录数据清空
            firstNameInsTextBox.Text = "";
            lastNameInsTextBox.Text = "";
            emailAddressInsTextBox.Text = "";
        }
    }
}

```

## 9、运行程序
代码完成之后，我们运行程序，结果下图所示：
![程序运行结果](https://img-blog.csdnimg.cn/direct/dd44e26f0cfd4299b3e7cfd06aee0fc0.png)
![插入记录](https://img-blog.csdnimg.cn/direct/a648c02b32ad4048b5b31f06bd290901.png)


# 四、参考资料
- [https://www.nuget.org/packages/MySql.Data/](https://www.nuget.org/packages/MySql.Data/)
- [https://www.nuget.org/packages/Dapper](https://www.nuget.org/packages/Dapper)
- [https://github.com/mysql-net/MySqlConnector](https://github.com/mysql-net/MySqlConnector)
- [https://github.com/DapperLib/Dapper](https://github.com/DapperLib/Dapper)
- [https://github.com/ccf19881030/WindowsFormsMySqlDbApp](https://github.com/ccf19881030/WindowsFormsMySqlDbApp)
