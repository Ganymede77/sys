#include "widgetlistinput.h"

WidgetListInput::WidgetListInput(int dataType, QVariant min, QVariant max, bool isCopy, QWidget *parent) :
    QFrame(parent)
{
    editor = dataType;
    expanded = isCopy;
    minimum = min;
    maximum = max;

    QGridLayout *lay = new QGridLayout();
    btn_add = new QToolButton();
    btn_add->setText(" + ");
    btn_remove = new QToolButton();
    btn_remove->setText(" - ");
    btn_expand = new QToolButton();
    btn_expand->setIcon(QIcon(":/ui_images/UI/ico_expand_arrow.png"));
    list = new QListWidget();

    QGridLayout *btn_lay = new QGridLayout();
    btn_lay->addWidget(btn_add, 0, 0, Qt::AlignLeft);
    btn_lay->addWidget(btn_remove, 0, 1, Qt::AlignLeft);
    if(!expanded)
        btn_lay->addWidget(btn_expand, 0, 2, Qt::AlignLeft);

    this->setLayout(lay);
    lay->addWidget(list, 0, 0, Qt::AlignLeft);
    lay->addLayout(btn_lay, 0, 1, Qt::AlignLeft);

    list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setContextMenuPolicy(Qt::ActionsContextMenu);

    if(expanded)
    {
        list->setSelectionMode(QAbstractItemView::ContiguousSelection);
        list->setDragEnabled(true);
        list->setDragDropMode(QAbstractItemView::InternalMove);
    }

    connect(list->itemDelegate(), SIGNAL(commitData(QWidget*)), this, SLOT(ValidateModelEdit(QWidget*)));
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SaveCurrentRowValue(QListWidgetItem*)));
    connect(btn_add, SIGNAL(pressed()), this, SLOT(on_toolButton_add_clicked()));
    connect(btn_remove, SIGNAL(pressed()), this, SLOT(on_toolButton_remove_clicked()));
    connect(btn_expand, SIGNAL(pressed()), this, SLOT(on_toolButton_expand_clicked()));

    QAction *act_copy = new QAction("Copy");
    QAction *act_paste = new QAction("Paste");
    QAction *act_select_all = new QAction("Select All");
    connect(act_copy, SIGNAL(triggered(bool)), this, SLOT(CopySelectedItems()));
    connect(act_paste, SIGNAL(triggered(bool)), this, SLOT(PasteClipboardItems()));
    connect(act_select_all, SIGNAL(triggered(bool)), list, SLOT(selectAll()));
    list->addAction(act_copy);
    list->addAction(act_paste);
    list->addAction(act_select_all);

    FadeOutEffect(btn_add, 1);
    FadeOutEffect(btn_remove, 1);
    if(!expanded)
        FadeOutEffect(btn_expand, 1);

    if(!expanded)
        CreateLine();

    this->setMinimumSize(150, 40);
    if(!expanded)
        this->setMaximumSize(150, 80);
    else
        this->setMaximumSize(INT_MAX, INT_MAX);

}

WidgetListInput::~WidgetListInput()
{

}

void WidgetListInput::ValidateModelEdit(QWidget *item)
{
    QLineEdit *lnEdt = reinterpret_cast<QLineEdit*>(item);
    QString valData = lnEdt->text();
    int nRow = list->currentRow();

    if(editor == QVariant::Int)
    {
        if(valData.toInt() < minimum.toInt() || valData.toInt() > maximum.toLongLong())
        {
            list->item(nRow)->setText(currentSelectedValue);
        }
        else
        {
            QRegExp intVal("[-]?[0-9]+");
            if(!intVal.exactMatch(valData))
                list->item(nRow)->setText(currentSelectedValue);
            else
                emit AcceptedValue(valData.toInt());
        }
    }
    else if(editor == QVariant::Double)
    {
        if(valData.toDouble() < minimum.toDouble() || valData.toDouble() > maximum.toDouble())
        {
            list->item(nRow)->setText(currentSelectedValue);
        }
        else
        {
            QRegExp doubleVal("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?");
            if(!doubleVal.exactMatch(valData))
                list->item(nRow)->setText(currentSelectedValue);
        }
    }
}

