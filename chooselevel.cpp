#include "chooselevel.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QDebug>
#include<QSoundEffect>
ChooseLevel::ChooseLevel(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡场景
    //设置固定大小
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("菜单");
    //创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //退出按钮实现
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });


    //选择关卡按钮音效
    QSoundEffect * chooseSound = new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile("://res/TapButtonSound.wav"));
    //返回按钮音效
    QSoundEffect * backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile("://res/BackButtonSound.wav"));


    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);

    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //实现点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){

        backSound->play();

        //延迟返回
        QTimer::singleShot(200,this,[=](){

            emit this->chooseSceneBack();
        });

    });

    //创建选择关卡的按钮
    for(int i=0; i < 20; i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i%4 * 70, 130 + i/4 * 70);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();
            QString str =QString("您选择的是第 %1 关").arg(i+1);
            // qDebug()<<str;

            //进入到游戏场景
            this->hide();//将选关场景隐藏掉
            play = new PlayScene(i+1);//创建游戏场景
            play->show();//显示游戏场景
            play->setGeometry(this->geometry());


            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25 + i%4 * 70, 130 + i/4 * 70);

        //设置 label上的文字对其方式 水平和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

 void ChooseLevel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
