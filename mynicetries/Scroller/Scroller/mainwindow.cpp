#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curDate = QDate::currentDate();
    ui->textEditCur->setText(curDate.toString());
    selDate = curDate;
    ui->textEditSel->setText(selDate.toString());

    fillYearTable(*ui->twYear);
    fillMonthTable(*ui->twMonth);
    fillDayTable(*ui->twDay, curDate.daysInMonth());
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    ui->textEditSel->setText(selDate.toString());
    fillDayTable(*ui->twDay, selDate.daysInMonth());
}

void MainWindow::on_twMonth_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twMonth->rowCount(); i++)
        ui->twMonth->item(i, 0)->setBackground(Qt::magenta);
    item->setBackground(Qt::red);
    selDate.setDate(selDate.year(), item->row()+1, 1);
    ui->textEditSel->setText(selDate.toString());
    fillDayTable(*ui->twDay, selDate.daysInMonth());
}

void MainWindow::on_twDay_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twDay->rowCount(); i++)
        ui->twDay->item(i, 0)->setBackground(Qt::yellow);
    item->setBackground(Qt::red);
    selDate.setDate(selDate.year(), selDate.month(), item->row()+1);
    ui->textEditSel->setText(selDate.toString());
}
