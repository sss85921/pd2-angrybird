#include "mainwindow.h"
#include <QApplication>
#include <QDialog>

extern int restart=1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    for(;;){
        MainWindow w;
        w.show();
        if(restart==0)break;
        a.exec();
    }
    return 0;
}
