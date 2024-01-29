## 一、OpenCvSharp4库
OpenCvSharp4库是一个基于.Net封装的OpenCV库，Github源代码地址为：[https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)，里面有关于Windows下安装`OpenCvSharp4库`的描述，如下图所示：
![OpenCvSharp4库](https://img-blog.csdnimg.cn/direct/46eb359cd4bc40929499a00504703119.png)
## 二、C#使用OpenCvSharp4库读取电脑摄像头数据并实时显示
## 1、使用VS2022创建一个C# .Net控制台程序，项目命名为OpenCVExample

## 2、安装OpenCvSharp4库
安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包，或者直接安装OpenCvSharp4.Windows
![安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包](https://img-blog.csdnimg.cn/direct/b452fee5b3304cf6852ad77ae1d8672a.png)

## 4、C#使用代码-使用OpenCvSharp4库读取电脑摄像头数据并实时显示
相关示例代码如下：
```CSharp
using OpenCvSharp;
using System;

namespace OpenCVExample
{
    public class Program
    {
        /// <summary>
        /// 从摄像头实时读取每帧图像，并实时显示
        /// </summary>
        public static void ReadFrameFromWebCam()
        {
            VideoCapture cap = new VideoCapture(0);
            cap.Set(3, 640);   // 设置宽度为640像素
            cap.Set(4, 480);   // 设置高度为480像素
            cap.Set(10, 70);    // 设置亮度为70
            if (!cap.IsOpened())    // 如果摄像头打开失败
            {
                Console.WriteLine("VidepCapture open failed");
                return;
            }
            while (true)
            {    // 如果cap初始化成功
                Mat frame = new Mat();
                if (cap.Read(frame))    // 抓取和解码，返回下一帧
                {
                    Cv2.ImShow("video Result", frame);  // 显示当前帧的图像数据
                    if (Cv2.WaitKey(1) == (int)('q'))   // 用户输入q键退出
                    {
                        break;
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            ReadFrameFromWebCam();
        }
    }
}
```

## 5、程序运行结果
运行步骤4中的C#代码，运行结果如下图所示：

![运行结果](https://img-blog.csdnimg.cn/direct/2e5f71b9a2224ade8ae3529bebc595a8.png)
## 三、参考资料
- [https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://youtu.be/WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
