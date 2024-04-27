#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include "mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSoundEffect>
#include<QMessageBox>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //详情
    connect(ui->actionxiangqing,&QAction::triggered,[=](){
        QMessageBox::information(this,"详情","制作人:Elysia");

    });


    //准备开始按钮音效
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile("://res/TapButtonSound.wav"));


    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooselevel =  new ChooseLevel;

    //监听选择关卡的返回按钮信号
    connect(chooselevel,&ChooseLevel::chooseSceneBack,this,[=](){
        this->setGeometry(chooselevel->geometry());
        chooselevel->hide();//将选择关卡场景 隐藏掉
        this->show();//重新显示主场景
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"1";

        //播放开始音效
        startSound->play();
        //弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //进入到选择关卡场景中
        //延时进入选择关卡
        QTimer::singleShot(200,this,[=](){

            chooselevel->setGeometry(this->geometry());

            //自身隐藏
            this->hide();
            //显示选择关卡
            chooselevel->show();




        });



    });
}

 void MainScene::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //左上角图标
    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}
