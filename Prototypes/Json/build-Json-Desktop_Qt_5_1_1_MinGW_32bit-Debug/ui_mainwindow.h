/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btCurDate;
    QTableWidget *twYear;
    QTableWidget *twMonth;
    QTableWidget *twDay;
    QTableWidget *twTimeLine;
    QTableWidget *twNotes;
    QPushButton *btDay;
    QPushButton *btWeek;
    QPushButton *btCalendar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btCurDate = new QPushButton(centralWidget);
        btCurDate->setObjectName(QStringLiteral("btCurDate"));
        btCurDate->setGeometry(QRect(10, 10, 91, 61));
        btCurDate->setAutoDefault(false);
        btCurDate->setDefault(false);
        btCurDate->setFlat(true);
        twYear = new QTableWidget(centralWidget);
        twYear->setObjectName(QStringLiteral("twYear"));
        twYear->setGeometry(QRect(10, 70, 31, 471));
        twMonth = new QTableWidget(centralWidget);
        twMonth->setObjectName(QStringLiteral("twMonth"));
        twMonth->setGeometry(QRect(40, 70, 31, 471));
        twDay = new QTableWidget(centralWidget);
        twDay->setObjectName(QStringLiteral("twDay"));
        twDay->setGeometry(QRect(70, 70, 31, 471));
        twTimeLine = new QTableWidget(centralWidget);
        twTimeLine->setObjectName(QStringLiteral("twTimeLine"));
        twTimeLine->setGeometry(QRect(120, 20, 301, 501));
        twNotes = new QTableWidget(centralWidget);
        twNotes->setObjectName(QStringLiteral("twNotes"));
        twNotes->setGeometry(QRect(435, 20, 301, 501));
        btDay = new QPushButton(centralWidget);
        btDay->setObjectName(QStringLiteral("btDay"));
        btDay->setGeometry(QRect(760, 0, 31, 181));
        btWeek = new QPushButton(centralWidget);
        btWeek->setObjectName(QStringLiteral("btWeek"));
        btWeek->setGeometry(QRect(760, 180, 31, 181));
        btCalendar = new QPushButton(centralWidget);
        btCalendar->setObjectName(QStringLiteral("btCalendar"));
        btCalendar->setGeometry(QRect(760, 360, 31, 181));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btCurDate->setText(QApplication::translate("MainWindow", "Today", 0));
        btDay->setText(QApplication::translate("MainWindow", "D", 0));
        btWeek->setText(QApplication::translate("MainWindow", "W", 0));
        btCalendar->setText(QApplication::translate("MainWindow", "C", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
