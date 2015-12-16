#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setitem.h"
#include<QFile>
#include<QTextStream>
#include<QDateTime>
#include<QPixmap>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateIconTimer=new QTimer();
    //updateIconTimer->setInterval(750);
    connect(updateIconTimer,SIGNAL(timeout()),this,SLOT(updateIcon()));

    this->setWindowIcon(QIcon(":/image/To_Do_List.ico"));
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/image/code.jpg");
    palette.setBrush(QPalette::Background, QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);

    timeFormat="年月日时分";
    forgotFile="forgotFile.txt";
    toDoFile="toDoFile.txt";
    loadForgotFormFile();
    loadToDoFromFile();
    updateForgotList();
    updateTodoList();
    onTimerOut();

    timer=new QTimer();
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    trayicon = new QSystemTrayIcon(this);
    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));
    QIcon icon(":/image/To_Do_List_Hide2.ico");
    trayicon->setIcon(icon);
    trayicon->setToolTip("Things To Do");
    trayicon->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadForgotFormFile()   {
    loadFromFile(forgotFile,forgotItemList);
}

void MainWindow::loadToDoFromFile() {
    loadFromFile(toDoFile,toDoItemList);
}

void MainWindow::loadFromFile(QString filePath,QList<QString>& list)   {
    QFile f(filePath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  {
        setLabelText("卧槽找不到文件啦!");
        return;
    }
    QTextStream readStream(&f);
    QString listItem;
    list.clear();
    while(!readStream.atEnd())  {
        listItem=readStream.readLine();
        list.append(listItem);
    }
    f.close();
}

void MainWindow::updateToFile(QString filePath,QList<QString>& list)    {
    //qDebug()<<list;
    QFile f(filePath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  {
        qDebug()<<"卧槽找不到文件啦1!";
        return;
    }
    f.close();
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))  {
        setLabelText("卧槽找不到文件啦!");
        qDebug()<<"卧槽找不到文件啦2!"<<f.error();
        return;
    }
    QTextStream writeStream(&f);
    for(int i=0;i<list.size();++i)  {
        writeStream<<list.at(i)<<"\n";
        writeStream.flush();
    }
    f.close();
    dealErrorFormat(filePath);
}

void MainWindow::updateForgotList() {
    updateList(forgotItemList,ui->forgotList);
}

void MainWindow::updateTodoList()  {
    updateList(toDoItemList,ui->toDoList);
}

void MainWindow::updateList(QList<QString>& list,QListWidget* listWidget)   {
    listWidget->clear();
    for(int i=0;i<list.size();++i)  {
        QString item=list.at(i).split('#').at(1);
        listWidget->addItem(item);
    }
}

void MainWindow::setLabelText(QString text) {
    ui->label->setText(text);
    ui->label2->setText(text);
}

void MainWindow::on_forgotList_itemClicked(QListWidgetItem *item)
{
    showItemMore(forgotItemList,item);
}

void MainWindow::on_forgotList_itemChanged(QListWidgetItem *item)
{
    showItemMore(forgotItemList,item);
}

void MainWindow::on_forgotList_itemPressed(QListWidgetItem *item)
{
    showItemMore(forgotItemList,item);
}

void MainWindow::on_toDoList_itemClicked(QListWidgetItem *item)
{
    showItemMore(toDoItemList,item);
}

void MainWindow::on_toDoList_itemChanged(QListWidgetItem *item)
{
    showItemMore(toDoItemList,item);
}

void MainWindow::on_toDoList_itemPressed(QListWidgetItem *item)
{
    showItemMore(toDoItemList,item);
}

