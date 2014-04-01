#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTableWidget>

#define PASTYEARS -5
#define FUTUREYEARS 6
#define MONTHS 12

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_twYear_itemClicked(QTableWidgetItem *item);
    void on_twMonth_itemClicked(QTableWidgetItem *item);
    void on_twDay_itemClicked(QTableWidgetItem *item);

private:
    void fillYearTable(QTableWidget& tableYear);
    void fillMonthTable(QTableWidget& tableMonth);
    void fillDayTable(QTableWidget& tableDay, int daysInMonth);
    void standartStuffForAllTables(QTableWidget& table);

private:
    Ui::MainWindow *ui;
    QDate curDate;
    QDate selDate;
};

#endif // MAINWINDOW_H
