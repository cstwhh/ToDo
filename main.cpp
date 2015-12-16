#include "mainwindow.h"
#include <QApplication>
#include<QFile>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(
        "QPushButton{font-family:""Consolas"";font-size: 20px;color: #fff;background-color: #5cb85c;border-color: #4cae4c;height:35px;width:80px;border-radius: 5px 5px 0 0;}"
        "QPushButton:hover{color: #fff;background-color: #449d44; border-color: #398439;}"
        "QPushButton#removeButton,#cancel{color: #fff;background-color: #d9534f;border-color: #d43f3a;height:35px;width:80px;border-radius: 5px 5px 0 0;}"
        "QPushButton#removeButton:hover,#cancel:hover{color: #fff;background-color: #c9302c;border-color: #ac2925;}"

        "QListWidget,QTabWidget{border: 0px ;color: #fff;background-color: #5bc0de;border-color: #46b8da;} "
        "QListWidget::item{border-radius: 2px 2px 0px 0px;height:32px;}"
        "QListWidget#toDoList::item:selected {background-color: #5cb85c;padding:0px;margin:1px;}"
        "QListWidget#toDoList::item:hover{background-color: #5cb85c;height:40px;}"
        "QListWidget#forgotList::item:selected {background-color: #f0ad4e;padding:0px;margin:1px;}"
        "QListWidget#forgotList::item:hover{background-color: #f0ad4e;height:40px;}"
        "QListWidget{font-family:""微软雅黑"";font-size: 20px;text-align: center;}"

        "QLabel{font-family:""微软雅黑"";font-size: 20px;text-align: center;border-radius: 5px 5px 0px 0px;}"
        "QLabel#label_5,#label_6{font-family:""Consolas"";}"

        "QTabBar::tab:!selected{color: #fff;background-color: #337ab7;border-color: #2e6da4;height:25px;width:80px;}"
        "QTabBar::tab:selected,QTabBar::tab:hover{color: #333;background-color: #fff;border-color: #ccc;height:25px;width:80px;}"
        "QTabBar::tab{font-family:""Consolas"";font-size: 18px;text-align: center;}"

        "QLCDNumber{color: #CC0033;background-color: #000000;text-align: center;}"

        "QSpinBox {padding-right: 15px;border-image: url(:/frame.png) 4;border-width: 2;height:25px;width:50px;}"
        "QSpinBox::up-button {subcontrol-origin: border;subcontrol-position: top right;width: 16px; border-image: url(:/spinup.png) 1; border-width: 1px;}"
        "QSpinBox::up-button:hover {border-image: url(:/spinup_hover.png) 1;}"
        "QSpinBox::up-button:pressed {border-image: url(:/spinup_pressed.png) 1;}"
        "QSpinBox::up-arrow {image: url(:/up_arrow.png);width: 7px;height: 7px;}"
        "QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off {image: url(:/up_arrow_disabled.png);}"
        "QSpinBox::down-button {subcontrol-origin: border;subcontrol-position: bottom right;width: 16px;border-image: url(:/spindown.png) 1;border-width: 1px;border-top-width: 0;}"
        "QSpinBox::down-button:hover {border-image: url(:/spindown_hover.png) 1;}"
        "QSpinBox::down-button:pressed {border-image: url(:/spindown_pressed.png) 1;}"
        "QSpinBox::down-arrow {image: url(:/down_arrow.png);width: 7px;height: 7px;}"
        "QSpinBox::down-arrow:disabled,QSpinBox::down-arrow:off {image: url(:/down_arrow_disabled.png);}"

        "QLineEdit,QTextEdit{font-family:""微软雅黑"";font-size: 15px;width: 100%;height:20px; padding: 6px 12px;line-height: 1.42857143;color: #555;background-color: #fff;border: 1px solid #ccc;border-radius: 4px;}"
                );
    MainWindow w;
    w.show();
    return a.exec();
}
