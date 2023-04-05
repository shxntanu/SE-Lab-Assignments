#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMouseEvent"
#include"QtDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRgb val=qRgb(3, 207, 252); // Pink
    start=true;
    ver=0;

    // Clipping Window

    dda(100,200,200,200,val);
    dda(200,200,200,300,val);
    dda(200,300,100,300,val);
    dda(100,300,100,200,val);
}

QImage img=QImage(500,500,QImage::Format_RGB888);

const int Left=1,Right=2,Top=8,Bottom=4,inside=0; // Region Coordinates

const int xmin=100,ymin=200,xmax=200,ymax=300; // Extremities of Clipping Window

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    QRgb green=qRgb(0,255,0);

    int p=ev->pos().x(); // Taking the x position of mouse
    int q=ev->pos().y(); // Taking the y position of mouse

    a[ver]=p;
    b[ver]=q+44; // Adding 44 to match with the tip of the cursor
    if(start){

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

int MainWindow::sign(int x)
{

    // Returns the sign of the number

    if(x==0)
    {
        return 0;
    }
    if(x>0)
    {
        return 1;
    }

    return -1;
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    for(int i=1;i<=ver-1;i++)
    {
        cohen(a[i],b[i],a[i-1],b[i-1]);
    }
    cohen(a[ver-1],b[ver-1],a[0],b[0]);

}

int MainWindow::code(int x1,int y1)
{

    // Returns the region code

    int c=inside;
    if(x1<xmin)
    {
        c=c | Left;
    }
   else if(x1>xmax)
    {
        c= c | Right;
    }
    if(y1<ymin)
    {
        c=c | Bottom;
    }
    else if(y1>ymax)
    {
        c=c | Top;
    }
    return c;
}

void MainWindow::cohen(int x1,int y1,int x2,int y2)
{

    int code1=code(x1,y1),code2=code(x2,y2); // Obtaining region code of endpoints of line

    int a=x1,b=y1,c=x2,d=y2;

    bool accept=false;

    while(true)
    {

        if(code1==0 && code2==0) // Line lies completely inside
        {
            accept=true;
            break;
        }

        else if(code1 & code2) // Line lies completely outside
        {
            break;
        }

        else // Line lies partially inside
        {

            int codeout; // Obtaining coordinates of endpoint outside clipping window

            if(code1!=0)
            {
                codeout=code1;
            }
            else
            {
                codeout=code2;
            }

            double x,y;

            if(codeout & Top) // if the above endpoint lies above the clipping window
            {
                y=ymax;
                x=x1+double((x2-x1)*(ymax-y1)/(y2-y1));
            }

            else if(codeout & Bottom) // if the above endpoint lies below the clipping window
            {
                y=ymin;
                x=x1+double((ymin-y1)*(x2-x1)/(y2-y1));
            }

            else if(codeout & Left) // if the above endpoint lies to the left of the clipping window
            {
                x=xmin;
                y=y1+double((xmin-x1)*(y2-y1)/(x2-x1));
            }

            else if(codeout & Right) // if the above endpoint lies to the right of the clipping window
            {
                x=xmax;
                y=y1+double((xmax-x1)*(y2-y1)/(x2-x1));
            }

            // Updating the values of the endpoint after clipping

            if(codeout==code1)
            {
                x1=x;
                y1=y;
                code1=code(x1,y1);
            }

            else
            {
                x2=x;
                y2=y;
                code2=code(x2,y2);
            }

        }

    }

    // Drawing the new line and erasing the old one

    if(accept)
    {
        QRgb old=qRgb(0,0,0);
        dda(a,b,c,d,old); // Erasing the old line

        QRgb ne=qRgb(255,0,0);
        dda(x1,y1,x2,y2,ne); // Keeping the new line
    }

}
