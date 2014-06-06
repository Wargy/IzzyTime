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
#include <QNetworkAccessManager>
#include <QNetworkReply>


#define table_space 55 //отступ слева от первой колонки таблицы задач со временем

using namespace std;
bool hideall=false;
QLinkedList<DragLabel> draglist;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    changed_ = false; //никаких изменений еще нет

    manager_ = new QNetworkAccessManager(this);

    connect(manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotFinished(QNetworkReply*)));

    curDate_ = QDate::currentDate();
    ui->btCurDate->setText("Today\n"+curDate_.toString());
    selDate_ = curDate_;
    ui->lSelDate->setText(selDate_.toString());

    fillYearTable(*ui->twYear);
    fillMonthTable(*ui->twMonth);
    fillDayTable(*ui->twDay, curDate_.daysInMonth());

    fillTaskField();
    standartStuffForAllTables(*ui->twTaskField);
    standartStuffForAllTables(*ui->twHangedTaskField);

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(sendFile()));
    timer_->start(PERIOD);



    //added by Wargy 21 04 DRAGON DROP!

    int start_x,start_y=0; //Начальная координата на экране форм Drag_n_drop
    int dr_distance=0; //Расстояние между формами при подгрузке их из файла
   // if (QFile::exists("dictionary/words.txt")==false) cout<<"FILE NOT DETECTED!"<<endl;
   // QFile dictionaryFile("dictionary/words.txt");

    //dictionaryFile.open(QFile::ReadOnly);

    //QTextStream inputStream(&dictionaryFile);

    start_x=450;
    start_y=60;
    dr_distance=70;

     setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::slotFinished(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        QMessageBox::critical(0,
                              tr("Error"),
                              tr("An error while download is occured"));
    }
    else
    {
        //перезаписываем файл - теперь все записи сохранены
        QLinkedList<Note>::iterator it;
        for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
        {
            if(it->getStatus() == false)
                it->setStatus(true);
        }
        saveFileJson();
    }

    reply->deleteLater();
}

void MainWindow::sync(QByteArray data)
{
    QUrl url("http://localhost/sync");
    url.setPort(8081);
  //  url.setPort(8081);
  //  url.setHost("localhost");
  //  url.setPath("localhost/sync");
    QNetworkRequest request;
request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QJsonDocument doc(json);
//    QByteArray data(doc.toJson());
qDebug()<<request.header(QNetworkRequest::ContentTypeHeader);
    qDebug() << "Sync" << QString::fromUtf8(data.data(), data.size());

   QNetworkReply *reply= manager_->post(request, data);


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
            tableYear.item(j, 0)->setSelected(true);
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
            tableMonth.item(j, 0)->setSelected(true);
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
            tableDay.item(j, 0)->setSelected(true);
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
        if(ui->twYear->item(i, 0)->isSelected())
            ui->twYear->item(i, 0)->setSelected(false);
    item->setSelected(true);
    selDate_.setDate(item->text().toInt(), selDate_.month(), 1);
    ui->lSelDate->setText(selDate_.toString());
    fillDayTable(*ui->twDay, selDate_.daysInMonth());
    //...и обновляем таблицу с задачами
    fillTaskField();
}

void MainWindow::on_twMonth_itemClicked(QTableWidgetItem *item)
{
    for(int i = 0; i < ui->twMonth->rowCount(); i++)
        if(ui->twMonth->item(i, 0)->isSelected())
            ui->twMonth->item(i, 0)->setSelected(false);
    item->setSelected(true);
    selDate_.setDate(selDate_.year(), item->row()+1, 1);
    ui->lSelDate->setText(selDate_.toString());
    fillDayTable(*ui->twDay, selDate_.daysInMonth());
    //...и обновляем таблицу с задачами
    fillTaskField();
}

