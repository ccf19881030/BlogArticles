## [C++ JSON解析库RapidJSON](https://www.cnblogs.com/buyishi/p/8598736.html)
https://github.com/Tencent/rapidjson
### jsontext.txt
```json
{
        "result" :
        [
                {
                        "face_id" : "a9cebf8d5ae6fff514d8d2d8e07fa55b",
                        "img_id" : "12.jpg",
                        "people_name" : "白活",
                        "similarity" : 100
                },
                {
                        "face_id" : "7f2de0e85bede3171c839d0dcabd849f",
                        "img_id" : "6.jpg",
                        "people_name" : "布伊什",
                        "similarity" : 55.379097
                },
                {
                        "face_id" : "40ebb31e8af7237a73dec9f242885a7e",
                        "img_id" : "2.jpg",
                        "people_name" : "布衣食",
                        "similarity" : 52.59766
                }
        ]
}
```

### rapidjson_test.cpp
```cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
int main()
{
    using namespace std;
    using namespace rapidjson;
    cout << "parsing test" << endl;
    string line, jsonText;
    ifstream ifs("json_text.txt");
    while (getline(ifs, line))
        jsonText.append(line);
    Document document;
    document.Parse(jsonText.c_str());
    const auto &array = document["result"].GetArray();
    for (const auto &e : array)
    {
        const auto &faceId = e["face_id"].GetString();
        const auto &imgId = e["img_id"].GetString();
        const auto &peopleName = e["people_name"].GetString();
        const auto &similarity = e["similarity"].GetDouble();
        cout << setprecision(15) << "face_id:\t" << faceId << endl;
        cout << "img_id:\t\t" << imgId << endl;
        cout << "people_name:\t" << peopleName << endl;
        cout << "similarity:\t" << similarity << endl << endl;
    }
    cout << endl << "generating test" << endl;
    Document d;
    d.SetObject();
    Document::AllocatorType &allocator = d.GetAllocator();
    Value arr(kArrayType);
    Value elem1(kObjectType);
    elem1.AddMember("name", "沃夫", allocator);
    elem1.AddMember("gender", "Male", allocator);
    elem1.AddMember("age", 24, allocator);
    arr.PushBack(elem1, allocator);
    Value elem2(kObjectType);
    elem2.AddMember("name", "布伊什", allocator);
    elem2.AddMember("gender", "Female", allocator);
    elem2.AddMember("age", 26, allocator);
    arr.PushBack(elem2, allocator);
    Value elem3(kObjectType);
    elem3.AddMember("name", "布衣食", allocator);
    elem3.AddMember("gender", "Male", allocator);
    elem3.AddMember("age", 28, allocator);
    arr.PushBack(elem3, allocator);
    d.AddMember("result", arr, allocator);
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);
    d.Accept(writer);
    cout << strBuf.GetString() << endl;
    
    return 0;
}
```
