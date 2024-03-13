#include "progressbar.h"
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>


ProgressBarDialog::ProgressBarDialog(QString msg, QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ok = new QPushButton("OK");
    abort = new QPushButton("Abort Current");
    abortA = new QPushButton("Abort All");
    messageArea = new QPlainTextEdit();

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(abort, QDialogButtonBox::ActionRole);
    buttonBox->addButton(abortA, QDialogButtonBox::ActionRole);
    buttonBox->addButton(ok, QDialogButtonBox::ActionRole);
    ok->setHidden(true);

    text = new QLabel("...");
    projLabel = new QLabel("0/0");
    projBar = new QProgressBar();
    projBox = new QGroupBox("Project Progress");
    QGridLayout *projGrid = new QGridLayout();
    projBox->setLayout(projGrid);
    projGrid->addWidget(projBar, 1, 0);

    repetitionBox = new QGroupBox("Run Progress");
    QGridLayout *repetitionGrid = new QGridLayout();
    repetitionLabel = new QLabel("0/0");
    repetitionBar = new QProgressBar();
    repetitionBox->setLayout(repetitionGrid);
    repetitionGrid->addWidget(repetitionBar, 1, 0);

    //infBar = new QProgressBar();
    boxGrid = new QGridLayout();

    setMinimumSize(480,400);
    setMaximumSize(480,400);
    QGridLayout *calcMessage_grid = new QGridLayout();
    calcMessage_grid->addWidget(text, 0, 0);
    calcMessage_grid->addLayout(boxGrid, 1, 0);
    calcMessage_grid->addWidget(messageArea, 2, 0);
    calcMessage_grid->addWidget(buttonBox, 3, 0);
    setLayout(calcMessage_grid);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(abort, SIGNAL(clicked()), this, SLOT(abortClicked()));
    connect(abortA, SIGNAL(clicked()), this, SLOT(abortAClicked()));
}

ProgressBarDialog::~ProgressBarDialog()
{ }

void ProgressBarDialog::appendMessage(const QString &text)
{
    messageArea->appendPlainText(text); // Adds the message to the widget
    messageArea->verticalScrollBar()->setValue(messageArea->verticalScrollBar()->maximum()); // Scrolls to the bottom
    //m_logFile.write(text); // Logs to file
}

QPushButton* ProgressBarDialog::clickedButton()
{
    QPushButton* tmp = clicked;
    clicked = NULL;
    return tmp;
}

void ProgressBarDialog::closeBtn()
{
    abort->setHidden(true);
    abortA->setHidden(true);
    ok->setHidden(false);
}

void ProgressBarDialog::projBarSetRange(long min, long max)
{
    projBar->setRange(min, max);
    projBarVal = min;
    projBarTotal = max;
}

void ProgressBarDialog::projBarSetValue(long val)
{
    projBar->setValue(val);
}

void ProgressBarDialog::projLabelSetText(QString val)
{
    projLabel->setText(val);
}

void ProgressBarDialog::repetitionBarSetRange(long min, long max)
{
    repetitionBar->setRange(min, max);
    repetitionBarVal = min;
    repetitionBarTotal = max;
}

void ProgressBarDialog::repetitionBarSetValue(long val)
{
    repetitionBar->setValue(val);
}

void ProgressBarDialog::repetitionLabelSetText(QString val)
{
    repetitionLabel->setText(val);
}

void ProgressBarDialog::setText(QString val)
{
    text->setText(val);
}

void ProgressBarDialog::testParalelismInterface(bool flag)
{
    if(flag) {
    } else {
        boxGrid->addWidget(repetitionBox, 0, 0);
        boxGrid->addWidget(projBox, 1, 0);
    }
}

void ProgressBarDialog::update(int status)
{
    if(status == 1)
    {
        //projBarVal++;
        //projBar->setValue(projBarVal);
        projBar->setValue(projBarTotal);
        repetitionBar->setValue(repetitionBarTotal);
        return;
    }
    repetitionBarVal++;
    projBarVal++;
    if(repetitionBarVal > repetitionBarTotal)
    {
        repetitionBarVal = 1;
    }
    repetitionBar->setValue(repetitionBarVal);
    projBar->setValue(projBarVal);
}
