# 一、下载[yaml-cpp](https://github.com/jbeder/yaml-cpp)源代码
yml文件和yaml文件是目前比较常用的配置文件，Java中的SpringBoot的application.yml配置使用的就是这种格式，另外诸如nodejs和g欧登语法对于yaml文件都有很好的支持。
yaml-cpp是一个yaml配置文件的C++解析库，其下载地址为：[https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
在Windows10中使用VS2017编译yaml-cpp库前，需要去Github上面下载对应的[yaml-cpp]((https://github.com/jbeder/yaml-cpp))源代码。目前的yaml-cpp最新版本是yaml-cpp-0.6.0。如下图所示：
![yam-cpp-0.6.0](https://img-blog.csdnimg.cn/20200919095104879.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

```clone
git clone https://github.com/jbeder/yaml-cpp.git
```
![yaml-cpp](https://img-blog.csdnimg.cn/20200919084952818.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
我在Windows10中下载好yaml-cpp源代码将其放在相应的目录下，最后下载的文件目录结构如下图所示：
![yaml-cpp的目录结构](https://img-blog.csdnimg.cn/20200919085114714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

# 二、下载并安装cmake
去官网[https://cmake.org/download/](https://cmake.org/download/)

![cmake](https://img-blog.csdnimg.cn/20200919091455845.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

![cmake_linux](https://img-blog.csdnimg.cn/20200919091639432.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
由于是CentOS所以选择对应的Linux源代码[cmake-3.18.2.tar.gz](https://github.com/Kitware/CMake/releases/download/v3.18.2/cmake-3.18.2.tar.gz)或者对应的[cmake-3.18.2-Linux-x86_64.tar.gz](https://github.com/Kitware/CMake/releases/download/v3.18.2/cmake-3.18.2-Linux-x86_64.tar.gz)源代码以及编译脚本[cmake-3.18.2-Linux-x86_64.sh](https://github.com/Kitware/CMake/releases/download/v3.18.2/cmake-3.18.2-Linux-x86_64.sh)
下载到对应的目录下执行cmake-3.18.2-Linux-x86_64.sh脚本安装cmake即可。另外需要配置好cmake的环境变量，将cmake命令加到系统的环境变量种。

# 三、使用cmake编译yaml-cpp
在CentOS7等Linux发行版下编译yaml-cpp是非常简单的，可以参考github上面的描述：
![Linux下编译yaml-cpp的步骤](https://img-blog.csdnimg.cn/20200919092407358.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
下载[yaml-cpp](https://github.com/jbeder/yaml-cpp)源代码，并且安装好了cmake之后（我安装的cmake版本是cmake 3.16.2），开始编译yaml-cpp，命令如下图所示:
```shell
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
cd yaml-cpp
mkdir build
cmake .. -DYAML_BUILD_SHARED_LIBS=ON
make
make install
```
![使用cmake编译yaml-cpp](https://img-blog.csdnimg.cn/20200919092810889.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![make](https://img-blog.csdnimg.cn/20200919092928290.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![make install](https://img-blog.csdnimg.cn/20200919094009662.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
编译安装好yaml-cpp库后会在build目录生成libyaml-cpp.so.0.6.3动态库以及yaml-cpp.pc等文件，可以从yaml-cpp.pc文件中看出yaml-cpp库默认的安装路径为：/usr/local目录，头文件安装路径为：/usr/local/include，库文件安装路径为：/usr/local/lib64
![make install](https://img-blog.csdnimg.cn/2020091909481578.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
至此在CentOS7下成功编译生成了yaml-cpp的lib动态库，并且安装到/usr/local目录下，可以使用yaml-cpp进行yaml或yml的解析和测试了。

# 四、测试使用yaml-cpp
首先在编写代码前，写一个config.yaml配置文件，其内容如下：
```yaml
lastLogin: 2020-09-18 10:17:40
username: root
password: 123
```
相关C++示例代码demo1.cpp如下：

```cpp
 #include <yaml-cpp/yaml.h>
 #include <iostream>
 #include <string>
 #include <fstream>
 using std::cout;
 using std::endl;
 
 int main(int argc, char* argv[])
 {
     YAML::Node config = YAML::LoadFile("config.yaml");
  
     if (config["lastLogin"]) {
          std::cout << "Last logged in: " << config["lastLogin"].as<std::string>() << std::endl;
     }
  
     const std::string username = config["username"].as<std::string>();
     const std::string password = config["password"].as<std::string>();
     config["lastLogin"] = "2020-09-19 11:17:40";
  
     std::ofstream fout("config.yaml");
     fout << config;
  
     return 0;
 }

```
编译并运行demo程序，
在demo1.cpp和config.yaml同级目录下执行如下命令：
```shell
g++ demo1.cpp -o demo1 -std=c++11 -I/usr/local/include -L/usr/local/lib64 -lyaml-cpp
```
编译demo1.cpp生成对应的demo1可执行文件
然后运行demo1可执行文件：
```shell
./demo1
```
运行结果如下图所示：
![demo1](https://img-blog.csdnimg.cn/20200919121903945.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
可以重新查看config.yaml文件，发现其中的lastLogin字段被修改成了2020-09-19 11:17:40
![demo1_test2](https://img-blog.csdnimg.cn/20200919122116830.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)



# 五、参考资料
- [https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [https://cmake.org/download/](https://cmake.org/download/)
