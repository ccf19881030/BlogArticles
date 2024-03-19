# 使用Opencv-python库读取图像、本地视频和摄像头实时数据
Python中使用OpenCV读取图像、本地视频和摄像头数据很简单，
首先需要安装Python，然后安装Opencv-python库
```
pip install opencv-python
```
然后在PyCharm或者VScode等IDE中输入对应的Python代码

## 一、使用opencv-python读取图像
![Lena.jpg](https://img-blog.csdnimg.cn/direct/3e4f4a44c5d44248ae000d107c73be90.jpeg#pic_center)
比如说我们要显示上面这幅数字图像处理中的`lena.jpg`这幅图像，读取的python代码如下所示：
```python
import cv2

# Load an image using imread
img = cv2.imread("images/lena.jpg")
# img = cv2.imread("Resources/test.png")
# Display image
cv2.imshow("Lena image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
```
在Python中运行结果如下：
![显示图像](https://img-blog.csdnimg.cn/direct/8c7a4b3f022a4de5881b0eb6077b009f.png)
## 使用opencv-python读取本地视频
Opencv-python在线文档中有关于的Python示例代码：[https://docs.opencv.org/4.9.0/dd/d43/tutorial_py_video_display.html](https://docs.opencv.org/4.9.0/dd/d43/tutorial_py_video_display.html)
```python
import numpy as np
import cv2 as cv
cap = cv.VideoCapture('vtest.avi')
while cap.isOpened():
    ret, frame = cap.read()
    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    cv.imshow('frame', gray)
    if cv.waitKey(1) == ord('q'):
        break
cap.release()
cv.destroyAllWindows()
```
![test_video.mp4](https://img-blog.csdnimg.cn/direct/e143d5f5bb884c50bf4ab534465ab3b8.png)
视频资源可以到[https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/test_video.mp4](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours/blob/master/Resources/test_video.mp4)下载
相关的显示本地视频的Python代码如下：
```python
import cv2

frameWidth = 640
frameHeight = 480
cap = cv2.VideoCapture("Resources/test_video.mp4")
while True:
    success, img = cap.read()
    img = cv2.resize(img, (frameWidth, frameHeight))
    cv2.imshow("Result", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
```
相应的运行结果如下图所示：
![读取本地视频并显示](https://img-blog.csdnimg.cn/direct/8f11bcf4c7124e23a50073006198f8e8.png)


## 三、使用opencv-python读取摄像头数据并实时显示
使用opencv-python读取摄像头数据是非简单，opencv-python文档[tutorial_py_video_display](https://docs.opencv.org/4.9.0/dd/d43/tutorial_py_video_display.html)里面有对应的示例代码，如下：
```python
import numpy as np
import cv2 as cv
cap = cv.VideoCapture(0)
if not cap.isOpened():
    print("Cannot open camera")
    exit()
while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    # Our operations on the frame come here
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    # Display the resulting frame
    cv.imshow('frame', gray)
    # 等待1毫秒，如果用户按下q键则退出循环
    if cv.waitKey(1) == ord('q'):
        break
# When everything done, release the capture
cap.release()
cv.destroyAllWindows()
```
我本地读取摄像头数据并显示的python代码如下：
```python
import cv2

frameWidth = 640
frameHeight = 480
cap = cv2.VideoCapture(0)
# cap.set(3, frameWidth)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, frameWidth)
# cap.set(4, frameHeight)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, frameHeight)
# cap.set(10, 50)
cap.set(cv2.CAP_PROP_BRIGHTNESS, 50)

while True:
    success, img = cap.read()
    cv2.imshow("Result", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
```
运行结果如下图所示：
![使用opencv-python读取本地摄像头视频](https://img-blog.csdnimg.cn/direct/897597e5e2c74280b57b59031d0de2f7.png)
## 参考资料
- [LEARN OPENCV in 3 HOURS with Python | Including 3xProjects | Computer Vision](https://www.youtube.com/watch?v=WQeoO7MI0Bs)
- [Learn-OpenCV-in-3-hours](https://github.com/murtazahassan/Learn-OpenCV-in-3-hours)
- [OpenCV tutorial](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
- [tutorial_py_video_display](https://docs.opencv.org/4.9.0/dd/d43/tutorial_py_video_display.html)
- [LEARN OPENCV C++ in 4 HOURS | Including 3x Projects | Computer Vision](https://www.youtube.com/watch?v=2FYm3GOonhk)
- [murtazahassan/Learn-OpenCV-cpp-in-4-Hours](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours)
- [OpenCV官网](https://opencv.org/)
- [OpenCV-Get Started](https://opencv.org/get-started/)
- [OpenCV Github仓库源代码](https://github.com/opencv/opencv)
