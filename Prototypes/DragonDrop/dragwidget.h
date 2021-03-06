#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H
#include <QWidget>


class DragWidget : public QWidget
 {
 public:
     DragWidget(QWidget *parent = 0);

 protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     void mousePressEvent(QMouseEvent *event);

 };

#endif // DRAGWIDGET_H
