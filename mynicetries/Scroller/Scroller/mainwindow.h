#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTableWidget>

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
    void fillDayTable(QTableWidget& tableDay);
    void standartStuffForAllTables(QTableWidget& table);

private:
    Ui::MainWindow *ui;
    QDate curDate;
    //int curRow;
    QDate selDate;
    //int selRow;
};

#endif // MAINWINDOW_H
