#-------------------------------------------------
#
# Project created by QtCreator 2014-06-03T03:31:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IzzyTime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    draglabel.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    note.h \
    draglabel.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    IzzyTime.qrc \
    IzzyTime.qrc \
    IzzyTime.qrc
