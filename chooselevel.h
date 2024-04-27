#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include"playscene.h"

class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);

    //背景图利用paintEvent实现
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene * play = NULL;

signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void chooseSceneBack();//只需要声明，不需要实现

};

#endif // CHOOSELEVEL_H