void WidgetListInput::SaveCurrentRowValue(QListWidgetItem *item)
{
    currentSelectedValue = item->text();
}

const QVariantList WidgetListInput::GetValues()
{
    QVariantList values;
    for(int i = 0; i < list->count(); ++i)
        values.append(list->item(i)->text());

    return values;
}

void WidgetListInput::SetValues(QVariantList values)
{   
    list->clear();

    for(int i = 0; i < values.size(); ++i)
    {
        QListWidgetItem *nItem = new QListWidgetItem();
        nItem->setFlags (nItem->flags () | Qt::ItemIsEditable);

        if(editor == QVariant::Int)
            nItem->setText(values.at(i).toString());
        else
            nItem->setText(values.at(i).toString());

        list->insertItem(i, nItem);

    }
}

void WidgetListInput::SetValue(QVariant value)
{   
    QVariantList v;
    v.append(value);
    SetValues(v);
}

void WidgetListInput::SetMinimum(QVariant value)
{
    minimum = value;
}

void WidgetListInput::SetMaximum(QVariant value)
{
    maximum = value;
}

void WidgetListInput::CreateLine()
{
    QListWidgetItem *nItem = new QListWidgetItem();
    nItem->setFlags (nItem->flags () | Qt::ItemIsEditable);

    if(editor == QVariant::Int || editor == QVariant::Double)
    {
        if(list->count() < minimum.toInt())
            nItem->setText(minimum.toString());
        else
            nItem->setText(QString::number(list->count()+1));

        if(list->count() >= maximum.toLongLong())
            nItem->setText(maximum.toString());
    }

    else if(editor == QVariant::String)
        nItem->setText("line" + QString::number(list->count()-1));

    list->insertItem(list->count(), nItem);
    list->setCurrentItem(nItem);
    list->scrollToBottom();
}

void WidgetListInput::CreateLine(QVariant data)
{
    if(editor == QVariant::Int)
    {
        QString valData = data.toString();
        if(valData.toInt() >= minimum.toInt() || valData.toInt() <= maximum.toLongLong())
        {
            QRegExp intVal("[-]?[0-9]+");
            if(intVal.exactMatch(valData))
            {
                QListWidgetItem *nItem = new QListWidgetItem();
                nItem->setFlags (nItem->flags () | Qt::ItemIsEditable);

                list->insertItem(list->count(), nItem);
                list->setCurrentItem(nItem);
                list->scrollToBottom();

                nItem->setText(data.toString());
            }
        }
    }
    else if(editor == QVariant::Double)
    {
        QRegExp doubleVal("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?");
        QString valData = data.toString();
        if(valData.toDouble() >= minimum.toDouble() && valData.toDouble() <= maximum.toDouble())
        {
            if(doubleVal.exactMatch(valData))
            {
                QListWidgetItem *nItem = new QListWidgetItem();
                nItem->setFlags (nItem->flags () | Qt::ItemIsEditable);

                list->insertItem(list->count(), nItem);
                list->setCurrentItem(nItem);
                list->scrollToBottom();

                nItem->setText(data.toString());
            }
        }
    }
    else if(editor == QVariant::String)
    {
        QListWidgetItem *nItem = new QListWidgetItem();
        nItem->setFlags (nItem->flags () | Qt::ItemIsEditable);

        list->insertItem(list->count(), nItem);
        list->setCurrentItem(nItem);
        list->scrollToBottom();

        nItem->setText(data.toString());
    }
}

void WidgetListInput::on_toolButton_add_clicked()
{
    CreateLine();
}

