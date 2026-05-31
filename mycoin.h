#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QWidget>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString img);
    //坐标
    int posX;
    int posY;
    //正反
    bool flag;
    //改变标志实现翻转
    void changeFlag();
    QTimer*timer1;//正-反
    QTimer*timer2;//反-正
    void mousePressEvent(QMouseEvent*e);
    bool isWin=false;//判断是否胜利的标志，一开始为假
signals:
};

#endif // MYCOIN_H
