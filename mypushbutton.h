#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数 参1 正常默认显示图片   参2  按下显示的图片
    MyPushButton(QString normalImg,QString pressImg = "");

    //成员属性 保存默认和按下显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1();
    void zoom2();

    //重写按钮 按下 和 释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:
};

#endif // MYPUSHBUTTON_H
