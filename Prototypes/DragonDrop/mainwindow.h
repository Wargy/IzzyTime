#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>
#include <QFile>
#include <QDate>
#include <QTableWidget>
#include <QTime>
#include <QTimer>
#include <QJsonObject>
#include "note.h"

#define PASTYEARS   -5
#define FUTUREYEARS 6
#define MONTHS      12
#define HOURS       24
#define PERIOD      60000   //ms

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
 /*   struct Note
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
    };*/

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_twYear_itemClicked(QTableWidgetItem *item);
    void on_twMonth_itemClicked(QTableWidgetItem *item);
    void on_twDay_itemClicked(QTableWidgetItem *item);
    void on_btCurDate_clicked();
    void on_twTaskField_itemDoubleClicked(QTableWidgetItem *item);
    bool isSelDatePresented();
    void sendFile();
    void readJsonObject(const QJsonObject json, Note &note);
    void writeJsonObject(QJsonObject &json, Note note);
    void loadFileJson();
    void saveFileJson();

    void on_btDay_clicked();

private:
    void fillYearTable(QTableWidget& tableYear);
    void fillMonthTable(QTableWidget& tableMonth);
    void fillDayTable(QTableWidget& tableDay, int daysInMonth);
    void standartStuffForAllTables(QTableWidget& table);
    void fillTaskField();
    void fillHangedTaskField();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow      *ui;
    QLinkedList<Note>    TimeLine_;
    QFile                fpjson_;
    QDate                curDate_;
    QDate                selDate_;
    QTimer              *timer_;
};

#endif // MAINWINDOW_H
