#include "addmultirow.h"
#include "ui_addmultirow.h"

AddMultiRow::AddMultiRow(QString min, QString max, bool isMultiVar, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMultiRow)
{
    ui->setupUi(this);

    QGridLayout *dialog_grid = new QGridLayout(this);
    QHBoxLayout *btn_lay = new QHBoxLayout();
    QLabel *lbl_row_numb = new QLabel("Number of Variables:");
    QLabel *lbl_name = new QLabel("Name Prefix:");
    QLabel *lbl_type = new QLabel("Variables Type:");

    //creating a validator for decimal numbers
    doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));

    spnbx_row_numb = new QSpinBox();
    dspnbx_min = new QLineEdit();
    dspnbx_max = new QLineEdit();
    //spnbx_rep_numb = new QSpinBox();
    lnEdt_name = new QLineEdit();
    cmbBx_type = new QComboBox();

    spnbx_row_numb->setMaximum(2147483647);
    //spnbx_rep_numb->setMaximum(2147483647);

    //spnbx_rep_numb->setMinimum(1);
    spnbx_row_numb->setMinimum(1);

    spnbx_row_numb->setButtonSymbols(QAbstractSpinBox::NoButtons);
    //spnbx_rep_numb->setButtonSymbols(QAbstractSpinBox::NoButtons);

    lnEdt_name->setPlaceholderText("Name Prefix");
    lnEdt_name->setText("r");

    cmbBx_type->addItem("Real");
    cmbBx_type->addItem("Integer");
    cmbBx_type->addItem("Binary");

    dialog_grid->addWidget(lbl_row_numb, 0, 0);
    dialog_grid->addWidget(spnbx_row_numb, 0, 1);
    dialog_grid->addWidget(lbl_name, 1, 0);
    dialog_grid->addWidget(lnEdt_name, 1, 1);
    dialog_grid->addWidget(lbl_type, 2, 0);
    dialog_grid->addWidget(cmbBx_type, 2, 1);

    if(isMultiVar)
    {
        QLabel *lbl_min = new QLabel("Min:");
        QLabel *lbl_max = new QLabel("Max:");
        //QLabel *lbl_rep_numb = new QLabel("Number of Repetitions:");

        lnEdt_name->setText("x");
        dialog_grid->addWidget(lbl_min, 3, 0);
        dialog_grid->addWidget(dspnbx_min, 3, 1);
        dialog_grid->addWidget(lbl_max, 4, 0);
        dialog_grid->addWidget(dspnbx_max, 4, 1);
        //dialog_grid->addWidget(lbl_rep_numb, 5, 0);
        //dialog_grid->addWidget(spnbx_rep_numb, 5, 1);
    }
    else
    {
        delete dspnbx_max;
        delete dspnbx_min;
        //delete spnbx_rep_numb;
    }

    btn_lay->addWidget(ui->btn_ok);
    btn_lay->addWidget(ui->btn_cancel);
    dialog_grid->addLayout(btn_lay, 6, 1, Qt::AlignRight);

    this->setLayout(dialog_grid);

    QScreen *screen = QGuiApplication::screens().at(0); //getting the desktop properties

    //height = screen height / screen count
    int const scH = int(screen->availableGeometry().height());
    //width = screen width / screen count
    int const scW = int(screen->availableGeometry().width());

    this->resize(int(scW*0.23), int(scH*0.31));
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);

}

AddMultiRow::~AddMultiRow()
{
    delete ui;
}

void AddMultiRow::on_btn_ok_clicked()
{
    if(lnEdt_name->text() == "")
    {
        //asks for confirmation
        QMessageBox::StandardButton message = QMessageBox::question(this, "Add Multiple Variables",
                                                                    "Are you sure you want to leave the <i>Name Prefix</i> field blank?",
                                                                    QMessageBox::Ok|QMessageBox::Cancel);
        //if user confirmed
        if(message == QMessageBox::Ok)
            this->done(0);
    }
    else
        this->done(0);
}

void AddMultiRow::on_btn_cancel_clicked()
{
    this->done(1);
}
