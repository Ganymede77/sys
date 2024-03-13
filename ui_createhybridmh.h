/********************************************************************************
** Form generated from reading UI file 'createhybridmh.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEHYBRIDMH_H
#define UI_CREATEHYBRIDMH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateHybridMh
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton_add;
    QPushButton *pushButton_remove;
    QListWidget *listWidget;
    QComboBox *comboBox;

    void setupUi(QDialog *CreateHybridMh)
    {
        if (CreateHybridMh->objectName().isEmpty())
            CreateHybridMh->setObjectName("CreateHybridMh");
        CreateHybridMh->setWindowModality(Qt::WindowModal);
        CreateHybridMh->resize(506, 199);
        CreateHybridMh->setFocusPolicy(Qt::ClickFocus);
        buttonBox = new QDialogButtonBox(CreateHybridMh);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(140, 150, 341, 32));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        pushButton_add = new QPushButton(CreateHybridMh);
        pushButton_add->setObjectName("pushButton_add");
        pushButton_add->setGeometry(QRect(340, 50, 75, 23));
        pushButton_remove = new QPushButton(CreateHybridMh);
        pushButton_remove->setObjectName("pushButton_remove");
        pushButton_remove->setGeometry(QRect(420, 50, 75, 23));
        listWidget = new QListWidget(CreateHybridMh);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 281, 131));
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        listWidget->setDefaultDropAction(Qt::MoveAction);
        comboBox = new QComboBox(CreateHybridMh);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(300, 20, 191, 21));

        retranslateUi(CreateHybridMh);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CreateHybridMh, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CreateHybridMh, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CreateHybridMh);
    } // setupUi

    void retranslateUi(QDialog *CreateHybridMh)
    {
        CreateHybridMh->setWindowTitle(QCoreApplication::translate("CreateHybridMh", "Create Hybrid MH", nullptr));
        pushButton_add->setText(QCoreApplication::translate("CreateHybridMh", "Add", nullptr));
        pushButton_remove->setText(QCoreApplication::translate("CreateHybridMh", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateHybridMh: public Ui_CreateHybridMh {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEHYBRIDMH_H
