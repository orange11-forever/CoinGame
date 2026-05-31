#include "mycoin.h"


MyCoin::MyCoin(QString img)
    : posX(0), posY(0), flag(false)
{
    QPixmap pix;
    bool ret=pix.load(img);
    if(!ret){
        qDebug()<<"图片加载失败";
    }
    this->setFixedSize(pix.width()*0.5,pix.height()*0.5);
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width() * 0.5, pix.height() * 0.5));
    //定时器
    this->timer1=new QTimer(this);
    this->timer2=new QTimer(this);
    //监听正-反
    connect(this->timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        bool ret=pix.load(":/images/coin-2.gif");
        if (!ret) {

            qDebug() << "图片加载失败";
        }
        this->setFixedSize(pix.width() * 0.5, pix.height() * 0.5);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width() * 0.5, pix.height() * 0.5));
        this->timer1->stop();
    });
    //监听反-正
    connect(this->timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        bool ret =pix.load(":/images/coin-1.gif");
        if(!ret){
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pix.width() * 0.5, pix.height() * 0.5);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width() * 0.5, pix.height() * 0.5));
        this->timer2->stop();
    });
}
//点击翻转
void MyCoin::changeFlag()
{
    if(this->flag){
        this->timer1->start(30);
        this->flag=false;
    }
    else{
        this->timer2->start(30);
        this->flag=true;
    }

}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isWin)
    {
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}
