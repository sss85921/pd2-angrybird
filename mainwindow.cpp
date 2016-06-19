#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>


extern int restart;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelpoint->setPixmap(QPixmap(":/image/5000.png"));
    ui->labelpoint_2->setPixmap(QPixmap(":/image/10000.png"));
    ui->labelpoint_3->setPixmap(QPixmap(":/image/15000.png"));
    ui->labelpoint_4->setPixmap(QPixmap(":/image/20000.png"));
    ui->labelpoint->hide();
    ui->labelpoint_2->hide();
    ui->labelpoint_3->hide();
    ui->labelpoint_4->hide();
    ui->labelegg->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(click==1 || click%2==0)
    {
        QPoint mouse_pos = event->pos();
        if((mouse_pos.x()-x_start-40)*(mouse_pos.x()-x_start-40)+(mouse_pos.y()-y_start-30)*(mouse_pos.y()-y_start-30)<=9000)
        {
            x_release = mouse_pos.x()-40;
            y_release = mouse_pos.y()-30;

            ui->labelbird->setGeometry(mouse_pos.x()-40,mouse_pos.y()-45,70,70);
        }
        //qDebug()<<"("<<mouse_pos.x()<<","<<mouse_pos.y()<<")";
            //qDebug()<<click<<"\n";
        //qDebug()<<"("<<x_release<<","<<y_release<<")";
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{

    click++;
    if(click==3)
    {
        tx=0;
        ty=0;
        x_release=bird_x;
        y_release=bird_y;
        v_horizontal = now_speed_x*3.0f;
        v_vertical = now_speed_y*3.0f;
    }
    if(click==5)
    {
        tx=0;
        ty=0;
        x_release=bird_x;
        y_release=bird_y;
        v_horizontal = 0;
        if(now_speed_y>=0)
            v_vertical =-50;
        if(now_speed_y<=0)
            v_vertical =50;

    }
    if(click==7)
    {

        ty=0;
        y_release=bird_y;
        v_vertical = now_speed_y+80.5f;

        ui->labelegg->setGeometry(bird_x,bird_y,50,50);
        ui->labelegg->show();
        egg_start_x=bird_x;
        egg_start_y=bird_y;
        egg_speed_horizontal=0;
        egg_speed_vertical=-100.0f;






    }

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug()<<click<<"\n";
    if(click==1 || click%2==0)
    {
        r_x = x_start - x_release;
        r_y = y_release - y_start;
        v_horizontal = r_x*1.2f;
        v_vertical = r_y*1.2f;

        //qDebug()<<"release\n";
        //qDebug()<<x_release<<"\n";
        //qDebug()<<y_release<<"\n";
        stop=0;
        timer_for_bird();
    }


}

void MainWindow::timer_for_bird(){

    //qDebug()<<"timer";
    timer = new QTimer(this);
    timer->setInterval(0.0001);
    connect(timer,SIGNAL(timeout()),this,SLOT(bird_fly()));
    timer->start();

}

void MainWindow::bird_fly()
{
    //qDebug()<<"bird_fly\n";
    if(stop==1)disconnect(timer,SIGNAL(timeout()),this,SLOT(bird_fly()));

    //qDebug()<<"("<<v<<")\n";



    if(bird_y<=560)
    {

        tx+=0.0001;//時間變化
        ty+=0.0001;//時間變化
        bird_x = x_release + ( v_horizontal*tx );//x方向軌跡變化
        bird_y = y_release - ( v_vertical*ty - 0.5*9.8*ty*ty);//y方向軌跡變化
        now_speed_y=v_vertical-9.8*ty;
        now_speed_x=v_horizontal;
        if(bird_x>=1600 || bird_x<=0){
            bird_order++;
            if(bird_order==2){
                ui->labelbird->setPixmap(QPixmap(":/image/bird2.png"));
                ui->labelbird_2->hide();
            }
            if(bird_order==3){
                ui->labelbird->setPixmap(QPixmap(":/image/bird4.png"));
                ui->labelbird_3->hide();
            }
            if(bird_order==4){
                ui->labelbird->setPixmap(QPixmap(":/image/bird5.png"));
                ui->labelbird_4->hide();
            }
            if(bird_order==5){
                ui->labelbird->hide();
            }
            //qDebug()<<"1122";
            ui->labelbird->setGeometry(160,460,70,70);
            tx=0;
            ty=0;
            now_speed_y=0;
            now_speed_x=0;
            v_vertical=0;
            v_horizontal=0;
            x_release=160;
            y_release=460;
            stop=1;
        }
        if(bird_y>=558 && hit>=-20)
        {
            ty=0;
            //tx=0;
            y_release=bird_y;
            //x_release=bird_x;
            v_vertical=-1.0*(now_speed_y/1.7f);

            hit-=10;

            if(hit<-20){
                bird_order++;
                if(bird_order==2){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird2.png"));
                    ui->labelbird_2->hide();
                }
                if(bird_order==3){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird4.png"));
                    ui->labelbird_3->hide();
                }
                if(bird_order==4){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird5.png"));
                    ui->labelbird_4->hide();
                }
                if(bird_order==5){
                    ui->labelbird->hide();
                }

                ui->labelbird->setGeometry(160,460,70,70);
                tx=0;
                ty=0;
                now_speed_y=0;
                now_speed_x=0;
                v_vertical=0;
                v_horizontal=0;
                x_release=160;
                y_release=460;
                stop=1;
            }
        }
        if(490-bird_x<=0.1 && bird_x<=490 && bird_y>=192 && hit!=1)
        {

            tx=0;
            hit=1;
            x_release=bird_x;
            v_horizontal=-1.0*(now_speed_x/1.7f);

        }
        if(bird_x>=490 && bird_x<=655 && 192-bird_y<=0.1 && bird_y<192 && hit!=2)
        {

            ty=0;
            hit=2;
            y_release=bird_y;
            v_vertical=-1.0*(now_speed_y/1.7f);

        }

        if(bird_x-655<=0.1 && bird_x>=655 && bird_y>=192 && hit!=3)
        {

            tx=0;
            hit=3;
            x_release=bird_x;
            v_horizontal=-1.0*(now_speed_x/1.7f);

        }
        if(bird_x>=655 && bird_x<=770 && 560-bird_y<=0.1 && bird_y<560 && hit!=14)
        {

            ty=0;
            hit=14;
            y_release=bird_y;
            v_vertical=-1.0*(now_speed_y/1.7f);

            num++;
            if(num==10){
                bird_order++;
                if(bird_order==2){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird2.png"));
                    ui->labelbird_2->hide();
                }
                if(bird_order==3){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird4.png"));
                    ui->labelbird_3->hide();
                }
                if(bird_order==4){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird5.png"));
                    ui->labelbird_4->hide();
                }
                if(bird_order==5){
                    ui->labelbird->hide();
                }

                ui->labelbird->setGeometry(160,460,70,70);
                tx=0;
                ty=0;
                now_speed_y=0;
                now_speed_x=0;
                v_vertical=0;
                v_horizontal=0;
                x_release=160;
                y_release=460;
                stop=1;
            }

        }
        if(770-bird_x<=0.1 && bird_x<=770 && bird_y>=295 && hit!=4)
        {

            tx=0;
            hit=4;
            x_release=bird_x;
            v_horizontal=-1.0*(now_speed_x/1.7f);

        }
        if(bird_x>=770 && bird_x<=932 && 295-bird_y<=0.1 && bird_y<295 && hit!=5)
        {

            ty=0;
            hit=5;
            y_release=bird_y;
            v_vertical=-1.0*(now_speed_y/1.7f);

        }
        if(bird_x-932<=0.1 && bird_x>=932 && bird_y>=295 && hit!=6)
        {

            tx=0;
            hit=6;
            x_release=bird_x;
            v_horizontal=-1.0*(now_speed_x/1.7f);

        }


        if(1213-bird_x<=0.1 && bird_x<=1213 && bird_y>=55 && hit!=11)
        {

            tx=0;
            hit=11;
            x_release=bird_x;
            v_horizontal=-1.0*(now_speed_x/1.7f);

        }
        if(bird_x>=932 && bird_x<=1213 && 560-bird_y<=0.1 && bird_y<560 && hit!=15)
        {

            ty=0;
            hit=15;
            y_release=bird_y;
            v_vertical=-1.0*(now_speed_y/1.7f);

            num++;
            if(num==10){
                bird_order++;
                if(bird_order==2){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird2.png"));
                    ui->labelbird_2->hide();
                }
                if(bird_order==3){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird4.png"));
                    ui->labelbird_3->hide();
                }
                if(bird_order==4){
                    ui->labelbird->setPixmap(QPixmap(":/image/bird5.png"));
                    ui->labelbird_4->hide();
                }
                if(bird_order==5){
                    ui->labelbird->hide();
                }

                ui->labelbird->setGeometry(160,460,70,70);
                tx=0;
                ty=0;
                now_speed_y=0;
                now_speed_x=0;
                v_vertical=0;
                v_horizontal=0;
                x_release=160;
                y_release=460;
                stop=1;
            }

        }
        if(bird_x>=1213 && bird_x<=1368 && 55-bird_y<=0.1 && bird_y<55 && hit!=12)
        {

            ty=0;
            hit=12;
            y_release=bird_y;
            v_vertical=-1.0*(now_speed_y/1.7f);

        }
        if(bird_x-1368<=0.1 && bird_x>=1368 && bird_y>=55 && hit!=13)
        {

            tx=0;
            hit=13;
            x_release=bird_x;
            v_horizontal=-1.0*(now_speed_x/1.7f);

        }

        now_speed_y=v_vertical-9.8*ty;
        now_speed_x=v_horizontal;

        ui->labelbird->setGeometry(bird_x,bird_y,81,81);


        //qDebug()<<"("<<bird_x<<","<<bird_y<<")\n";
        //qDebug()<<v_horizontal<<"\n";
        //qDebug()<<v_vertical<<"\n";


        if(bird_x>=640 && bird_x<=775 && bird_y>=495 && bird_y<=560)
        {
            ui->pig->hide();
            hit_pig_1=1;
        }
        if(bird_x>=780 && bird_x<=915 && bird_y>=212 && bird_y<=277)
        {
            ui->pig_2->hide();
            hit_pig_2=1;
        }
        if(bird_x>=1000 && bird_x<=1135 && bird_y>=490 && bird_y<=545)
        {
            ui->pig_3->hide();
            hit_pig_3=1;
        }
        if(bird_x>=1220 && bird_x<=1350 && bird_y>=-30 && bird_y<=35)
        {
            ui->pig_4->hide();
            hit_pig_4=1;
        }
        hit_pig_num = hit_pig_1 + hit_pig_2 + hit_pig_3 + hit_pig_4;
        if(hit_pig_num==1){
            ui->point0->hide();
            ui->labelpoint->show();
        }
        if(hit_pig_num==2){
            ui->labelpoint->hide();
            ui->labelpoint_2->show();
        }
        if(hit_pig_num==3){
            ui->labelpoint_2->hide();
            ui->labelpoint_3->show();
        }
        if(hit_pig_num==4){
            ui->labelpoint_3->hide();
            ui->labelpoint_4->show();
        }

        egg_pos_x=egg_start_x;
        egg_pos_y=egg_start_y-(egg_speed_vertical*ty-0.5*9.8*ty*ty);
        ui->labelegg->setGeometry(egg_pos_x,egg_pos_y,50,50);

        if(egg_pos_y>=560){
            ui->labelegg->hide();
        }
        if(egg_pos_y>=192 && egg_pos_x>=490 && egg_pos_x<=655){
            ui->labelegg->hide();
        }
        if(egg_pos_y>=295 && egg_pos_x>=770 &&egg_pos_x<=932){
            ui->labelegg->hide();
        }
        if(egg_pos_y>=55 && egg_pos_x>=1213 &&egg_pos_x<=1368){
            ui->labelegg->hide();
        }
        if(egg_pos_x>=640 && egg_pos_x<=775 && egg_pos_y>=495)
        {
            ui->pig->hide();
            hit_pig_1=1;
        }
        if(egg_pos_x>=780 && egg_pos_x<=915 && egg_pos_y>=212)
        {
            ui->pig_2->hide();
            hit_pig_2=1;
        }
        if(egg_pos_x>=1000 && egg_pos_x<=1135 && egg_pos_y>=490)
        {
            ui->pig_3->hide();
            hit_pig_3=1;
        }
        if(egg_pos_x>=1220 && egg_pos_x<=1350 && egg_pos_y>=-30)
        {
            ui->pig_4->hide();
            hit_pig_4=1;
        }

    }
    /*if(hit_pig_num==4 || bird_order==5){
        this->hide();
        scorepage score;
        score.exec();
    }*/

}

void MainWindow::on_pushButton_clicked()
{
    restart=0;
    this->close();

}

void MainWindow::on_pushButton_2_clicked()
{

    this->close();
}
