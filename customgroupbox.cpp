#include "customgroupbox.h"
#include "ui_customgroupbox.h"

CustomGroupBox::CustomGroupBox(QWidget *parent, QString title) :
    QGroupBox(parent),
    ui(new Ui::CustomGroupBox)
{
    ui->setupUi(this);

    this->setTitle(title);

    QScreen *screen = QGuiApplication::screens().at(0); //getting the desktop properties
    //width = screen width / screen count
    int const scW = screen->availableGeometry().width();
    //height = screen height / screen count
    int const scH = screen->availableGeometry().height();

    lay = new QGridLayout(this);
    lay->setHorizontalSpacing(scW*0.0078);
    lay->setVerticalSpacing(scH*0.0138);

    this->setWindowFlag(Qt::SubWindow);
    this->setLayout(lay);

    //grip = new QSizeGrip(this);
    //lay->addWidget(grip, 0, 0, Qt::AlignBottom | Qt::AlignRight);

    scale = 1;
    refWid = this->width();
    refHeig = this->height();

}

CustomGroupBox::~CustomGroupBox()
{
    delete ui;
}

void CustomGroupBox::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
    on_CustomGroupBox_clicked();
}

void CustomGroupBox::mouseMoveEvent(QMouseEvent *event)
{
    //if(event->buttons() & Qt::LeftButton)
        //this->move(mapToParent(event->pos() - offset));
}

void CustomGroupBox::on_CustomGroupBox_clicked()
{
    this->raise();
}

void CustomGroupBox::addToBox(QWidget *wid, int row, int col, Qt::Alignment alig)
{
    wid->setParent(this);
    lay->addWidget(wid, row, col, alig);
    //delete grip;
    //grip = new QSizeGrip(this);
    //lay->addWidget(grip, lay->rowCount()-1, lay->columnCount()+1, Qt::AlignBottom | Qt::AlignRight);
}

void CustomGroupBox::addToBox(QWidget *wid, int row, int col, int rowspan, int colspan, Qt::Alignment alig)
{
    wid->setParent(this);
    lay->addWidget(wid, row, col, rowspan, colspan, alig);
    //delete grip;
    //grip = new QSizeGrip(this);
    //lay->addWidget(grip, lay->rowCount()-1, lay->columnCount()+1, Qt::AlignBottom | Qt::AlignRight);
}

void CustomGroupBox::addLayoutToBox(QLayout *layout, int row, int col, Qt::Alignment alig)
{
    lay->addLayout(layout, row, col, alig);
    //delete grip;
    //grip = new QSizeGrip(this);
    //lay->addWidget(grip, lay->rowCount()-1, lay->columnCount()+1, Qt::AlignBottom | Qt::AlignRight);
}

/*void CustomGroupBox::ResizeRequested(double step)
{
    scale += step;

    if(scale > 2)
        scale = 2;

    else if(scale < 0.2)
        scale = 0.2;

    this->resize(refWid*scale, refHeig*scale);
}*/
