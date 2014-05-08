#include "dragwidget.h"
#include <QFile>
#include <QTextStream>
#include <draglabel.h>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include <iostream>
#include <stdio.h>
#include <string>
#include <QLineEdit>
using namespace std;
DragWidget::DragWidget(QWidget *parent)
     : QWidget(parent)
 {
     QFile dictionaryFile(":/dictionary/words.txt");

     dictionaryFile.open(QFile::ReadOnly);
     QTextStream inputStream(&dictionaryFile);

     int x = 470;
          int y = 73;

          while (!inputStream.atEnd()) {
              QString word;
              word = inputStream.readLine();

              cout<<"word="<<word.toStdString()<<endl;
              if (!word.isEmpty()) {
                  DragLabel *wordLabel = new DragLabel(word, this);
                  wordLabel->move(x, y);
                  wordLabel->show();
                  wordLabel->setAttribute(Qt::WA_DeleteOnClose);
                  x += wordLabel->width() + 2;
      #if defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
                  if (x >= 345) {
      #else
                  if (x >= 600) {
      #endif
                      x = 470;
                      y += wordLabel->height() + 2;

                  }
              }
          }
#ifndef Q_WS_S60
    //Fridge magnets is used for demoing Qt on S60 and themed backgrounds look better than white
    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::transparent);
    setPalette(newPalette);
    #endif

    //setMinimumSize(400, qMax(200, y));
    setMinimumSize(400, qMax(200, y));

    setWindowTitle(tr("Fridge Magnets"));
      setAcceptDrops(true);
}//end of constructor

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos())); //указатель на объект, который находится в ивенте?
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

          if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                 child->close();
             else
                 child->show();


 }

void DragWidget::dragEnterEvent(QDragEnterEvent *event) // вход в состояние  перетаскивания
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

void DragWidget::dragMoveEvent(QDragMoveEvent *event) //dragmove - пока в процессе перемещения
{
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);

            event->accept();
        } else {
                event->ignore();
            //  QPoint t_pos = event->pos();
             if (event->pos().x()<1100) {
            event->acceptProposedAction();

                 }
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }

}

void DragWidget::dropEvent(QDropEvent *event) //Drop event, технология отпускания объекта?
 {
     if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
         const QMimeData *mime = event->mimeData();

         //

         QByteArray itemData = mime->data("application/x-fridgemagnet");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly);

                QString text;
                QPoint offset;
                dataStream >> text >> offset;

                //
                DragLabel *newLabel = new DragLabel(text, this);
                         newLabel->move(event->pos() - offset);
                        //отображает при двух кликах, можно делать паузу между кликами или тыкать что угодно
                         QSize size_l(200,100);
                         QSize size_2(260,60);


                         if (event->pos().x()<400)
                         newLabel->setSize(size_l);
                         else newLabel->setSize(size_2);

                        newLabel->repaint(20,20,200);
                        // newLabel->setText("proverka");

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
//mime - тип перенесённого объекта. Нужен для взаимодействия нескольких виджетов разного типа
