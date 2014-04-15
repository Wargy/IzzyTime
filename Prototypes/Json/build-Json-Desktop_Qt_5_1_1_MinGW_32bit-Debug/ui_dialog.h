/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *edtTitle;
    QTextEdit *edtText;
    QLabel *lTitle;
    QLabel *lText;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        edtTitle = new QLineEdit(Dialog);
        edtTitle->setObjectName(QStringLiteral("edtTitle"));
        edtTitle->setGeometry(QRect(20, 40, 261, 21));
        edtText = new QTextEdit(Dialog);
        edtText->setObjectName(QStringLiteral("edtText"));
        edtText->setGeometry(QRect(20, 100, 261, 171));
        lTitle = new QLabel(Dialog);
        lTitle->setObjectName(QStringLiteral("lTitle"));
        lTitle->setGeometry(QRect(20, 20, 261, 16));
        lText = new QLabel(Dialog);
        lText->setObjectName(QStringLiteral("lText"));
        lText->setGeometry(QRect(20, 80, 261, 16));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        lTitle->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\267\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272:</span></p></body></html>", 0));
        lText->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\265\320\272\321\201\321\202:</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
