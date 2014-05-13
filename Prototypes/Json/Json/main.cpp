#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    return a.exec();
}
