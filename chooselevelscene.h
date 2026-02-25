#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include"playscene.h"
#include <QMainWindow>
#include<QPainter>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*e);
    //游戏场景指针
    PlayScene*play;
signals:
    //返回按钮自定义信号
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
