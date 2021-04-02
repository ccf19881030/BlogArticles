## [QGraphicsView框架下，图元的操作（缩放，平移，旋转）](https://blog.csdn.net/EddyXie/article/details/91489519)
关于QGraphicsView框架的结构和技术细节，就不多做介绍了，向大家推荐两篇博客，有兴趣的可以自己看一下：

https://blog.csdn.net/abcvincent/article/details/71773700

https://blog.51cto.com/9291927/1879128

这里我们讲一下QGraphicsView框架下，图元的操作

QGraphicsView框架下，想要旋转，平移，缩放窗口中的图元，一般有两种思路：

1. 操作View，概念类似于旋转摄像头，从而获取对场景Scene的不同观察结果，这样操作的好处是，场景中的图元本质上没有发生任何的变化，仅仅改变了View的计算矩阵，效率非常高，并且，如果该Scene被多个View绑定观察，对单独一个view的操作，将不会影响到别的view的观察结果

2.操作Scene中所有的图元Item或者直接操作单个图元Item，概念类似于真实改变了场景中的各个物体的摆放方式，该方法使用的场合位：当一个场景，被多个view观察的时候，场景中的某一个变化操作，需要被这多个view同时观察到

这里我们详细先介绍一下第二种方法的处理，而第一种方法，我将会在下一篇文章中，做详细的介绍：

1. 图元的缩放：
图元的缩放方式，即直接调用图元自身的void QGraphicsItem::setScale(qreal factor)方法，传参为对调用方法的图元大小的缩放比， 但需要注意的是，该方法的缩放基准是固定的，也就是说，如果连续两次调用该方法，但是传参的数字一样的话，第二次的调用将不会改变图元的大小，如果我们想持续按一个比例缩小图元，可以通过调用该图元的qreal QGraphicsItem::scale()方法，获取上一次设置的缩放比，然后再乘上我们新设置的缩放比，示例代码：
void MyScale(qreal factor){
        //每次调用，在原先的缩放比上，乘上新的缩放比
        MyItem->setScale(MyItem->scale() * factor)；
}

2.图元的平移
图元的平移有两种方法，调用图元自身的void QGraphicsItem::setPos(qreal x, qreal y)或者void QGraphicsItem::moveBy(qreal dx, qreal dy)，两个方法，setPos方法为绝对定位，其传参的x与y坐标值，属于场景Scene的坐标，如果调用的时候，坐标来源于view的鼠标点击事件的坐标，需要调用mapToScene()将view坐标值转换到场景坐标。而moveBy方法，则是相对定位，官方文档的介绍是，moveBy等同于setPos(pos() + QPointF(dx, dy))，所以传参为移动矢量的坐标

3.图元的旋转
图元的旋转方法，调用图元自身的void QGraphicsItem::setRotation(qreal angle)方法，传参为旋转的角度值(不是弧度制，是角度制)，但是该方法使用需要有两点注意，首先，每次旋转的时候，旋转中心默认为图元的左上角，所以如果需要围绕图元兹省的中心旋转，需要再旋转之前，调用图元自身的void QGraphicsItem::setTransformOriginPoint(qreal x, qreal y)方法，将旋转中心设置为图元的中心，该方法传参的坐标值为图元自身的坐标系，然后，setRotation设置的值的基准也是不变的，也就是说，连续两次调用该方法，都传入相同的参数值，图元只会旋转一次，所以可以通过调用qreal QGraphicsItem::rotation()方法，获取上一次设置的角度，示例代码：
void MyRotation(qreal angel){
        //设置旋转中心为操作图元的中心
        MyItem->setTransformOriginPoint(MyItem->boundingRect().center().x(), MyItem->boundingRect().center().y());
        //每次调用，在原先的旋转角度上，加上新的旋转角度
        MyItem->setRotation(MyItem->rotation() + angel)；
}
