# VC++中使用OpenCV进行形状和轮廓检测
在VC++中使用OpenCV进行形状和轮廓检测，轮廓是形状分析以及物体检测和识别的有用工具。如下面的图像中`Shapes.png`中有三角形、矩形、正方形、圆形等，我们如何去区分不同的形状，并且根据轮廓进行检测呢？
![Shapes..png](https://img-blog.csdnimg.cn/direct/94ac54b254c745aa9c662b33db298405.png#pic_center)
原图下载地址为：[https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours/blob/main/Resources/shapes.png](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours/blob/main/Resources/shapes.png)
1、首先我们对原始图像进行预处理，将原始图形灰度化、高斯模糊、Canny边缘检测、膨胀化处理，最后得到一副膨胀的图形
2、基于这幅膨胀的图像，我们调用`findContours`函数从膨胀化的二值图像中检索出所有的轮廓，结果放到`vector<vector<Point>> contours`数组中
3、遍历每一个轮廓多边形，首选计算轮廓面积，过滤那些面积特别小的轮廓（比如面积小于1000则不处理，例如上图中的那个黑色的圆点），消除噪声；计算轮廓周长(封闭的或者非封闭的)或曲线长度，以指定精度逼近多边形曲线，计算顶点集合或灰度图像的非零像素的右上边界矩形，获取边界包围盒；然后轮廓多边形的角落（顶点）个数objCor，根据objCor判断轮廓多边形的形状类型，特别注意矩形和正方形的区别，我们根据轮廓的宽高比来区分，当轮廓宽高比大于0.95或者小于1.05时我们可以认定轮廓为正方形
4、最后我们在第三步基础上，绘制轮廓或填充轮廓，颜色为粉色；绘制边界包围盒，颜色为绿色；在边界包围盒左上方往上5像素的位置，绘制其形状的描述文字

## C++示例代码
示例代码如下：
```cpp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Color Detection  //////////////////////
// 获取轮廓边界、绘制边界包围盒、形状描述
void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// 从膨胀化的二值图像中检索轮廓
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());	// 逼近的多边形曲线，接近contours轮廓多边形		
	vector<Rect> boundRect(contours.size());	// contours轮廓多边形的边界包围盒

	// 遍历每一个轮廓多边形
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);	// 计算轮廓的面积
		cout << area << endl;
		string objectType;

		if (area > 1000)	// 过滤那些面积特别小的轮廓，消除噪声
		{
			float peri = arcLength(contours[i], true);	// 计算轮廓周长(封闭的或者非封闭的)或曲线长度
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);	// 以指定精度逼近多边形曲线
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);	// 计算顶点集合或灰度图像的非零像素的右上边界矩形，获取边界包围盒

			int objCor = (int)conPoly[i].size();	// 轮廓多边形的角落（顶点）个数
			// 根据objCor判断轮廓多边形的形状类型
			if (objCor == 3) {
				objectType = "Tri";	// 三角形
			} else if (objCor == 4)	{ // 四边形
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;	// 边界包围盒的宽高比：宽度/高度
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) {	// 边界包围盒宽高比大于0.95，或者小于1.05，则认为是正方形
					objectType = "Square";	// 正方形
				} else {
					objectType = "Rect";	// 矩形
				}
			} else if (objCor > 4) {
				objectType = "Circle";	// 圆形
			}

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);	// 绘制轮廓或填充轮廓，颜色为粉色
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);	// 绘制边界包围盒，颜色为绿色
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);	// 在边界包围盒左上方往上5像素的位置，绘制其形状的描述文字
		}
	}
}


int main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);	// 灰度图
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);	// 高斯模糊处理
	Canny(imgBlur, imgCanny, 25, 75);	// Canny边缘检测算法
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);	// 膨胀图

	// 基于膨胀图，在原图上绘制轮廓边界、绘制边界包围盒以及形状描述
	getContours(imgDil, img);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);

	waitKey(0);

	return 0;
}
```
运行结果如下图所示：
![运行结果](https://img-blog.csdnimg.cn/direct/da23743cfa9b43fd8ec2a916fd2286d0.png)
## 参考资料
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://youtu.be/WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
