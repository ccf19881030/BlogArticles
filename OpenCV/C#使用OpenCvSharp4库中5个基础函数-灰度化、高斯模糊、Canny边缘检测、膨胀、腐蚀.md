# C#使用OpenCvSharp4库中5个基础函数-灰度化、高斯模糊、Canny边缘检测、膨胀、腐蚀
使用[OpenCV](https://opencv.org/)可以对彩色原始图像进行基本的处理，涉及到5个常用的处理：
- 1. 灰度化
- 2. 模糊处理
- 3. Canny边缘检测
- 4. 膨胀
- 5. 腐蚀

## 1、测试图像lena.jpg
本例中我们采用数字图像处理中经常用到的一副标准图像`lena.png`作为测试图像，如下图所示:
![资源](https://img-blog.csdnimg.cn/direct/8b2e7e64e35a43979733b9ce3e090b55.png)
具体资源下载地址为：[lena图像下载地址](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/lena.png)
![lena.png](https://img-blog.csdnimg.cn/direct/54eca397c6fb402d8659ee952b0e773c.png#pic_center)
## 2、使用Visual Studio 2022创建一个基于C# .Net控制台的程序
首先我们新建一个基于C# .Net控制台的程序，项目名为`OpenCVExample`，然后把`lena.jpg`拷贝到`E:\SoftDevelop\CPlus\VS2022Projects\CSharpExamples\OpenCVExample\OpenCVExample\bin\Debug\images`对应目录下，如下图所示：
![项目资源所在目录](https://img-blog.csdnimg.cn/direct/a763f19de6f149e3b95ded7ac361d543.png)
## 安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包，或者直接安装OpenCvSharp4.Windows包
![安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包](https://img-blog.csdnimg.cn/direct/6db519b25e834ebeac53975b29d8174a.png)
安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包之后，`packages.config`配置文件如下：
```config
<?xml version="1.0" encoding="utf-8"?>
<packages>
  <package id="OpenCvSharp4" version="4.9.0.20240103" targetFramework="net48" />
  <package id="OpenCvSharp4.runtime.win" version="4.9.0.20240103" targetFramework="net48" />
  <package id="System.Buffers" version="4.5.1" targetFramework="net48" />
  <package id="System.Memory" version="4.5.5" targetFramework="net48" />
  <package id="System.Numerics.Vectors" version="4.5.0" targetFramework="net48" />
  <package id="System.Runtime.CompilerServices.Unsafe" version="6.0.0" targetFramework="net48" />
  <package id="System.ValueTuple" version="4.5.0" targetFramework="net48" />
</packages>
```

## C#示例代码
对应的C#代码如下：
```CSharp
using OpenCvSharp;

namespace OpenCVExample
{
    public class Program
    {
        /// <summary>
        /// OpenCV的5个基础函数-灰度化、高斯模糊、Canny边缘检测、膨胀、腐蚀
        /// </summary>
        public static void FiveBasicFunction()
        {
            Mat img = Cv2.ImRead("images/lena.jpg");    // 读取图像
            Mat grayImg = new Mat();
            Cv2.CvtColor(img, grayImg, ColorConversionCodes.BGR2GRAY);
            Mat blurImg = new Mat();
            Cv2.GaussianBlur(grayImg, blurImg, new Size(7, 7), 0);
            Mat cannyImg = new Mat();
            Cv2.Canny(blurImg, cannyImg, 150, 200);
            Mat dialationImg = new Mat();
            Mat kernel = new Mat(5, 5, MatType.CV_8UC1);
            Cv2.Dilate(blurImg, dialationImg, kernel);
            Mat erodeImg = new Mat();
            Cv2.Erode(dialationImg, erodeImg, kernel);


            Cv2.ImShow("Image", img);   // 显示原图像
            Cv2.ImShow("Gray Image", grayImg);  // 显示灰度图像
            Cv2.ImShow("Blur Image", blurImg);  // 显示高斯模糊图像
            Cv2.ImShow("Canny Image", cannyImg);    // 显示Canny边缘检测图像
            Cv2.ImShow("Dialation Image", dialationImg);    // 膨胀图
            Cv2.ImShow("Erode Image", erodeImg);    // 腐蚀图


            Cv2.WaitKey(0);

            Cv2.DestroyAllWindows();
        }
       
        static void Main(string[] args)
        {
            FiveBasicFunction();
           
            //Console.ReadKey();
        }
    }
}
```

## 程序运行结果
在VS2022中运行上述代码，结果如下图所示：
![原图和灰度图像](https://img-blog.csdnimg.cn/direct/53db0a5d576544489c26ea67cd0c67fb.png)
![高斯模糊图像和Canny边缘检测图像](https://img-blog.csdnimg.cn/direct/63439642a116434a845c5d7e6fa6f3aa.png)

![膨胀图和腐蚀图像](https://img-blog.csdnimg.cn/direct/3986206e3005452aa04e40cc109407b7.png)

## 参考资料
- [https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://youtu.be/WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
