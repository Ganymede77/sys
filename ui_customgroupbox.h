/********************************************************************************
** Form generated from reading UI file 'customgroupbox.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMGROUPBOX_H
#define UI_CUSTOMGROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>

QT_BEGIN_NAMESPACE

class Ui_CustomGroupBox
{
public:

    void setupUi(QGroupBox *CustomGroupBox)
    {
        if (CustomGroupBox->objectName().isEmpty())
            CustomGroupBox->setObjectName("CustomGroupBox");
        CustomGroupBox->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CustomGroupBox->sizePolicy().hasHeightForWidth());
        CustomGroupBox->setSizePolicy(sizePolicy);
        CustomGroupBox->setFocusPolicy(Qt::ClickFocus);
        CustomGroupBox->setAutoFillBackground(true);
        CustomGroupBox->setStyleSheet(QString::fromUtf8(""));
        CustomGroupBox->setAlignment(Qt::AlignCenter);
        CustomGroupBox->setFlat(false);

        retranslateUi(CustomGroupBox);

        QMetaObject::connectSlotsByName(CustomGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *CustomGroupBox)
    {
        CustomGroupBox->setWindowTitle(QCoreApplication::translate("CustomGroupBox", "GroupBox", nullptr));
        CustomGroupBox->setTitle(QCoreApplication::translate("CustomGroupBox", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomGroupBox: public Ui_CustomGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMGROUPBOX_H
