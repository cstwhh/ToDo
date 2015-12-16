#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QList>
#include<QListWidget>
#include<QTimer>
#include<QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void addItemFromDialog(QString info);
    void changeEvent(QEvent *e);
    ~MainWindow();

private slots:
    void on_forgotList_itemClicked(QListWidgetItem *item);

    void on_forgotList_itemChanged(QListWidgetItem *item);

    void on_forgotList_itemPressed(QListWidgetItem *item);

    void on_addButton_clicked();

    void on_toDoList_itemClicked(QListWidgetItem *item);

    void on_toDoList_itemChanged(QListWidgetItem *item);

    void on_toDoList_itemPressed(QListWidgetItem *item);

    void on_modifyButton_clicked();

    void on_removeButton_clicked();

    void onTimerOut();

    void updateIcon();

    void on_selectTab_tabBarClicked(int index);

    void on_selectTab_currentChanged(int index);

    void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::MainWindow *ui;
    QList<QString> forgotItemList,toDoItemList;
    QString forgotFile,toDoFile,timeFormat;
    QTimer* timer;
    QTimer* updateIconTimer;
    bool iconIndex;
    QSystemTrayIcon* trayicon;

    void loadForgotFormFile();
    void loadToDoFromFile();
    void loadFromFile(QString,QList<QString>&);
    void updateToFile(QString filePath,QList<QString>& list);

    void updateForgotList();
    void updateTodoList();
    void updateList(QList<QString>&,QListWidget*);

    void showItemMore(QList<QString>&,QListWidgetItem*);

    void removeItem(QListWidgetItem *item);
    void removeItem(QListWidget* listWidget,QListWidgetItem *item,QList<QString>& list,QString path);
    void addItem(QListWidget* listWidget,QString itemStr,QList<QString>& list,QString path);

    void setLabelText(QString);
    void setToDoItem(QListWidget* listWidget,QList<QString>& list);

    void dealErrorFormat(QString filePath);
   };

#endif // MAINWINDOW_H
