#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFile>
#include <QDate>
#include <QTableWidget>
#include <QTime>

#define PASTYEARS   -5
#define FUTUREYEARS 6
#define MONTHS      12
#define HOURS       24

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Note
    {
        QDate   DateStart;
        QDate   DateEnd;
        QTime   TimeStart;
        QTime   TimeEnd;
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

private slots:
    void on_twYear_itemClicked(QTableWidgetItem *item);
    void on_twMonth_itemClicked(QTableWidgetItem *item);
    void on_twDay_itemClicked(QTableWidgetItem *item);
    void on_btCurDate_clicked();

private:
    void fillYearTable(QTableWidget& tableYear);
    void fillMonthTable(QTableWidget& tableMonth);
    void fillDayTable(QTableWidget& tableDay, int daysInMonth);
    void standartStuffForAllTables(QTableWidget& table);
    void fillTaskField();
    void fillHangedTaskField();

private:
    Ui::MainWindow *ui;
    QList<Note>    TimeLine_;
    QFile          fpjson_;
    QDate          curDate;
    QDate          selDate;
};

#endif // MAINWINDOW_H