void MainWindow::showItemMore(QList<QString>& list,QListWidgetItem *item)    {
    QString target=item->text();
    for(int i=0;i<list.size();++i)
        if(list.at(i).split('#').at(1)==target) {
            QList<QString> timeList=list.at(i).split('#').at(0).split('/');
            QString thisTimeFormat=timeFormat.mid(timeFormat.length()-timeList.size());
            QString timeText;
            for(int j=0;j<timeList.size();++j)  {
                timeText.append(timeList.at(j));
                timeText.append(QString(thisTimeFormat.at(j)));
            }
            ui->lineEdit->setText(timeText);


            QDateTime selectTime(QDate(timeList.at(0).toInt(),timeList.at(1).toInt(),timeList.at(2).toInt()),
                                 QTime(timeList.at(3).toInt(),timeList.at(4).toInt()));
            int secs=QDateTime::currentDateTime().secsTo(selectTime);
            if(secs<0&&ui->toDoList->findItems(item->text(),Qt::MatchContains).size()!=0)  {
                QString target=item->text();
                for(int i=0;i<toDoItemList.size();++i)
                    if(toDoItemList.at(i).split('#').at(1)==target) {
                        addItem(ui->forgotList,toDoItemList.at(i),forgotItemList,forgotFile);
                        break;
                    }
                removeItem(ui->toDoList,item,toDoItemList,toDoFile);
                return setToDoItem(ui->toDoList,toDoItemList);
            }
            else if(secs>0&&ui->forgotList->findItems(item->text(),Qt::MatchContains).size()!=0)    {
                QString target=item->text();
                for(int i=0;i<forgotItemList.size();++i)
                    if(forgotItemList.at(i).split('#').at(1)==target) {
                        addItem(ui->toDoList,forgotItemList.at(i),toDoItemList,toDoFile);
                        break;
                    }
                removeItem(ui->forgotList,item,forgotItemList,forgotFile);
                return setToDoItem(ui->forgotList,forgotItemList);
            }
            if(ui->selectTab->currentIndex()==1&&secs<10*60&&toDoItemList.size()>0)    {
                if(updateIconTimer!=NULL&&!updateIconTimer->isActive()) {
                    updateIconTimer->start(750);
                }
            }
            else {
                if(updateIconTimer!=NULL&&updateIconTimer->isActive()) {
                    updateIconTimer->stop();
                    trayicon->setIcon(QIcon(":/image/To_Do_List.ico"));
                }
            }
            int hour=secs/3600;
            int minute=(secs-hour*3600)/60;
            int second=(secs-hour*3600-minute*60);
            ui->timeLCD->setDigitCount(10);
            //设置显示的模式为十进制
            ui->timeLCD->setMode(QLCDNumber::Dec);
            //设置显示方式
            ui->timeLCD->setSegmentStyle(QLCDNumber::Flat);
            ui->timeLCD->display(QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second));
            if(list.at(i).split('#').size()>2)
                setLabelText(list.at(i).split('#').at(2));
            else setLabelText("Wu Hanghang");
            break;
        }
}

void MainWindow::on_addButton_clicked()
{
    QList<QString> date=QDateTime::currentDateTime().toString("M d h m").split(' ');
    setItem* dialog=new setItem(this,date.at(0).toInt(),date.at(1).toInt(),date.at(2).toInt(),date.at(3).toInt(),
                                "","");
    dialog->show();
}

void MainWindow::removeItem(QListWidgetItem *item)  {
    if(ui->toDoList->findItems(item->text(),Qt::MatchContains).size()!=0)  {
        QString target=item->text();
        for(int i=0;i<toDoItemList.size();++i)
            if(toDoItemList.at(i).split('#').at(1)==target) {
                addItem(ui->forgotList,toDoItemList.at(i),forgotItemList,forgotFile);
                break;
            }
        removeItem(ui->toDoList,item,toDoItemList,toDoFile);
    }
    else {
        removeItem(ui->forgotList,item,forgotItemList,forgotFile);
    }
}

void MainWindow::removeItem(QListWidget* listWidget,QListWidgetItem *item,
                            QList<QString>& list,QString path)  {
    QString target=item->text();
    //qDebug()<<target;
    for(int i=0;i<list.size();++i)
        if(list.at(i).split('#').at(1)==target) {
            list.removeAt(i);
            break;
        }
    updateList(list,listWidget);
    setToDoItem(listWidget,list);
    updateToFile(path,list);
}

void MainWindow::addItem(QListWidget* listWidget,QString itemStr,
             QList<QString>& list,QString path) {
    list.append(itemStr);
    qSort(list);
    updateList(list,listWidget);
    updateToFile(path,list);
}

void MainWindow::addItemFromDialog(QString info)    {
    if(ui->selectTab->currentIndex()==1)
        addItem(ui->toDoList,info,toDoItemList,toDoFile);
    else
        addItem(ui->forgotList,info,forgotItemList,forgotFile);
}

