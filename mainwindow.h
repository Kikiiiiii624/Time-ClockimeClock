#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <QDebug>
#include <QPoint>
#include <QDate>
#include <QTimer>   // 定时器
#include <QLabel>   //  标签
#include <QDateTime>   // 获取当前时间
#include <QLCDNumber>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //绘制时钟函数
    void paintEvent(QPaintEvent *);

private slots:

    void on_lcdNumber_overflow();


private:
    QLCDNumber *lcdNumber;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
