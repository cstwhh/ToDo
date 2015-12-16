#include "setitem.h"
#include "ui_setitem.h"
#include<QDateTime>
#include<QDebug>

setItem::setItem(MainWindow *parent, int month, int day, int hour, int minute, QString toDo, QString more) :
    QDialog(parent),
    ui(new Ui::setItem)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/blue.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation)));
    this->setPalette(palette);

    this->parent=parent;
    ui->monthBox->setValue(month);
    ui->dayBox->setValue(day);
    ui->hourBox->setValue(hour);
    ui->minuteBox->setValue(minute);
    ui->toDoEdit->setText(toDo);
    ui->moreEdit->setText(more);
}

setItem::~setItem()
{
    delete ui;
}

void setItem::on_okButton_clicked()
{
    QString itemStr="";
    itemStr.append(QDateTime::currentDateTime().toString("yyyy")+"/");
    itemStr.append(QString::number(ui->monthBox->value())+"/");
    itemStr.append(QString::number(ui->dayBox->value())+"/");
    itemStr.append(QString::number(ui->hourBox->value())+"/");
    itemStr.append(QString::number(ui->minuteBox->value())+"#");
    itemStr.append(ui->toDoEdit->toPlainText());
    itemStr.append("#"+ui->moreEdit->toPlainText());
    parent->addItemFromDialog(itemStr);
    this->accept();
}

void setItem::on_cancel_clicked()
{
    this->reject();
}
