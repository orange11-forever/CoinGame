#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<QPainter>
#include <QMainWindow>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);
    int levelIndex;//关卡号
    void paintEvent(QPaintEvent*e)override;
    //二维游戏数组初始化关卡
    int gameArray[4][4];
    //金币的二维数组
    MyCoin*coinBtn[4][4];
    bool isWin =true;
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
