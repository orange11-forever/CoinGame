#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPainter>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    ~ChooseLevelScene();
    void paintEvent(QPaintEvent*e)override;
    //游戏场景指针
    PlayScene*play;
signals:
    //返回按钮自定义信号
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
