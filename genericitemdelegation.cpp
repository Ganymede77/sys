#include "genericitemdelegation.h"

GenericItemDelegation::GenericItemDelegation(int editorType, bool isDisabled, QVariantList extras, QObject *parent) : QItemDelegate(parent)
{
    type = editorType;
    disabled = isDisabled;
    extraAtt = extras;
}

QWidget *GenericItemDelegation::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    switch(type)
    {
    case QVariant::String: // line edit
    {
        QLineEdit *editor = new QLineEdit(parent);

        if(!extraAtt.isEmpty())
            editor->setText(extraAtt.at(0).toString());

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    case QVariant::Bool: //combobox
    {
        QComboBox *editor = new QComboBox(parent);
        for(int i = 0; i < extraAtt.size(); ++i)
            editor->addItem(extraAtt.at(i).toString());

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    case QVariant::Double: // double spinbox
    {
        QRegExpValidator *doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));

        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(doubleValidator);

        if(!extraAtt.isEmpty())
            editor->setText(extraAtt.at(0).toString());

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    case QVariant::Int: // spinbox
    {
        QLineEdit *editor = new QLineEdit(parent);
        QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+"));
        editor->setValidator(validator);

        //editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
        //editor->setMinimum(-2147483647);
        //editor->setMaximum(2147483647); //int32 maximum size

        if(!extraAtt.isEmpty())
            editor->setText(extraAtt.at(0).toString());

        if(disabled)
            editor->setDisabled(true);

        return editor;
    }
    }

    return parent;
}

void GenericItemDelegation::setEditorData(QWidget *editor,
                               const QModelIndex &index) const
{
    // this method is called to set the Editor value, but not the table; see setModelData for that
    switch(type)
    {
    case QVariant::String: //line edit
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current value
        QLineEdit *lnEdt = static_cast<QLineEdit*>(editor);
        lnEdt->setText(value);
        break;
    }
    case QVariant::Bool: //specific combobox
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current selected item
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        combobox->setCurrentText(value);

        break;
    }
    case QVariant::Double: //double spinbox
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current value
        QLineEdit *spinbox = static_cast<QLineEdit*>(editor);
        spinbox->setText(value);

        break;
    }
    case QVariant::Int: //spinbox
    {
        QString value = index.model()->data(index, Qt::EditRole).toString(); // gets the current value
        QLineEdit *spinbox = static_cast<QLineEdit*>(editor);
        spinbox->setText(value);
        break;
    }
    }
}

void GenericItemDelegation::setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const
{
    // this method gets the ComboBox value and gives it to the actual table, not the editor itself; see setEditor Data for that
    switch(type)
    {
    case QVariant::String: //line edit
    {
        QLineEdit *lnEdt = static_cast<QLineEdit*>(editor);
        QString value = lnEdt->text(); // gets the current text

        model->setData(index,value);

        break;
    }
    case QVariant::Bool: //specific combobox
    {
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        model->setData(index, combobox->currentText());
        break;
    }
    case QVariant::Double: //double spinbox
    {
        QLineEdit *spinbox = static_cast<QLineEdit*>(editor);
        QString value = spinbox->text();
        model->setData(index, value);

        break;
    }
    case QVariant::Int: //spinbox
    {
        QLineEdit *spinbox = static_cast<QLineEdit*>(editor);
        QString value = spinbox->text();
        model->setData(index, value);

        break;
    }
    }

}

void GenericItemDelegation::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}
