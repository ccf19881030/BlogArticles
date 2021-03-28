  ## [Qt 之镜像旋转(https://blog.csdn.net/liang19890820/article/details/51858986)
  接口
关于镜像旋转，QImage中有对应的接口，可以通过设定水平、垂直方向旋转：

QImage QImage::mirrored(bool horizontal = false, bool vertical = true) const
返回图片的镜像，取决于水平和垂直设置为true或false。

注意：原始图像没有发生改变。

```cpp
QImage image(":/Images/logo");
QImage mirroredImage = image.mirrored(false, false);
QPixmap pixmap = QPixmap::fromImage(mirroredImage);

ui->label->setPixmap(pixmap);
```
