#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class ProjectSettings;
}

//!  \brief This class creates a dialog that presents the Project settings.
/*!
  This class inherits QDialog and creates a dialog that presents the Project settings,
  allowing the user to change them, if desired. It's important to notice that
  this class do not store any information about the selected settings,
  it works as a "medium" to the actual settings, which are stored at the MainWindow class.
*/
class ProjectSettings : public QDialog
{
    Q_OBJECT

public:
    //! Constructor for the ProjectSettings class.
    /*!
        \param sets - a QMap<QString, QString> that holds the current settings that will be displayed to the user
    */
    explicit ProjectSettings(QMap<QString, QString> sets = QMap<QString, QString>(), QWidget *parent = 0);
    /*! Destructor for the ProjectSettings class */
    ~ProjectSettings();

private slots:
    /*! This slot sets the selected settings on the MainWindow class */
    void on_buttonBox_accepted();
    /*! This slot sets the selected Initial Path for the project (DEPRECATED) */
    void on_btn_init_clicked();
    /*! This slot sets the selected Solution File Path for the project */
    void on_btn_solution_clicked();
    /*! This slot sets the selected name for the project */
    void on_lnEdt_proj_name_editingFinished();
    /*! This slot sets the selected path for the LOF-MH executable (DEPRECATED) */
    void on_btn_lofmh_path_clicked();

signals:
    /*! This signal is emitted when the user finished editing its settings, passing a
     * QMap<QString, QString> with the selected settings */
    void ProjectSettingsChanged(QMap<QString, QString> map);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
    Ui::ProjectSettings *ui;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    QMap <QString, QString> settings; /*!< Temporarily holds the selected settings */

};

#endif // PROJECTSETTINGS_H
