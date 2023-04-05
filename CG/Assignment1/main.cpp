#include "mainwindow.h"

#include <QApplication>
#include <QtGui>
#include <QtWidgets>
#include <QWidget>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QImage image(500, 500, QImage::Format_RGB888);
    QRgb value;
    value=qRgb(0,255,0); //set color of pixel as green

    for(int x=50;x<250;++x){
    image.setPixel(x,50,value);
    }
    for (int y=50;y<=180;++y){
        image.setPixel(250,y,value);
    }
    for(int x=250;x>=50;--x){
        image.setPixel(x,180,value);
    }
    for(int y=180;y>=50;--y){
        image.setPixel(50,y,value);
    }

    int x1 = 50,y1=115,x2=150,y2=50;
    float x_inc, y_inc, dx, dy, x, y;
        dx = x2-x1;
        dy = y2-y1;
        int len = abs(dx)>abs(dy)? abs(dx):abs(dy);
        x_inc = dx / len;
        y_inc = dy / len;
        x = x1;
        y = y1;
        for(int i=0; i<len; i++){
            image.setPixel(x, y, qRgb(255, 255, 255));
            x += x_inc;
            y += y_inc;
        }

        x1 = 150,y1=50,x2=250,y2=115;
            dx = x2-x1;
            dy = y2-y1;
            len = abs(dx)>abs(dy)? abs(dx):abs(dy);
            x_inc = dx / len;
            y_inc = dy / len;
            x = x1;
            y = y1;
            for(int i=0; i<len; i++){
                image.setPixel(x, y, qRgb(255, 255, 255));
                x += x_inc;
                y += y_inc;
            }

        x1 = 250,y1=115,x2=150,y2=180;
            dx = x2-x1;
            dy = y2-y1;
            len = abs(dx)>abs(dy)? abs(dx):abs(dy);
            x_inc = dx / len;
            y_inc = dy / len;
            x = x1;
            y = y1;
            for(int i=0; i<len; i++){
                image.setPixel(x, y, qRgb(255, 255, 255));
                x += x_inc;
                y += y_inc;
            }

        x1 = 150,y1=180,x2=50,y2=115;
            dx = x2-x1;
            dy = y2-y1;
            len = abs(dx)>abs(dy)? abs(dx):abs(dy);
            x_inc = dx / len;
            y_inc = dy / len;
            x = x1;
            y = y1;
            for(int i=0; i<len; i++){
                image.setPixel(x, y, qRgb(255, 255, 255));
                x += x_inc;
                y += y_inc;
            }


        int xc =150,yc=115,rad=54;
        int x3 =0, y3=rad;
        int d = 3 - 2*rad;

        while(x3<=y3){
            image.setPixel(xc + x3, yc + y3, qRgb(255, 255, 255));
            image.setPixel(xc - x3, yc + y3, qRgb(255, 255, 255));
            image.setPixel(xc + x3, yc - y3, qRgb(255, 255, 255));
            image.setPixel(xc - x3, yc - y3, qRgb(255, 255, 255));
            image.setPixel(xc + y3, yc + x3, qRgb(255, 255, 255));
            image.setPixel(xc - y3, yc + x3, qRgb(255, 255, 255));
            image.setPixel(xc + y3, yc - x3, qRgb(255, 255, 255));
            image.setPixel(xc - y3, yc - x3, qRgb(255, 255, 255));

            if(d<0)
                d += 4*x3+6;
            else{
                d += 4*(x3-y3)+10;
                y3 --;
            }
            x3 ++;
        }






    QLabel l; //shows pixel on screen
    l.setPixmap(QPixmap::fromImage(image));
    l.show();
    return a.exec();
}
