## [C++之RapidJSON生成json数据](https://blog.csdn.net/chen134225/article/details/94046308)
RapidJSON 是一个 C++ 的 JSON 解析器及生成器。
### 1、示例代码如下：
```cpp
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

int main () {

  string name = "xiaoming";
  string gender = "boy";
  vector<string> hobby = {"足球","篮球","电影"};
  map<string, double> score = {{"数学",91.5},{"语文", 95.5},{"英语", 96}};

  string lover_name = "xiaohong";
  string love_gender = "girl";
  vector<string> lover_hobby = {"画画","跳舞","唱歌"};
  map<string, double> lover_score = {{"数学", 78.5},{"语文", 89},{"英语", 90}};

  rapidjson::StringBuffer s;
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);
  writer.StartObject();

  writer.Key("name");
  writer.String(name.c_str());
  writer.Key("gender");
  writer.String(gender.c_str());

  writer.Key("hobby");
  writer.StartArray();
  for(auto &item : hobby){
    writer.String(item.c_str());
  }
  writer.EndArray();

  writer.Key("socre");
  writer.StartObject();
  for(auto &item : score){
    writer.Key((item.first).c_str());
    writer.Double(item.second);
  }
  writer.EndObject();

  writer.Key("lover");
  writer.StartObject();

  writer.Key("name");
  writer.String(lover_name.c_str());
  writer.Key("gender");
  writer.String(love_gender.c_str());

  writer.Key("hobby");
  writer.StartArray();
  for(auto &item : lover_hobby){
    writer.String((item.c_str()));
  }
  writer.EndArray();

  writer.Key("score");
  writer.StartObject();
  for(auto &item : lover_score){
    writer.Key((item.first).c_str());
    writer.Double(item.second);
  }
  writer.EndObject();

  writer.EndObject();

  writer.EndObject();

  //将生成的json数据写入json1.txt文件中
  std::string outFileName = "json1.txt";
  std::ofstream outfile(outFileName,std::ios::trunc);
  outfile << s.GetString();
  outfile.close();

  std::cout << s.GetString() << std::endl;

}
```

### 2、上面代码生成的json文件如下所示：
```json
{
  "name": "xiaoming",
  "gender": "boy",
  "hobby": [
    "足球",
    "篮球",
    "电影"
  ],
  "socre": {
    "数学": 91.5,
    "英语": 96,
    "语文": 95.5
  },
  "lover": {
    "name": "xiaohong",
    "gender": "girl",
    "hobby": [
      "画画",
      "跳舞",
      "唱歌"
    ],
    "score": {
      "数学": 78.5,
      "英语": 90,
      "语文": 89
    }
  }
}
```
### 3.RapidJSON解析json数据
https://blog.csdn.net/chen134225/article/details/90573407
