## 1、[boost-使用format和lexical_cast实现数字和字符串之间的转换](https://www.cnblogs.com/milanleon/p/7423292.html)
```cpp
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

using std::string;

int main(int argc, char* agrv[])
{
     boost::format fmt("double value: %.2f");
     double d = 12.34f;
     std::string str = (fmt % d).str();
     std::cout << str << std::endl;
 
     std::string strValue("3.1415926");
     double d2 = boost::lexical_cast<double>(strValue);
     std::cout << d2 << std::endl;
 
     return 0;
}
```

## [boost-字符编码转换：使用conv](https://www.cnblogs.com/milanleon/p/7442920.html)
Windows下的字符集转换可以使用WideCharToMultiByte/ MultiByteToWideChar，Linux下字符集转换可以使用iconv()函数，下面为使用boost的conv来进行字符集转换：
```cpp
#include <boost/locale/encoding.hpp>
#include <iostream>
#include <string>

using std::string;
using std::wstring;

string UTF8toGBK(const string & str)
{
    return boost::locale::conv::between(str, "GBK", "UTF-8");
}

string GBKtoUTF8(const string & str)
{
    return boost::locale::conv::between(str, "UTF-8", "GBK");
}

wstring GBKtoUNICODE(const string & str)
{
    return boost::locale::conv::to_utf<wchar_t>(str, "GBK");
}

string UNICODEtoGBK(wstring wstr)
{
    return boost::locale::conv::from_utf(wstr, "GBK");
}

string UNICODEtoUTF8(const wstring& wstr)
{
    return boost::locale::conv::from_utf(wstr, "UTF-8");
}

wstring UTF8toUNICODE(const string & str)
{
    return boost::locale::conv::utf_to_utf<wchar_t>(str);
}

 int main(int argc, char* agrv[])
{
     string str1 = "wuhan hubei, 中国";
     std::cout << str1 << std::endl;
 
     string strResult = GBKtoUTF8(str1);
     std::cout << strResult << std::endl;
 
     return 0;
 }

```
