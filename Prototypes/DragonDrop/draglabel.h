#ifndef DRAGLABEL_H
#define DRAGLABEL_H
#include <QLabel>
#include <QString>
#include <QColor>
#include <QLineEdit>

class DragLabel : public QLabel
{
public:
    DragLabel(const QString &text, QWidget *parent);
    void repaint();

    void setSize(QSize size);
    QSize getSize() const;

    void setText(QString labelText);
    QString getText() const;

    void setColor(int red, int green, int blue);
    QColor getColor() const;

    void setEdit(bool edit);
    bool getEdit() const;

    //void keyPressEvent(QKeyEvent *event);

      QLineEdit* in_edit;
private:
    QString m_labelText;
    QSize m_size;
    QColor m_color;
    bool m_edit; //Состояние edit. Если m_edit TRUE то полоска ввода видна.


};

#endif // DRAGLABEL_H
