#ifndef GENERICITEMDELEGATION_H
#define GENERICITEMDELEGATION_H

#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QItemDelegate>
#include <QDebug>

//!  \brief This class creates a generic QItemDelegation.
/*!
  This class creates a generic QItemDelegation. Every model-based widget needs a QItemDelegation.
  This class provides a generic QItemDelegation that can accept integers, doubles, strings and
  ComboBoxes (where you must provide its available options).
*/
class GenericItemDelegation : public QItemDelegate
{

public:
    //! Constructor for the GenericItemDelegation class.
    /*!
        \param type  - an integer argument that is used to set the type of data type that will be used
        \param isDisabled - a boolean flag that says if the editor will be disabled (i.e read-only) or not
        \param extras - a QVariantList argument that has all the extra attributes that you want to pass to the editor
    */
    GenericItemDelegation(int type = QVariant::Int, bool isDisabled = false, QVariantList extras = QVariantList(), QObject *parent = Q_NULLPTR);

    /*! Creates the needed editor based on the selected data type */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*! Sets the editor data */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /*! When data is modified, this model reflects the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /*! Gives the ComboBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int type; /*!< Holds the type of data being used. It's possible to use QVariant::(Type) to set this */
    bool disabled; /*!< Flag that says tells if the editor is disabled */
    QVariantList extraAtt; /*!< Any extra attributtes that you may want to pass to the constructor (usually, the options of the ComboBox type) */

};

#endif // GENERICITEMDELEGATION_H
