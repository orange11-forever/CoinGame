#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"chooselevelscene.h"
#include <QMainWindow>
#include<QPainter>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*e)override;
    //维护选择关卡场景指针
    ChooseLevelScene*chooseScene;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
