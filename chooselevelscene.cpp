#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPixmap>
#include"mypushbutton.h"
#include<QLabel>
#include<QTimer>
#include<QSoundEffect>
#include<QUrl>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}, play(nullptr)
{
    //设置尺寸
    this->setFixedSize(420,688);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置图标
    this->setWindowIcon(QIcon(":/images/OIP-C (3).jpg"));
    //音乐
    QSoundEffect*bgm2=new QSoundEffect(this);
    bgm2->setSource(QUrl("qrc:/images/wow.wav"));
   //菜单栏
    QMenuBar*bar=menuBar();
    this->setMenuBar(bar);
   QMenu*startMenu= bar->addMenu("开始");
   //菜单项
   QAction *quitAction=startMenu->addAction("退出");
   connect(quitAction,&QAction::triggered,[=](){
       this->close();
   });
    //返回按钮
   MyPushButton*backBtn=new MyPushButton(":/images/backbtn.png",":/images/backbtn-2.png");
   backBtn->setParent(this);
   backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
   connect(backBtn,&MyPushButton::clicked,[=](){
       backBtn->zoom1();
       backBtn->zoom2();
       bgm2->play();
       emit chooseSceneBack();
   });
   //关卡矩阵实现
   for(int i=0;i<20;i++){
       MyPushButton*menuBtn=new MyPushButton(":/images/F18CEFAD11A216604644DDC38D027B32.jpg",":/images/F18CEFAD11A216604644DDC38D027B32.jpg");
       menuBtn->setParent(this);
       menuBtn->move((i%4)*100,(i/4)*100);
       connect(menuBtn,&MyPushButton::clicked,[=](){
           //音乐
           bgm2->play();
           if (this->play) {
               delete this->play;
               this->play = nullptr;
           }
           this->play=new PlayScene(i+1);
           this->play->show();
           this->hide();//关卡场景转换
           //监听游玩场景信号
           connect(this->play,&PlayScene::chooseSceneBack,[=](){
               QTimer::singleShot(500,this,[=](){
                   this->play->hide();//关卡场景hide
                   this->show();//显示选择关卡场景
                   delete this->play;
                   this->play=NULL;//关卡指针滞空
               });
           });
       });
    //QLabel显示数字
       QLabel*label=new QLabel;
       label->setParent(this);
       label->move((i%4)*100,(i/4)*100);
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i+1));
       //文本居中
       label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
       //鼠标穿透
       label->setAttribute(Qt::WA_TransparentForMouseEvents);
   }
}

ChooseLevelScene::~ChooseLevelScene()
{
    if (play) {
        delete play;
        play = nullptr;
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/73417F82CCD03885D9E180A49C9E0D7C.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
