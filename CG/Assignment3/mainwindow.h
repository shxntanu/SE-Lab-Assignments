#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
void mousePressEvent(QMouseEvent *ev);
void dda(double x1,double y1,double x2,double y2,QRgb val);
int sign(int x);
void cohen(int x1,int y1,int x2,int y2);
int code(int x1,int y1);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool start;
    int ver,a[100],b[100];
};

#endif // MAINWINDOW_H
