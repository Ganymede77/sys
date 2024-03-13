#include "personalitemdelegation.h"

PersonalItemDelegation::PersonalItemDelegation(QObject *parent, int column, bool isDisabled) : QItemDelegate(parent)
{
    columnEditor = column;
    disabled = isDisabled;
    nameValidity = true;
}

QWidget *PersonalItemDelegation::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    switch(columnEditor)
    {
    case 0: // line edit
    {
        QLineEdit *editor = new QLineEdit(parent);

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    case 1: // specific combobox
    {
        QComboBox *editor = new QComboBox(parent);

        editor->addItem("Real");
        editor->addItem("Integer");
        editor->addItem("Binary");

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    case 2: // double spinbox
    {
        QRegExpValidator *doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));

        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(doubleValidator);

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    case 3: // spinbox
    {
        QSpinBox *editor = new QSpinBox(parent);

        editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
        editor->setMinimum(1);
        editor->setMaximum(INT_MAX);

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    }

    return parent;
}

void PersonalItemDelegation::setEditorData(QWidget *editor,
                               const QModelIndex &index) const
{
    // this method is called to set the Editor value, but not the table; see setModelData for that
    switch(columnEditor)
    {
    case 0: //line edit
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current value
        QLineEdit *lnEdt = static_cast<QLineEdit*>(editor);
        lnEdt->setText(value);
        break;
    }
    case 1: //specific combobox
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current selected item
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        combobox->setCurrentText(value);

        break;
    }
    case 2: //double spinbox
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current value
        QLineEdit *spinbox = static_cast<QLineEdit*>(editor);
        spinbox->setText(value);

        break;
    }
    case 3: //spinbox
    {
        int value = index.model()->data(index, Qt::EditRole).toInt(); // gets the current value
        QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
        spinbox->setValue(value);
        break;
    }
    }
}

void PersonalItemDelegation::setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const
{
    // this method gets the ComboBox value and gives it to the actual table, not the editor itself; see setEditor Data for that
    switch(columnEditor)
    {
    case 0: //line edit
    {
        QLineEdit *lnEdt = static_cast<QLineEdit*>(editor);
        QString value = lnEdt->text(); // gets the current text
        if(model->columnCount() > 2)
            emit CheckName(value, true);
        else
            emit CheckName(value, false);

        if(nameValidity)
            model->setData(index,value);
        else
            lnEdt->setText(model->data(index).toString());
        break;
    }
    case 1: //specific combobox
    {
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        model->setData(index, combobox->currentText());
        break;
    }
    case 2: //double spinbox
    {
        QLineEdit *spinbox = static_cast<QLineEdit*>(editor);
        QString value = spinbox->text();
        model->setData(index, value);

//        for(int i = 0; i < model->rowCount(); ++i)
//        {
//            double vMin = model->data(model->index(i,2)).toDouble();
//            double vMax = model->data(model->index(i,3)).toDouble();
//            int stpSize = model->data(model->index(i,4)).toInt();
//            if(stpSize > 0)
//                model->setData(model->index(i,5), int((vMax-vMin)/stpSize)); // set Step as (Max-Min)/stpSize
//            else
//                model->setData(model->index(i,5), 1); // set Step as 1 if stpSize <= 0 to avoid dividing by 0 or negative
//        }
        break;
    }
    case 3: //spinbox
    {
        QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
        spinbox->interpretText();
        int value = spinbox->value();
        model->setData(index, value);

//        for(int i = 0; i < model->rowCount(); ++i)
//        {
//            double vMin = model->data(model->index(i,2)).toDouble();
//            double vMax = model->data(model->index(i,3)).toDouble();
//            int stpSize = model->data(model->index(i,4)).toInt();
//            if(stpSize > 0)
//                model->setData(model->index(i,5), int((vMax-vMin)/stpSize)); // set Step as (Max-Min)/stpSize
//            else
//                model->setData(model->index(i,5), 1); // set Step as 1 if stpSize <= 0 to avoid dividing by 0 or negative
//        }
        break;
    }
    }

    emit EditedModel(&index);
}

void PersonalItemDelegation::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}

void PersonalItemDelegation::NameIsValid(bool valid)
{
    nameValidity = valid;
}
