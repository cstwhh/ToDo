#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T19:18:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToDo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    setitem.cpp

HEADERS  += mainwindow.h \
    setitem.h

FORMS    += mainwindow.ui \
    setitem.ui

RESOURCES += \
    file.qrc

DISTFILES += \
    icon.rc
RC_FILE = icon.rc
