# 使用Opencv-python对图像进行缩放和裁剪
在Python中使用`opencv-python`对图像进行缩放和裁剪非常简单，可以使用`resize`函数对图像进行缩放，使用对`cv2.typing.MatLike`操作，如img = cv2.imread("Resources/shapes.png")和img[46:119,352:495] 进行裁剪，
如有下面一副图像：
![shapes.png](https://img-blog.csdnimg.cn/direct/12c74b55868649e9a4f6829c1bc6dc77.png#pic_center)
可以去[https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/shapes.png](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/shapes.png)地址下载

使用Opencv-python对图像进行缩放和裁剪的示例代码如下所示：
```python
import cv2
import numpy as np

img = cv2.imread("Resources/shapes.png")    # 读取本地图像
print(img.shape)

imgResize = cv2.resize(img,(1000,500))  # 将原图缩放成1000*500
print(imgResize.shape)  # 打印缩放后的图像大小

imgCropped = img[46:119,352:495]    # 对原图进行裁剪

cv2.imshow("Image",img) # 显示原图
cv2.imshow("Image Resize",imgResize)    # 显示缩放后的图像
cv2.imshow("Image Cropped",imgCropped)  # 显示对原图裁剪后的图像

cv2.waitKey(0)  # 永久等待按键输入
cv2.destroyAllWindows()
```

运行结果如下图所示：
![运行结果](https://img-blog.csdnimg.cn/direct/aa80bfda462e4c1eb086ed5879b171ae.png)
![测试结果](https://img-blog.csdnimg.cn/direct/788607074c87419482ddde0ce058f78e.png)
## 参考资料
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://www.youtube.com/watch?v=WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
- [OpenCV官网](https://opencv.org/)
- [OpenCV-Get Started](https://opencv.org/get-started/)
- [OpenCV Github仓库源代码](https://github.com/opencv/opencv)