void MainWindow::on_twDay_itemClicked(QTableWidgetItem *item) // Функция заполнения дня
{
    hideall=true;
   //clearDragon(draglist);
   // MainWindow::


    for(int i = 0; i < ui->twDay->rowCount(); i++)
        if(ui->twDay->item(i, 0)->isSelected())
            ui->twDay->item(i, 0)->setSelected(false);
    item->setSelected(true);
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
            ui->twYear->item(i, 0)->setSelected(true);
        else
            ui->twYear->item(i, 0)->setSelected(false);
    }

    for(int i = 0; i < ui->twMonth->rowCount(); i++)
    {
        if(ui->twMonth->item(i, 0)->text().toInt() == selDate_.month())
            ui->twMonth->item(i, 0)->setSelected(true);
        else
            ui->twMonth->item(i, 0)->setSelected(false);
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

    //подготавливаем табличку для датированных записей
    ui->twTaskField->setColumnCount(2);
    ui->twTaskField->setColumnWidth(0, 51);
    ui->twTaskField->setColumnWidth(1, 250);

    //...и для подвешенных задачек
    ui->twHangedTaskField->setColumnCount(1);
    ui->twHangedTaskField->setColumnWidth(0, 301);
    for(int i=0; i<10; i++)
        ui->twHangedTaskField->insertRow(i);

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
        int i = 0, r = 0, rr = 0;
        if(isSelDatePresented())
        {
            for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
            {
                if(it->getDateStart() == selDate_)
                {
                    if(it->getTimeStart().toString() == "") // если эта задача подвешенная
                    {
                        //adding dragonDROP

                        ui->twHangedTaskField->setItem(rr, 0, new QTableWidgetItem(it->getTitle()
                                                                                  +" "
                                                                                  +it->getText()));
                         DragLabel* taskline = new DragLabel("",this,true);
                         taskline->setText(it->getTitle()+" "+it->getText());
                        // Этот кусок добавлен Варгушей поздно ночью
                         taskline->setRow(rr);
                         taskline->setCol(1);

                        //
                         int lab_y = ui->twHangedTaskField->y();
                         int lab_x = ui->twHangedTaskField->x();
                         QSize size=taskline->getSize();
                         int task_height = size.height();
                         taskline->setGeometry(QRect(lab_x+table_space/2,lab_y+rr*task_height,1,1));
                         taskline->repaint();
                      // int rw=
                         if (hideall==true) taskline->hide();
                         draglist.push_back(*taskline);
                       //  taskline= draglist.first();
                         rr++;
                    }
                    else
                    { //если задача привязана по времени
                        r = it->getTimeStart().hour();
                        ui->twTaskField->setItem(r, 1, new QTableWidgetItem(it->getTitle()
                                                                            +" "
                                                                            +it->getText()));
                        DragLabel* taskline = new DragLabel("",this,true);
                        taskline->setText(it->getTitle()+" "+it->getText());
                        // Этот кусок добавлен Варгушей поздно ночью
                         taskline->setRow(r);
                         taskline->setCol(0);
                        //

                        int lab_y = ui->twTaskField->y();
                        int lab_x = ui->twTaskField->x();
                        QSize size=taskline->getSize();
                        int task_height = size.height();
                        taskline->setGeometry(QRect(lab_x+table_space,lab_y+r*task_height,1,1));
                        taskline->repaint();
                        if (hideall==true) taskline->hide();
                        draglist.append(*taskline);

                        r++;
                        //r -> номер строки
                    }// Конец вставки Dragon Dropa!
                }
                i++;
            }
        }
    }
}

void MainWindow::on_twTaskField_itemDoubleClicked(QTableWidgetItem *item) // Создание диалогового окна
{
    Dialog *dialog = new Dialog(this);
    Note note;
    if(dialog->exec() == QDialog::Accepted)
    {
        note.setStatus(false); //т.к. еще не сохранена
        note.setTitle(dialog->getTitle());
        note.setText(dialog->getText());
        note.setDateStart(selDate_);
        note.setDateEnd(selDate_);
        note.setTimeStart(QTime::fromString(item->text()));
        note.setTimeEnd(QTime::fromString(item->text()));

//        qDebug() << note.getTitle();
//        qDebug() << note.getText();
//        qDebug() << note.getDateStart();
//        qDebug() << note.getDateEnd();
//        qDebug() << note.getTimeStart();
//        qDebug() << note.getTimeEnd();

        ui->twTaskField->setItem(item->row(), 1, new QTableWidgetItem(dialog->getTitle()
                                                                      +" "
                                                                     +dialog->getText()));
       //Добавлено Казанцевым  4.06.14 в 12:10  - Создание драгндропа вместо текстовой записи
        DragLabel* taskline = new DragLabel("",this,true);
        taskline->setText(dialog->getTitle()+" "+dialog->getText());
        int lab_y = ui->twTaskField->y();
        int lab_x = ui->twTaskField->x();
        QSize size=taskline->getSize();
        int task_height = size.height();
        taskline->setGeometry(QRect(lab_x+table_space,lab_y+item->row()*30,1,1));
        taskline->repaint();
        taskline->show();
        if (hideall==true) taskline->hide();
         draglist.push_back(*taskline);
        //----

        //и записываем в контейнер:
        if(TimeLine_.size() != 0)
        {
            QLinkedList<Note>::iterator it;
            int i = 0;
            if(isSelDatePresented())
            {
                for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
                {
                    if(it->getDateStart() == note.getDateStart())
                    {
                        TimeLine_.insert(it, note);
                        break;
                    }
                    i++;
                }
            }
            else
                TimeLine_.push_back(note);
        }
        else
            TimeLine_.append(note);
    }
    saveFileJson(); //<--- temp
    changed_ = true;
}

