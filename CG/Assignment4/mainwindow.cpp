#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QtDebug"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start=true;
    ver=0;
    axes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scaling_clicked()
{
    double scale = ui->scaling_box->toPlainText().toFloat();
        clear();
        axes();
      scaling(scale);
}

void MainWindow::on_translating_clicked()
{
    QString textx = ui->translating_box_1->toPlainText();
    QString texty = ui->translating_box_2->toPlainText();
    bool flag;
    int tfx = textx.split(" ")[0].toInt(&flag);
    int tfy = texty.split(" ")[0].toInt(&flag);
    if(flag)
    {
        clear();
        axes();
        translate(tfx,tfy);
    }
}

void MainWindow::on_rotating_clicked()
{
    clear();
    axes();
    float theta = ui->spinBox->text().toFloat();
    rotate(theta);
}

QRgb green=qRgb(0,255,0);

QImage img=QImage(700,700,QImage::Format_RGB888);

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    QRgb green=qRgb(0,255,0);

    int p=ev->pos().x(); // Taking the x position of mouse
    int q=ev->pos().y(); // Taking the y position of mouse

    a[ver]=p;
    b[ver]=q; // Adding 44 to match with the tip of the cursor
    if(start)
    {
        if(ev->button()==Qt::RightButton)
        {
            // Right click ends the coordinate plotting

            dda(a[ver],b[ver],a[0],b[0],green);
            start=false;
        }
        else
        {
            if(ver>0)
            {

                dda(a[ver],b[ver],a[ver-1],b[ver-1],green); // Drawing line between successive points

            }
        }
        ver++;

    }
}

void MainWindow::dda(double x1,double y1,double x2,double y2,QRgb val)
{

    // DDA Line Drawing Algorithm

    double dx=x2-x1,dy=y2-y1,steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    double x=x1,y=y1;
    double xinc=dx/steps,yinc=dy/steps;
    for(int i=1;i<=steps;i++)
    {
        img.setPixel(x,y,val);
        x+=xinc;
        y+=yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::scaling(float scalfac)
{
    int t1[ver],t2[ver];
    for(int i=0;i<ver;i++){
        int x=a[i] - 350;
        int y=350 - b[i];
           t1[i]  = x*scalfac;
           t2[i]  = y*scalfac;
     }
    for(int i=0;i<ver-1;i++){

           dda(t1[i]+350,350-t2[i],t1[i+1]+350,350-t2[i+1],green);

        }
        dda(t1[0]+350,350-t2[0],t1[ver-1]+350,350-t2[ver-1],green);
}

void MainWindow::clear(){
    img.fill(qRgb(0,0,0));
}

void MainWindow::axes()
{
    dda(0,350,700,350,qRgb(255,255,255));
    dda(350,0,350,700,qRgb(255,255,255));
}

void MainWindow::translate(int tfx, int tfy)
{
    int t1[ver],t2[ver];
    for(int i=0;i<ver;i++)
    {
        int x=a[i] - 350;
        int y=350 - b[i];
        t1[i]  = x + tfx;
        t2[i]  = y + tfy;
        }
         for(int i=0;i<ver-1;i++){

           dda(t1[i]+350,350-t2[i],t1[i+1]+350,350-t2[i+1],green);

        }
        dda(t1[0]+350,350-t2[0],t1[ver-1]+350,350-t2[ver-1],green);
}

void MainWindow::rotate(float theta)
{
    int t1[ver],t2[ver];
    theta = theta * 3.14 / 180;

    for(int i =0;i<ver;i++)
    {
        int x = a[i] - 350;
        int y = 350 - b[i];

        t1[i] = x*cos(theta) - y*sin(theta);
        t2[i] = x*sin(theta) + y*cos(theta);
    }

    for(int i=0;i<ver-1;i++)
    {
        dda(t1[i]+350,350-t2[i],350+t1[i+1],350-t2[i+1],green);
    }
}

//void MainWindow::clearval()
//{
//    for(int i=0;i<ver;i++){
//        a[i]=NULL;
//    }
//}
