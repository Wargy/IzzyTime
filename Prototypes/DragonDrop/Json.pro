#-------------------------------------------------
#
# Project created by QtCreator 2014-04-13T00:01:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Json
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scroller.cpp \
    dialog.cpp \
    draglabel.cpp

HEADERS  += mainwindow.h \
    scroller.h \
    dialog.h \
    draglabel.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    Json_res.qrc
