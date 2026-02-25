#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg,QString pressImg) {
    this->normalPath=normalImg;
    this->pressPath=pressImg;
    //创建Qpixmap
    QPixmap pix;
    bool ret= pix.load(this->normalPath);
    if(!ret){
        qDebug()<<"图片加载失败";
    }
    //按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置图标
    this->setIcon(pix);
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标大小
    this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));

}
//向下
void MyPushButton::zoom1()
{//创建动画
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    //设置间隔
    animation->setDuration(200);
//设置起始值
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
//结束值
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
//动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
//执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}
//向上
void MyPushButton::zoom2()
{
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{//按下路径不为空,切图
    if(!this->pressPath.isEmpty()){
        QPixmap pix;
        bool ret =pix.load(this->pressPath);
        if(!ret){
            qDebug()<<"图片加载错误";
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
    }
    //父类处理其他事情
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{ //还原图片
    if(!this->pressPath.isEmpty()){
        QPixmap pix;
        bool ret =pix.load(this->normalPath);
        if(!ret){
            qDebug()<<"图片加载错误";
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
    }
    //父类处理其他事情
    QPushButton::mouseReleaseEvent(e);
}