void MainWindow::on_twHangedTaskField_cellDoubleClicked(int row, int column)
{
    Dialog *dialog = new Dialog(this);
    Note note;
    if(dialog->exec() == QDialog::Accepted)
    {
        note.setStatus(false); //т.к. еще не сохранена
        note.setTitle(dialog->getTitle());
        note.setText(dialog->getText());
        note.setDateStart(selDate_);
        note.setDateEnd(selDate_);

//        qDebug() << note.getTitle();
//        qDebug() << note.getText();
//        qDebug() << note.getDateStart();
//        qDebug() << note.getDateEnd();
//        qDebug() << note.getTimeStart();
//        qDebug() << note.getTimeEnd();

        ui->twHangedTaskField->setItem(row, column, new QTableWidgetItem(dialog->getTitle()
                                                                         +" "
                                                                         +dialog->getText()));
        //и записываем в контейнер:
        if(TimeLine_.size() != 0)
        {
            QLinkedList<Note>::iterator it;
            int i = 0;
            if(isSelDatePresented())
            {
                for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
                {
                    if(it->getDateStart() == note.getDateStart())
                    {
                        TimeLine_.insert(it, note);
                        break;
                    }
                    i++;
                }
            }
            else
                TimeLine_.push_back(note);
        }
        else
            TimeLine_.append(note);
    }
    saveFileJson(); //<--- temp
    changed_ = true;
}

bool MainWindow::isSelDatePresented()
{
    QLinkedList<Note>::iterator it;
    for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
    {
//        qDebug() << it->getDateStart();
//        qDebug() << selDate_;
//        qDebug() << (it->getDateStart() == selDate_);
        if(it->getDateStart() == selDate_)
            return true;
    }
    return false;
}

void MainWindow::sendFile()
{
//    QMessageBox::information(this,
//                             "Timer Event",
//                             "Just a proof for successful timer work.\n"
//                             "That's all. Really.",
//                             QMessageBox::Ok);
    //тут запись в файл и отправка на сервер
    if(changed_)
    {
        //сохраняем в локальном файле...
        //(да, в "несохраненном" виде - на случай отсутствия сети)
        saveFileJson();

        fpjson_.setFileName("./data2.json");
        if(!fpjson_.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,
                                 "Внимание!",
                                 "Не удалось открыть файл json",
                                 QMessageBox::Ok);\
            return;
        }
        QByteArray data = fpjson_.readAll(); //читаем весь массив
        fpjson_.close();

        //... и отправляем на сервер
        sync(data);

        changed_ = false;
    }
    //...
}



//----- собственно, работа с json: -----
void MainWindow::readJsonObject(const QJsonObject json, Note &note)
{
    note.setStatus(json["saved"].toBool());
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

//    qDebug() << note.getTitle();
//    qDebug() << note.getText();
//    qDebug() << note.getDateStart();
//    qDebug() << note.getDateEnd();
//    qDebug() << note.getTimeStart();
//    qDebug() << note.getTimeEnd();
}

void MainWindow::writeJsonObject(QJsonObject &json, Note note)
{
    json["saved"]     = note.getStatus();
    json["DateStart"] = note.getDateStart().isNull()?"null":note.getDateStart().toString("yyyy-MM-dd");
    json["DateEnd"]   = note.getDateEnd().isNull()?"null":note.getDateEnd().toString("yyyy-MM-dd");
    json["TimeStart"] = note.getTimeStart().isNull()?"null":note.getTimeStart().toString("HH:mm:ss");
    json["TimeEnd"]   = note.getTimeEnd().isNull()?"null":note.getTimeEnd().toString("HH:mm:ss");
    json["Title"]     = note.getTitle();
    json["Text"]      = note.getText();
}

