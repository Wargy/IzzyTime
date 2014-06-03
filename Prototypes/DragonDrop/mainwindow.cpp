#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "note.h"
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

    curDate_ = QDate::currentDate();
    ui->btCurDate->setText("Today\n"+curDate_.toString());
    selDate_ = curDate_;
    ui->lSelDate->setText(selDate_.toString());

    fillYearTable(*ui->twYear);
    fillMonthTable(*ui->twMonth);
    fillDayTable(*ui->twDay, curDate_.daysInMonth());

    fillTaskField();
    standartStuffForAllTables(*ui->twTaskField);

    fillHangedTaskField();
    standartStuffForAllTables(*ui->twHangedTaskField);

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(sendFile()));
    timer_->start(PERIOD);



    //added by Wargy 21 04 DRAGON DROP!

    int start_x,start_y=0; //Начальная координата на экране форм Drag_n_drop
    int dr_distance=0; //Расстояние между формами при подгрузке их из файла
       // if (QFile::exists("dictionary/words.txt")==false) cout<<"FILE  DICTIONARY NOT DETECTED!"<<endl;
       // QFile dictionaryFile("dictionary/words.txt");

     if (QFile::exists("dictionary/words.txt")==false) cout<<"FILE  DICTIONARY NOT DETECTED!"<<endl;
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
        newItem->setText(QString::number(selDate_.year() + i));
        tableYear.setItem(j, 0, newItem);
        if((selDate_.year() + i) == selDate_.year())
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
        if(i == selDate_.month())
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
        if(i == selDate_.day())
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
    selDate_.setDate(item->text().toInt(), selDate_.month(), 1);
    ui->lSelDate->setText(selDate_.toString());
    fillDayTable(*ui->twDay, selDate_.daysInMonth());
    //...и обновляем таблицу с задачами
    fillTaskField();
}

void MainWindow::on_twMonth_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twMonth->rowCount(); i++)
        ui->twMonth->item(i, 0)->setBackground(Qt::magenta);
    item->setBackground(Qt::red);
    selDate_.setDate(selDate_.year(), item->row()+1, 1);
    ui->lSelDate->setText(selDate_.toString());
    fillDayTable(*ui->twDay, selDate_.daysInMonth());
    //...и обновляем таблицу с задачами
    fillTaskField();
}

void MainWindow::on_twDay_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twDay->rowCount(); i++)
        ui->twDay->item(i, 0)->setBackground(Qt::yellow);
    item->setBackground(Qt::red);
    selDate_.setDate(selDate_.year(), selDate_.month(), item->row()+1);
    ui->lSelDate->setText(selDate_.toString());
    //...и обновляем таблицу с задачами
    fillTaskField();
}

void MainWindow::on_btCurDate_clicked()
{
    selDate_ = curDate_;
    ui->lSelDate->setText(selDate_.toString());

    for(int i = 0; i < ui->twYear->rowCount(); i++)
    {
        if(ui->twYear->item(i, 0)->text().toInt() == selDate_.year())
            ui->twYear->item(i, 0)->setBackgroundColor(Qt::red);
        else
            ui->twYear->item(i, 0)->setBackground(Qt::cyan);
    }

    for(int i = 0; i < ui->twMonth->rowCount(); i++)
    {
        if(ui->twMonth->item(i, 0)->text().toInt() == selDate_.month())
            ui->twMonth->item(i, 0)->setBackground(Qt::red);
        else
            ui->twMonth->item(i, 0)->setBackground(Qt::magenta);
    }

    fillDayTable(*ui->twDay, selDate_.daysInMonth());

    //...и обновляем таблицу с задачами
    fillTaskField();
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
    loadFileJson();
    if(TimeLine_.size() != 0)
    {
        QLinkedList<Note>::iterator it;
        int i = 0, r = 0;
        if(isSelDatePresented())
        {
            for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
            {
                if(it->getDateStart() == selDate_)
                {
                    r = it->getTimeStart().hour();
                    ui->twTaskField->setItem(r, 1, new QTableWidgetItem(it->getTitle()
                                                                        +" "
                                                                        +it->getText()));
                }
                i++;
            }
        }
    }
}

void MainWindow::fillHangedTaskField()
{
    ui->twHangedTaskField->setColumnCount(1);
    ui->twHangedTaskField->setColumnWidth(0, 301);
    for(int i=0; i<10; i++)
        ui->twHangedTaskField->insertRow(i);
    //...и выводим подвешенные задачки
}

