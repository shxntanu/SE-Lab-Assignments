#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QLabel>
#include <cmath>
#include <QTime>

QImage img=QImage(800,776,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    koch(200,266,100,100,3);
    koch(100,100,300,100,3);
    koch(300,100,200,266,3);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::delay(int n)
{
    QTime dieTime = QTime::currentTime().addMSecs(n);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, n);
}

void MainWindow::koch(int x1,int y1,int x2,int y2,int it)
{
    float angle=(60 * 3.14)/180;
    int x3=((2*x1)+x2)/3;
    int y3=((2*y1)+y2)/3;
    int x4=((2*x2)+x1)/3;
    int y4=((2*y2)+y1)/3;

    int x=x3 + ((x4-x3)*cos(angle)) + ((y4-y3)*sin(angle));
    int y=y3 - ((x4-x3)*sin(angle)) + ((y4-y3)*cos(angle));

    if(it>0)
    {
        koch(x1,y1,x3,y3,it-1);
        koch(x3,y3,x,y,it-1);
        koch(x,y,x4,y4,it-1);
        koch(x4,y4,x2,y2,it-1);
    }
    else
    {
        dda(x1,y1,x3,y3);
        dda(x3,y3,x,y);
        dda(x,y,x4,y4);
        dda(x4,y4,x2,y2);
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    QRgb val=qRgb(0,255,0);
    float dx=x2-x1,dy=y2-y1,x=x1,y=y1;
    float steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    float xinc=dx/steps,yinc=dy/steps;
    for(int i=0;i<=steps;i++)
    {
        img.setPixel(x,y,val);
        delay(5);
        x+=xinc;
        y+=yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));


}
