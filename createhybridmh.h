#ifndef CREATEHYBRIDMH_H
#define CREATEHYBRIDMH_H

#include <QDialog>
#include <QComboBox>
#include <QTreeWidget>
#include <QScreen>

namespace Ui {
class CreateHybridMh;
}
//!  \brief This class allows the user to create a hybrid metaheuristics based problem.
/*!
  This class allows the user to create a hybrid metaheuristics based problem. It inherits QDialog.
  The created dialog presents an interface where the user can insert multiple metaheuristics
  that will constitute a hybrid metaheuristic in the problem.
*/
class CreateHybridMh : public QDialog
{
    Q_OBJECT

public:
    //! Constructor for the CreateHybridMh class.
    /*!
        \param cb - a QComboBox argument that contains all the metaheuristics available to be used in a hybrid set.
    */
    explicit CreateHybridMh(QWidget *parent = 0, QComboBox *cb = 0);
    /*! Destructor for the CreateHybridMh class */
    ~CreateHybridMh();

signals:
    /*!
        This signal is emitted after the user has confirmed its selections, passing them
        inside a QMap<int, QTreeWidgetItem*>
    */
    void ValidHybrid(QMap<int, QTreeWidgetItem*>);

private slots:
    //! This is slot is called when the user presses the "Ok" button on the dialog
    void on_buttonBox_accepted();
    //! This is slot is called when the user presses the "Add" button on the dialog
    void on_pushButton_add_clicked();
    //! This is slot is called when the user presses the "Remove" button on the dialog
    void on_pushButton_remove_clicked();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
    Ui::CreateHybridMh *ui;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    // user variables //////////////
    QMap<int, QTreeWidgetItem*> treeItems; /*!< a QMap<int, QTreeWidgetItem*> that store the selected itens by the user */
    int itemNumber; /*!< an integer that stores the number of selected itens */

    // ////////////////////////////
};

#endif // CREATEHYBRIDMH_H
