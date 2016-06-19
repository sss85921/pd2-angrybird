#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>
#include <QGraphicsview>
#include <QDialog>
#include <QGraphicsItem>
#include <stdlib.h>
#include <time.h>
#include <QLabel>
#include <QPixmap>
#include <math.h>
#include <QtMath>
#include <QtCore/qmath.h>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMouseEvent>
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    int click=0;
    int press=0;
    int num=0;
    int hit=100;
    int hit_pig_1=0;
    int hit_pig_2=0;
    int hit_pig_3=0;
    int hit_pig_4=0;
    int hit_pig_num;
    int bird_order=1;
    int stop;
    float tx=0;
    float ty=0;
    float x_release ;
    float y_release ;
    float x_start = 160;
    float y_start = 460;
    float bird_x;
    float bird_y;
    float r_x;
    float r_y;
    float now_speed_y;
    float now_speed_x;
    float now_bird_y;
    float now_bird_x;
    float v;
    float v_horizontal;
    float v_vertical;
    float egg_pos_x;
    float egg_pos_y;
    float egg_speed_horizontal;
    float egg_speed_vertical;
    float egg_start_x;
    float egg_start_y;

    QTimer *timer;

public slots:
    void on_pushButton_clicked();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timer_for_bird();
    void bird_fly();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
