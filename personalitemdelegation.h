#ifndef PERSONALITEMDELEGATION_H
#define PERSONALITEMDELEGATION_H

#include <QItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDebug>

//!  \brief This class creates a specific QItemDelegation.
/*!
  This class creates a specific QItemDelegation. Every model-based widget needs a QItemDelegation.
  This class provides a specific QItemDelegation that can accept integers, doubles, strings and
  ComboBoxes. It is used to insert some specific behavior into the Problem Variables table.
*/
class PersonalItemDelegation : public QItemDelegate
{
    Q_OBJECT
public:
    //! Constructor for the PersonalItemDelegation class.
    /*!
        \param column - an integer that appoints the column of the editor in the widget. This is usally 0.
        \param isDisabled - a boolean flag that says if the editor will be disabled (i.e read-only) or not
    */
    PersonalItemDelegation(QObject *parent = Q_NULLPTR, int column = 0, bool isDisabled = false);

    /*! Creates the needed editor based on the selected data type */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*! Sets the editor data */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /*! When data is modified, this model reflects the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /*! Gives the ComboBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int columnEditor; /*!< Appoints the column that you're editing */
    bool disabled; /*!< Flag that says if the editor is disabled */
    bool nameValidity; /*!< Flag that says if the name is valid, i.e. not repeated */

private slots:
    /*! This slot sets the \var nameValidity flag to the received value of \p valid */
    void NameIsValid(bool valid);

signals:
    /*! This signal is emitted whenever the user finishes editing the model */
    void EditedModel(const QModelIndex *ind) const;
    /*! This signal is emitted to ask for a check of the \p name argument
        \param name - a QString argument that represents the input value that must be checked
        \param variableTable - a bollean flag that says if you're editing the variables table*/
    void CheckName(QString name, bool variablesTable) const;
};

#endif // PERSONALITEMDELEGATION_H
