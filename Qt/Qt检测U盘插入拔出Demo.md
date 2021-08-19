# UDiskDetectExample
本文转载自[Qt检测U盘插入拔出Demo](https://blog.csdn.net/u014597198/article/details/72820737)
要做这个，要先知道Qt的QAbstractNativeEventFilter类，虚函数nativeEventFilter。这个类的主要作用是捕获全局windows消息。

**先看一下效果**：

![img](https://img-blog.csdn.net/20170531153904512?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxNDU5NzE5OA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

**基本注意以下两点：**

1、新建的类要继承`QAbstractNativeEventFilter`

2、新建的类要被安装事件过滤，比如：

```cpp
qApp->installNativeEventFilter(QAbstractNativeEventFilter *filterObj);
```

**这里我封装了一个简单的类uDisk：**

(1)、头文件`uDisk.h`

```cpp
#ifndef UDISK_H
#define UDISK_H

#include <QWidget>
#include <Windows.h>
#include <QAbstractNativeEventFilter>
#include <Dbt.h>

// Qt的QAbstractNativeEventFilter类，虚函数nativeEventFilter。这个类的主要作用是捕获全局windows消息。
class uDisk : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    uDisk(QWidget *parent = nullptr);
    ~uDisk();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

signals:
    // U盘插入信号
    void sigUDiskCome(QString uDiskName);
    // U盘拔出信号
    void sigUDiskRemove();
private:
    char FirstDriveFromUDisk(ULONG unitmask);
};
#endif // UDISK_H
```

(2)、源文件：

```cpp
#include "udisk.h"
#include <QApplication>
#include <QDebug>

uDisk::uDisk(QWidget *parent)
    : QWidget(parent)
{
}

uDisk::~uDisk()
{
}

// 在QWidget中重新实现它的nativeEvent函数来接收处理WM_DEVICECHANGE消息
bool uDisk::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if (msgType == WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam)
        {
        case DBT_DEVICEARRIVAL:
            if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if (lpdbv->dbcv_flags == 0)
                {
                    QString strUSBDisk = QString(this->FirstDriveFromUDisk(lpdbv->dbcv_unitmask));
                    emit sigUDiskCome(strUSBDisk);
                }
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if (lpdbv->dbcv_flags == 0)
                {
                    emit sigUDiskRemove();
                }
            }
             break;
        case DBT_DEVNODES_CHANGED:
            break;
        default:
            break;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

char uDisk::FirstDriveFromUDisk(ULONG unitmask)
{
    char i;
    for (i = 0; i < 26; i++)
    {
        if (unitmask & 0x01)
        {
            break;
        }
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}
```

如何使用uDisk类？

(1)、引用uDisk.h头文件：

```cpp
#include "udisk.h"
```

(2)、声明uDisk类对象：

```cpp
uDisk* m_uDisk = Q_NULLPTR;
```

(3)、调用：

```cpp
m_uDisk = new uDisk;
qApp->installNativeEventFilter(m_uDisk);
connect(m_uDisk, &uDisk::sigUDiskCome, [=](QString uDiskName){
    ui->label->setText(tr("U Disk Come!").append(tr("The Disk is ") + uDiskName));
});
connect(m_uDisk, &uDisk::sigUDiskRemove, [=](){
    ui->label->setText(tr("U Disk Remove!"));
});
```

(4)、在调用类析构时记得析构掉： 

```cpp
if(m_uDisk) {
    delete m_uDisk;
    m_uDisk = Q_NULLPTR;
}
```
