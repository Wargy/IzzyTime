#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Note
    {
        double  DateStart;
        double  DateEnd;
        double  TimeStart;
        double  TimeEnd;
        QString Title;
        QString Text;
        bool    Priority;
        bool    Reminder;
        int     Color;
        char    Mask;
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<Note>    TimeLine_;
    QFile          fpjson_;
};

#endif // MAINWINDOW_H
