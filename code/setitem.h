#ifndef SETITEM_H
#define SETITEM_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class setItem;
}

class setItem : public QDialog
{
    Q_OBJECT

public:
    explicit setItem(MainWindow *parent,int month,int hour,int day,int minute,QString toDo,QString more);
    ~setItem();

private slots:
    void on_okButton_clicked();

    void on_cancel_clicked();

private:
    Ui::setItem *ui;
    MainWindow *parent;
};

#endif // SETITEM_H
