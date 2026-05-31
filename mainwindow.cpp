#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"mypushbutton.h"
#include<QSoundEffect>
#include<QTimer>
#include<QUrl>
MainWindow::MainWindow(QWidget*parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //音乐
    QSoundEffect*bgm1=new QSoundEffect(this);
    bgm1->setSource(QUrl("qrc:/images/nomoremanbo.wav"));
    bgm1->setLoopCount(QSoundEffect::Infinite);
    bgm1->play();
    //点击退出菜单项，实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //设置固定尺寸
    this->setFixedSize(420,688);
    //设置标题
    this->setWindowTitle("翻金币");
    //设置窗口图标
    this->setWindowIcon(QIcon(":/images/OIP-C (3).jpg"));
    //创建第二个选关场景
    this->chooseScene = new ChooseLevelScene;
    //开始按钮
    MyPushButton*startBtn=new MyPushButton(":/images/start.png",":/images/start.png");
    startBtn->setParent(this);
    startBtn->move((this->width()-startBtn->width())*0.5,this->height()*0.7);
    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"进入选择关卡场景";
        //弹跳效果
        startBtn->zoom1();
        startBtn->zoom2();
        //延时效果
        QTimer::singleShot(500,this,[=](){
            this->chooseScene->setGeometry(this->geometry());
            this->chooseScene->show();
            this->hide();
        });
    });
//监听返回按钮
    connect(this->chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        QTimer::singleShot(500,this,[=](){
            this->setGeometry(this->chooseScene->geometry());//窗口位置优化
            this->show();
            this->chooseScene->hide();
        });
    });
}
//绘图事件
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //创建Qpixmap
    QPixmap pix;
    pix.load(":/images/OIP-C.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //金币logo
    pix.load(":/images/coinicon.png");
    //绘制
    painter.drawPixmap(10,30,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chooseScene;
}
