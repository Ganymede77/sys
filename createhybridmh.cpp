#include "createhybridmh.h"
#include "ui_createhybridmh.h"

CreateHybridMh::CreateHybridMh(QWidget *parent, QComboBox *cb) :
    QDialog(parent),
    ui(new Ui::CreateHybridMh)
{
    ui->setupUi(this);

    itemNumber = 0;
    for(int i = 0; i < cb->count(); ++i)
        ui->comboBox->addItem(cb->itemText(i));

    QScreen *screen = QGuiApplication::screens().at(0); //getting the desktop properties

    //height = screen height / screen count
    int const scH = int(screen->availableGeometry().height());
    //width = screen width / screen count
    int const scW = int(screen->availableGeometry().width());

    //proportions for spacing between things. it's number/property
    // 10/720
    int const h10 = int(scH * 0.014);
    // 20/720
    int const h20 = int(scH * 0.028);
    // 10/1280
    int const w10 = int(scW * 0.0078);
    // 20/1280
    int const w20 = int(scW * 0.0156);

    this->resize(scW*0.4,scH*0.28);
    ui->listWidget->setGeometry(w10,h10,scW*0.22,scH*0.182);
    ui->comboBox->setGeometry(ui->listWidget->x()+ui->listWidget->width()+w20, ui->listWidget->y()+h10,
                              scW*0.15,scH*0.029);
    ui->pushButton_add->setGeometry(this->width()-scW*0.125, ui->comboBox->y()+scH*0.042, scW*0.058, scH*0.032);
    ui->pushButton_remove->setGeometry(ui->pushButton_add->x()+ui->pushButton_add->width()+scH*0.004,
                                       ui->pushButton_add->y(), scW*0.058, scH*0.032);
    ui->buttonBox->move(this->width() - ui->buttonBox->width() - w20, this->height() - ui->buttonBox->height() - h20);
}

CreateHybridMh::~CreateHybridMh()
{
    delete ui;
}

void CreateHybridMh::on_buttonBox_accepted()
{
    emit ValidHybrid(treeItems);
}

void CreateHybridMh::on_pushButton_add_clicked()
{
    QTreeWidgetItem *nTreeItem = new QTreeWidgetItem();
    nTreeItem->setText(0, ui->comboBox->currentText());
    nTreeItem->setData(0, Qt::UserRole, ui->listWidget->count());

    ui->listWidget->insertItem(ui->listWidget->count(), ui->comboBox->currentText() + " - " + QString::number(itemNumber));
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    ui->listWidget->currentItem()->setData(Qt::UserRole, ui->listWidget->count()-1);

    treeItems.insert(ui->listWidget->count()-1, nTreeItem);

    itemNumber++;
}

void CreateHybridMh::on_pushButton_remove_clicked()
{
    if(ui->listWidget->selectionModel()->hasSelection())
    {
        treeItems.remove(ui->listWidget->currentItem()->data(Qt::UserRole).toInt());
        delete ui->listWidget->currentItem();
    }

}
