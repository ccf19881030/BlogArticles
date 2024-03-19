# C#中使用OpenCvSharp4绘制直线、矩形、圆、文本
继之前的[Python中使用Opencv-python库绘制直线、矩形、圆、文本](https://blog.csdn.net/ccf19881030/article/details/136001999)和[VC++中使用OpenCV绘制直线、矩形、圆和文字](https://editor.csdn.net/md/?articleId=136002716)，将之前的Python和C++示例代码翻译成C#语言，很简单，还是借用[OpenCvSharp4](https://github.com/shimat/opencvsharp)库中的Line、Rectangle、Circle、PutText，值得一提的是[https://github.com/opencv/opencv](https://github.com/opencv/opencv)以及[OpenCvSharp4](https://github.com/shimat/opencvsharp)库和[Opencv-python](https://docs.opencv.org/3.4/d6/d00/tutorial_py_root.html)的函数基本相同。

## 一、OpenCvSharp4库
OpenCvSharp4库是一个基于.Net封装的OpenCV库，Github源代码地址为：[https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)，里面有关于Windows下安装`OpenCvSharp4库`的描述，如下图所示：
![OpenCvSharp4库](https://img-blog.csdnimg.cn/direct/46eb359cd4bc40929499a00504703119.png)
## 二、C#中使用OpenCvSharp4绘制直线、矩形、圆、文本
## 1、使用VS2022创建一个C# .Net控制台程序，项目命名为OpenCVExample

## 2、安装OpenCvSharp4库
安装`OpenCvSharp4`和`OpenCvSharp4.runtime.win`两个`NuGet`包，或者直接安装`OpenCvSharp4.Windows`
![安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包](https://img-blog.csdnimg.cn/direct/b452fee5b3304cf6852ad77ae1d8672a.png)
## 3、使用OpenCvSharp4绘制直线、矩形、圆、文本
对应的C#代码如下：
```csharp
using OpenCvSharp;
using System;

namespace OpenCVExample
{
    public class Program
    {
    	/// <summary>
        /// 绘制直线、矩形、圆、文字
        /// </summary>
        public static void DrawShapes()
        {
            Mat img = new Mat(512, 512, MatType.CV_8UC3, new Scalar(0, 0, 0)); // 高度512，宽度512，颜色为黑色
            int height = img.Height;
            int width = img.Width;
            int channels = img.Channels();
            Console.WriteLine("height: {0}, width: {1}, channels: {2}", height, width, channels);

            // 在图像左上角原点(0,0)到右下角画一条绿色的直线，线条厚度为3
            Cv2.Line(img, new Point(0, 0), new Point(height, width), new Scalar(0, 255, 0), 3);
            // 在左上角顶点(0,0)和右下角(250,350)处绘制一个红色矩形，边界线条厚度为2
            Cv2.Rectangle(img, new Point(0, 0), new Point(250, 350), new Scalar(0, 0, 255), 2);
            // 以(400,50)为中心，绘制半径为30的圆，颜色为青色（绿＋蓝＝青（Cyan)）
            Cv2.Circle(img, new Point(400, 50), 30, new Scalar(255, 255, 0), 2);
            // 在(350,300)处绘制文字，字体为FONT_HERSHEY_COMPLEX，比例为1，颜色为黄色，厚度为2
            Cv2.PutText(img, "OpenCV", new Point(350, 300), HersheyFonts.HersheyComplex, 1, new Scalar(0, 255, 255), 2);

            Cv2.ImShow("Image", img);
            Cv2.WaitKey(0); // 永久等待用户输入，直到用户按下按键结束
            Cv2.DestroyAllWindows();    // 销毁所有窗口
        }   
        static void Main(string[] args)
        {
            DrawShapes();
        }
    }
}
```

## 4、程序运行结果
在Visual Studio 2022中运行上述代码，结果如下：
![C#中使用OpenCvSharp4绘制直线、矩形、圆、文本](https://img-blog.csdnimg.cn/direct/ecc847ac6e084a1a9aa088522e5c31e0.png)
## 三、参考资料
- [OpenCvSharp4](https://github.com/shimat/opencvsharp)
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [murtazahassan/Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://youtu.be/WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
- [OpenCV官网](https://opencv.org/)
- [Python中使用Opencv-python库绘制直线、矩形、圆、文字](https://editor.csdn.net/md/?articleId=136001999)
