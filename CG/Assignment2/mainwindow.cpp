#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <cmath>
QImage image(1000, 1000, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    void draw_line(int x1, int y1, int x2, int y2, QRgb value);
    void draw_circle(int xc, int yc, int rad, QRgb value);
    void Scan_Line_Fill_Concave();
    void draw_polygon();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void draw_line(int,int,int,int,QRgb);
void draw_circle(int,int,int,QRgb);
void Scan_Line_Fill_Concave();
void draw_polygon();
void delay(int);

void MainWindow::on_pushButton_2_clicked()
{
    draw_polygon();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    Scan_Line_Fill_Concave();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::Scan_Line_Fill_Concave()
{

  int x1[] = {300,450,509,525,575,590,400,300};
  int y1[] = {400,500,400,567,520,630,700,400};
  int i = 0;
  int n = 7;
  int ymin = 700;
  int ymax = 0;
  int c,j,y;
  float m[50],a[50],dx,dy,t; // a[] used to store x coordinates of intersection points
  QRgb green;
  green=qRgb(0,255,0);

  // Storing slopes of all the lines and also ymin and ymax

  for(i=0;i<n;i++)
  {
        if(y1[i]>=ymax)
        {
            ymax = y1[i];
        }
        if(y1[i]<=ymin)
        {
            ymin = y1[i];
        }
        dx = x1[i+1]-x1[i];
        dy = y1[i+1]-y1[i];
        if(dx==0)
        {
            m[i] = 0;
        }
        if(dy==0)
        {
            m[i] = 1;
        }
        if(dx!=0 and dy!=0)
        {
            m[i] = dx/dy;
        }

  }


  for(y = ymax;y>=ymin;y--)
  {

      // Starting from Ymax and going all the way to Ymin


      c = 0;
      for(i=0;i<n;i++)
      {
          if((y1[i]>y and y1[i+1]<=y) or (y1[i]<=y && y1[i+1]>y))
          {

              // x2 = x1 + (y2-y1)/m

              a[c]=x1[i]+(m[i]*(y-y1[i]));
              c++;
          }
      }

     // Bubble sorting all the X coordinates of intersection of Scan Line at y

     for(i=0;i<c-1;i++)
     {
       for(j=0;j<c-1;j++)
       {
           if(a[j]>a[j+1])
           {
               t=a[j];
               a[j]=a[j+1];
               a[j+1]=t;
           }
       }
     }
	
     // Filling in between alternate pairs of coordinates

     for(i=0;i<c-1;i=i+2)
     {
         draw_line(a[i],y,a[i+1],y,green);
         ui->label->setPixmap(QPixmap::fromImage(image));
         delay(50);
     }
     
     
    //Scan Line

     if(y==650)
     {
         QRgb red = qRgb(255,0,0);
        draw_line(200,y,700,y,red);
     }

  }
}

void draw_polygon()
{
    int x1[] = {300,450,509,525,575,590,400,300};
    int y1[] = {400,500,400,567,520,630,700,400};
    int n = 7;
    QRgb green;
    green=qRgb(0,255,0);
    for(int i=0;i<n;i++)
    {

        draw_line(x1[i],y1[i],x1[i+1],y1[i+1],green);
    }
}


void draw_line(int x1, int y1, int x2, int y2, QRgb value){

    float x_inc, y_inc, dx, dy, x, y;
    dx = x2-x1;
    dy = y2-y1;
    int len = abs(dx)>abs(dy)? abs(dx):abs(dy);
    x_inc = dx / len;
    y_inc = dy / len;
    x = x1;
    y = y1;
    for(int i=0; i<len; i++){
        image.setPixel(x, y, value);
        x += x_inc;
        y += y_inc;
    }
}



