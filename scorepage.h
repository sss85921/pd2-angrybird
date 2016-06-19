#ifndef SCOREPAGE_H
#define SCOREPAGE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class scorepage;
}

class scorepage : public QDialog
{
    Q_OBJECT

public:
    explicit scorepage(QWidget *parent = 0);
    ~scorepage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::scorepage *ui;
};

#endif // SCOREPAGE_H
