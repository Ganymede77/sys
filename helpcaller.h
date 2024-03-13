#ifndef HELPCALLER_H
#define HELPCALLER_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QKeyEvent>
#include <QDesktopServices>
#include <QApplication>
#include <QHelpEngine>
#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QTabWidget>
#include <QSplitter>
#include <QGridLayout>
#include <QHeaderView>

#include "helpbrowser.h"

class HelpCaller : public QWidget
{
    Q_OBJECT

public:
    explicit HelpCaller(QWidget *parent = nullptr);
    void InstallHelpFiles(QMap<QWidget*, QString> helpMap);
    void SetDefaultPage(QString page) {defaultPage = page;}
    QMap<QWidget*, QString> GetHelpFiles() {return helpMap;}
    void SetSource(QString src) {textViewer->setSource(QUrl(src));}

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void closeEvent(QCloseEvent *event);

private:
     QMap<QWidget*, QString> helpMap;
     HelpBrowser *textViewer;
     QString defaultPage;

};

#endif // HELPCALLER_H