void MainWindow::on_modifyButton_clicked()
{
    QListWidget* curWidget;
    QList<QString>* curList;
    QString curFile;
    if(ui->selectTab->currentIndex()==0)    {
        curWidget=ui->forgotList;
        curList=&forgotItemList;
        curFile=forgotFile;
    }
    else    {
        curWidget=ui->toDoList;
        curList=&toDoItemList;
        curFile=toDoFile;
    }
    if(curWidget->currentItem()!=NULL) {
        QListWidgetItem* curItem=curWidget->currentItem();
        QString target=curItem->text();
        for(int i=0;i<curList->size();++i)
            if(curList->at(i).split('#').at(1)==target) {
                QList<QString> time=curList->at(i).split('#').at(0).split('/');
                QString more="";
                if(curList->at(i).split('#').size()>2)
                    more=curList->at(i).split('#').at(2);
                setItem* dialog=new setItem(this,time.at(1).toInt(),time.at(2).toInt(),time.at(3).toInt(),time.at(4).toInt(),
                                            target,more);
                removeItem(curWidget,curItem,*curList,curFile);

                dialog->show();
                break;
            }
    }
}

void MainWindow::on_removeButton_clicked()
{
    if(ui->selectTab->currentIndex()==1&&ui->toDoList->currentItem()!=NULL)
        removeItem(ui->toDoList,ui->toDoList->currentItem(),toDoItemList,toDoFile);
    else if(ui->selectTab->currentIndex()==0&&ui->forgotList->currentItem()!=NULL)
        removeItem(ui->forgotList,ui->forgotList->currentItem(),forgotItemList,forgotFile);
}

void MainWindow::setToDoItem(QListWidget* listWidget,QList<QString>& list)  {
    if(list.size()>0)  {
        listWidget->setCurrentItem(listWidget->item(0));
        return showItemMore(list,listWidget->item(0));
    }
}

void MainWindow::onTimerOut()  {
    if(!isActiveWindow())
        ui->selectTab->setCurrentIndex(1);
    if(ui->selectTab->currentIndex()==0)    {
        if(ui->forgotList->currentItem()!=NULL)
            showItemMore(forgotItemList,ui->forgotList->currentItem());
        else setToDoItem(ui->forgotList,forgotItemList);
    }
    else    {
        if(ui->toDoList->currentItem()!=NULL)
            showItemMore(toDoItemList,ui->toDoList->currentItem());
        else setToDoItem(ui->toDoList,toDoItemList);
    }
}

void MainWindow::on_selectTab_tabBarClicked(int)
{
    onTimerOut();
}

void MainWindow::on_selectTab_currentChanged(int)
{
    onTimerOut();
}

void MainWindow::dealErrorFormat(QString filePath)  {
    QFile f(filePath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  {
        setLabelText("卧槽找不到文件啦!");
        return;
    }
    QTextStream readStream(&f);
    QString lastItem;
    while(!readStream.atEnd()&&(lastItem.length()==0||lastItem=="\n"))
        lastItem=readStream.readLine();
    QString listItem;
    QList<QString> list;
    list.clear();
    while(!readStream.atEnd())  {
        listItem=readStream.readLine();
        if(listItem.length()<1||(listItem.at(0)<'0'||listItem.at(0)>'9'))   {
            lastItem+=(" "+listItem);
        }
        else    {
            list.append(lastItem);
            lastItem=listItem;
        }
    }
    if(listItem.length()<1||(listItem.at(0)<'0'||listItem.at(0)>'9'))
        list.append(lastItem);
    else
        list.append(listItem);
    f.close();
    if(!f.open(QIODevice::WriteOnly))   {
        setLabelText("卧槽找不到文件啦!");
        return;
    }
    QTextStream write(&f);
    for(int i=0;i<list.size()-1;++i)
        write<<list.at(i)<<"\n";
    write<<list.at(list.size()-1);
    f.close();
}

void MainWindow::changeEvent(QEvent *e)
{
    if((e->type()==QEvent::WindowStateChange)&&this->isMinimized())
        this->hide();
}

void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger||reason==QSystemTrayIcon::DoubleClick)  {
        if(this->isHidden())    {
            this->show();
            this->setWindowState(Qt::WindowActive);
            this->activateWindow();
        }
        else
            this->hide();
    }
}

void MainWindow::updateIcon()   {
    QApplication::alert(this,750);
    if(iconIndex)   {
        trayicon->setIcon(QIcon(":/image/To_Do_List.ico"));
        iconIndex=false;
    }
    else    {
        trayicon->setIcon(QIcon(":/image/To_Do_List_Hide2.ico"));
        iconIndex=true;
    }
    //iconIndex=!iconIndex;
}
