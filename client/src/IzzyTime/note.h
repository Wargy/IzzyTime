#ifndef NOTE_H
#define NOTE_H

#include <QDate>
#include <QTime>
#include <QString>

class Note
{
public:
    Note();

    QDate getDateStart() { return DateStart; }

    QDate getDateEnd() { return DateEnd; }

    QTime getTimeStart() { return TimeStart; }

    QTime getTimeEnd() { return TimeEnd; }

    QString getTitle() { return Title; }

    QString getText() { return Text; }

    /*bool getPriority() { return Priority; }

    bool getReminder() { return Reminder; }

    int getColor() { return Color; }

    char getMask() { return Mask; }*/

    void setDateStart(QDate pDateStart) { DateStart = pDateStart; }

    void setDateEnd(QDate pDateEnd) { DateEnd = pDateEnd; }

    void setTimeStart(QTime pTimeStart) { TimeStart = pTimeStart; }

    void setTimeEnd(QTime pTimeEnd) { TimeEnd = pTimeEnd; }

    void setTitle(QString pTitle) { Title = pTitle; }

    void setText(QString pText) { Text = pText; }

private:
    QDate   DateStart;
    QDate   DateEnd;
    QTime   TimeStart;
    QTime   TimeEnd;
    QString Title;
    QString Text;
    /*bool    Priority;
    bool    Reminder;
    int     Color;
    char    Mask;*/
};

#endif // NOTE_H
