# C#使用OpenCvSharp4库读取本地视频
## OpenCvSharp4库
OpenCvSharp4库是一个基于.Net封装的OpenCV库，Github源代码地址为：[https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)，里面有关于Windows下安装`OpenCvSharp4库`的描述，如下图所示：
![OpenCvSharp4库](https://img-blog.csdnimg.cn/direct/46eb359cd4bc40929499a00504703119.png)
## 视频资源地址
视频资源可以到[https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/test_video.mp4](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/test_video.mp4)下载

## 新建一个C# .Net控制台程序OpenCVExample，并安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包，或者直接安装OpenCvSharp4.Windows
![安装OpenCvSharp4和OpenCvSharp4.runtime.win两个NuGet包](https://img-blog.csdnimg.cn/direct/651f1a8417f44be1b202dee87d859e21.png)
## C#示例代码
C#示例代码如下，如下代码展示了怎么使用VideoCapture和Cv2.ImShow读取本地视频：
```CSharp
using OpenCvSharp;
using System;

namespace OpenCVExample
{
    public class Program
    {
        /// <summary>
        ///  读取本地视频并逐帧显示
        /// </summary>
        public static void ReadLocalVideo()
        {
            VideoCapture cap = new VideoCapture("Resources\\test_video.mp4");   // 读取本地视频文件
            if (!cap.IsOpened())
            {
                Console.WriteLine("VidepCapture open failed");
                return;
            }
            while (true)
            {    // 如果cap初始化成功
                Mat frame = new Mat();
                if (cap.Read(frame))    // 抓取和解码，返回下一帧
                {
                    Cv2.ImShow("video Result", frame);
                    if (Cv2.WaitKey(1) == (int)('q'))   // 用户输入q键退出
                    {
                        break;
                    }
                }
                else
                {
                    // 当视频播放完毕，也退出
                    Console.WriteLine("there is no frame to read");
                    break;
                }

            }
        }

        static void Main(string[] args)
        {
            ReadLocalVideo();
           
            //Console.ReadKey();
        }
    }
}

```

## 运行结果
程序运行结果如下图所示：
![读取本地视频运行结果](https://img-blog.csdnimg.cn/direct/d21447d21d2a4aa2a2574cf9c0e1ed24.png)
## 参考资料
- [https://github.com/shimat/opencvsharp](https://github.com/shimat/opencvsharp)
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://youtu.be/WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
