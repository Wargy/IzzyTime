#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T00:40:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IzzyTime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    dialog.cpp \
    draglabel.cpp

HEADERS  += mainwindow.h \
    note.h \
    dialog.h \
    draglabel.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    IzzyTime.qrc
