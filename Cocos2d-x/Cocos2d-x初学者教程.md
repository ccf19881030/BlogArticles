本文翻译自[https://www.raywenderlich.com/](https://www.raywenderlich.com/)网站上Guanghui Qu写的2015年4月30号的一篇博文[Cocos2d-x Tutorial for Beginners](https://www.raywenderlich.com/1848-cocos2d-x-tutorial-for-beginners)，他使用的Cocos2d-x的版本是[ version 3.5](http://www.cocos2d-x.org/filedown/cocos2d-x-3.5.zip)。另外，关于在Windows10下使用Cocos2d-x 3.17.2构建项目的，可以参考我之前写的博客：[Win10+Python2.7.14+cocos2d-x-3.17.2+VS2017环境搭建](https://blog.csdn.net/ccf19881030/article/details/108807428)


# Cocos2d-x初学者教程
在此Cocos2d-x教程中，学习如何使用C ++为iOS，Android等创建基本的跨平台游戏！
Guanghui Qu
2015年4月30日·文章（30分钟）·初学者
![Cocos2d-x](https://img-blog.csdnimg.cn/20200930092514737.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

Cocos2d-x是一种快速，强大且易于使用的开源2D游戏引擎。

它与Apple的[Sprite Kit](http://www.raywenderlich.com/sprite-kit-tutorials)非常相似，但具有一个关键优势– Cocos2d-x是跨平台的。

这意味着您可以使用一组代码来制作适用于iOS，Android，Windows Phone，Mac OS X，Windows桌面和Linux的游戏。 对于独立游戏开发者来说，这是意义巨大的！

在本教程中，您将学习如何使用C ++在Cocos2d-x中创建一个简单的2D游戏。 是的-会有忍者！ ：]

`**注意：本教程假定您了解C ++开发的基础知识。 如果您不熟悉C ++，请务必先阅读有关该主题的书。**`

## 入门
在[www.cocos2d-x.org/download](http://www.cocos2d-x.org/download)下载最新版本的Cocos2d-x； 本教程使用[3.5版](http://cocostudio.download.appget.cn/Cocos2D-X/cocos2d-x-3.5.zip)。

将下载的文件放在您要存储Cocos2d-x安装的位置，例如在主目录中，然后将其解压缩。

打开`终端`并`cd`到刚解压缩的文件夹中。 例如，如果将项目放置在主目录中，请运行以下命令：
```shell
cd ~/cocos2d-x-3.5/
```
现在运行以下命令：
```shell
python setup.py
```
这将设置必要的Shell环境变量。 当它提示您配置特定于Android的变量`NDK_ROOT`，`ANDROID_SDK_ROOT`和`ANT_ROOT`时，只需按3次`Enter`回车键即可完成配置。

**注意：Cocos2D需要在您的机器上安装Python 2.7+。 如果不确定所用的Python版本，请在命令行上键入`python`，它将显示该版本（然后按Ctrl-D退出）。 如果您使用的是Python的旧版本，请在[python.org](https://www.python.org/downloads/)上安装最新版本的Python。**

如下面的屏幕截图所示，该脚本指示您执行另一个命令以完成设置：
![cocos2d-x-3.5](https://img-blog.csdnimg.cn/20200930093500263.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
**注意：根据您使用的shell，您可能会看到一些不同的输出。 在上面的屏幕截图中，安装程序包提示输入“ source / Users / rwenderlich / bash_profile”命令，因为我使用的是Bash，但例如如果我一直使用Zsh，它会提示我运行“ source /Users/rwenderlich/.zshrc”。**

按照脚本的输出说明输入命令。 节省时间的秘诀：您可以使用代字号（〜）代替`/ Users / your_user_name`，因此要保存击键，可以键入以下内容：
```shell
source ~/.zshrc  (or source ~/.bash_profile)
```
您输入的命令只是重新处理您的shell配置，并使其可以访问新变量。 现在，您可以从任何目录在终端中调用cocos命令。

运行以下命令以创建一个名为SimpleGame的C ++游戏模板：
```shell
cocos new -l cpp -d ~/Cocos2d-x-Tutorial SimpleGame
```

这将在您的主目录中创建一个名为`Cocos2d-x-Tutorial`的目录，并在其中创建一个名为`SimpleGame`的子目录，其中包含您项目的文件。

**注意：要了解可用的`cocos`子命令，请键入`cocos --help`或`cocos -h`。 您还可以通过添加“ --help”或“ -h”（例如`cocos new -h`）来了解任何子命令的选项，以查看`new`命令的选项。**
在`Finder`中双击`〜/ Cocos2d-x-Tutorial / SimpleGame / proj.ios_mac / SimpleGame.xcodeproj`以在`Xcode`中打开项目。

一旦进入`Xcode`，请确保`SimpleGame Mac`是活动方案，如下所示：
![SimpleGame Mac](https://img-blog.csdnimg.cn/20200930094053382.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

尽管`Cocos2d-x`能够为许多平台构建游戏，但在本教程中，您将重点关注制作`OS X`应用程序。 将这个项目移植到其他平台上是一件很简单的事情（是的，很简单！），这在本教程的结尾进行了简要讨论。

生成并运行您的应用，以全面了解模板项目：
![HelloWorld](https://img-blog.csdnimg.cn/20200930094147547.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 分辨率设置
默认情况下，Cocos2d-x游戏的名称为“ MyGame”，分辨率为960×640，但是这些细节很容易更改。
打开AppDelegate.cpp并在其中找到以下行
**AppDelegate::applicationDidFinishLaunching**:
```cpp
glview = GLViewImpl::create("My Game");
```
用以下代码替换该行：
```cpp
glview = GLViewImpl::createWithRect("SimpleGame", Rect(0,0, 480, 320), 1.0);
```
这会将应用程序的名称更改为“ SimpleGame”，并将其分辨率设置为480×320，以匹配模板随附的背景图片。

再次构建并运行您的应用，以查看新的较小的游戏：
![SimpleGame](https://img-blog.csdnimg.cn/20200930094850117.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
请注意，您传递给`createWithRect`的第三个参数-`1.0`。 此参数缩放帧，通常用于测试分辨率大于显示器的帧。 例如，要在小于1920×1080的监视器上测试1920×1080的分辨率，您可以传递`0.5`以将窗口缩放到960×540。

虽然对`createWithRect`的调用更改了台式机上的游戏框架，但在iOS设备上这种方式无法正常工作； 而是游戏的分辨率与屏幕尺寸匹配。 这是在iPhone 6上的外观：
![Big SimpleGame](https://img-blog.csdnimg.cn/20200930095001886.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
那么，您如何处理多种分辨率呢？ 在本教程中，您将基于960×640分辨率创建一组游戏资源，然后在运行时根据需要简单地按比例放大或缩小资产。
要实现这一点，请在内部添加以下代码:
`AppDelegate::applicationDidFinishLaunching`，位于在`Director上`调用`setDisplayStats`的行的上方：
```cpp
// 1
Size designSize = Size(480,320);
Size resourceSize = Size(960,640);
// 2
director->setContentScaleFactor(resourceSize.height / designSize.height);
director->getOpenGLView()->setDesignResolutionSize(
  designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
```
上面的代码是这样的：
- .在这里，您可以定义`designSize`（创建游戏逻辑时要使用的尺寸）和`resourceSize`（您所有艺术资产所基于的尺寸）。
- 2.这些行告诉您游戏的`Driector`根据您提供的设计和资源大小在必要时扩展资产。
有关`Cocos2d-x`如何处理分辨率的详细说明，请参阅[Cocos2d-x Wiki关于多分辨率适配的条目](http://cocos2d-x.org/wiki/Detailed_explanation_of_Cocos2d-x_Multi-resolution_adaptation)。

## 添加精灵
接下来，下载[该项目的资源文件](https://koenig-media.raywenderlich.com/uploads/2015/03/SimpleGameResources.zip)并将其解压缩到方便的位置。

在刚刚提取的`SimpleGameResources`文件夹中选择所有文件，并将它们`拖到``Xcode`项目的`Resources`组中。 在出现的对话框中，请确保在单击“完成”之前选中“复制项目”，`SimpleGame iOS`和`SimpleGame Mac`。
![Choose options for adding these files](https://img-blog.csdnimg.cn/20200930100930602.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
接下来打开`HelloWorldScene.h`，在包含`cocos2d.h`的行之后添加以下行：
```cpp
using namespace cocos2d;
```
这指定您将使用`cocos2d`命名空间； 这使您可以执行诸如写`Sprite *`而不是`cocos2d :: Sprite *`的操作。 这不是绝对必要的，但肯定会使开发更加愉快。 ：]

现在，您需要一个私有成员变量来指向您的`player`精灵。 将以下代码添加到`HelloWorld`类的声明中：
```cpp
private:
  Sprite* _player;
```
接下来，打开`HelloWorldScene.cpp`并将`HelloWorld::init`方法的内容替换为以下内容：
```cpp
// 1
if ( !Layer::init() ) {
  return false;
}
// 2
auto origin = Director::getInstance()->getVisibleOrigin();
auto winSize = Director::getInstance()->getVisibleSize();
// 3
auto background = DrawNode::create();
background->drawSolidRect(origin, winSize, Color4F(0.6,0.6,0.6,1.0));
this->addChild(background);
// 4
_player = Sprite::create("player.png");
_player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
this->addChild(_player);
    
return true;
```
这是此方法的逐步播放：

- 1.首先，您调用父类的`init`方法。 只有成功后，您才能继续进行`HelloWorldScene`的设置。
- 2.然后，您可以使用游戏的`Director`单例来获取窗口的边界。
- 3.然后，您创建一个`DrawNode`来绘制一个灰色矩形，该矩形将填充屏幕并将其添加到场景中。 这是您游戏的背景。
- 4.最后，您通过传入图片名称来创建player精灵。 您将其从屏幕的左边缘垂直居中放置10％，并将其添加到场景中。
生成并运行您的应用； 瞧，女士们，先生们，忍者进入了大楼！ ：]
![添加忍者精灵](https://img-blog.csdnimg.cn/2020093010150992.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 移动怪物
忍者需要生活中的目标，因此您需要在场景中添加一些怪物，忍者才能战斗。 为了让事情变得更加有趣，您希望怪物们四处走动-否则，这并不会带来太大的挑战！ 您将在屏幕右侧的右边创建怪物，并为它们设置一个动作，告诉它们向左移动。

首先，打开`HelloWorldScene.h`并添加以下方法声明：
```cpp
void addMonster(float dt);
```
然后在`HelloWorldScene.cpp`中添加以下方法实现：
```cpp
void HelloWorld::addMonster(float dt) {
  auto monster = Sprite::create("monster.png");
    
  // 1
  auto monsterContentSize = monster->getContentSize();
  auto selfContentSize = this->getContentSize();
  int minY = monsterContentSize.height/2;
  int maxY = selfContentSize.height - monsterContentSize.height/2;
  int rangeY = maxY - minY;
  int randomY = (rand() % rangeY) + minY;
    
  monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, randomY));
  this->addChild(monster);
    
  // 2
  int minDuration = 2.0;
  int maxDuration = 4.0;
  int rangeDuration = maxDuration - minDuration;
  int randomDuration = (rand() % rangeDuration) + minDuration;
    
  // 3
  auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, randomY));
  auto actionRemove = RemoveSelf::create();
  monster->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}
```
它相对简单，但是上面的代码是这样的：

- 1.该方法的第一部分与您之前对player进行的操作类似：它会创建一个怪物(monster)精灵并将其放置在屏幕外的右侧。 它将y位置设置为随机值，以保持有趣的状态。
- 2.接下来，该方法会计算要添加到个怪物(monster)身上的动作的随机持续时间，介于2到4秒之间。 每个怪物(monster)都会在屏幕上移动相同的距离，因此改变持续时间会导致怪物(monster)的速度随机。
- 3.最后，该方法创建一个动作，该动作使怪物(monster)从右到左在屏幕上移动，并指示怪物(monster)运行它。 下面将对此进行详细说明。

Cocos2d-x提供了许多非常方便的内置动作，可帮助您随时间轻松地更改精灵的状态，包括移动动作，旋转动作，淡入淡出动作，动画动作等。 在这里，您对怪物使用三个动作：
- `MoveTo`：在特定的时间内将对象从一个点移动到另一点。
- `RemoveSelf`：从其父节点删除节点，从而有效地将其从场景中“删除”。 在这种情况下，您可以使用该操作将不再可见的怪物从场景中移除。 这很重要，因为否则您将有无穷无尽的怪物供不应求，并最终会消耗掉设备的所有资源。
- Sequence：让您一次执行一系列其他操作。 这意味着您可以让怪物在场景中移动，并在到达目的地时将其从屏幕上移开。

在让忍者进城之前，还有最后一件事要做-您需要实际调用创建怪物的方法！ 为了使事情变得有趣，您将创建不断产生的怪物。

只需在`return`语句之前，将以下代码添加到`HelloWorld:: init`的末尾：
```cpp
srand((unsigned int)time(nullptr));
this->schedule(schedule_selector(HelloWorld::addMonster), 1.5); 
```
`srand((unsigned int)time(nullptr));`播种随机数生成器。 如果您不这样做，那么每次您运行该应用程序时，您的随机数都会相同。 感觉不会很随意，是吗？ ：]

然后，将`HelloWorld::addMonster`传递到`schedule`方法中，该方法每`1.5`秒调用一次`addMonster()`。
在这里，`Cocos2d-x`利用了`C ++`指向成员函数的指针。 如果您不了解其工作原理，请参阅ioscpp以获取更多信息。

而已！ 建立并运行您的项目； 您现在应该可以看到妖怪在屏幕上快乐地（或愤怒地（视情况而定！））移动：
![添加怪物 2](https://img-blog.csdnimg.cn/20200930102238663.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 射击弹丸
您勇敢的小忍者需要一种保护自己的方法。 在游戏中实现火力的方法有很多，但是在此项目中，您将让用户单击或轻击屏幕以沿单击或轻击的方向发射弹丸。 ew！ ：]

为简化起见，您将通过`MoveTo`操作实现这一点-但这意味着您需要做一些数学运算。

`MoveTo`操作需要射弹的目标位置，但是您不能直接使用输入位置，因为该点仅代表相对于玩家的射击方向。 您想让子弹一直移动到该点，直到子弹到达屏幕外的最终目的地。

这是说明问题的图片：
![射击弹丸的物理图](https://img-blog.csdnimg.cn/20200930102340103.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
从原点到触摸位置的x和y偏移会创建一个小三角形； 您只需要制作一个具有相同比率的大三角形即可，并且您知道要使其中一个端点不在屏幕上。

利用`Cocos2d-x`随附的矢量数学例程，可以轻松执行这些计算。 但是，在计算移动位置之前，您需要启用输入事件处理功能才能弄清楚用户触摸的位置！
将以下代码添加到`HelloWorld:: init`的末尾，就在`return`语句的上方：
```cpp
auto eventListener = EventListenerTouchOneByOne::create();
eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);
```
Cocos2d-x版本3及更高版本使用`EventDispatcher`来调度各种事件，例如触摸，加速计和键盘事件。

**注意：在整个讨论中，术语“触摸”是指触摸设备上的点击以及桌面上的点击。 Cocos2d-x使用相同的方法来处理两种类型的事件。**

为了从`EventDispatcher`接收事件，您需要注册一个`EventListener`。 触摸事件侦听器有两种类型：

- `EventListenerTouchOneByOne`：此类型为每个触摸事件调用一次您的回调方法。
- `EventListenerTouchAllAtOnce`：此类型对所有触摸事件调用一次您的回调方法。

触摸事件侦听器支持四个回调，但是您只需要为您关心的事件绑定方法。

- `onTouchBegan`：在手指首次触摸屏幕时调用。 如果使用的是`EventListenerTouchOneByOne`，则必须返回true才能接收其他三个触摸事件中的任何一个。
- `onTouchMoved`：当您的手指已经触摸屏幕而没有离开屏幕而移动时调用。
- `onTouchEnded`：当手指离开屏幕时调用。
- `onTouchCancelled`：在某些情况下被调用以停止事件处理，例如当您触摸屏幕时，然后像电话之类的中断应用程序。
在这个游戏中，您实际上只在乎何时发生触摸。 声明您的回调以在`HelloWorldScene.h`中接收触摸通知，如下所示：
```cpp
bool onTouchBegan(Touch *touch, Event *unused_event);
```

然后在`HelloWorldScene.cpp`中实现您的回调：
```cpp
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
  // 1  - Just an example for how to get the  _player object
  //auto node = unused_event->getCurrentTarget();
    
  // 2
  Vec2 touchLocation = touch->getLocation();
  Vec2 offset = touchLocation - _player->getPosition();
    
  // 3
  if (offset.x < 0) {
    return true;
  }

  // 4
  auto projectile = Sprite::create("projectile.png");
  projectile->setPosition(_player->getPosition());
  this->addChild(projectile);

  // 5
  offset.normalize();
  auto shootAmount = offset * 1000;

  // 6
  auto realDest = shootAmount + projectile->getPosition();

  // 7
  auto actionMove = MoveTo::create(2.0f, realDest);
  auto actionRemove = RemoveSelf::create();
  projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));
    
  return true;
}
```
上面的方法正在进行很多工作，因此请花点时间逐步检查一下。

- 1.第一行已被注释掉，但是它在那里向您展示了如何访问作为第二个参数传递给`addEventListenerWithSceneGraphPriority(eventListener, _player)`的`_player`对象。
- 2.您可以在此处获得场景坐标系内触摸的坐标，然后计算该点与播放器当前位置的偏移量。这是`Cocos2d-x`中向量数学的一个示例。
- 3.如果`offset`的`x`值为负，则表示玩家正在尝试向后射击。在此游戏中不允许这样做（真正的忍者永不回头！），因此只需返回而无需发射弹丸。
- 4.在玩家的位置上创建一个弹丸，并将其添加到场景中。
- 5.然后，您调用`normalize()`将偏移量转换为单位向量，该向量是长度为1的向量。将其乘以1000可得到长度为1000的向量，该向量指向用户点击的方向。为什么是1000？该长度应足以以该分辨率延伸超出屏幕边缘：]
- 6.将向量添加到弹丸的位置即可得到目标位置。
- 7.最后，创建一个动作，将弹丸移至目标位置超过两秒钟，然后将其从场景中移除。
生成并运行您的应用；触摸屏幕，使您的忍者向即将来临的部落射击！
![添加飞镖](https://img-blog.csdnimg.cn/20200930103018154.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 碰撞检测与物理
现在您已经拥有飞镖飞来飞去的地方-但您的忍者真正想要做的就是放下一些零头。 因此，您需要一些代码来检测弹丸何时与目标相交。

关于`Cocos2d-x`的一件好事是它内置了一个物理引擎！ 物理引擎不仅对于模拟逼真的运动非常有用，而且对于检测碰撞也非常有用。 您将使用Cocos2d-x的物理引擎来确定怪物和投射物何时发生碰撞。

首先在`HelloWorld::createScene`的实现上方，向`HelloWorldScene.cpp`添加以下代码：
```cpp
enum class PhysicsCategory {
  None = 0,
  Monster = (1 << 0),    // 1
  Projectile = (1 << 1), // 2
  All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};
```
些位掩码定义了您需要的物理类别-并非双关语！ ：]在这里，您已经创建了两种类型，`Monster`和`Projectile`，以及两个特殊值，用于指定没有类型或所有类型。 您将使用这些类别为对象分配类型，从而允许您指定允许哪些对象类型相互碰撞。

**注意：您可能想知道这种奇特的语法是什么。 Cocos2d-x上的类别只是一个32位整数。 此语法将整数中的特定位设置为代表不同的类别，最多给您32种可能的类别。 在这里，您将第一位设置为指示怪物，将下一位设置为代表弹丸，依此类推。**

接下来，用以下代码替换`HelloWorld::createScene`的第一行：
```cpp
auto scene = Scene::createWithPhysics();
scene->getPhysicsWorld()->setGravity(Vec2(0,0));
scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
```
这将创建一个启用了物理的场景。 `Cocos2d-x`使用`PhysicsWorld`来控制其物理模拟。 在这里，您可以在两个方向上将世界的重力设置为零，这实际上会禁用重力，并且可以启用调试绘图以查看物理物体。 在对物理相互作用进行原型设计时，启用调试绘图很有帮助，这样可以确保事情正常进行。

在`HelloWorld::addMonster`中，在创建怪物精灵的第一行之后添加以下代码：
```cpp
// 1
auto monsterSize = monster->getContentSize();
auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height),
                                          PhysicsMaterial(0.1f, 1.0f, 0.0f));
// 2
physicsBody->setDynamic(true);
// 3
physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
    
monster->setPhysicsBody(physicsBody);
```
这是上面的代码的作用：

- 1.为精灵创建一个`PhysicsBody`。物理实体代表`Cocos2d-x`物理仿真中的对象，您可以使用任何形状来定义它们。在这种情况下，可以使用与精灵大小相同的矩形作为怪兽的近似值。您可以使用更精确的形状，但是更简单的形状足以满足大多数游戏和更高的性能要求。
- 2.将精灵设置为`动态`。这意味着物理引擎不会向怪物施加力。相反，您将直接通过之前创建的`MoveTo`操作对其进行控制。
- 3.在这里，您可以设置类别，碰撞和接触测试位掩码：
	- 类别：定义对象的类型–`Monster`。
	- 碰撞：定义在碰撞期间应以何种类型的对象物理影响该对象-在这种情况下为`None`。因为此对象也是动态的，所以此字段无效，但出于完整性考虑，在此将其包括在内。
	- 接触测试：定义碰撞应通过其生成通知的对象类型-`Projectile`。您将在本教程的稍后部分注册并处理这些通知。
	- 最后，将物理物体分配给怪物。
接下来，将以下代码添加到`HelloWorld::onTouchBegan`中，紧接设置弹丸位置的行之后：
```cpp
auto projectileSize = projectile->getContentSize();
auto physicsBody = PhysicsBody::createCircle(projectileSize.width/2 );
physicsBody->setDynamic(true); 
physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
projectile->setPhysicsBody(physicsBody);
```
这与您为怪物执行的物理设置非常相似，不同的是它使用圆形而不是矩形来定义物理物体。 请注意，并不是绝对必要设置接触测试位掩码，因为怪物已经在检查与射弹的碰撞，但这有助于使代码的意图更加清晰。

立即构建并运行您的项目； 您会看到红色形状叠加在物理物体上，如下所示：
![SimpleGame final](https://img-blog.csdnimg.cn/20200930103712243.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
射弹被设置为可以击中怪物，因此当它们碰撞时，您需要将它们都移除。

还记得早先的物理学世界吗？ 好吧，您可以在其上设置一个联系人代表，以在两个物理物体碰撞时得到通知。 在那里，您将编写一些代码来检查对象的类别，如果它们是怪物和弹丸，则可以使其蓬勃发展！

首先，将以下方法声明添加到`HelloWorldScene.h`中：
```cpp
bool onContactBegan(PhysicsContact &contact);
```
这是您注册以接收联系事件的方法。

接下来，在`HelloWorldScene.cpp`中实现以下方法：
```cpp
bool HelloWorld::onContactBegan(PhysicsContact &contact) {
  auto nodeA = contact.getShapeA()->getBody()->getNode();
  auto nodeB = contact.getShapeB()->getBody()->getNode();
    
  nodeA->removeFromParent();
  nodeB->removeFromParent();
  return true;
}
```
传递给此方法的`PhysicsContact`包含有关碰撞的信息。 在这个游戏中，您知道唯一会碰撞的对象是怪物和射弹。 因此，您将使节点参与碰撞并将其从场景中移除。

最后，您需要注册以接收联系人通知。 在`return`语句之前，将以下行添加到`HelloWorld ::init`的末尾：
```cpp
auto contactListener = EventListenerPhysicsContact::create();
contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
```
这将创建一个联系人侦听器，注册`HelloWorld::onContactBegan`以接收事件并将侦听器添加到`EventDispatcher`。 现在，只要两个物理物体发生碰撞并且它们的类别位掩码与它们的接触测试位掩码匹配，`EventDispatcher`就会调用`onContactBegan`。

生成并运行您的应用； 现在，当您的弹丸与目标相交时，它们应该消失：
![Simple 碰撞检测](https://img-blog.csdnimg.cn/20200930103955880.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 画龙点睛
您现在已经快要制作出一款可行（但非常简单）的游戏了。 您只需要添加一些声音效果和音乐（因为哪种游戏都没有声音！）和一些简单的游戏逻辑即可。

`Cocos2d-x`带有一个称为`CocosDenshion`的简单音频引擎，您将使用它来播放声音。

**注意：Cocos2d-x还包括第二个音频引擎，旨在代替简单的音频引擎模块。 但是，它仍处于试验阶段，并且不适用于所有受支持的平台，因此您将不在此处使用它。**

该项目已经包含了一些很酷的背景音乐以及您之前导入的超赞的“ pew-pew”音效。 您只需要玩它们！

为此，在其他`#include`语句之后，将以下代码添加到`HelloWorldScene.cpp`的顶部：
```cpp#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
```
这将导入`SimpleAudioEngine`模块，并指定您将在此文件中使用`CocosDenshion`命名空间。

接下来，将以下定义添加到`PhysicsCategory`枚举上方的`HelloWorldScene.cpp`：
```cpp#define BACKGROUND_MUSIC_SFX  "background-music-aac.mp3"
#define PEW_PEW_SFX           "pew-pew-lei.mp3"
```
在这里，您定义了两个字符串常量：`BACKGROUND_MUSIC_SFX`和`PEW_PEW_SFX`。 这只是将文件名放在一个位置，这使得以后更容易更改它们。 像这样组织代码（甚至使用完全独立的文件甚至更好），可以更轻松地支持特定于平台的更改，例如在`iPhone`上使用`.mp3`文件，在`Windows Phone`上使用`.wav`文件。

现在，在`return`语句之前，将以下行添加到`HelloWorld::ini`t的末尾：
```cpp
SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC_SFX, true);
```
场景建立后，即会开始播放背景音乐。

至于声音效果，请将以下行添加到`HelloWorld::onTouchBegan`的`return`语句上方：
```cpp
SimpleAudioEngine::getInstance()->playEffect(PEW_PEW_SFX);
```
每当忍者发动攻击时，这都会起到很好的“ pew-pew”声音效果。 很方便，是吗？ 您仅需一行代码即可播放声音效果。

生成并运行，并享受您的时髦音乐！

然后去哪儿？
这是上面教程中[完成的示例游戏](http://www.raywenderlich.com/downloads/Cocos2d-x-Tutorial-Finished.zip)。

希望您喜欢[Cocos2d-x](http://cocos2d-x.org)，并从中获得灵感来制作自己的游戏！ 要了解有关Cocos2d-x的更多信息，请[访问Cocos2d-x网站以获取大量学习资源](http://cocos2d-x.org/learn)。

如果对本教程有任何疑问或意见，请加入下面的讨论！

## 关于本项目在其他系统如Windows上的移植
我使用的是Window7系统，Cocos2d-x的版本是3.17.2，Python是2.7.18
使用`VS2017`打开项目下的SimpleGame\proj.win32\文件夹下的`SimpleGame.sln`，然后编译运行，前提是需要配置好Cocos2d-x 3.17.2的开发环境，关于环境搭建可以参考我之前写的一篇博客：[Win10+Python2.7.14+cocos2d-x-3.17.2+VS2017环境搭建](https://blog.csdn.net/ccf19881030/article/details/108807428),下面是我在VS2017中运行本项目的截图：
![VS2017中的运行结果截图](https://img-blog.csdnimg.cn/20200930174325894.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
最终的项目源代码我已经托管到[Github](https://github.com/ccf19881030/Cocos2d-x-Tutorial)和[Gitee](https://gitee.com/havealex/cocos2d-x-tutorial)上，需要的话执行如下命令自取：

从github上获取cocos2d-x-tutorial源代码
```shell
git clone https://github.com/ccf19881030/Cocos2d-x-Tutorial.git
```

从gitee码云上获取cocos2d-x-tutorial源代码
```shell
git clone https://gitee.com/havealex/cocos2d-x-tutorial.git
```


## 参考资料
- [Cocos2d-x Tutorial for Beginners](https://www.raywenderlich.com/1848-cocos2d-x-tutorial-for-beginners)
- [ Cocos2d-x 3.5源代码](http://www.cocos2d-x.org/filedown/cocos2d-x-3.5.zip)
- [SimpleGame项目的资源文件](https://koenig-media.raywenderlich.com/uploads/2015/03/SimpleGameResources.zip)
- [SimpleGame项目最终源代码-Cocos2d-x-Tutorial-Finished](http://www.raywenderlich.com/downloads/Cocos2d-x-Tutorial-Finished.zip)
- [Win10+Python2.7.14+cocos2d-x-3.17.2+VS2017环境搭建](https://blog.csdn.net/ccf19881030/article/details/108807428)