void WidgetListInput::on_toolButton_remove_clicked()
{
    int itens = list->selectedItems().count()-1;
    for(int i = itens; i >= 0; --i)
    {
        if(list->count() > 1)
        {
            delete list->takeItem(list->row(list->selectedItems().at(i)));
        }
    }

}

void WidgetListInput::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    FadeInEffect(btn_add);
    FadeInEffect(btn_remove);
    if(!expanded)
        FadeInEffect(btn_expand);
}

void WidgetListInput::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    FadeOutEffect(btn_add);
    FadeOutEffect(btn_remove);
    if(!expanded)
        FadeOutEffect(btn_expand);
}

void WidgetListInput::FadeInEffect(QWidget *widget, int time)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    widget->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(time);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}

void WidgetListInput::FadeOutEffect(QWidget *widget, int time)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    widget->setGraphicsEffect(eff);

    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(time);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}

void WidgetListInput::CopyContent(WidgetListInput *target)
{
    target->SetValues(this->GetValues());
}

void WidgetListInput::on_toolButton_expand_clicked()
{
    QPushButton *ok_btn = new QPushButton("Ok");
    QPushButton *cancel_btn = new QPushButton("Cancel");
    QDialog *dialog = new QDialog();
    WidgetListInput *displayInput = new WidgetListInput(editor, minimum, maximum, true);

    QGridLayout *lay = new QGridLayout();
    QGridLayout *btn_lay = new QGridLayout();

    btn_lay->addWidget(ok_btn, 0, 0, Qt::AlignLeft);
    btn_lay->addWidget(cancel_btn, 0, 1, Qt::AlignRight);

    lay->addWidget(displayInput, 0, 0);
    lay->addLayout(btn_lay, 1, 0, Qt::AlignRight);

    dialog->setLayout(lay);
    dialog->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    dialog->setWindowFlag(Qt::WindowCloseButtonHint, false);

    connect(ok_btn, SIGNAL(clicked(bool)), displayInput, SLOT(CloseExpandedWindow()));
    connect(cancel_btn, SIGNAL(clicked(bool)), dialog, SLOT(close()));
    connect(ok_btn, SIGNAL(clicked(bool)), dialog, SLOT(close()));

    CopyContent(displayInput);
    connect(displayInput, SIGNAL(EditFinished(QVariantList)), this, SLOT(ReceiveParameters(QVariantList)));

    dialog->setWindowTitle("LOF System");
    dialog->exec();

}

void WidgetListInput::ReceiveParameters(QVariantList params)
{
    this->SetValues(params);
}

void WidgetListInput::CloseExpandedWindow()
{
    QVariantList val = this->GetValues();
    emit EditFinished(val);
}

void WidgetListInput::CopySelectedItems()
{
    QVariantList data;
    QClipboard *clipboard = QApplication::clipboard();

    QList<QListWidgetItem*> selectedRows = list->selectedItems();
    if(selectedRows.size() > 0)
    {
        //std::sort(selectedRows.begin(), selectedRows.end());

        for(int i = 0; i < selectedRows.size(); ++i)
            data.append(selectedRows.at(i)->text());

        QString dat = data.at(0).toString();
        clipboard->clear();
        for(int i = 1; i < selectedRows.size(); ++i)
        {
            dat += "\n" + data.at(i).toString();
        }
        clipboard->setText(dat);
    }
}

void WidgetListInput::PasteClipboardItems()
{
    QClipboard *clipboard = QApplication::clipboard();

    if(clipboard->text() != "")
    {
        QString clipboardData = clipboard->text();
        QStringList lines = clipboardData.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < lines.size(); ++i)
            CreateLine(lines.at(i));
    }
}

void WidgetListInput::keyPressEvent(QKeyEvent *event)
{
    if (event == QKeySequence::Copy)
        CopySelectedItems();

    else if(event == QKeySequence::Paste)
        PasteClipboardItems();

    event->accept();
}
