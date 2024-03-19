# OpenCV-python中5个基础函数-灰度化、高斯模糊、Canny边缘检测、膨胀和腐蚀
使用[OpenCV](https://opencv.org/)可以对彩色原始图像进行基本的处理，涉及到5个常用的处理：
- 1. 灰度化
- 2. 模糊处理
- 3. Canny边缘检测
- 4. 膨胀
- 5. 腐蚀
本例中我们采用数字图像处理中经常用到的一副标准图像`lena.png`作为测试图像，如下图所示:
![资源](https://img-blog.csdnimg.cn/direct/8b2e7e64e35a43979733b9ce3e090b55.png)
具体资源下载地址为：[lena图像下载地址](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/lena.png)
![lena.png](https://img-blog.csdnimg.cn/direct/54eca397c6fb402d8659ee952b0e773c.png#pic_center)


之前写过一篇博文：[opencv中初学者必须了解的5个函数-灰度化、模糊、Canny边缘检测、膨胀和侵蚀](https://ccf19881030.blog.csdn.net/article/details/135722118)，是用C++ OpenCV实现的，对应代码如下：
```cpp
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

///// Basic OpenCV Functions ////////
int main()
{
	std::string imgPath = "Resources/test.png";
	//std::string imgPath = "images/lena.jpg";

	cv::Mat imgSrc;
	cv::Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;
	imgSrc = cv::imread(imgPath);	// 读取原图像
	cvtColor(imgSrc, imgGray, COLOR_BGR2GRAY);	// 将原图转换成灰度图

	// 高斯模糊算法
	GaussianBlur(imgSrc, imgBlur, Size(3, 3), 3, 0);

	// Canny边缘检测算法
	Canny(imgBlur, imgCanny, 25, 75);

	// dilate and erode - 膨胀和腐蚀
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);	// 膨胀图

	erode(imgDilate, imgErode, kernel);	// 腐蚀化


	cv::imshow("Image Source", imgSrc);			// 显示原图
	cv::imshow("Image Gray", imgGray);			// 显示灰度图
	cv::imshow("Image Gaussian Blur", imgBlur); // 显示高斯模糊处理后的图像
	cv::imshow("Image Canny Detect", imgCanny);	// 显示Canny边缘检测后的图像
	cv::imshow("Image Dilation", imgDilate);	// 膨胀
	cv::imshow("Image Erode", imgErode);		// 腐蚀

	cv::waitKey(0);

	return 0;
}
```

对应的Python代码如下：
```python
import cv2
import numpy as np

img = cv2.imread("Resources/lena.png")  # 读取本地图像
kernel = np.ones((5,5),np.uint8)    # 生成一个全为5*5的矩阵，值都为1

imgGray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)  # 将原图像转换成灰度图
imgBlur = cv2.GaussianBlur(imgGray,(7,7),0) # 将灰度图高斯模糊处理
imgCanny = cv2.Canny(img,150,200)   # 将原图进行Canny边缘检测
imgDialation = cv2.dilate(imgCanny,kernel,iterations=1) # 膨胀处理
imgEroded = cv2.erode(imgDialation,kernel,iterations=1) # 腐蚀处理

cv2.imshow("Image", img)    # 显示原图
cv2.imshow("Gray Image",imgGray)    # 显示灰度图
cv2.imshow("Blur Image",imgBlur)    # 显示高斯模糊图像
cv2.imshow("Canny Image",imgCanny)  # Canny边缘检测后的图像
cv2.imshow("Dialation Image",imgDialation)  # 膨胀图
cv2.imshow("Eroded Image",imgEroded)    # 腐蚀图
cv2.waitKey(0)  # 永久等待按键输入

cv2.destroyAllWindows() # 销毁所有窗口
```
运行结果如下：
![test1](https://img-blog.csdnimg.cn/direct/450d25de16db4bc298405d9a8d65b83b.png)
![canny](https://img-blog.csdnimg.cn/direct/480c4d40d46d4215a5e182df650da15c.png)
![Erode](https://img-blog.csdnimg.cn/direct/0f0b9e08769a45b19ca40f5e886c9fe4.png)
## 参考资料
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://youtu.be/WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
