# Windows中使用MySql.Data库将C# 接到 MySQL
本文翻译自`CodeProject`上的一篇博文：[Connect C# to MySQL](https://www.codeproject.com/Articles/43438/Connect-C-to-MySQL)，作者是：[
Etienne Rached](https://www.codeproject.com/script/Membership/View.aspx?mid=5727371)。
由于文章是2009 年 11 月 18 日写的，到现在已经将近15年了，所以有些地方需要基于最新的.Net和C#版本进行修改，尤其是在`MySql.Data`库和.Net版本的使用和匹配上。

使用 MySQL Connector/Net 将 C# 连接到 MySQL，插入、更新、选择、删除示例，从 C# 或 .NET 应用程序备份和恢复 MySQL 数据库。
本文的目的是逐步展示如何使用 MySql Connect/NET 使用 C# 和 MySql 连接。我将在整篇文章中创建有关 DML（插入、更新、选择、删除）的简单示例，以展示如何使用 C# 查询数据库，最后我将向您展示如何备份数据库并将其保存在 .sql 中我们的应用程序中的文件，以及如何将其恢复。
- [Download demo - 127.6 KB](https://www.codeproject.com/KB/database/ConnectCsharpToMysql/connectcsharptomysql_demo.zip)
- [Download source - 15.43 KB](https://www.codeproject.com/KB/database/ConnectCsharpToMysql/connectcsharptomysql_source.zip)

## 入门
### 下载Connector/Net
首先确保您已经从[MySQL官方网站](http://dev.mysql.com/downloads/connector/net/6.1.html)下载并安装了MySQL Connector/NET。在本文中，我将使用 Connector/NET 版本 6.1。
### 创建数据库
现在让我们创建数据库以及稍后将从应用程序中查询的表。

从命令行，我们首先**创建数据库**：
```SQL
create database ConnectCsharpToMysql;
```
然后我们在创建表之前选择**要使用的数据库**：
```SQL
use ConnectCsharpToMysql;
```
我们创建将从应用程序中查询的表：
```SQL
create table tableInfo
(
id INT NOT NULL AUTO_INCREMENT,
name VARCHAR(30),
age INT,
PRIMARY KEY(id)
);
```
## 使用代码
添加引用并从项目创建 MySQL 连接器 DLL
在开始编写代码之前，我们需要在项目中添加 `mysql` 引用。为此，我们右键单击项目名称，然后选择“添加引用”：
![添加引用](https://img-blog.csdnimg.cn/direct/7d3f67cbabfc45a9ad04e25753817554.png)
然后我们从列表中选择 `MySql.Data`：
![添加MySql.Data库](https://img-blog.csdnimg.cn/direct/dd5d8f0f20494bef9826dd603c014c2e.png)
为了在未安装连接器的其他计算机上使用该应用程序，我们必须从引用创建一个 DLL。为此，我们右键单击项目中的引用名称，然后在其属性中将 copy local 设置为 true：
![点击属性右键菜单](https://img-blog.csdnimg.cn/direct/b450ee76f8514fc0a1cefde1fa53d256.png)
![将Copy Local属性设置为True](https://img-blog.csdnimg.cn/direct/68469d77cd2f431c9b8bd74ff0da4263.png)
**注意**：由于自从2009年离现在很久远，我们目前在VS2022等IDE中添加`MySql.Data`库很简单，只需要通过`NuGet包管理器`搜索`MySql.Data`包安装即可，也可以借助`NuGet命令行`安装`MySql.Data`包。
### 创建类
创建一个新类来连接数据库并将实际代码与访问数据库的代码分开始终是一个更好的主意。这将有助于保持我们的代码整洁、更易于阅读且更高效。

我们首先添加 MySql Connector 库：
```C#
//Add MySql Library
using MySql.Data.MySqlClient;
```
然后声明并初始化我们将使用的变量：

- `connection`：将用于打开到数据库的连接。
- `server`：表示我们的服务器托管在哪里，在我们的例子中，它是 localhost。
- `database`：是我们将使用的数据库的名称，在我们的例子中，它是我们之前创建的数据库，即`connectcsharptomysql`。
- `uid`：是我们的 MySQL 用户名。
- `password`：是我们的MySQL密码。
- `connectionString`：包含连接数据库的连接字符串，并将被赋值给连接变量。

我们的类将如下所示：
（本文稍后将填充空方法。）
```C#
class DBConnect
{
    private MySqlConnection connection;
    private string server;
    private string database;
    private string uid;
    private string password;

    //Constructor
    public DBConnect()
    {
        Initialize();
    }

    //Initialize values
    private void Initialize()
    {
        server = "localhost";
        database = "connectcsharptomysql";
        uid = "username";
        password = "password";
        string connectionString;
        connectionString = "SERVER=" + server + ";" + "DATABASE=" + 
		database + ";" + "UID=" + uid + ";" + "PASSWORD=" + password + ";";

        connection = new MySqlConnection(connectionString);
    }

    //open connection to database
    private bool OpenConnection()
    {
    }

    //Close connection
    private bool CloseConnection()
    {
    }

    //Insert statement
    public void Insert()
    {
    }

    //Update statement
    public void Update()
    {
    }

    //Delete statement
    public void Delete()
    {
    }

    //Select statement
    public List <string> [] Select()
    {
    }

    //Count statement
    public int Count()
    {
    }

    //Backup
    public void Backup()
    {
    }

    //Restore
    public void Restore()
    {
    }
}
```

### 打开和关闭连接
我们应该始终在查询表之前打开一个连接，并在完成后立即关闭它，以释放资源并表明不再需要该连接。
打开和关闭与数据库的连接非常简单，但是，最好在打开或关闭连接之前使用异常处理来捕获错误并进行处理。
```C#
//open connection to database
private bool OpenConnection()
{
    try
    {
        connection.Open();
        return true;
    }
    catch (MySqlException ex)
    {
        //When handling errors, you can your application's response based 
        //on the error number.
        //The two most common error numbers when connecting are as follows:
        //0: Cannot connect to server.
        //1045: Invalid user name and/or password.
        switch (ex.Number)
        {
            case 0:
                MessageBox.Show("Cannot connect to server.  Contact administrator");
                break;

            case 1045:
                MessageBox.Show("Invalid username/password, please try again");
                break;
        }
        return false;
    }
}

//Close connection
private bool CloseConnection()
{
    try
    {
        connection.Close();
        return true;
    }
    catch (MySqlException ex)
    {
        MessageBox.Show(ex.Message);
        return false;
    }
}
```

### 使用 DML（插入、更新、选择、删除）
通常，`Insert`、`update`和`delete`用于写入或更改数据库中的数据，而`Select`用于读取数据。
因此，我们有不同类型的方法来执行这些查询。
方法如下：

- `ExecuteNonQuery`：用于执行不会返回任何数据的命令，例如`Insert`, `update` 或 `delete`。
- `ExecuteReader`：用于执行将返回0个或更多记录的命令，例如`Select`。
- `ExecuteScalar`：用于执行仅返回 1 个值的命令，例如 `Select Count(*)`。
我将从Insert`, `update` 和 `delete`开始，这是最简单的。成功执行命令的流程如下：
- 1. 打开与数据库的连接。
- 2. 创建 MySQL 命令。
- 3. 为命令分配连接和查询。这可以使用构造函数或使用 `MySqlCommand` 类中的 `Connection` 和 `CommandText` 方法来完成。
- 4. 执行命令。
- 5. 关闭连接。
```C#
//Insert statement
public void Insert()
{
    string query = "INSERT INTO tableinfo (name, age) VALUES('John Smith', '33')";

    //open connection
    if (this.OpenConnection() == true)
    {
        //create command and assign the query and connection from the constructor
        MySqlCommand cmd = new MySqlCommand(query, connection);
        
        //Execute command
        cmd.ExecuteNonQuery();

        //close connection
        this.CloseConnection();
    }
}

//Update statement
public void Update()
{
    string query = "UPDATE tableinfo SET name='Joe', age='22' WHERE name='John Smith'";

    //Open connection
    if (this.OpenConnection() == true)
    {
        //create mysql command
        MySqlCommand cmd = new MySqlCommand();
        //Assign the query using CommandText
        cmd.CommandText = query;
        //Assign the connection using Connection
        cmd.Connection = connection;

        //Execute query
        cmd.ExecuteNonQuery();

        //close connection
        this.CloseConnection();
    }
}

//Delete statement
public void Delete()
{
    string query = "DELETE FROM tableinfo WHERE name='John Smith'";

    if (this.OpenConnection() == true)
    {
        MySqlCommand cmd = new MySqlCommand(query, connection);
        cmd.ExecuteNonQuery();
        this.CloseConnection();
    }
}
```

为了执行 `Select` 语句，我们添加了几个步骤，并使用 `ExecuteReader 方法`，该方法将返回 `dataReader` 对象来读取和存储数据或记录。

- 1. 打开与数据库的连接。
- 2. 创建 MySQL 命令。
- 3. 为命令分配连接和查询。这可以使用构造函数或使用 `MySqlCommand` 类中的 `Connection` 和 `CommandText` 方法来完成。
- 4. 创建一个 `MySqlDataReader` 对象来读取选定的记录/数据。
- 5. 执行命令。
- 6. 读取记录并显示它们或将它们存储在列表中。
- 7. 关闭数据读取器。
- 8. 关闭连接。

```C#
//Select statement
public List< string >[] Select()
{
    string query = "SELECT * FROM tableinfo";

    //Create a list to store the result
    List< string >[] list = new List< string >[3];
    list[0] = new List< string >();
    list[1] = new List< string >();
    list[2] = new List< string >();

    //Open connection
    if (this.OpenConnection() == true)
    {
        //Create Command
        MySqlCommand cmd = new MySqlCommand(query, connection);
        //Create a data reader and Execute the command
        MySqlDataReader dataReader = cmd.ExecuteReader();
        
        //Read the data and store them in the list
        while (dataReader.Read())
        {
            list[0].Add(dataReader["id"] + "");
            list[1].Add(dataReader["name"] + "");
            list[2].Add(dataReader["age"] + "");
        }

        //close Data Reader
        dataReader.Close();

        //close Connection
        this.CloseConnection();

        //return list to be displayed
        return list;
    }
    else
    {
        return list;
    }
}
```

有时，一个命令总是只返回一个值，例如如果我们想要计算记录数，我们一直在使用 `Select Count(*) from tableinfo;`，在这种情况下，我们将不得不使用 `ExecuteScalar` 方法将返回一个值。

成功运行并`ExecuteScalar`的流程如下：

- 1. 打开与数据库的连接。
- 2. 创建 MySQL 命令。
- 3. 为命令分配连接和查询。这可以使用构造函数或使用 `MySqlCommand` 类中的 `Connection` 和 `CommandText` 方法来完成。
- 4. 执行命令。
- 5. 如有必要，解析结果。
- 6. 关闭连接。

```C#
//Count statement
public int Count()
{
    string query = "SELECT Count(*) FROM tableinfo";
    int Count = -1;

    //Open Connection
    if (this.OpenConnection() == true)
    {
        //Create Mysql Command
        MySqlCommand cmd = new MySqlCommand(query, connection);

        //ExecuteScalar will return one value
        Count = int.Parse(cmd.ExecuteScalar()+"");
        
        //close Connection
        this.CloseConnection();

        return Count;
    }
    else
    {
        return Count;
    }
}
```

### 备份和恢复数据库
在向您展示如何从我们的应用程序备份数据库之前，我将解释一些有关进程、命令、参数以及输入和输出的信息。
通常，要从命令行备份 MySQL 数据库，我们编写以下内容：
```shell
mysqldump -u username -p password -h localhost ConnectCsharpToMysql > "C:\Backup.sql"
```
为了恢复它，我们写：
```shell
mysql -u username -p password -h localhost ConnectCsharpToMysql < "C:\Backup.sql"
```
下面的命令可以这样划分：

- `mysql` 和 `mysqldump` 是文件名或可执行文件。
- -u 用户名 -p 密码 -h localhost 是`参数`。
- > “C:\Backup.sql”是输出的定向位置。
- <“C:\Backup.sql”是输入的定向位置。
现在我们知道了命令是如何划分的，我们可以开始在我们的应用程序中实现它。

在 C# 和 .NET 应用程序中，启动进程很容易。首先我们添加库：
```C#
using System.Diagnostics;
```
然后我们启动一个应用程序，例如 Internet Explorer：
```C#
Process.Start("IExplore.exe");
```
`ProcessStartInfo` 与 `Process` 结合使用，在进程启动之前对其进行设置。
例如，要使用参数启动 Internet Explorer，我们编写以下内容：
```C#
ProcessStartInfo psi = new ProcessStartInfo();
psi.FileName = "IExplore.exe";
psi.Arguments = "www.codeproject.com";
Process.Start(psi);
```
要将输出写入文件或读取输入，我们可以使用 `ProcessStartInfo` 组件中的 `RedirectStandardInput` 和 `RedirectStandardOutput` 属性来使进程从文件或其他设备获取输入或将输出返回到文件或其他设备。如果我们在 `Process` 组件上使用 `StandardInput` 或 `StandardOutput` 属性，则必须首先在 `ProcessStartInfo` 属性上设置相应的值。否则，当我们读取或写入流时，系统会抛出异常。

现在回到我们的应用程序，要备份数据库，我们必须将 `RedirectStandardOutput` 设置为 `true`，并将进程的输出读取到`字符串`中并将其保存到文件中。
```C#
//Backup
public void Backup()
{
    try
    {
        DateTime Time = DateTime.Now;
        int year = Time.Year;
        int month = Time.Month;
        int day = Time.Day;
        int hour = Time.Hour;
        int minute = Time.Minute;
        int second = Time.Second;
        int millisecond = Time.Millisecond;

        //Save file to C:\ with the current date as a filename
        string path;
        path = "C:\\MySqlBackup" + year + "-" + month + "-" + day + 
	"-" + hour + "-" + minute + "-" + second + "-" + millisecond + ".sql";
        StreamWriter file = new StreamWriter(path);

        
        ProcessStartInfo psi = new ProcessStartInfo();
        psi.FileName = "mysqldump";
        psi.RedirectStandardInput = false;
        psi.RedirectStandardOutput = true;
        psi.Arguments = string.Format(@"-u{0} -p{1} -h{2} {3}", 
			uid, password, server, database);
        psi.UseShellExecute = false;

        Process process = Process.Start(psi);

        string output;
        output = process.StandardOutput.ReadToEnd();
        file.WriteLine(output);
        process.WaitForExit();
        file.Close();
        process.Close();
    }
    catch (IOException ex)
    {
        MessageBox.Show("Error , unable to backup!");
    }
}
```
为了恢复数据库，我们读取 .sql 文件并将其存储在字符串中，然后将 `RedirectStandardInput` 属性设置为 `true`，并将`字符串`的输入写入进程。
```C#
//Restore
public void Restore()
{
    try
    {
        //Read file from C:\
        string path;
        path = "C:\\MySqlBackup.sql";
        StreamReader file = new StreamReader(path);
        string input = file.ReadToEnd();
        file.Close();

        ProcessStartInfo psi = new ProcessStartInfo();
        psi.FileName = "mysql";
        psi.RedirectStandardInput = true;
        psi.RedirectStandardOutput = false;
        psi.Arguments = string.Format(@"-u{0} -p{1} -h{2} {3}", 
			uid, password, server, database);
        psi.UseShellExecute = false;

        
        Process process = Process.Start(psi);
        process.StandardInput.WriteLine(input);
        process.StandardInput.Close();
        process.WaitForExit();
        process.Close();
    }
    catch (IOException ex)
    {
        MessageBox.Show("Error , unable to Restore!");
    }
}
```

## 总结
在本文中，我演示了如何使用`insert`, `update`, `delete` 和 `select`语句的简单示例将 C# 连接到 MySQL 并查询表。
另外，由于它在 Internet 上并未广泛使用，因此我决定演示如何从 C# 应用程序备份和恢复 MySQL 数据库。

### 历史
2009 年 11 月 17 日：初始帖子

### License
本文以及任何相关的源代码和文件均根据代码项目开放许可证 (CPOL) 获得许可

### 撰写者
[艾蒂安·拉希德](https://www.codeproject.com/script/Membership/View.aspx?mid=5727371)
软件开发人员
加拿大 加拿大
该成员尚未提供传记。假设它很有趣且多种多样，并且可能与编程有关。

# 在VS2022中运行本文的源代码
我们首选从下面这两个地方分别下示例和源代码，
- [Download demo - 127.6 KB](https://www.codeproject.com/KB/database/ConnectCsharpToMysql/connectcsharptomysql_demo.zip)
- [Download source - 15.43 KB](https://www.codeproject.com/KB/database/ConnectCsharpToMysql/connectcsharptomysql_source.zip)
然后确保我们Windows系统中安装了VS2022和MySQL等软件，
然后使用VS2022打开源代码`connectcsharptomysql_source`，下载后的源代码目录结构如下图所示：
![connectcsharptomysql_source源代码目录结构](https://img-blog.csdnimg.cn/direct/c4d524650c9344058639dec0fbf6e6dd.png)
我们使用VS2022打开`ConnectCsharpToMysql.sln`工程文件，并对项目进行升级，然后通过VS2022中的`NuGet包管理器`安装[MySql.Data](https://www.nuget.org/packages/MySql.Data/)包，截止目前最新的`MySql.Data`库最新版本为：`8.3.0`，如下图所示：
![MySql.Data](https://img-blog.csdnimg.cn/direct/bd26bf74f7ab41f39b1dac46272c51f4.png)
![MySql.Data包](https://img-blog.csdnimg.cn/direct/69ce0aa4e90e4cb9a7e4b87d87e3e12d.png)
然后为了简单这个程序将MySQL数据库的账号和密码硬编码到了代码中，我们只需要将`DBConnect.cs`文件中·Initialize()`函数中对应的用户名和密码改成自己本地的MySQL数据库对应的即可，如下图所示：
![修改数据库的用户名和密码](https://img-blog.csdnimg.cn/direct/0c618e39da3442e9a1f709198b777b14.png)

## 运行程序
程序运行结果如下图所示：
![程序运行结果](https://img-blog.csdnimg.cn/direct/3b0bb963bce543eca6b4506c28fd1539.png)