void MainWindow::loadFileJson()
{
    fpjson_.setFileName("./data2.json");
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
    fpjson_.setFileName("./data2.json");
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
//----- собственно, работа с json -----



//DRAGON DROP!!!!
void MainWindow::mousePressEvent(QMouseEvent *event) // Реакция на нажатие мыши в области объекта
{
    int col,row;
    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos())); //указатель на объект, который находится в ивенте
 draglist.push_back(*child);
    if (!child)
        return;

;
    if (hideall==true) child->hide();
    // Изменение содержимого облачка. Если в строке ввода есть текст, заменить текст облака на вводный
    if (child->in_edit->text().length()>1)
    {
        child->setText(child->in_edit->text());
        // Этот кусок добавлен Варгушей поздно ночью

         col=child->getCol();
         row=child->getRow();
         cout<<"row before = "<<endl;
         ui->twTaskField->setEnabled(true);

        if(col==0) { ui->twTaskField->setItem(row,1,new QTableWidgetItem(child->in_edit->text())); }
                if(col==1) { ui->twHangedTaskField->setItem(row-1,1,new QTableWidgetItem(child->in_edit->text())); cout<<"row="<<child->getRow(); }
        else cout<<"col="<<col<<endl;
         // ACHTUNG
                Note note;
                note.setTitle(child->getText());
                note.setDateStart(selDate_);
                note.setDateEnd(selDate_);
//                note.setTimeStart(QTime::fromString(ui->twHangedTaskField->item(0,0)->text()));
//                note.setTimeEnd(QTime::fromString(ui->twHangedTaskField->item(1,0)->text()));

                if(TimeLine_.size() != 0)
                {
                    QLinkedList<Note>::iterator it;
                    int i = 0;
                    if(isSelDatePresented())
                    {
                        for(it = TimeLine_.begin(); it != TimeLine_.end(); ++it)
                        {
                            if(it->getDateStart() == note.getDateStart())
                            {
                                TimeLine_.insert(it, note);
                                break;
                            }
                            i++;
                        }
                    }
                    else
                        TimeLine_.push_back(note);
                }
                else
                    TimeLine_.append(note);
                saveFileJson();

                //ACHTUNG!
    }
    if (child->getEdit()==true) child->setEdit(false); else child->setEdit(true);
    // Сокрытие/отображение лайнедита после клика

    QPoint hotSpot = event->pos() - child->pos();//расположение ивента - расположение объекта,
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    //Передаём в поток данных текст объекта, его координату и состояние лайнедита
    dataStream << child->getText() << QPoint(hotSpot) << child->getEdit()<< child->getRow() << child->getCol() ;
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

void MainWindow::dropEvent(QDropEvent *event) //Drop event, метод описывающий отпускание объекта
 {
     if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
         const QMimeData *mime = event->mimeData();

         QByteArray itemData = mime->data("application/x-fridgemagnet");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly); //считывает инфо о наших магнитах из потока и пересоздаёт их

                QString text;
                QPoint offset;
                int col,row;

                bool edit;
                dataStream >>text >> offset >> edit>> col>>row ;

                DragLabel *newLabel = new DragLabel(text, this,edit);
                        newLabel->setRow(row);
                        newLabel->setCol(col);
                         newLabel->move(event->pos() - offset);
                         if (newLabel->pos().x()>440) newLabel->setCol(1); else newLabel->setCol(0);
                        //отображает при двух кликах, можно делать паузу между кликами или тыкать что угодно


                         newLabel->show();
                         if (hideall==true) newLabel->hide();
                         newLabel->setAttribute(Qt::WA_DeleteOnClose);
                             draglist.push_back(*newLabel);
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
                 DragLabel *newLabel = new DragLabel(piece, this,true);
                 newLabel->move(position);

                 newLabel->show();
                 if (hideall==true) newLabel->hide();
                  draglist.push_back(*newLabel);
                 newLabel->setAttribute(Qt::WA_DeleteOnClose);

                 position += QPoint(newLabel->width(), 0);
             }

             event->acceptProposedAction();
         } else {
             event->ignore();
         }
     }

void MainWindow::clearDragon(QLinkedList<DragLabel> dr_list)
{
 QLinkedList<DragLabel>::iterator it;

 DragLabel tst =dr_list.takeFirst();

 cout<<"TST="<<tst.getText().toStdString()<<endl;
 tst.setText("1111111");
 tst.repaint();
 tst.show();
// dr_list.removeFirst();
 // delete(&it);
 //dr_list.clear();

}

//DRAGON DROP!!!
