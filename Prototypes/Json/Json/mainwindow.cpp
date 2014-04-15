#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curDate = QDate::currentDate();
    ui->btCurDate->setText("Today\n"+curDate.toString());
    selDate = curDate;
    ui->lSelDate->setText(selDate.toString());

    fillYearTable(*ui->twYear);
    fillMonthTable(*ui->twMonth);
    fillDayTable(*ui->twDay, curDate.daysInMonth());

    fillTaskField();
    standartStuffForAllTables(*ui->twTaskField);

    fillHangedTaskField();
    standartStuffForAllTables(*ui->twHangedTaskField);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Это нужно вынести в отдельный класс!
//--->
void MainWindow::fillYearTable(QTableWidget& tableYear)
{
    int j = 0;
    QTableWidgetItem *newItem;
    tableYear.setColumnCount(1);
    for(int i = PASTYEARS; i < FUTUREYEARS; i++)
    {
        tableYear.insertRow(j);
        newItem = new QTableWidgetItem();
        newItem->setText(QString::number(selDate.year() + i));
        tableYear.setItem(j, 0, newItem);
        if((selDate.year() + i) == selDate.year())
            tableYear.item(j, 0)->setBackground(Qt::red);
        else
            tableYear.item(j, 0)->setBackground(Qt::cyan);
        j++;
    }
    standartStuffForAllTables(*ui->twYear);
}

void MainWindow::fillMonthTable(QTableWidget& tableMonth)
{
    int j = 0;
    QTableWidgetItem *newItem;
    tableMonth.setColumnCount(1);
    for(int i = 1; i < MONTHS+1; i++)
    {
        tableMonth.insertRow(j);
        newItem = new QTableWidgetItem();
        newItem->setText(QString::number(i));
        tableMonth.setItem(j, 0, newItem);
        if(i == selDate.month())
            tableMonth.item(j, 0)->setBackground(Qt::red);
        else
            tableMonth.item(j, 0)->setBackground(Qt::magenta);
        j++;
    }
    standartStuffForAllTables(*ui->twMonth);
}

void MainWindow::fillDayTable(QTableWidget& tableDay, int daysInMonth)
{
    tableDay.clear();
    tableDay.setRowCount(0);

    int j = 0;
    QTableWidgetItem *newItem;
    tableDay.setColumnCount(1);
    for(int i = 1; i < daysInMonth+1; i++)
    {
        tableDay.insertRow(j);
        newItem = new QTableWidgetItem();
        newItem->setText(QString::number(i));
        tableDay.setItem(j, 0, newItem);
        if(i == selDate.day())
            tableDay.item(j, 0)->setBackground(Qt::red);
        else
            tableDay.item(j, 0)->setBackground(Qt::yellow);
        j++;
    }
    standartStuffForAllTables(*ui->twDay);
}

void MainWindow::standartStuffForAllTables(QTableWidget& table)
{
    table.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table.setEditTriggers(QAbstractItemView::NoEditTriggers);
    table.verticalHeader()->hide();
    table.horizontalHeader()->hide();
    table.setEditTriggers(QAbstractItemView::NoEditTriggers);
    table.setSelectionMode(QAbstractItemView::NoSelection);
    table.setFocusPolicy(Qt::NoFocus);
}

void MainWindow::on_twYear_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twYear->rowCount(); i++)
        ui->twYear->item(i, 0)->setBackground(Qt::cyan);
    item->setBackground(Qt::red);
    selDate.setDate(item->text().toInt(), selDate.month(), 1);
    ui->lSelDate->setText(selDate.toString());
    fillDayTable(*ui->twDay, selDate.daysInMonth());
}

void MainWindow::on_twMonth_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twMonth->rowCount(); i++)
        ui->twMonth->item(i, 0)->setBackground(Qt::magenta);
    item->setBackground(Qt::red);
    selDate.setDate(selDate.year(), item->row()+1, 1);
    ui->lSelDate->setText(selDate.toString());
    fillDayTable(*ui->twDay, selDate.daysInMonth());
}

void MainWindow::on_twDay_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twDay->rowCount(); i++)
        ui->twDay->item(i, 0)->setBackground(Qt::yellow);
    item->setBackground(Qt::red);
    selDate.setDate(selDate.year(), selDate.month(), item->row()+1);
    ui->lSelDate->setText(selDate.toString());
}

void MainWindow::on_btCurDate_clicked()
{
    selDate = curDate;
    ui->lSelDate->setText(selDate.toString());

    for(int i = 0; i < ui->twYear->rowCount(); i++)
    {
        if(ui->twYear->item(i, 0)->text().toInt() == selDate.year())
            ui->twYear->item(i, 0)->setBackgroundColor(Qt::red);
        else
            ui->twYear->item(i, 0)->setBackground(Qt::cyan);
    }

    for(int i = 0; i < ui->twMonth->rowCount(); i++)
    {
        if(ui->twMonth->item(i, 0)->text().toInt() == selDate.month())
            ui->twMonth->item(i, 0)->setBackground(Qt::red);
        else
            ui->twMonth->item(i, 0)->setBackground(Qt::magenta);
    }

    fillDayTable(*ui->twDay, selDate.daysInMonth());

    //...и прочая логика
}
//<---
//Это нужно вынести в отдельный класс!

void MainWindow::fillTaskField()
{
    QTime time;
    ui->twTaskField->setColumnCount(2);
    ui->twTaskField->setColumnWidth(0, 51);
    ui->twTaskField->setColumnWidth(1, 250);
    for(int i=0; i<HOURS; i++)
    {
        time.setHMS(i, 0, 0, 0);
        ui->twTaskField->insertRow(i);
        ui->twTaskField->setItem(i, 0, new QTableWidgetItem(time.toString()));
    }
    //...и считываем из контейнера
}

void MainWindow::fillHangedTaskField()
{
    ui->twHangedTaskField->setColumnCount(1);
    ui->twHangedTaskField->setColumnWidth(0, 301);
    for(int i=0; i<10; i++)
        ui->twHangedTaskField->insertRow(i);
    //...и выводим подвешенные задачки
}
