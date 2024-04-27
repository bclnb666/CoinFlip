#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;


    //背景图利用paintEvent实现
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];//二维数组，维护每个关卡的具体数据

    MyCoin *coinBtn[4][4];

    //是否胜利的标志
    bool isWin;

signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void chooseSceneBack();//只需要声明，不需要实现
};

#endif // PLAYSCENE_H
