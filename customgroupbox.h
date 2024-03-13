#ifndef CUSTOMGROUPBOX_H
#define CUSTOMGROUPBOX_H

#include <QGroupBox>
#include <QMouseEvent>
#include <QSizeGrip>
#include <QGridLayout>
#include <QScreen>
#include <QDebug>
#include <QSpacerItem>
#include <QPainter>

namespace Ui {
class CustomGroupBox;
}

//!  \brief This class creates a custom QGroupBox.
/*!
  This class inherits QGroupBox. It's used to create a movable and resizable QGroupBox object.
*/
class CustomGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    //! Constructor for the CustomGroupBox class.
    /*!
        \param title - a QString argument that will set the title of the created CustomGroupBox.
    */
    explicit CustomGroupBox(QWidget *parent = 0, QString title = "");
    /*! Destructor for the CustomGroupBox class */
    ~CustomGroupBox();

    //! Insert a specific widget inside the layout of the CustomGroupBox.
    /*!
        \param wid - the widget that you want to add to the layout
        \param row - an integer number that represents the row that you want the widget \p wid to be inserted on.
        \param col - an integer number that represents the column that you want the widget \p wid to be inserted on.
        \param alig - a Qt::Alignment that represents the type of alignment that will be used in the layout by the \p wid widget.
    */
    void addToBox(QWidget *wid, int row, int col, Qt::Alignment alig = Qt::Alignment());
    //! Insert a specific widget inside the layout of the CustomGroupBox, utilizing rowspan and colspan.
    /*!
        Insert a specific widget inside the layout of the CustomGroupBox, utilizing rowspan and colspan.
        Check the <a href="http://doc.qt.io/qt-5/qgridlayout.html" target="_blank">QGridLayout</a> class for more information on how to use
        rowspan and colspan.

        \param wid - the widget that you want to add to the layout
        \param row - an integer number that represents the row that you want the widget \p wid to be inserted on.
        \param col - an integer number that represents the column that you want the widget \p wid to be inserted on.
        \param rowspan - and integer number that is used to determine the rowspan of the widget \p wid inside the layout.
        \param colspan - and integer number that is used to determine the columnspan of the widget \p wid inside the layout.
        \param alig - a Qt::Alignment that represents the type of alignment that will be used in the layout by the \p wid widget.
    */
    void addToBox(QWidget *wid, int row, int col, int rowspan, int colspan, Qt::Alignment alig = Qt::Alignment());
    //! Insert a specific widget inside the layout of the CustomGroupBox.
    /*!
        \param lay - the QLayout item that you want to add to the CustomGroupBox layout
        \param row - an integer number that represents the row that you want the QLayout \p lay to be inserted on.
        \param col - an integer number that represents the column that you want the QLayout \p lay to be inserted on.
        \param alig - a Qt::Alignment that represents the type of alignment that will be used in the CustomGroupBox layout by the \p lay object.
    */
    void addLayoutToBox(QLayout *lay, int row, int col, Qt::Alignment alig = Qt::Alignment());
    //! Getter that returns the \p x position of the created %CustomGroupBox
    int getX(){return x();}

private slots:
    //! This slot handles the %CustomGroupBox being clicked by the user
    void on_CustomGroupBox_clicked();
    //! This slot handles requests of resize of the %CustomGroupBox
    /*!
        \param step - the "amount" that you want to resize the box
    */
    //void ResizeRequested(double step);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
    Ui::CustomGroupBox *ui;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    QPoint offset; /*!< The offset that the mouse is in relation to its old position */
    QSizeGrip *grip; /*!< The widget that allows the box to be resized */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    QGridLayout *lay;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    int refWid; /*!< The original width of this widget. Is used to scale the widget proportionaly */
    int refHeig; /*!< The original height of this widget. Is used to scale the widget proportionaly */
    double scale; /*!< The scale factor of the box */

    //! This method handles requests of pressing a button from the mouse
    /*!
        \param event - the mouse event that happened
    */
    void mousePressEvent(QMouseEvent *event);
    //! This method handles the user moving the mouse while holding a button
    /*!
        \param event - the mouse button being held
    */
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // CUSTOMGROUPBOX_H