void MainWindow::on_twTaskField_itemDoubleClicked(QTableWidgetItem *item)
{
    DragLabel* label = new DragLabel("text",this);
    label->move(400,200);
    label->setColor(200,0,200);
    label->setSize(QSize(240,40));
    int lab_y = item->row()*ui->twTaskField->rowHeight(1);
    lab_y += ui->twTaskField->y();
    int lab_x = ui->twTaskField->x();
    lab_x+= ui->twTaskField->columnWidth(0);
    label->setGeometry(lab_x,lab_y,1,1);

    label->repaint();

            label->show();

//    Dialog *dialog = new Dialog(this);
//    Note note;
//    if(dialog->exec() == QDialog::Accepted)
//    {
//        note.setTitle(dialog->getTitle());
//        note.setText(dialog->getText());
//        note.setDateStart(selDate_);
//        note.setDateEnd(selDate_);
//        note.setTimeStart(QTime::fromString(item->text()));
//        note.setTimeEnd(QTime::fromString(item->text()));

//        qDebug() << note.getTitle();
//        qDebug() << note.getText();
//        qDebug() << note.getDateStart();
//        qDebug() << note.getDateEnd();
//        qDebug() << note.getTimeStart();
//        qDebug() << note.getTimeEnd();

//        ui->twTaskField->setItem(item->row(), 1, new QTableWidgetItem(dialog->getTitle()
//                                                                      +" "
//                                                                      +dialog->getText()));
//        //и записываем в контейнер:
//        if(TimeLine_.size() != 0)
//        {
//            QLinkedList<Note>::iterator it;
//            int i = 0;
//            if(isSelDatePresented())
//            {
//                for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
//                {
//                    if(it->getDateStart() == note.getDateStart())
//                    {
//                        TimeLine_.insert(it, note);
//                        break;
//                    }
//                    i++;
//                }
//            }
//            else
//                TimeLine_.push_back(note);
//        }
//        else
//            TimeLine_.append(note);
//    }
//    saveFileJson(); //<--- temp
}

bool MainWindow::isSelDatePresented()
{
    QLinkedList<Note>::iterator it;
    for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
    {
        qDebug() << it->getDateStart();
        qDebug() << selDate_;
        qDebug() << (it->getDateStart() == selDate_);
        if(it->getDateStart() == selDate_)
            return true;
    }
    return false;
}

void MainWindow::sendFile()
{
    QMessageBox::information(this,
                             "Timer Event",
                             "Just a proof for successful timer work.\n"
                             "That's all. Really.",
                             QMessageBox::Ok);
    //тут запись в файл и отправка на сервер
    //saveFileJson();
    //...
}



//----- собственно, работа с json: -----
void MainWindow::readJsonObject(const QJsonObject json, Note &note)
{
    note.setDateStart(QDate::fromString(json["DateStart"].toString()));
    note.setDateEnd(QDate::fromString(json["DateEnd"].toString()));
    note.setTimeStart(QTime::fromString(json["TimeStart"].toString()));
    note.setTimeEnd(QTime::fromString(json["TimeEnd"].toString()));
    note.setTitle(json["Title"].toString());
    note.setText(json["Text"].toString());
//    item.Priority
//    item.Reminder
//    item.Color
//    item.Mask

    qDebug() << note.getTitle();
    qDebug() << note.getText();
    qDebug() << note.getDateStart();
    qDebug() << note.getDateEnd();
    qDebug() << note.getTimeStart();
    qDebug() << note.getTimeEnd();
}

void MainWindow::writeJsonObject(QJsonObject &json, Note note)
{
    json["DateStart"] = note.getDateStart().toString();
    json["DateEnd"]   = note.getDateEnd().toString();
    json["TimeStart"] = note.getTimeStart().toString();
    json["TimeEnd"]   = note.getTimeEnd().toString();
    json["Title"]     = note.getTitle();
    json["Text"]      = note.getText();
}

void MainWindow::loadFileJson()
{
    fpjson_.setFileName("data.json");
    if(!fpjson_.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,
                             "Внимание!",
                             "Не удалось открыть файл json",
                             QMessageBox::Ok);\
        return;
    }
    QByteArray data = fpjson_.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    TimeLine_.clear();
    QJsonObject json = doc.object();
    QJsonArray jarr = json["TimeLine"].toArray();
    Note note;
    QJsonObject jobj;
    for(int i=0; i<jarr.size(); ++i)
    {
        jobj = jarr[i].toObject();
        readJsonObject(jobj, note);
        TimeLine_.append(note);
    }
    fpjson_.close();
}

void MainWindow::saveFileJson()
{
    fpjson_.setFileName("data.json");
    if(!fpjson_.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this,
                             "Внимание!",
                             "Не удалось открыть файл json",
                             QMessageBox::Ok);
        return;
    }
    QJsonObject json;
    QJsonArray jarr;
    QLinkedList<Note>::iterator it;
    for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
    {
        writeJsonObject(json, *it);
        jarr.append(json);
    }
    QJsonObject jobj;
    jobj["TimeLine"] = jarr;
    QJsonDocument doc(jobj);
    fpjson_.write(doc.toJson());
    fpjson_.close();
}



//DRAGON DROP!!!!
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos())); //указатель на объект, который находится в ивенте
    if (!child)
        return;

;
if(child->in_edit->text().length()>1)    child->setText(child->in_edit->text());
    child->in_edit->hide();
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


         QByteArray itemData = mime->data("application/x-fridgemagnet");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly); //считывает инфо о наших магнитах из потока и пересоздаёт их

                QString text;
                QPoint offset;
                dataStream >> text >> offset;

                //
                DragLabel *newLabel = new DragLabel(text, this);
                         newLabel->move(event->pos() - offset);
                        //отображает при двух кликах, можно делать паузу между кликами или тыкать что угодно


                    // newLabel->in_edit.show();

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

void MainWindow::on_btDay_clicked()
{
    for (int i=0;i<23;i++)
    {
        cout<<"item height="<<ui->twTaskField->rowHeight(i)<<endl;
    }
}
