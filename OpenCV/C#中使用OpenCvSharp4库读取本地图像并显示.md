# C#中使用OpenCvSharp4库读取本地图像并显示
[OpenCvSharp4](https://github.com/shimat/opencvsharp)是基于.NET 的 OpenCV 包装器，[OpenCV](https://github.com/opencv/opencv)源代码是采用C和C++写的，目前对于C++和Python开发者相对来说比较友好，对于Python开发者而言官方提供了[opencv-python](https://github.com/opencv/opencv-python)使用。
首选我们使用Visual Studio 2022创建一个.Net控制台程序`ReadImageUseOpenCvSharp4`，然后安装`OpenCvSharp4`安装包，我们在Visual Studio 2022中依次点击【项目】菜单->【管理 NuGet 程序包(N)】，如下面的Gif动态图所示：
![Visual Studio 2022中C#控制台项目安装OpenCvSharp4库](https://img-blog.csdnimg.cn/direct/0e3db31157274ab2943a02fa5a6d8bb5.gif#pic_center)
可以看到安装完`OpenCvSharp4`包之后我们的App.Config文件中有了相关的依赖包，目前的最新版本是4.9.0.20240103，如下图所示：
![OpenCvSharp4![包](https://img-blog.csdnimg.cn/direct/aa58bb3adc484ed58565a72971e9169a.png)


接下来我们在C#项目中使用[OpenCvSharp4](https://github.com/shimat/opencvsharp)库读取本地图片并显示，
首先我们下载一副数字图像处理中常用的[lena.png](https://upload.wikimedia.org/wikipedia/en/7/7d/Lenna_%28test_image%29.png?download)
![维基百科中的lena图片，512*512](https://img-blog.csdnimg.cn/direct/5a4a0e1557c64c7da1bef4a945864706.png)
将下载后的图像重命名为`Lena.png`放到项目对应目录，比如`E:\SoftDevelop\CPlus\VS2022Projects\CSharpExamples\ReadImageUseOpenCvSharp4\ReadImageUseOpenCvSharp4\bin\Debug\images`目录下，如下图所示：

![Lena.png](https://img-blog.csdnimg.cn/direct/c87af161a52d488288cf1549c555f6b8.png)

C#中使用OpenCvSharp4库读取本地图像并显示很简单，对应的C#代码如下：
```CSharp
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;  // 导入OpenCvSharp命名空间

namespace ReadImageUseOpenCvSharp4
{
    public class Program
    {
        static void Main(string[] args)
        {
            Mat img = Cv2.ImRead("images/lena.png");    // 读取本地图像
            Cv2.ImShow("Lena Image", img);

            Cv2.WaitKey(0); // 永久等待，直到用户输入按键退出

            Cv2.DestroyAllWindows();    // 销毁所有窗口
        }
    }
}
```
直接运行以上代码发现报错了，错误如下：
![运行程序报错](https://img-blog.csdnimg.cn/direct/fd355701bc56488985b3196809fb0001.png)
发现除了安装[OpenCvSharp4](https://github.com/shimat/opencvsharp)这个包之外，还得安装`OpenCvSharp4.runtime.win`这个依赖包，如下图所示：
![OpenCvSharp4.runtime.win](https://img-blog.csdnimg.cn/direct/0e2949a6ccad41cc9bed91f02345b6d6.png)
这一点在[https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)这个源代码地址首页有相关描述，如下图所示：
![Windows下安装OpenCvSharp4](https://img-blog.csdnimg.cn/direct/bc287b509127487b98fd157205ac7e93.png)
有关Windows下安装[OpenCvSharp4](https://github.com/shimat/opencvsharp)包可以直接将`OpenCvSharp4`和`OpenCvSharp4.runtime.win`这两个NuGet包添加到项目中。你也可以使用`OpenCvSharp4.Windows`代替。

## 运行程序
接下来运行上述代码，如下图所示：
![运行结果](https://img-blog.csdnimg.cn/direct/37481833e4bc45fe91a0ab7547c62eb2.png)
## 参考资料
- [https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)
- [C# 无法加载 DLL“OpenCvSharpExtern](https://blog.csdn.net/weixin_42832191/article/details/108663110)
