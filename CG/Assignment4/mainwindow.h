#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *ev);
    void dda(double ,double ,double ,double ,QRgb );
    void scaling(float);
    void clear();
    void axes();
    void translate(int,int);
    void rotate(float);
    void clearval();

private slots:
    void on_scaling_clicked();
    void on_translating_clicked();
    void on_rotating_clicked();

private:
    Ui::MainWindow *ui;
    bool start;
    int ver,a[100],b[100];
};
#endif // MAINWINDOW_H
