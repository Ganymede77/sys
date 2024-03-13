#ifndef LOFAUXILIAR_H
#define LOFAUXILIAR_H

#include <QStandardItemModel>
#include <QMainWindow>
#include "mhs/mhsets.h"
#include "mhs/problemsets.h"
#include <QDoubleSpinBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QVariant>
#include <QString>
#include <QTableWidget>

static bool isIntermediateValueHelper(qint64 num, qint64 minimum, qint64 maximum, qint64 *match = 0);

class QScienceSpinBox : public QDoubleSpinBox
{
Q_OBJECT
public:
    QScienceSpinBox(QWidget * parent = 0);

    int decimals() const;
    void setDecimals(int value);

    QString textFromValue ( double value ) const;
    double valueFromText ( const QString & text ) const;

private:
    int dispDecimals;
    QChar delimiter, thousand;
    QDoubleValidator * v;

private:
    void initLocalValues(QWidget *parent);
    bool isIntermediateValue(const QString &str) const;
    QVariant validateAndInterpret(QString &input, int &pos, QValidator::State &state) const;
    QValidator::State validate(QString &text, int &pos) const;
    void fixup(QString &input) const;
    QString stripped(const QString &t, int *pos) const;
    double round(double value) const;
    void stepBy(int steps);

public slots:
    void stepDown();
    void stepUp();

};


class QTableViewClipboard : public QTableView
{
    Q_OBJECT
public:
//  QTableWidgetWithCopyPaste(int rows, int columns, QWidget *parent = 0) :
//      QTableView(rows, columns, parent)
//  {}

  QTableViewClipboard(QWidget *parent = 0) :
  QTableView(parent)
  {}

private:
  void copy();
  //void paste();

public slots:
  void keyPressEvent(QKeyEvent * event);
};


#endif // LOFAUXILIAR_H
