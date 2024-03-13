#ifndef WIDGETLISTINPUT_H
#define WIDGETLISTINPUT_H

#include <QFrame>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QToolButton>
#include <QPushButton>
#include <QDialog>

#include <QStandardItemModel>
#include <QVariantList>
#include <QMouseEvent>
#include <QClipboard>
#include <QApplication>
#include <QAction>
#include <QRegExp>
#include <QListWidgetItem>
#include <QDebug>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "genericitemdelegation.h"

//!  \brief This class creates a widget that allows the user to input a list of values.
/*!
  This class creates a widget that allows the user to input a list of values. It can accept
  integers, doubles and strings, but only one of them simultaneously.
  It has three buttons that are used to interact with the widget: add, remove and expand.
  The 'add' button creates a new line in the widget that corresponds to the same data type that
  is being used. The 'remove' button deletes the selected lines of the widget.
  The 'expand' button expands the widget into a docked dialog, for better visualization.
*/
class WidgetListInput : public QFrame
{
    Q_OBJECT

public:
    //! Constructor for the WidgetListInput class.
    /*!
        \param dataType - an integer that defines the data type that will be used by the WidgetListInput object
        you can define this data type with QVariant::(Type). The data type is defined according to the following table
        Value             | Data Type
        ----------------- | ---------
        QVariant::Int     | Integer
        QVariant::Double  | Double
        QVariant::String  | String

        \param isCopy - a boolean flag that says if the WidgetListInput being created is an "expansion"
        (see on_toolButton_expand_clicked() for more info on the "expansion" system)
    */
    explicit WidgetListInput(int dataType = QVariant::String, QVariant min = QVariant::fromValue(-2147483648), QVariant max = QVariant::fromValue(2147483648),
                             bool isCopy = false, QWidget *parent = Q_NULLPTR);
    /*! Destructor for the WidgetListInput class */
    ~WidgetListInput();

public:
    /*! Getter that returns all values inside the WidgetListInput object */
    QVariantList const GetValues();
    /*! Setter that appends all values to the WidgetListInput object */
    void SetValues(QVariantList values);
    /*! Setter that appends one value to the WidgetListInput object */
    void SetValue(QVariant value);
    /*! Setter that asserts a minimum numerical value as input (Only useful with numbers) */
    void SetMinimum(QVariant value);
    /*! Setter that asserts a maximum numerical value as input (Only useful with numbers) */
    void SetMaximum(QVariant value);

private slots:
    /*! This slot is called to add a new row to the WidgetListInput */
    void on_toolButton_add_clicked();
    /*! This slot is called to remove the selected rows from the WidgetListInput */
    void on_toolButton_remove_clicked();
    /*! This slot expands the current WidgetListInput into a similar dialog.
        This is useful in cases where the user wants to see all its values at once
        or simply because the WidgetListInput is too small - which can happen due to resolution
        problems -.*/
    void on_toolButton_expand_clicked();
    /*! This slot inserts a series of values, that are inside \p params, into the WidgetListInput */
    void ReceiveParameters(QVariantList params);
    /*! This slot closes the expanded dialog window (see on_toolButton_expand_clicked() for more info on the "expansion" system)*/
    void CloseExpandedWindow();
    /*! This copies the selected itens to the clipboard, where the user can paste in a table form */
    void CopySelectedItems();
    /*! This pastes whatever item is in the clipboard - if it matches the data type being used -
        creating a new row for each line */
    void PasteClipboardItems();

protected:
    /*! This is a reimplemented function of QWidget::enterEvent(QEvent*). This is called when the
        mouse is inside the boundaries of the WidgetListsInput object. In this context, it's used with
        FadeInEffect(QWidget*, int) to make the action buttons appear to the user*/
    virtual void enterEvent(QEvent *event);
    /*! This is a reimplemented function of QWidget::leaveEvent(QEvent*). This is called when the
        mouse leaves the boundaries of the WidgetListsInput object. In this context, it's used with
        FadeOutEffect(QWidget*, int) to make the action buttons appear to the user*/
    virtual void leaveEvent(QEvent *event);

private:
    int editor; /*!< Holds the type of data being used. It's possible to use QVariant::(Type) to set this */
    bool expanded; /*!< Flag that says if this is an expanded window (button 'Expand' clicked) */
    QVariant minimum; /*!< holds the minimum int numerical input */
    QVariant maximum; /*!< holds the maximum int numerical input */
    QString currentSelectedValue;

private:
    QToolButton *btn_add, *btn_remove, *btn_expand;
    QListWidget *list;

private:
    /*! This method creates a new row on the WidgetListInput with a default value, according to the data type.
        The default value is the row number */
    void CreateLine();
    /*! This method creates a new row on the WidgetListInput with a value of \p data */
    void CreateLine(QVariant data);
    /*! This method creates a Fade In effect on the %QWidget \p widget, taking \p time to complete the effect */
    void FadeInEffect(QWidget *widget, int time = 250);
    /*! This method creates a Fade Out effect on the %QWidget \p widget, taking \p time to complete the effect */
    void FadeOutEffect(QWidget *widget, int time = 250);
    /*! This copies the content of the current WidgetListInput to \p target WidgetListInput */
    void CopyContent(WidgetListInput *target);
    /*! This is a reimplementation of QWidget::keyPressEvent(QKeyEvent*).
        This method handle keyboard inputs - in this case, copy and paste commands -.*/
    void keyPressEvent(QKeyEvent *event);

signals:
    /*! This signal is emitted when the user finished editing an expanded WidgetListInput values */
    void EditFinished(QVariantList val);
    void AcceptedValue(int val);

private slots:
    void ValidateModelEdit(QWidget *item);
    void SaveCurrentRowValue(QListWidgetItem *item);

};

#endif // WIDGETLISTINPUT_H
