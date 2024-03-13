#ifndef LOFMHSETTINGS_H
#define LOFMHSETTINGS_H

#include <QDialog>
#include <QVariantList>
#include <QScreen>
#include <QDebug>
#include <QLayout>
#include <QFormLayout>
#include <QStandardItemModel>
#include <QThread>
#include "helpcaller.h"

namespace Ui {
class LofMhSettings;
}

//!  \brief This class creates a dialog that presents the LOF-MH settings.
/*!
  This class inherits QDialog and creates a dialog that presents the LOF-MH settings,
  allowing the user to change them, if desired. It's important to notice that
  this class do not store any information about the selected settings,
  it works as a "medium" to the actual settings, which are stored at the MainWindow class.
*/
class LofMhSettings : public QDialog
{
    Q_OBJECT

public:
    /*! Constructor for the LofMhSettings class */
    explicit LofMhSettings(QWidget *parent = Q_NULLPTR);
    /*! Destructor for the LofMhSettings class */
    ~LofMhSettings();

private slots:
    //! This slot is called when the dialog gets rejected
    void on_buttonBox_rejected();
    //! This slot is called when the dialog gets accepted
    void on_buttonBox_accepted();
    //! This slot is called when the user changes the value of the \p cmbBx_seed_initial QComboBox
    void on_cmbBx_seed_initial_currentIndexChanged(int index);
    //! This slot sets the value of the settings when the LofMhSettings dialog is first open
    void SettingsReceived(QMap<QString, QVariant> params);
    //! This slot is called when the user finishes editing the \p spnBx_nmb_repet QSpinBox
    void on_spnBx_nmb_repet_editingFinished();
    //! This slot is called whenever the user toogles the \p rdBtn_parallel_search QRadioButton
    void on_rdBtn_parallel_pop_toggled(bool checked);
    void on_rdBtn_parallel_run_toggled(bool checked);
    void on_rdBtn_parallel_search_toggled(bool checked);
    //! This slot is called whenever the user toogles the \p chkBx_parallel_activated QCheckBox
    void on_chkBx_parallel_activated_toggled(bool checked);
    //! This slot is called when the user finishes editing the \p lnEdt_project_name QLineEdit
    void on_lnEdt_project_name_editingFinished();

signals:
    /*! This signal is emitted whenever the user confirm its changes in the settings
        inside the LofMhSettings dialog. This signal sends a QMap<QString, QVariant> with
        the value of every configuration.*/
    void SettingsChanged(QMap<QString, QVariant> params);

private:
    HelpCaller *helpOpener;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
    Ui::LofMhSettings *ui;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

};

#endif // LOFMHSETTINGS_H
