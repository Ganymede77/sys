#ifndef COMMONS_H_LOF_
#define COMMONS_H_LOF_

#include <QString>
#include <QVariantList>
#include <widgetlistinput.h>

// /// COMMON HEADERS FOR MAINWINDOW AND MHS FILES ///

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include <QMap>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QVariantList>
#include <QErrorMessage>
#include <QProcess>
#include <QPdfWriter>
#include <QCloseEvent>
#include <sys/time.h>
#include <stdlib.h>
#include <QRandomGenerator>
#include <QPrinter>
#include <QObject>
#include <QTableView>
#include <QTreeWidgetItem>
#include <QStackedWidget>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QScrollArea>
#include <QRadioButton>
#include <QScrollBar>
#include <QProgressBar>


// This is a convention function made to simplify the code on the setMhParameters system
/* it gets a map, possibly coming from LoadMultipleMhAttFromFile and assign the multiple value inputs
  to a variantlist if it matches the tag parameter
  the list is returned
*/
QVariantList GetMultipleAttFromMap(QMap <QString, QVariant> map, QString tag);

QString GenerateWidgetListInputInfo(WidgetListInput &widget);

QString GenerateStepInfo(QString start, QString stop, QString step);

QVariantList CalculateStepList(QString start, QString stop, QString step);

/* This method generates a QString containing a pseudorandom set of characters
    \param leng - an integer that sets the length of the returning pseudorandom generated QString
*/
QString GenerateRandomChar(int leng);

/* This method is used to retrieve multiple attributes from a single tag, since they are ordered.
    By example: \code{.xml} "<tag att0="a" att1="b" att2="c" otAtt="d" />" wold return a QMap <QString, QVariant>
    containing ["a", "b", "c"].
    \param f - a QFile * object that appoints to the xml file that will be fetched
    \param key - a QString that specifies the key that will be used to store the information retrieved inside the returning QMap <QString, QVariant>
    \param tag - a QString that specifies the tag that must be fetched
    \param att - a QString that specifies the attribute that will be returned
*/
QMap<int, QMap<QString, QVariant> > LoadMultipleMhAttFromFile(QFile *f, QString key, QString tag, QString att);

/* This method retrieves an attribute from the specified XML file
    \param xmlFile - a QFile * object that will be fetched
    \param tag - a QString that specifies the tag were the attribute can be found
    \param att - a QString with the name of the attribute that must be returned */
QVariantList GetXmlAttribute(QFile *xmlFile, QString tag, QString att);

/* This method retrieves a double attribute at a determined position from the specified XML file
    \param xmlFile - a QFile * object that will be fetched
    \param tag - a QString that specifies the tag were the attribute can be found
    \param att - a QString with the name of the attribute that must be returned */
double GetXmlDoubleAttributeAt(QFile *xmlFile, QString tag, QString att, int position);

/* This method retrieves a int attribute at a determined position from the specified XML file
    \param xmlFile - a QFile * object that will be fetched
    \param tag - a QString that specifies the tag were the attribute can be found
    \param att - a QString with the name of the attribute that must be returned */
int GetXmlIntAttributeAt(QFile *xmlFile, QString tag, QString att, int position);

/* This method retrieves a string attribute at a determined position from the specified XML file
    \param xmlFile - a QFile * object that will be fetched
    \param tag - a QString that specifies the tag were the attribute can be found
    \param att - a QString with the name of the attribute that must be returned */
QString GetXmlStringAttributeAt(QFile *xmlFile, QString tag, QString att, int position);

/* This method retrieves a whole tag from the specified XML file
    \param xmlFile - a QFile * object that will be fetched
    \param tag - a QString that specifies the tag that must be returned
*/
QList<QMap <QString, QString>> GetXmlTag(QFile *xmlFile, QString tag);

/* This method retrieves the text value of a tag from the specified XML file
    \param xmlFile - a QFile * object that will be fetched
    \param tag - a QString that specifies the tag that must be fetched
*/
QString GetXmlTextValue(QFile *xmlFile, QString tag);
/* This method refreshs the info inside all ProblemSets and MhSets objects */

double RoundDecimals(double number);

std::vector<std::string> split(const std::string& s, char seperator);

#endif // COMMONS_H
