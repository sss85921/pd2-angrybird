#include "scorepage.h"
#include "ui_scorepage.h"
#include <QDialog>
#include "mainwindow.h"

scorepage::scorepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scorepage)
{
    ui->setupUi(this);
}

scorepage::~scorepage()
{
    delete ui;
}

void scorepage::on_pushButton_clicked()
{
    this->hide();
    MainWindow main;
    main.exec();

}

void scorepage::on_pushButton_2_clicked()
{
    close();
}
