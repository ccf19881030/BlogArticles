## [在Qt中使用SQLite数据库](https://www.cnblogs.com/xia-weiwen/p/6806709.html)
```cpp
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase database;
    // 建立数据库
    // 检查连接、添加数据库驱动、设置数据库名称、数据库登录用户名、密码。
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("ccf");
        database.setPassword("123456");
    }

    // 打开数据库
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else {
        qDebug() << "connected database successful!";
    }

    // 操作数据库
    QSqlQuery sql_query;
    // 例1：创建表格
    //创建一个名为student的表格，表格包含三列，第一列是id，第二列是名字，第三列是年龄。
    QString create_table_sql = "create table student (id int primary key, name varchar(30), age int)";
    sql_query.prepare(create_table_sql);
    if (!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table student." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table student created successful!";
    }

    // 查询最大id
    QString select_max_id_sql = "SELECT max(id) FROM student";
    int max_id = 0;
    sql_query.prepare(select_max_id_sql);
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else {
        while (sql_query.next())
        {
            max_id = sql_query.value(0).toInt();
            qDebug() << QString("max id:%1").arg(max_id);
        }
    }
    // 例2： 插入数据
    QString insert_sql = "insert into student values(?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(max_id + 1);
    //sql_query.addBindValue(1);
    sql_query.addBindValue("Wang");
    sql_query.addBindValue(25);
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else {
        qDebug() << "insertd Wang!";
    }

    if (!sql_query.exec("INSERT INTO student VALUES(2, \"Li\", 23)"))
    {
        qDebug() << sql_query.lastError();
    }
    else {
        qDebug() << "insert Li!";
    }

    // 例4：查询部分数据
    QString select_sql = "SELECT id, name FROM student";
    if (!sql_query.exec(select_sql))
    {
        qDebug() << sql_query.lastError();
    }
    else {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            qDebug() << QString("id:%1  name:%2").arg(id).arg(name);
        }
    }

    // 例3：更新数据（修改数据）
    QString update_sql = "UPDATE student set name = :name WHERE id = :id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":name", "Qt");
    sql_query.bindValue(":id", 1);
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else {
        qDebug() << "updated!";
    }

    // 例5：删除与清空
    // 删除一条数据
    QString delete_sql = "DELETE FROM student WHERE id = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(1);
    if (!sql_query.exec())
    {
       qDebug() << sql_query.lastError();
    }
    else {
        qDebug() << "deleted!";
    }
    // （2）清空表格（删除所有）
    QString clear_sql = "delete from student";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    // 查询全部数据
    QString select_all_sql = "select * from student";
    sql_query.prepare(select_all_sql);
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            int age = sql_query.value(2).toInt();
            qDebug() << QString("id:%1  name:%2 age:%3").arg(id).arg(name).arg(age);
        }
    }
    // 关闭数据库
    database.close();

    return a.exec();
}
```

## [在CodeBlocks中编译带加密的sqlite3，并利用CppSQLite3操纵sqlite3](https://www.iteye.com/blog/emonkey-1613282)

## [VC2010中编译Sqlite3为静态库并带加密功能的方法](https://bbs.csdn.net/topics/380018685)

## [ 带有加密功能的 SQLite Qt 插件](https://www.devbean.net/2012/07/qt-sqlite-plugin-with-encryption/)
