### [C++ Converting a String to Double](https://stackoverflow.com/questions/16747915/c-converting-a-string-to-double)

### https://zh.cppreference.com/w/cpp/string/basic_string/stof
### http://www.cplusplus.com/reference/string/stod/

###[c++中string，double 三种互转代码示例](https://www.cnblogs.com/jingmi/p/11206236.html)
```cpp
#include <iostream>
#include <string>
#include <sstream> //for istringstream
#include <iomanip> //for setprecision
#include <cstdio> //for sscanf
using namespace std;

int main()
{
    cout << "/************string to double************/" << endl;
    /************string to double************/
    string str = "12.34567890e2";
    cout << "string: "<<str << endl;

    //using std::stod
    double d;
    string::size_type size; //13
    d = stod(str, &size);  //1234.56789
    cout << "double value get by stod:         " << setprecision(14) << d << ", size:"<<size << endl; //Note: must setprecision to see entire value

    //using sstream
    istringstream istrStream(str);
    istrStream >> d;  //1234.56789
    cout << "double value get by istringstream:" << setprecision(14) << d << endl;

    //using sscanf
    int len; //13
    sscanf_s(str.c_str(), "%14lf%n", &d, &len); //1234.56789
    cout << "double value get by sscanf:       " << setprecision(14) << d <<", size:"<<len<< endl;


    cout << "\n\n/**************double to string***************/" << endl;
    /**************double to string***************/
    double d8 = 1.123456789e2;
    cout << "double value: " << setprecision(14) << d8 << endl;

    string str8 = std::to_string(d8);//112.345679
    cout << "string get by std::to_string: " << str8 << endl;

    ostringstream ostrStream;
    ostrStream << setprecision(10);
    ostrStream << d8;
    str8 = ostrStream.str();//112.3456789
    cout << "string get by ostringstream:  "<< str8 << endl;

    char ch[64];
    sprintf_s(ch, "%g", d8);
    str8 = ch;//112.346
    cout << "string get by sprintf:        " << str8 << endl;

    //below code is used to avoid control exit quickly
    char c;
    cin >> c;

    return 0;
}
```
