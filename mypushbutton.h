#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QPropertyAnimation>
class MyPushButton:public QPushButton
{ Q_OBJECT
public:
    MyPushButton(QString normalImg,QString pressImg);
    QString normalPath;
    QString pressPath;
    //弹跳
    void zoom1();
    void zoom2();
    //鼠标按下与释放事件
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
};

#endif // MYPUSHBUTTON_H
