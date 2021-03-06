#include "draglabel.h"
#include <QPainter>

#include <QPalette>
#include <QPushButton>
#include <iostream>
//#include <QKeyEvent>

#define dr_width 210 // Ширина и высота облака по умолчанию
#define dr_height 40

#define min_width 210
#define min_height 40


using namespace std;
DragLabel::DragLabel(const QString &text, QWidget *parent, bool edit) //CONSTRUCTOR *** CONSTRUCTOR ****
     : QLabel(parent)
 {

     //QSize size = metric.size(Qt::TextSingleLine, text);
     QSize size (dr_width,dr_height); //Изначально создаём стандартную форму 210 на 60, если меняем методом, жарим repaint
     QImage image(size.width(), size.height(),
                      QImage::Format_ARGB32_Premultiplied);
     image.fill(qRgba(0, 0, 0, 0));

     //параметры шрифта
     QFont font;
     font.setStyleStrategy(QFont::ForceOutline);


     // Меняет настройку gradient, после чего запилит её в brush и нарисует прямоугольник
     QLinearGradient gradient(0, 0, 0, image.height()-1);
         gradient.setColorAt(0.0, Qt::transparent);
         gradient.setColorAt(0.2, QColor(250, 100, 100));
         gradient.setColorAt(0.8, QColor(250, 103, 100));
         gradient.setColorAt(1.0, QColor(252, 107, 100));
        // Рисование прямоугольника
         QPainter painter;
         painter.begin(&image);
         painter.setRenderHint(QPainter::Antialiasing);
         painter.setBrush(gradient);
         painter.drawRoundedRect(QRectF(0.5, 0.5, image.width()-1, image.height()-1),
                                 25, 25, Qt::RelativeSize);

         painter.setFont(font);
         painter.setBrush(Qt::black);
         painter.drawText(QRect(QPoint(6, 6), size), Qt::AlignCenter, text);
         painter.end();
         //загрузка картинки image, которую мы нарисовали
        setPixmap(QPixmap::fromImage(image));
        setMinimumWidth(min_width);
         setMinimumHeight(min_height);
         in_edit = new  QLineEdit (this);

         in_edit->setGeometry(size.width()*0.1,size.height()*0.45,size.width()*0.8,23);//x,y,width,height


           in_edit->setStyleSheet("background:transparent");

    m_edit=edit;
         if(m_edit==true)  {  in_edit->show(); } else  { in_edit->hide(); }

 //         QPixmap      pix("labla1.png");
         // setPixmap(pix);

             m_labelText = text;
             m_size=size;
            m_color.setRed(200);
            m_color.setGreen(30);
            m_color.setBlue(100);
// Добавлено Казанцевым Тёмной страшной ночью
            m_col=-1;
            m_row=-1;
    }

DragLabel::DragLabel(const DragLabel& obj)
{
 m_labelText=obj.getText();
 m_size=obj.getSize();
 m_color=obj.getColor();
 m_edit=obj.getEdit();
}



// Изменение формы задачи по ходу выполнения программы ******* REPAINT  REPAINT REPAINT ******
void DragLabel::repaint()
{
    QImage image(m_size.width(),m_size.height(),
                      QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0,0,0,0));

    QLinearGradient gradient(0, 0, 0, image.height()-1);
        gradient.setColorAt(0.0, Qt::transparent);
        gradient.setColorAt(0.2, QColor(m_color.red(), m_color.green(), m_color.blue()));
        gradient.setColorAt(0.8, QColor(m_color.red(), m_color.green(), m_color.blue()));
        gradient.setColorAt(1.0, QColor(m_color.red(), m_color.green(), m_color.blue()));


        setMinimumWidth(m_size.width());
        setMinimumHeight(m_size.height());
        // Рисование прямоугольника
         QPainter painter;
         painter.begin(&image);
         painter.setRenderHint(QPainter::Antialiasing);
         painter.setBrush(gradient);
         painter.drawRoundedRect(QRectF(0.5, 0.5, m_size.width()-1, m_size.height()-1),
                                 25, 25, Qt::RelativeSize);

         //параметры шрифта
         QFont font;
         font.setStyleStrategy(QFont::ForceOutline);
         painter.setFont(font);
         painter.setBrush(Qt::black);
         painter.drawText(QRect(QPoint(6, 6), m_size), Qt::AlignCenter, m_labelText);
         painter.end();




    setPixmap(QPixmap::fromImage(image));



}

 // GETTERS AND SETTERS
void DragLabel::setText(QString labelText)
{
    m_labelText=labelText;
}

QString DragLabel::getText() const
{
    return(m_labelText);
}

void DragLabel::setSize(QSize size)
{
    m_size=size;
}

QSize DragLabel::getSize() const
{
    return (m_size);
}

void DragLabel::setColor(int red,int green,int blue)
{
    m_color.setRed(red);
    m_color.setGreen(green);
    m_color.setBlue(blue);
}

QColor DragLabel::getColor() const
{
    return (m_color);
}

void DragLabel::setEdit(bool edit)
{
    m_edit=edit;
}

bool DragLabel::getEdit() const
{
    return (m_edit);
}

// Добавлено темной страшной ночью
void DragLabel::setRow(int row)
{
    m_row=row;
}

int DragLabel::getRow()
{
    return(m_row);
}

void DragLabel::setCol(int col)
{
    m_col=col;
}

int DragLabel::getCol()
{
    return(m_col);
}
