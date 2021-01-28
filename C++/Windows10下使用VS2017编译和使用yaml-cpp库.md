# 一、下载[yaml-cpp]((https://github.com/jbeder/yaml-cpp))源代码
yaml-cpp是一个yaml配置文件的C++解析库，其下载地址为：[https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
在Windows10中使用VS2017编译yaml-cpp库前，需要去Github上面下载对应的[yaml-cpp]((https://github.com/jbeder/yaml-cpp))源代码
```clone
git clone https://github.com/jbeder/yaml-cpp.git
```
![yaml-cpp](https://img-blog.csdnimg.cn/20200919084952818.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
我在Windows10中下载好yaml-cpp源代码将其放在相应的目录下，最后下载的文件目录结构如下图所示：
![yaml-cpp的目录结构](https://img-blog.csdnimg.cn/20200919085114714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

# 二、使用cmake编译yaml-cpp
进入下载好的yaml-cpp源代码的根目录，进行如下操作：
## 1、首先新建一个build文件夹，在build文件夹下编译生成Makefile文件就不会很乱
## 2、在build文件夹下shift+鼠标右键，选择在此处打开powershell窗口，输入cmake ..
需要注意的是：在Windows10中使用cmake编译yaml-cpp之前，需要安装好cmake并且配置好cmake的环境变量。我安装的是cmake 3.11.1版本
如下图所示：
![cmake](https://img-blog.csdnimg.cn/20200919085641769.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
使用cmake编译yaml-cpp库后生成的文件如下图所示：
![cmake_build](https://img-blog.csdnimg.cn/20200919085743789.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 3、在VS2017中编译yaml-cpp
cmake结束，打开工程编译
使用VS2017打开项目文件YAML-CPP.sln
![yaml-cpp](https://img-blog.csdnimg.cn/20200919090109995.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
选择所需要的库类型，比如Debug/Release、Win32/X64，一共是4种组合：
- Debug和Win32
- Debug和X64
- Release和Win32
- Release和X64
选好对应的编译类型（Debug/Release）和平台类型（Win32/X64）之后，
然后右键ALL_BUILD项目进行生成，之后在build文件夹下会生成yaml-cpp.lib
![all_build](https://img-blog.csdnimg.cn/20200919091111542.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

如果使用debug模式会在build/Debug下生成yaml-cppd.lib;如果使用release模式会在build/Release目录下生成yaml-cpp.lib
将生成的lib拷贝到你需要的地方，至此编译过程结束


# 三、在VS2017中使用yaml-cpp
编译好yaml-cpp后，可以在VS2017中使用，可以参考[Tutorial](https://github.com/jbeder/yaml-cpp/wiki/Tutorial)
![Tutorial](https://img-blog.csdnimg.cn/20200919102905377.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
在VS2017中新建一个基于控制台的Win32应用程序，
如下图所示：
![yaml-cpp-demo01](https://img-blog.csdnimg.cn/20200919103100743.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

![VS2017](https://img-blog.csdnimg.cn/2020091910295977.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
在项目根目录下创建一个config.yaml文件，其内容如下：
```yaml
lastLogin: 2020-08-19 10:26:10
username: root
password: 123
```
在VS2017中指定yaml-cpp的头文件和库文件所在路径：
我的yaml-cpp头文件所在路径为：D:\env_build\yaml-cpp\include
lib库文件yaml-cpp.lib所在路径分别为：D:\env_build\yaml-cpp\lib\Debug\和D:\env_build\yaml-cpp\lib\Release\
- 指定yaml-cpp头文件

![include](https://img-blog.csdnimg.cn/20200919103237826.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
- 指定yaml-cpp库文件路径
![lib](https://img-blog.csdnimg.cn/20200919103452711.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
- 指定yaml-cpp.lib库
![yaml-cpp.lib](https://img-blog.csdnimg.cn/20200919103535169.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
配置好项目yaml-cpp-demo01的yaml-cpp的头文件和库文件等相关配置好，运行下面的示例代码：

```cpp
#include "pch.h"
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
	config["lastLogin"] = "2020-09-19 10:26:10";


	std::cout << "username: " << username << ", password: " << password << std::endl;

	std::ofstream fout("config.yaml");
	fout << config;

	return 0;
}
```
运行结果如下图所示：
![run](https://img-blog.csdnimg.cn/20200919103806469.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
运行后config.yaml中的lastLogin字段也被修改成了：2020-09-19 10:26:10
如下图所示：
![config1](https://img-blog.csdnimg.cn/20200919103921463.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![config2](https://img-blog.csdnimg.cn/20200919103937929.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
至此，可以在VS2017下使用yaml-cpp库读写yaml配置文件了。

# 四、 参考资料
- [windows下yaml-cpp从配置环境到使用](https://blog.csdn.net/sinat_38602176/article/details/105640629)
- [jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [Tutorial](https://github.com/jbeder/yaml-cpp/wiki/Tutorial)
- [How To Emit YAML](https://github.com/jbeder/yaml-cpp/wiki/How-To-Emit-YAML)
- [yaml-cpp API文档](https://codedocs.xyz/jbeder/yaml-cpp/index.html)
- [How to load YAML file via yaml-cpp?](https://www.howtobuildsoftware.com/index.php/how-do/c7Cl/c-yaml-cpp-how-to-load-yaml-file-via-yaml-cpp)
