#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<chooselevel.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //背景图利用paintEvent实现
    void paintEvent(QPaintEvent *);

    ChooseLevel *chooselevel = NULL;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
