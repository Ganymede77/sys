#ifndef ADDMULTIROW_H
#define ADDMULTIROW_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QScreen>
#include <QMessageBox>

namespace Ui {
class AddMultiRow;
}

//!  \brief This class creates a dialog that let the user set-up multiple variables to the project.
/*!
  This class creates a dialog that let the user set-up multiple variables to the project.
  It inherits QDialog and accept input arguments that configure it's functionality.
  This dialog is used to allow the user to input multiple variables to the project simultaneously
  avoiding repetitive work. It also can be used to allow them to input multiple results,
  on the Results table.
*/
class AddMultiRow : public QDialog
{
    Q_OBJECT

public:
    //! Constructor for the AddMultiRow class.
    /*!
        \param min  - a QString argument that is used to set the default on the 'Minimum' widget input
        \param max  - a QString argument that is used to set the default on the 'Maximum' widget input
        \param isMultiVar  - a boolean argument that is used to set the correct input widgets in case this is creating a dialog for the variable project input
    */
    explicit AddMultiRow(QString min = "0", QString max = "0", bool isMultiVar = true, QWidget *parent = 0);
    /*! Destructor for the AddMultiRow class */
    ~AddMultiRow();

private:
    QSpinBox *spnbx_row_numb; /*!< QSpinBox * that stores the number of rows that will be added */
    QLineEdit *dspnbx_min; /*!< QLineEdit * that stores the value of the "Minimum" field of the rows that will be added */
    QLineEdit *dspnbx_max; /*!< QLineEdit * that stores the value of the "Maximum" field of the rows that will be added */
    QLineEdit *lnEdt_name; /*!< QLineEdit * that stores the value of the "Name Prefix" field of the rows that will be added */
    QComboBox *cmbBx_type; /*!< QComboBox * that let the user select the type of the variables that he wants to input (Integer, Real or Binary) */

public:
    //! Getter for the \p spnbx_row_numb QSpinBox * object
    QSpinBox &GetSpnbxRowNumb() const {return *spnbx_row_numb;}
    //! Getter for the \p dspnbx_min QLineEdit * object
    QLineEdit &GetDspnbxMin() const {return *dspnbx_min;}
    //! Getter for the \p dspnbx_max QLineEdit * object
    QLineEdit &GetDspnbxMax() const {return *dspnbx_max;}
    //! Getter for the \p lnEdt_name QLineEdit * object
    QLineEdit &GetLnEdtName() const {return *lnEdt_name;}
    //! Getter for the \p cmbBx_type QComboBox * object
    QComboBox &GetCmbBxType() const {return *cmbBx_type;}

private:
    QRegExpValidator *doubleValidator; /*!< A validator that accepts only "double equivalent" digits.
                                        It is defined as \code{.cpp} "[-+]?[0-9]+([.,][0-9]+)?([eE][-+]?[0-9]+)?"
                                        \endcode */

private slots:
    //! This is slot is called when the user presses the "Ok" button on the dialog
    void on_btn_ok_clicked();
    //! This is slot is called when the user presses the "Cancel" button on the dialog
    void on_btn_cancel_clicked();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
    Ui::AddMultiRow *ui;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
};

#endif // ADDMULTIROW_H
