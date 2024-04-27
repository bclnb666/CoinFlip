#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QDebug>
#include<QPropertyAnimation>
#include<QSoundEffect>
#include<QMessageBox>
#include"mypushbutton.h"
#include "mycoin.h"
#include"dataconfig.h"
// PlayScene::PlayScene(QWidget *parent)
//     : QMainWindow{parent}
// {}
PlayScene::PlayScene(int levelNum)
{
    this->levelIndex= levelNum;


    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    QString str1 =QString("翻金币 第 %1 关").arg(levelIndex);
    this->setWindowTitle(str1);
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

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //返回按钮音效
    QSoundEffect * backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile("://res/BackButtonSound.wav"));

    //翻金币音效
    QSoundEffect * coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl::fromLocalFile("://res/ConFlipSound.wav"));

    //胜利音效
    QSoundEffect * winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile("://res/LevelWinSound.wav"));

    //实现点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){

        backSound->play();

        //延迟返回
        QTimer::singleShot(200,this,[=](){

            emit this->chooseSceneBack();
        });

    });


    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    //设置字体样式
    QFont font;
    font.setFamily("华文行楷");
    font.setPointSize(20);
    QString str =QString("Level: %1 关").arg(this->levelIndex);
    //将字体设置到标签控件当中
    label->setFont(font);
    label->setText(str);
    label->setGeometry(30,this->height()-50,120,50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]= config.mData[this->levelIndex][i][j];
        }
    }


    //胜利图片显示
    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());




    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel * label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //显示金币
                str=":/res/Coin0001.png";
            }
            else
            {
                //显示银币
                str=":/res/Coin0008.png";
            }
            MyCoin *coin =new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];//1正面 0反面

            //将金币放入到 金币的二维数组里 以便后期的维护
            coinBtn[i][j] = coin;

            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //点击按钮期间禁用其他按钮
                for(int i= 0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }



                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                //翻转周围金币
                //延时反转
                QTimer::singleShot(250,this,[=](){


                    //周围的右侧金币反转条件
                    if(coin->posX + 1<= 3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    coinSound->play();
                    //周围的左侧金币反转条件
                    if(coin->posX - 1>= 0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }

                    //周围的下侧金币反转条件
                    if(coin->posY + 1<= 3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }
                    //周围的上侧金币反转条件
                    if(coin->posY - 1>= 0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    //翻完周围金币后才能点击其他按钮
                    for(int i= 0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }


                    //判断是否胜利
                    this->isWin = true;
                    for(int i= 0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin ==true)
                    {
                        //胜利，将所有的按钮胜利标志改为true
                        winSound->play();
                        for(int i= 0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }


                        //将胜利的图片砸下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();

                        // //是否进入下一关
                        // //延迟返回
                        // QTimer::singleShot(800,this,[=](){

                        //     emit QMessageBox::question(this," ","是否进入下一关？",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
                        // });

                    }
                });

            });

        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}
