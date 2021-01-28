## 1、应用背景
   通常在程序设计中采用xml、ini、yaml、json等配置文件比较多。在Java的SpringBoot项目中通常采用yaml或者yml文件作为应用的配置项。由于本人在实际项目中采用C++编写控制台程序的过程中使用yaml文件比较多，目前使用比较的多的就是[yaml-cpp](https://github.com/jbeder/yaml-cpp)这个C++ yaml解析库了。之前写过两篇关于在[CentOS7下编译yaml-cpp库](https://ccf19881030.blog.csdn.net/article/details/108676702)和[Windows10下使用VS2017编译和使用yaml-cpp库](https://ccf19881030.blog.csdn.net/article/details/108676484)的文章。
   最近实际项目中换成了最新版的Visual Studio 2019，我使用的Windows系统是Win7和Windows10，所以需要重新编译基于VS2019下的yaml-cpp的Debug和Release版本的Win32的静态lib库，大体步骤和[Windows10下使用VS2017编译和使用yaml-cpp库](https://ccf19881030.blog.csdn.net/article/details/108676484)这篇博客描述的一致。
   
## 2、下载yaml-cpp源代码
   首先从[https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)上下载源代码
   ```
   git clone https://github.com/jbeder/yaml-cpp.git
   ```
   使用`git`拉取代码
   或者直接在[https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)上下载zip文件，然后解压缩到指定的文件目录下：
   ![下载yaml-cpp的zip压缩包](https://img-blog.csdnimg.cn/20210127232511335.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
## 3、使用VS2019和CMake3.18.3编译yaml-cpp
首先确保已经在自己的系统下安装了VS2019和CMake
我的系统是Windows7、VS2019、CMake 3.18.3，可以根据需要选择Windows10、CMake 3.19.2也行
解压后的yaml-cpp源码包目录结构如下：
![yaml-cpp的源代码](https://img-blog.csdnimg.cn/20210127232816641.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
Github仓库上对于在Windows10下使用yaml-cpp的CMake编译介绍到比较简单，具体如下图所示：
![使用CMake编译yaml-cpp库](https://img-blog.csdnimg.cn/20210127232952127.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
下载好yaml-cpp源代码并解压到`F:\rate\iot_sdk\third_part`目录下，然后再该目录下创建一个`build`目录，用于存放编译过程中的中间文件，这样做主要是为了不影响源代码，弄错了可以删除重来。
我在Windows7系统下使用VS2019和CMake 3.18.3编译yaml-cpp的命令为：
```
cmake .. -G "Visual Studio 16 2019" -A Win32 -DCMAKE_INSTALL_PREFIX=F:\rate\iot_sdk\third_part\yaml-cpp\install  -DYAML_BUILD_SHARED_LIBS=OFF ..
```
或者
```
cmake .. -G "Visual Studio 16 2019 Win32 "  -DCMAKE_INSTALL_PREFIX=F:\rate\iot_sdk\third_part\yaml-cpp\install  -DYAML_BUILD_SHARED_LIBS=OFF ..
```
上面的-G命令指定了VS2019作为工具，-DCMAKE_INSTALL_PREFIX指定安装目录，
-DYAML_BUILD_SHARED_LIBS指定是否编译动态库的开关，ON表示编译动态库，OFF表示不编译动态库只编译静态库。
![YAML_CPP.sln](https://img-blog.csdnimg.cn/20210127233814186.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
然后使用VS2019打开YAML_CPP.sln工程文件，如下图所示：
![使用VS2019打开YAML_CPP.sln工程文件](https://img-blog.csdnimg.cn/20210127234035504.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![选择自己的Windows SDK版本](https://img-blog.csdnimg.cn/20210127234156363.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
### 3.1、使用VS2019编译Win32 Debug模式的`yaml-cppd.lib`库
选择需要编译的平台和模式，如Win32/Win64以及Debug/Release
上面选择了Debug以及Win32，然后右键点击【解决方案】-》【生成解决方案】
![生成解决方案](https://img-blog.csdnimg.cn/20210127234523547.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
然后会生成一些基于Win32平台的Debug版本的静态库
![其他静态库](https://img-blog.csdnimg.cn/20210127234634482.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![yaml-cpd.lib静态库](https://img-blog.csdnimg.cn/20210127234801349.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
这个`yaml-cppd.lib`就是我们使用VS2019项目编译出来的基于Win32平台的Debug静态库，在使用VS2019开发yaml-cpp的项目中需要引入这个lib库

### 3.2、使用VS2019编译Win32 Release模式的`yaml-cpp.lib`库
选择Release、Win32，右键点击【解决方案】-》【生成解决方案】，如下图所示：
![编译Win32 Debug模式的yaml-cpp.lib库](https://img-blog.csdnimg.cn/2021012723520875.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![yaml-cpp.lib库](https://img-blog.csdnimg.cn/20210127235314709.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![其他lib库](https://img-blog.csdnimg.cn/20210127235345835.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
关于在Windows7下使用VS2019编译Win64位的Debug库和Release库的方法也是类似的，对应的CMake编译命令为：
```
cmake .. -G "Visual Studio 16 2019 Win64 "  -DCMAKE_INSTALL_PREFIX=F:\rate\iot_sdk\third_part\yaml-cpp\install  -DYAML_BUILD_SHARED_LIBS=OFF ..
```
生成了YAML-CPP.sln项目工程后，使用VS2019打开，分别选择Win64位的Debug或Win64的Release模式，然后右键点击【解决方案】-》【生成解决方案】，会分别在相应目录下生成yaml-cppd.lib和yaml-cpp.lib文件

## 4、在VS2019中使用yaml-cpp库读写yaml文件
这个在VS2019中引入yaml-cpp库的方式和VS2017中一样，具体可以参考我之前的博客[Windows10下使用VS2017编译和使用yaml-cpp库](https://ccf19881030.blog.csdn.net/article/details/108676484)
![在VS2019中使用yaml-cpp](https://img-blog.csdnimg.cn/20210127235546581.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![运行结果](https://img-blog.csdnimg.cn/2021012723561983.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
测试的config.yaml文件如下：
```yaml
lastLogin: 2021-01-20 08:26:10
username: root
password: 123
```
C++测试源代码如下：
```cpp
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"


int main()
{
    YAML::Emitter out;
    out << "Hello, World!";

    std::cout << "Here's the output YAML:\n" << out.c_str();

    YAML::Node config = YAML::LoadFile("config.yaml");

    if (config["lastLogin"]) {
        std::cout << "Last logged in: " << config["lastLogin"].as<std::string>() << std::endl;
    }

    const std::string username = config["username"].as<std::string>();
    const std::string password = config["password"].as<std::string>();

    //login(username, password);
    //config["lastLogin"] = getCurrentDateTime();
    config["lastLogin"] = "2021-01-21 10:26:10";


    std::cout << "username: " << username << ", password: " << password << std::endl;

    std::ofstream fout("config.yaml");
    fout << config;

    return 0;
}
```
## 5、参考资料
- [CentOS7下编译yaml-cpp库](https://ccf19881030.blog.csdn.net/article/details/108676702)
- [Windows10下使用VS2017编译和使用yaml-cpp库](https://ccf19881030.blog.csdn.net/article/details/108676484)
- [windows下yaml-cpp从配置环境到使用](https://blog.csdn.net/sinat_38602176/article/details/105640629)
- [jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [Tutorial](https://github.com/jbeder/yaml-cpp/wiki/Tutorial)
- [How To Emit YAML](https://github.com/jbeder/yaml-cpp/wiki/How-To-Emit-YAML)
- [yaml-cpp API文档](https://codedocs.xyz/jbeder/yaml-cpp/index.html)
- [How to load YAML file via yaml-cpp?](https://www.howtobuildsoftware.com/index.php/how-do/c7Cl/c-yaml-cpp-how-to-load-yaml-file-via-yaml-cpp)
