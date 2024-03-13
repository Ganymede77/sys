/********************************************************************************
** Form generated from reading UI file 'addmultirow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMULTIROW_H
#define UI_ADDMULTIROW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddMultiRow
{
public:
    QPushButton *btn_ok;
    QPushButton *btn_cancel;

    void setupUi(QDialog *AddMultiRow)
    {
        if (AddMultiRow->objectName().isEmpty())
            AddMultiRow->setObjectName("AddMultiRow");
        AddMultiRow->resize(300, 225);
        AddMultiRow->setFocusPolicy(Qt::ClickFocus);
        AddMultiRow->setContextMenuPolicy(Qt::NoContextMenu);
        AddMultiRow->setSizeGripEnabled(true);
        btn_ok = new QPushButton(AddMultiRow);
        btn_ok->setObjectName("btn_ok");
        btn_ok->setGeometry(QRect(80, 170, 93, 28));
        btn_cancel = new QPushButton(AddMultiRow);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setGeometry(QRect(180, 170, 93, 28));

        retranslateUi(AddMultiRow);

        QMetaObject::connectSlotsByName(AddMultiRow);
    } // setupUi

    void retranslateUi(QDialog *AddMultiRow)
    {
        AddMultiRow->setWindowTitle(QCoreApplication::translate("AddMultiRow", "Add Multiple Variables", nullptr));
        btn_ok->setText(QCoreApplication::translate("AddMultiRow", "Ok", nullptr));
        btn_cancel->setText(QCoreApplication::translate("AddMultiRow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddMultiRow: public Ui_AddMultiRow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMULTIROW_H
