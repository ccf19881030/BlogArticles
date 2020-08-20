## [CppSQLite - C++ Wrapper for SQLite](https://www.codeproject.com/Articles/6343/CppSQLite-C-Wrapper-for-SQLite)
CppSQLite - C++ Wrapper for SQLite
A C++ wrapper around the SQLite embedded database library.
- [Download CppSQLite demo projects, source and sqlite.dll for SQLite 2.8.15 - 156 KB](https://www.codeproject.com/KB/database/CppSQLite/CppSQLite_1_4_demo_and_src.zip)
- [Download CppSQLite 3 demo projects, source and sqlite3.dll for SQLite 3.0.8 - 171 KB](https://www.codeproject.com/KB/database/CppSQLite/CppSQLite_3_1_demo_and_src.zip)
- [Download CppSQLite 3.2 demo projects, source and sqlite3.dll for SQLite 3.4.0 - 252 KB](https://www.codeproject.com/KB/database/CppSQLite/CppSQLite3_2.zip)

### Introduction
This article describes CppSQLite, a very thin C++ wrapper around the public domain SQLite database library.

A description of how to link applications with SQLite is provided, then an example program using CppSQLite is presented, and finally the CppSQLite classes are documented.

To set the scene, here is a quote from the SQLite author...

SQLite is a C library that implements an embeddable SQL database engine. Programs that link with the SQLite library can have SQL database access without running a separate RDBMS process. The distribution comes with a standalone command-line access program (SQLite) that can be used to administer a SQLite database and which serves as an example of how to use the SQLite library.

SQLite is not a client library used to connect to a big database server. SQLite is the server. The SQLite library reads and writes directly to and from the database files on disk.

### Background
I am always on the lookout for simple yet powerful software development tools and ideas, and SQLite definitely falls into this category. In fact, the "Lite" name is a bit misleading, as it implements a large subset of the SQL standard, including transactions, and when projects such as PHP start to bundle it as standard instead of MySQL, you have to take a look.

I thought it would be fun to write a thin wrapper around the C interface to make it C++ friendly. There are already a number of C++ wrappers listed on the SQLite website, but one is commercial, another seemed a bit complex, and another is specific to the wxWidgets framework. After all, the author of SQLite looks to have gone to pains to keep things simple, so I thought a C++ wrapper for it should keep things simple as well.

### Working With SQLite
SQLite is provided in 2 packages on the Windows platform, as a compiled DLL, and also in source form. Even if you only wish to use the DLL, you will still need to get the source code, as this contains the required header file.

If desired, the SQLite source could be compiled into a library (.lib) file for statically linking with your application, but this is not covered in this article. Compilation instructions can be found on the SQLite web site.

Linking dynamically still requires that a .lib file is built for linking with your application. This can be done using Microsoft's LIB command. On my system, this is located at D:\Program Files\Microsoft Visual Studio\VC98\Bin\lib.exe.

Unzip sqlite.zip which contains sqlite.dll and sqlite.def, and execute the following command to produce the lib file.
```shell
c:\>lib /def:sqlite.def
```
sqlite.h needs to be visible to your application at compile time, as does sqlite.lib.

sqlite.dll needs to be available to your application at runtime.

### CppSQLite Demo Code
The following code demonstrates how to use the main features of SQLite via CppSQLite, with comments inline.
```cpp

```#include "CppSQLite.h"
#include <ctime>
#include <iostream>

using namespace std;

const char* gszFile = "C:\\test.db";

int main(int argc, char** argv)
{
    try
    {
        int i, fld;
        time_t tmStart, tmEnd;
        CppSQLiteDB db;

        cout << "SQLite Version: " << db.SQLiteVersion() << endl;

        remove(gszFile);
        db.open(gszFile);

        cout << endl << "Creating emp table" << endl;
        db.execDML("create table emp(empno int, empname char(20));");
        ///////////////////////////////////////////////////////////////
        // Execute some DML, and print number of rows affected by each one
        ///////////////////////////////////////////////////////////////
        cout << endl << "DML tests" << endl;
        int nRows = db.execDML("insert into emp values (7, 'David Beckham');");
        cout << nRows << " rows inserted" << endl;

        nRows = db.execDML(
         "update emp set empname = 'Christiano Ronaldo' where empno = 7;");
        cout << nRows << " rows updated" << endl;

        nRows = db.execDML("delete from emp where empno = 7;");
        cout << nRows << " rows deleted" << endl;

        /////////////////////////////////////////////////////////////////
        // Transaction Demo
        // The transaction could just as easily have been rolled back
        /////////////////////////////////////////////////////////////////
        int nRowsToCreate(50000);
        cout << endl << "Transaction test, creating " << nRowsToCreate;
        cout << " rows please wait..." << endl;
        tmStart = time(0);
        db.execDML("begin transaction;");

        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[128];
            sprintf(buf, "insert into emp values (%d, 'Empname%06d');", i, i);
            db.execDML(buf);
        }

        db.execDML("commit transaction;");
        tmEnd = time(0);

        ////////////////////////////////////////////////////////////////
        // Demonstrate CppSQLiteDB::execScalar()
        ////////////////////////////////////////////////////////////////
        cout << db.execScalar("select count(*) from emp;") 
               << " rows in emp table in ";
        cout << tmEnd-tmStart << " seconds (that was fast!)" << endl;

        ////////////////////////////////////////////////////////////////
        // Re-create emp table with auto-increment field
        ////////////////////////////////////////////////////////////////
        cout << endl << "Auto increment test" << endl;
        db.execDML("drop table emp;");
        db.execDML(
         "create table emp(empno integer primary key, empname char(20));");
        cout << nRows << " rows deleted" << endl;

        for (i = 0; i < 5; i++)
        {
            char buf[128];
            sprintf(buf, 
       "insert into emp (empname) values ('Empname%06d');", i+1);
            db.execDML(buf);
            cout << " primary key: " << db.lastRowId() << endl;
        }

     ///////////////////////////////////////////////////////////////////
     // Query data and also show results of inserts into auto-increment field
     //////////////////////////////////////////////////////////////////
        cout << endl << "Select statement test" << endl;
        CppSQLiteQuery q = db.execQuery("select * from emp order by 1;");

        for (fld = 0; fld < q.numFields(); fld++)
        {
            cout << q.fieldName(fld) << "(" << q.fieldType(fld) << ")|";
        }
        cout << endl;

        while (!q.eof())
        {
            cout << q.fieldValue(0) << "|";
            cout << q.fieldValue(1) << "|" << endl;
            q.nextRow();
        }

        ///////////////////////////////////////////////////////////////
        // SQLite's printf() functionality. Handles embedded quotes and NULLs
        ////////////////////////////////////////////////////////////////
        cout << endl << "SQLite sprintf test" << endl;
        CppSQLiteBuffer bufSQL;
        bufSQL.format("insert into emp (empname) values (%Q);", "He's bad");
        cout << (const char*)bufSQL << endl;
        db.execDML(bufSQL);

        bufSQL.format("insert into emp (empname) values (%Q);", NULL);
        cout << (const char*)bufSQL << endl;
        db.execDML(bufSQL);

        ////////////////////////////////////////////////////////////////////
        // Fetch table at once, and also show how to 
        // use CppSQLiteTable::setRow() method
        //////////////////////////////////////////////////////////////////
        cout << endl << "getTable() test" << endl;
        CppSQLiteTable t = db.getTable("select * from emp order by 1;");

        for (fld = 0; fld < t.numFields(); fld++)
        {
            cout << t.fieldName(fld) << "|";
        }
        cout << endl;
        for (int row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            for (int fld = 0; fld < t.numFields(); fld++)
            {
                if (!t.fieldIsNull(fld))
                    cout << t.fieldValue(fld) << "|";
                else
                    cout << "NULL" << "|";
            }
            cout << endl;
        }

        ////////////////////////////////////////////////////////////////////
        // Test CppSQLiteBinary by storing/retrieving some binary data, checking
        // it afterwards to make sure it is the same
        //////////////////////////////////////////////////////////////////
        cout << endl << "Binary data test" << endl;
        db.execDML("create table bindata(desc char(10), data blob);");
        
        unsigned char bin[256];
        CppSQLiteBinary blob;

        for (i = 0; i < sizeof bin; i++)
        {
            bin[i] = i;
        }

        blob.setBinary(bin, sizeof bin);

        bufSQL.format("insert into bindata values ('testing', %Q);", 
                      blob.getEncoded());
        db.execDML(bufSQL);
        cout << "Stored binary Length: " << sizeof bin << endl;

        q = db.execQuery("select data from bindata where desc = 'testing';");

        if (!q.eof())
        {
            blob.setEncoded((unsigned char*)q.fieldValue("data"));
            cout << "Retrieved binary Length: " 
       << blob.getBinaryLength() << endl;
        }

        const unsigned char* pbin = blob.getBinary();
        for (i = 0; i < sizeof bin; i++)
        {
            if (pbin[i] != i)
            {
                cout << "Problem: i: ," << i << " bin[i]: " 
             << pbin[i] << endl;
            }
        }

        /////////////////////////////////////////////////////////
        // Pre-compiled Statements Demo
        /////////////////////////////////////////////////////////////
        cout << endl << "Transaction test, creating " << nRowsToCreate;
        cout << " rows please wait..." << endl;
        db.execDML("drop table emp;");
        db.execDML("create table emp(empno int, empname char(20));");
        tmStart = time(0);
        db.execDML("begin transaction;");

        CppSQLiteStatement stmt = db.compileStatement(
            "insert into emp values (?, ?);");
        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[16];
            sprintf(buf, "EmpName%06d", i);
            stmt.bind(1, i);
            stmt.bind(2, buf);
            stmt.execDML();
            stmt.reset();
        }

        db.execDML("commit transaction;");
        tmEnd = time(0);

        cout << db.execScalar("select count(*) from emp;") 
           << " rows in emp table in ";
        cout << tmEnd-tmStart << " seconds (that was even faster!)" << endl;
        cout << endl << "End of tests" << endl;
    }
    catch (CppSQLiteException& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }

    ////////////////////////////////////////////////////////////////
    // Loop until user enters q or Q
    ///////////////////////////////////////////////////////////
    char c(' ');

    while (c != 'q' && c != 'Q')
    {
        cout << "Press q then enter to quit: ";
        cin >> c;
    }
    return 0;
}
```

### CppSQLite Classes
The following simple classes are defined to encapsulate the functionality of SQLite.

All the CppSQLite classes are contained in 2 files CppSQLite.h and CppSQLite.cpp, which will need to be added to your application.

### CppSQLiteException
Encapsulates a SQLite error code and message. Nothing complicated here, and this class could easily be incorporated into an existing exception hierarchy, if required.

Error messages returned by SQLite need to be sqlite_freemem()'d by the programmer, and this class takes on that responsibility. Note that for error messages generated by CppSQLite, we don't want to free the memory, so there is an optional trailing parameter that dictates whether CppSQLiteException frees the memory.

```cpp
class CppSQLiteException
{
public:

    CppSQLiteException(const int nErrCode,
                    char* szErrMess,
                    bool bDeleteMsg=true);

    CppSQLiteException(const CppSQLiteException&  e);

    virtual ~CppSQLiteException();

    const int errorCode() { return mnErrCode; }

    const char* errorMessage() { return mpszErrMess; }

    static const char* errorCodeAsString(int nErrCode);

private:

    int mnErrCode;
    char* mpszErrMess;
};
```

### CppSQLiteDB
Encapsulates a SQLite database file.

```cpp
class CppSQLiteDB
{
public:

    enum CppSQLiteDBOpenMode
    {
        openExisting,
        createNew,
        openOrCreate
    };

    CppSQLiteDB();

    virtual ~CppSQLiteDB();

    void open(const char* szFile);

    void close();

    int execDML(const char* szSQL);

    CppSQLiteQuery execQuery(const char* szSQL);

    int execScalar(const char* szSQL);

    CppSQLiteTable getTable(const char* szSQL);

    CppSQLiteStatement compileStatement(const char* szSQL);

    int lastRowId();

    void interrupt() { sqlite_interrupt(mpDB); }

    void setBusyTimeout(int nMillisecs);

    static const char* SQLiteVersion() { return SQLITE_VERSION; }

private:

    CppSQLiteDB(const CppSQLiteDB& db);
    CppSQLiteDB& operator=(const CppSQLiteDB& db);

    sqlite_vm* compile(const char* szSQL);

    void checkDB();

    sqlite* mpDB;
    int mnBusyTimeoutMs;
};

```
open() and close() methods are self explanatory. SQLite does provide a mode argument to sqlite_open() but this is documented as having no effect, so is not provided for in CppSQLite.

execDML() is used to execute Data Manipulation Language (DML) commands such as create/drop/insert/update/delete statements. It returns the number of rows affected. Multiple SQL statements separated by semi-colons can be submitted and executed all at once. Note: there is a potential problem with the way that CppSQLite returns the number of rows affected. If there are any other un-finalized() operations in progress the number of rows affected will be cumulative and include those from previous statements. So if this feature is important to you, you have to make sure that any CppSQLiteQuery and CppSQLiteStatement objects that have not destructed yet have finalize() called on them before you execDML().

execQuery() is used to execute queries. The CppSQLiteQuery object is returned by value, as this frees the programmer from having to delete it.

execScalar() is an idea I got from ADO.NET. It is a shortcut for when you need to run a simple aggregate function, for example, "select count(*) from emp" or "select max(empno) from emp". It returns the value of the first field in the first row of the query result. Other columns and rows are ignored.

getTable() allows for the SQLite feature which can fetch a whole table in a single operation, rather than having to fetch one row at a time as with a query. Actually, subsets of table rows can be fetched by specifying a query with a where clause, but the whole result set is returned at once. Again, the CppSQLiteTable object is returned by value for convenience.

compileStatement() allows for the experimental SQLite pre-compiled SQL feature. See CppSQLiteStatement below.

SQLite is typeless, which means all fields are stored as strings. The one exception to this is the INTEGER PRIMARY KEY type, which allows an auto increment field, much like the SQL Server's identity columns. The lastRowId() function is used to determine the value of the primary key from the last row inserted.

interrupt() is useful when multithreading, and allows one thread to interrupt an operation in progress on another thread.

setBusyTimeout() can also be useful when multithreading, and allows the programmer to dictate how long SQLite waits before returning SQLITE_BUSY if another thread has a lock on the database. The default value is 60 seconds, set when the database is opened.

The copy constructor and operator=() are made private, as it does not make sense to copy a CppSQLiteDB object.

Finally, the static method SQLiteVersion() returns the version number of the underlying SQLite DLL.

### CppSQLiteQuery
Encapsulates a SQLite query result set.

```cpp
class CppSQLiteQuery
{
public:

    CppSQLiteQuery();

    CppSQLiteQuery(const CppSQLiteQuery& rQuery);

    CppSQLiteQuery(sqlite_vm* pVM,
                bool bEof,
                int nCols,
                const char** paszValues,
                const char** paszColNames,
                bool bOwnVM=true);

    CppSQLiteQuery& operator=(const CppSQLiteQuery& rQuery);

    virtual ~CppSQLiteQuery();

    int numFields();

    const char* fieldName(int nCol);

    const char* fieldType(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, 
          const char* szNullValue="");

    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    bool eof();

    void nextRow();

    void finalize();

private:

    void checkVM();

    sqlite_vm* mpVM;
    bool mbEof;
    int mnCols;
    const char** mpaszValues;
    const char** mpaszColNames;
    bool mbOwnVM;
};
```
nextRow() and eof() allow iteration of the query results.

numFields(), fieldValue(), fieldName(), fieldType() and fieldIsNull() allow the programmer to determine the number of fields, their names, values, types and whether they contain a SQL NULL. There are overloaded versions allowing the required field to be either specified by index or name.

getIntField(), getFloatField() and getStringField() provide a slightly easier to program way of getting field values, by never returning a NULL pointer for SQL NULL, and there is a default 2nd parameter that allows the programmer to specify which value to return instead.

It is not possible to iterate backwards through the results. The reason for this is that CppSQLite is a thin wrapper and does not cache any returned row data. If this is required, CppSQLiteDB::getTable() should be used, or the application could inherit from this class.

finalize() frees the memory associated with the query, but the destructor automatically calls this.

### CppSQLiteTable
SQLite provides a method to obtain a complete table's contents in a single block of memory, CppSQLiteTable encapsulates this functionality.
```cpp
class CppSQLiteTable
{
public:

    CppSQLiteTable();

    CppSQLiteTable(const CppSQLiteTable& rTable);

    CppSQLiteTable(char** paszResults, int nRows, int nCols);

    virtual ~CppSQLiteTable();

    CppSQLiteTable& operator=(const CppSQLiteTable& rTable);

    int numFields();

    int numRows();

    const char* fieldName(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    void setRow(int nRow);

    void finalize();

private:

    void checkResults();

    int mnCols;
    int mnRows;
    int mnCurrentRow;
    char** mpaszResults;
};
```
setRow() provides a random access method for movement between rows, and can be used in conjunction with numRows() to iterate the table. This design decision was made for simplicity, as following the same model as for CppSQLiteQuery, would have required functions for bof(), eof(), first(), last(), next() and prev().

numFields(), fieldValue(), fieldName(), fieldIsNull(), getIntField(), getFloatField(), getStringField(), close(), and operator=() provide the same functionality as for CppSQLiteQuery.

### CppSQLiteBuffer
Encapsulates SQLite "sprintf" functionality.

SQLite provides a function sqlite_mprintf() which is like the C runtime sprintf() except there is no possibility of overrunning the buffer supplied, as sqlite_mprintf() uses malloc to allocate enough memory. The other benefit over sprintf() is the %Q tag, which works like %s except that it will massage apostrophes so that they don't mess up the SQL string being built, and also translate NULL pointers into SQL NULL values.

```cpp
class CppSQLiteBuffer
{
public:

    CppSQLiteBuffer();

    ~CppSQLiteBuffer();

    const char* format(const char* szFormat, ...);

    operator const char*() { return mpBuf; }

    void clear();

private:

    char* mpBuf;
};
```
operator const char*() allows the programmer to pass an instance of this object to the functions defined on CppSQLiteDB.

### CppSQLiteBinary
Because SQLite stores all data as NULL terminated strings, it is not possible to store binary data if it has embedded NULLs. SQLite provides 2 functions sqlite_encode_binary() and sqlite_decode_binary() that can be used to allow storage and retrieval of binary data. CppSQLiteBinary encapsulates these 2 functions.

These two functions are not currently provided as part of the pre-compiled DLL, so I have copied the entire contents of SQLite's encode.c file into the CppSQLite.cpp file. Should these functions be provided in the DLL at some future point, they can easily be removed from CppSQLite.cpp.

```cpp
class CppSQLiteBinary
{
public:

    CppSQLiteBinary();

    ~CppSQLiteBinary();

    void setBinary(const unsigned char* pBuf, int nLen);
    void setEncoded(const unsigned char* pBuf);

    const unsigned char* getEncoded();
    const unsigned char* getBinary();

    int getBinaryLength();

    unsigned char* allocBuffer(int nLen);

    void clear();

private:

    unsigned char* mpBuf;
    int mnBinaryLen;
    int mnBufferLen;
    int mnEncodedLen;
    bool mbEncoded;
};
```
CppSQLiteBinary can accept data in either encoded or binary form using the setEncoded() and setBinary() functions. Whichever is used, enough memory is always allocated to store the encoded version, which is usually longer as nulls and single quotes have to be escaped.

Data is retrieved using the getEncoded() and getBinary() functions. Depending on which form the data is currently in within the class, it may need to be converted.

getBinaryLength() returns the length of the binary data stored, again converting the held format from encoded to binary, if required.

allocBuffer() can be used to prevent data having to be cycled via a temporary buffer like in the example code at the start of this article. This function could be used as in the following example where data is read straight from a file into a CppSQLiteBinary object.
```cpp
int f = open(gszJpgFile, O_RDONLY|O_BINARY);
int nFileLen = filelength(f);
read(f, blob.allocBuffer(nFileLen), nFileLen);
```

### CppSQLiteStatement
SQLite provides some experimental functionality for working with pre-compiled SQL. When the same SQL is being executed over and over again with different values, a significant performance improvement can be had by only compiling the SQL once, and executing it multiple times, each time with different values. CppSQLiteStatement encapsulates this functionality.

```cpp
class CppSQLiteStatement
{
public:

    CppSQLiteStatement();

    CppSQLiteStatement(const CppSQLiteStatement& rStatement);

    CppSQLiteStatement(sqlite* pDB, sqlite_vm* pVM);

    virtual ~CppSQLiteStatement();

    CppSQLiteStatement& operator=(const CppSQLiteStatement& rStatement);

    int execDML();

    CppSQLiteQuery execQuery();

    void bind(int nParam, const char* szValue);
    void bind(int nParam, const int nValue);
    void bind(int nParam, const double dwValue);
    void bindNull(int nParam);

    void reset();

    void finalize();

private:

    void checkDB();
    void checkVM();

    sqlite* mpDB;
    sqlite_vm* mpVM;
};
```
A CppSQLiteStatement object is obtained by calling CppSQLiteDB::compileStatement() with a SQL statement containing placeholders, as follows:
```cpp
CppSQLiteStatement stmt = db.compileStatement("insert into emp values (?, ?);");
stmt.bind(1, 1);
stmt.bind(2, "Emp Name");
stmt.execDML();
stmt.reset();
```

The CppSQLiteStatement::bind() methods are then used to set the values of the placeholders, before calling either execDML() or execQuery() as appropriate.

After the programmer has finished with the result from either execDML() or execQuery(), the reset() method can be called to put the statement back to a compiled state. The CppSQLiteStatement::bind() methods can then be used again, followed by execDML() or execQuery(). A typical use would be in a loop as demonstrated in the CppSQLiteDemo program.

### Multithreading
SQLite is compiled as thread-safe on Windows by default, and CppSQLite makes use of some SQLite features to help with multithreaded use. Included in the source code accompanying this article is a 2nd demo program called CppSQLiteDemoMT, which demonstrates these features.

Each thread wishing to utilize CppSQLite on the same database file at the same time must have its own CppSQLiteDB object, and call open(). To put this another way, it is an error for more than 1 thread to call into a CppSQLiteDB object at the same time. The one exception to this is CppSQLiteDB::interrupt(), which can be used from one thread to interrupt the work of another thread.

The other change to CppSQLite for multithreaded use is to make use of the sqlite_busy_timeout() function which causes SQLite to wait up to the specified number of milliseconds before returning SQLITE_BUSY. By default, CppSQLite sets this to 60,000 (60 seconds), but this can be changed using CppSQLiteDB::setBusyTimeout() as required. Various examples of doing this are shown in the CppSQLiteDemoMT program.


### SQLite Functionality Not Currently Wrapped
SQLite provides a mechanism that allows the application developer to define stored procedures and aggregate functions that can be called from SQL statements. These stored procedures are written in C by the application developer, and made known to SQLite via function pointers. This is how the SQL built in functions are implemented by SQLite, but this functionality is not currently catered for in CppSQLite.

SQLite provides some other variations on the functions wrapped, and the reader is encouraged to study the SQLite documentation.

### Managed C++
It is possible to compile SQLite and CppSQLite into a managed C++ program, It Just Works (IJW). You will need to set the CppSQLite.cpp file so that it does not use pre-compiled headers and also not to use Managed extensions, i.e. don't use /clr.

There is a Managed C++ demo included with the CppSQLite downloads.

### SQLite Version 3
At the time of writing, SQLite version 3 is in beta. See http://www.sqlite.org/ for further details. I have produced a port of CppSQLite to SQLite version 3, and the following notes explain the differences.

There are a new set of classes with the prefix CppSQLite3, for example CppSQLite3Exception. This allows programs to link with both versions of CppSQLite, as is possible with both versions of SQLite itself.

There is not support for UTF-16 initially, as it is not something I have experience of, and wouldn't know how to test. This can be added later with another set of classes, called for example CppSQLite3Exception16 etc. Note that some sqlite3 stuff such as sqlite3_exec() and sqlite3_get_table() do not appear to have UTF-16 versions, also sqlite3_vmprintf(), used by CppSQLiteBuffer.

Error messages are now returned by sqlite3_errmsg() and do not need to be freed. To keep consistency between CppSQLite and CppSQLite3 the code that throws exceptions with messages returned from SQLite version 3 has been changed so that it passes DONT_DELETE_MSG as the final parameter to CppSQLite3Exception. The exception to this is the messages returned by sqlite3_exec() and sqlite3_get_table().

SQLite version 3 now has direct support for BLOB data, and therefore no need to encode or decode it, and there would seem to be no job for CppSQLiteBinary. However, the SQLite version 3 change means that the only way to work with BLOB data would seem to be using prepared statements (CppSQLiteStatement). Not really a problem, but up until now, CppSQLiteBinary had allowed use of (encoded) binary data in calls to CppSQLiteDB::execQuery(), CppSQLiteDB::execDML() and on data returned from CppSQLiteDB::getTable().

sqlite_encode_binary() and sqlite_decode_binary() are still included in the SQLite version 3 source distribution, although it is not clear whether this is an error as they do not have the sqlite3 prefix, nor are they exported from the DLL. CppSQLite3 replicates the source to these 2 functions. This used to be the case with CppSQlite up to version 1.3 as up until version 2.8.15 of SQLite, they were not exported from the DLL. CppSQLite3Binary is an exact copy of CppSQLiteBinary, bundled with the source to sqlite_encode_binary() and sqlite_decode_binary(). This will allow easy porting between CppSQLite and CppSQLite3. Programs wishing to use sqlite3 BLOBs and their reduced storage space will not need to use CppSQLite3Binary, and will need to be rewritten anyway.

SQLite version 3 introduces changes to the data typing system used. See http://www.sqlite.org/datatype3.html . For this reason, CppSQLiteQuery::FieldType() has been replaced with 2 functions: CppSQLiteQuery::FieldDeclType() which returns the declared data type for the column as a string, and and CppSQLiteQuery::FieldDataType() whhich returns the actual type of the data stored in that column for the current row as one of the SQLite version 3 #defined vallues.

The demo programs have been changed slightly to demonstrate the new features, and also to account for SQLite version 3's different locking behaviour. See http://www.sqlite.org/lockingv3.html. Note that SQLite version 3.0.5 introduced a compile time option which changes locking behaviour, see http://www.sqlite.org/changes.html for more details.

The SQLite version 3 is available as a separate download at the top of this article.

### Future Work
I may add support for the remaining SQLite features to CppSQLite. At the moment, this means stored procedures and aggregate functions.

### Cross Platform Capability
Since version 1.2 of CppSQLite, I have tried hard not to do anything which is Microsoft specific, and have successfully compiled and run the demo programs on mingw32, as well as with Visual C++.

As mingw32 is based on GCC, there should be no major problems on Linux/Unix, although the multi threaded demo program CppSQLiteDemoMT uses the _beginthread() call, which will obviously not work. This can probably be easily fixed, using pthreads for example.

### Contributions
Thanks to fellow Code Project members for suggestions and buf fixes for CppSQLite, and also to Mateusz Loskot for acting as a reviewer.

### Conclusion
CppSQLite makes SQLite easier to use within a C++ program, yet doesn't provide significantly less power or efficiency than the flat C interface.

If nothing else, writing CppSQLite has provided the author with an insight into the power and simplicity of SQLite. It is hoped that readers of this article also benefit in some way.

### History for CppSQLite (Targets SQLite 2.8.n)
.0 - 3rd Mar 2004 - Initial version.
1.1 - 10th Mar 2004
Renamed CppSQLiteException::errorMess() to CppSQLiteException::errorMessage().
2nd constructor to CppSQLiteException().
Now decodes error codes to strings in CppSQLiteException.
Call sqlite_finalize() immediately to get error details after problems with sqlite_step().
Added CppSQLiteBinary class.
1.2 - 2nd Apr 2004 - Not released.
Updated article.
Removed use of Microsoft specific extensions (I hope)
Check for NULL pointers
Updated for SQLite 2.8.13
Utilized sqlite_busy_timeout() and sqlite_interrupt() to help with multithreaded use
2nd demonstration program for multithreaded use
Added support from pre-compiled SQL statements
Added ability to determine column types from CppSQLiteQuery
Added CppSQLiteDB::execScalar()
1.2.1 - 15th Apr 2004
Updated article following review
Use of C++ rather than C standard headers following review
1.3 - 21st May 2004
Added "BSD Style" License notice to source files
Fixed bugs on bind()
Added getIntField(), getStringField(), getFloatField()
Added overloaded functions to access fields by name
CppSQLiteDB::ExecDML() implemented with sqlite_exec() so multiple statements can be executed at once.
Added note in article about potential problem with return value from CppSQLiteDB::execDML()
Added managed C++ example program
1.4 - 30th August 2004
Upgraded to SQLite 2.8.15
Removed source for sqlite_encode_binary() and sqlite_decode_binary() as there are now exported from the SQLite DLL
Added article section on Managed C++

### History for CppSQLite3 (Targets SQLite 3.n.n)
3.0 - 30th August 2004
Initial version to work with SQLite version 3.0.6
3.1 - 26th October 2004
Upgraded to vSQLite 3.0.8
Added CppSQLiteDB3::tableExists() function
Implemented getXXXXField using SQLite3 functions instead of atoi(), atof(), etc.
3.2 - 24th June, 2011
Bundled with SQLite3 version 3.4.0
CppSQLite3DB::SQLiteHeaderVersion(), CppSQLite3DB::SQLiteLibraryVersion(), CppSQLite3DB::SQLiteLibraryVersionNumber()
Fixed execScalar to handle a NULL result
Added Int64 functions to CppSQLite3Statement
Added CppSQLite3DB::IsAutoCommitOn(), can be used to test if a transaction is active
Throw exception from CppSQLite3DB::close() on error
Trap above exception in CppSQLite3DB::~CppSQLite3DB()
Bigger buffer size 256 in table
sqlite3_prepare replaced with sqlite3_prepare_v2
Fix to CppSQLite3DB::compile() as provided by Dave Rollins
Binds parameters by name as suggested by Dave Rollins

### About the Author

Rob Groves
Web Developer
United Kingdom United Kingdom
Software developer using C/C++, ASP, .NET and SQL Server/Oracle relational databases.
