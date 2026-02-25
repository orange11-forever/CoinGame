#include "playscene.h"
#include<QMenuBar>
#include<QLabel>
#include"mypushbutton.h"
#include"dataconfig.h"
#include"QPropertyAnimation"
#include<QSoundEffect>
#include<QUrl>
PlayScene::PlayScene(int index)
{
    this->levelIndex=index;
    //关卡名
    this->setWindowTitle("游戏关卡");
    //尺寸
    this->setFixedSize(520,688);
    //图标
    this->setWindowIcon(QIcon(":/images/OIP-C (3).jpg"));
    //音乐
    QSoundEffect*bgm3=new QSoundEffect(this);
    QSoundEffect*bgm4=new QSoundEffect(this);
    bgm3->setSource(QUrl("qrc:/images/ohyeah.wav"));
    bgm4->setSource(QUrl("qrc:/images/wow.wav"));
    //菜单栏
    QMenuBar*bar=menuBar();
    QMenu*startMenu= bar->addMenu("开始");
    QAction*quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮
    MyPushButton*backBtn =new MyPushButton(":/images/backbtn.png",":/images/backbtn-2.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
        backBtn->zoom1();
        backBtn->zoom2();
        bgm4->play();
        //返回选择观卡场景
        emit chooseSceneBack();
    });
    //显示关卡号
    QLabel* label =new QLabel;
    label->setParent(this);
    QString str=QString("Level:%1").arg(this->levelIndex);
    label->setText(str);
    //设置大小以及位置
    label->setGeometry(QRect(30,this->height()-50,this->width(),50));
    //调整字体大小，颜色
    QFont font("华文新魏",20);
    label->setFont(font);
    QPalette palette=label->palette();
    palette.setColor(QPalette::WindowText,Qt::black);
    label->setPalette(palette);
    //胜利图片
    QLabel*winLabel=new QLabel;
    winLabel->setParent(this);
    QPixmap pix;
    pix.load(":/images/victory.png");
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0,0,pix.width(),pix.height());
    winLabel->move(this->width()*0.5-pix.width()*0.5,-pix.height());
    //初始化关卡二维数组
    DataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.m_Data[this->levelIndex][i][j];
        }
    }
    //创建金币背景
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //绘制金币矩阵背景
            QPixmap pix;
            pix.load(":/images/whitebkg.png");
            QLabel*label =new QLabel;
            label->setGeometry(0,0,pix.width()*0.05,pix.height()*0.05);
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * pix.width()*0.05, 150 + j * pix.height()*0.05);
            //创建硬币 1正面 2反面
            QString str;
            if(gameArray[i][j]==1){
                str=":/images/coin-1.gif";
            }
            else{
                str=":/images/coin-2.gif";
            }
            MyCoin*coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*pix.width()*0.05,150+j*pix.height()*0.05);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];
            coinBtn[i][j]=coin;
            //监听点击 翻转图片
            connect(coin,&MyCoin::clicked,[=](){
                coin->changeFlag();
                //记录当前状态，同步二维数组
                gameArray[i][j]=gameArray[i][j]==0?1:0;
                //延时翻转
                QTimer::singleShot(200,this,[=](){
                //翻转周围图片
                //右侧
                if(coin->posX+1<=3){
                    this->coinBtn[coin->posX+1][coin->posY]->changeFlag();
                    gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==0?1:0;
                }
                //左
                if(coin->posX-1>=0){
                    this->coinBtn[coin->posX-1][coin->posY]->changeFlag();
                    gameArray[coin->posX-1][coin->posY]=gameArray[coin->posX-1][coin->posY]==0?1:0;
                }
                //上
                if(coin->posY-1>=0){
                    this->coinBtn[coin->posX][coin->posY-1]->changeFlag();
                    gameArray[coin->posX][coin->posY-1]=gameArray[coin->posX][coin->posY-1]==0?1:0;
                }
                //下
                if(coin->posY+1<=3){
                    this->coinBtn[coin->posX][coin->posY+1]->changeFlag();
                    gameArray[coin->posX][coin->posY+1]=gameArray[coin->posX][coin->posY+1]==0?1:0;
                }
                //检测游戏胜利
                this->isWin=true;
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        if(this->coinBtn[i][j]->flag==false){
                            this->isWin=false;
                            break;
                        }
                    }
                }
                if(this->isWin){
                   // qDebug()<<"游戏胜利";
                //Coin里的isWin改变，禁止再次点击
                   for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           this->coinBtn[i][j]->isWin=true;
                       }
                   }
                   //胜利动画
                   QPropertyAnimation*animation=new QPropertyAnimation(winLabel,"geometry");
                   animation->setDuration(1000);
                   animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                   animation->setEndValue(QRect(winLabel->x(),winLabel->y()+200,winLabel->width(),winLabel->height()));
                   animation->setEasingCurve(QEasingCurve::OutBounce);
                   animation->start(QAbstractAnimation::DeleteWhenStopped);
                   bgm3->play();
                }
                });
            });
        }
    }
}
void PlayScene::paintEvent(QPaintEvent *e)
{//绘制背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/playbkg.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
//绘制自行车小耄logo
    pix.load(":/images/E7AF67868D503717BD39D33645A95511.jpg");
    pix= pix.scaled(pix.width()*0.3,pix.height()*0.3);
    painter.drawPixmap(0,5,pix);
}
