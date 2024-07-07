#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icon/Clock.png"));

    //禁止用户点击窗口最大化按钮
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    //设置窗口大小s
    resize(900,600);

    // 处理QLCDNumber控件
    ui->lcdNumber->setDigitCount(10);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);

    //定时器
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(timer,SIGNAL(timeout()),this,SLOT(on_lcdNumber_overflow()));
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lcdNumber_overflow()
{
    // 获取系统当前时间
    QTime qtime=QTime::currentTime();

    // 设置晶体管控件QLCDNumber显示时间
    ui->lcdNumber->display(qtime.toString("HH:mm:ss"));
}

void MainWindow::paintEvent(QPaintEvent *)
{

    static const QPoint hour[4]={
        QPoint(10,0),
        QPoint(0,25),
        QPoint(-10,0),
        QPoint(0,-120)
    };

    static const QPoint minute[4]={

        QPoint(10,0),
        QPoint(0,25),
        QPoint(-10,0),
        QPoint(0,-245)
    };

    static const QPoint second[3]={

        QPoint(-5,85),
        QPoint(5,85),
        QPoint(0,-275)
    };


    int size = qMin(width(), height()) * 0.6; // 缩小时钟大小，占窗口大小的80%
    QTime time=QTime::currentTime();//获取系统时间
    qDebug()<<"hour:"<<time.hour()<<"minute:"<<time.minute()<<"second:"<<time.second();

    QPainter p(this); // 创建画家对象
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing); // 抗锯齿
    p.translate(width() / 4, height() / 2); // 移动到窗口中上部分，高度的四分之一处
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(85,170,127));
    p.drawEllipse(QPoint(),100,100);
    p.scale(size / 600.0, size / 600.0);



    QBrush brush;//定义画刷
    brush.setColor(QColor(255,255,255));//设置画刷颜色
    brush.setStyle(Qt::SolidPattern);//设置样式

    QPen pen;//定义画笔
    pen.setWidth(20);//设置画笔宽度
    pen.setColor(QColor(205,214,216));//rgb设置颜色
    pen.setStyle(Qt::SolidLine);//设置样式
    p.setPen(pen);//将画笔交给画家

    //画表框
    p.drawEllipse(QPoint(0,0),290,290);

    //画日期de背景

    pen.setWidth(5);//设置画笔宽度
    pen.setColor(QColor(0,0,0));//rgb设置颜色
    p.setPen(pen);//将画笔交给画家
    p.setBrush(QColor(255,255,255));
    p.drawRect(148,-15,100,33);

    //画日期
    QDate date = QDate::currentDate();
    qDebug() << date;
    QString riqi=date.toString("dd");
    qDebug() <<riqi;

    QString zhou=date.toString("ddd");
    qDebug() <<zhou;

    QString showt=zhou+"|"+riqi;

    QFont font2;
    font2.setFamily("Microsoft YaHei");
    // 大小
    font2.setPointSize(15);
    p.setFont(font2);
    pen.setColor(QColor(0,0,0));
    p.setPen(pen);
    p.save();
    p.drawText(155,10,showt);
    p.restore();


    //绘制12数字三角替代
    static const QPoint twe[3]={
        QPoint(0,-240),
        QPoint(-17,-210),
        QPoint(17,-210)
    };
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    p.save();
    p.drawConvexPolygon(twe,3);
    //恢复上一次保存的结果，和save()成对出现
    p.restore();

    //画三角形边上的两个点
    p.setPen(Qt::NoPen);//将画笔交给画家
    p.setBrush(QColor(255,255,255));
    p.save();
    p.drawEllipse(QPoint(-19,-233),5,5);
    p.drawEllipse(QPoint(19,-233),5,5);
    p.restore();


    //画文字
    QFont font;
    font.setFamily("Microsoft YaHei");
    // 大小
    font.setPointSize(20);
    p.setFont(font);
    pen.setColor(QColor(255,255,255));
    p.save();
    p.setPen(pen);
    p.drawText(-28,-120,"IWC");
    p.restore();

    font.setPointSize(8);
    p.setFont(font);
    p.save();
    p.setPen(pen);
    p.drawText(-57,-90,"LEILAOTONGKUAN");
    p.restore();


    font.setPointSize(10);
    p.setFont(font);
    p.save();
    p.setPen(pen);
    p.drawText(-49,90,"MARK XVLL");
    p.drawText(-52,115,"AUTOMATIC");
    p.restore();

    //绘制时针
    pen.setWidth(3);//设置画笔宽度
    pen.setColor(QColor(128,138,135));//rgb设置颜色
    p.setPen(pen);//将画笔交给画家
    p.setBrush(QColor(255,255,255));
    p.setBrush(brush);//将画刷交给画家
    p.save();//保存当前状态
    p.rotate(30*(time.hour()+time.minute()/60));
    p.drawConvexPolygon(hour,4);
    //恢复上一次保存的结果，和save()成对出现
    p.restore();


    //绘制分针
    pen.setWidth(3);//设置画笔宽度
    pen.setColor(QColor(128,138,135));//rgb设置颜色
    p.setPen(pen);//将画笔交给画家
    // p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    p.save();//保存画家状态
    p.rotate(6*(time.minute()+time.second()/60));
    p.drawConvexPolygon(minute,4);
    //恢复上一次保存的结果，和save()成对出现
    p.restore();//还原画家状态


    //绘制秒针
    pen.setWidth(1);//设置画笔宽度
    pen.setColor(QColor(128,138,135));//rgb设置颜色
    p.setPen(pen);//将画笔交给画家
    //p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    p.save();
    p.rotate(6*time.second());

    //p.drawLine(QPoint(0,0),QPoint(0,200));
    p.drawConvexPolygon(second,3);
    //恢复上一次保存的结果，和save()成对出现
    p.restore();


    //画中心圆
    pen.setWidth(3);//设置画笔宽度
    pen.setColor(QColor(128,138,135));//rgb设置颜色
    p.setPen(pen);//将画笔交给画家
    p.setBrush(QColor(255,255,255));
    p.save();
    p.drawEllipse(QPoint(0,0),10,10);
    p.restore();

    //画中心点
    p.setPen(Qt::NoPen);//将画笔交给画家
    p.setBrush(QColor(128,138,135));
    p.save();
    p.drawEllipse(QPoint(0,0),3,3);
    p.restore();

    //绘制分钟线
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255,255,255));

    for(int i=0;i<=60;i++){
        if ((i%5)!=0)
        {
            pen.setWidth(5);
            p.setPen(pen);
            p.drawLine(0, 260, 0, 278);
        }
        else if((i%5==0)){
            pen.setWidth(15);
            p.setPen(pen);
            p.drawLine(0, 273, 0, 268);

            if(i==0){

                p.setPen(Qt::NoPen);
                p.save();
                p.restore();

            }
            if(i==15){
            }

            else if(i!=0&&i!=15&&i!=60) {
                QFont font;
                font.setFamily("Microsoft YaHei");
                // 大小
                font.setPointSize(30);
                p.setFont(font);
                pen.setWidth(100);
                pen.setColor(QColor(255,255,255));
                p.setPen(pen);
                p.drawText(-15,-200,QString::number(i/5));

            }
        }
        p.rotate(6);
    }

}




