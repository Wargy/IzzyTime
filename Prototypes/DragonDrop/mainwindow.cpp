#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <draglabel.h>
#include <QSize>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPalette>
#include <iostream>
#include <QFile>

using namespace std;

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

    //added by Wargy 21 04 DRAGON DROP!

    int start_x,start_y=0; //Начальная координата на экране форм Drag_n_drop
    int dr_distance=0; //Расстояние между формами при подгрузке их из файла
    if (QFile::exists("dictionary/words.txt")==false) cout<<"FILE NOT DETECTED!"<<endl;
    QFile dictionaryFile("dictionary/words.txt");

    dictionaryFile.open(QFile::ReadOnly);

    QTextStream inputStream(&dictionaryFile);

    start_x=450;
    start_y=60;
    dr_distance=70;
    while (!inputStream.atEnd()) {
        QString word;
        word = inputStream.readLine();

          if (!word.isEmpty()) {
        DragLabel *wordLabel = new DragLabel(word, this);
    wordLabel->move(start_x, start_y);
    wordLabel->show();
    wordLabel->setAttribute(Qt::WA_DeleteOnClose);
    start_y+=dr_distance;
          } //   if (!word.isEmpty()) {
     } //  while (!inputStream.atEnd())


     setAcceptDrops(true);

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

//DRAGON DROP!!!!
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos())); //указатель на объект, который находится в ивенте
    if (!child)
        return;

;
    QPoint hotSpot = event->pos() - child->pos();//расположение ивента - расположение объекта,




    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << child->getText() << QPoint(hotSpot); //Походу даже вытаскивает из потока данных! Нужно как то извратиться и создать поток цветов!

    QMimeData *mimeData = new QMimeData;
       mimeData->setData("application/x-fridgemagnet", itemData);
       mimeData->setText(child->getText());

       QDrag *drag = new QDrag(this);
           drag->setMimeData(mimeData);
           drag->setPixmap(*child->pixmap());
           drag->setHotSpot(hotSpot);

           child->hide();
           child->setEdit(true);

          if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                 child->close();
             else
                 child->show();


 }

void MainWindow::dragEnterEvent(QDragEnterEvent *event) // вход в состояние  перетаскивания
 {
     if (event->mimeData()->hasFormat("application/x-fridgemagnet")) { //Если ивент принадлежит  драглейблу
         if (children().contains(event->source())) {
             event->setDropAction(Qt::MoveAction);

             event->accept();

         } else {
            event->acceptProposedAction(); //Если не принимать acceptAction  виджет будет переползать на место.

         }
         //
     } else if (event->mimeData()->hasText()) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }

void MainWindow::dragMoveEvent(QDragMoveEvent *event) //dragmove - пока в процессе перемещения
{
    event->ignore();
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);

            event->accept();
        } else {
                event->ignore();
            //  QPoint t_pos = event->pos();
             if (event->pos().x()<700&&event->pos().y()<550) {


            event->acceptProposedAction();

                 }
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }

}

void MainWindow::dropEvent(QDropEvent *event) //Drop event, метод отпускания объекта?
 {
     if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
         const QMimeData *mime = event->mimeData();

         //

         QByteArray itemData = mime->data("application/x-fridgemagnet");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly); //считывает инфо о наших магнитах из потока и пересоздаёт их

                QString text;
                QPoint offset;
                dataStream >> text >> offset;

                //
                DragLabel *newLabel = new DragLabel(text, this);
                         newLabel->move(event->pos() - offset);
                        //отображает при двух кликах, можно делать паузу между кликами или тыкать что угодно


                         newLabel->show();
                         newLabel->setAttribute(Qt::WA_DeleteOnClose);

                         if (event->source() == this) {
                             event->setDropAction(Qt::MoveAction);
                             event->accept();
                         } else {
                             event->acceptProposedAction();
                         }
                         //
     } else if (event->mimeData()->hasText()) {
             QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
                                  QString::SkipEmptyParts);
             QPoint position = event->pos();

             foreach (QString piece, pieces) {
                 DragLabel *newLabel = new DragLabel(piece, this);
                 newLabel->move(position);

                 newLabel->show();
                 newLabel->setAttribute(Qt::WA_DeleteOnClose);

                 position += QPoint(newLabel->width(), 0);
             }

             event->acceptProposedAction();
         } else {
             event->ignore();
         }
     }



//DRAGON DROP!!!
