#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QTextBrowser>
#include <QHelpEngine>

class HelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    explicit HelpBrowser(QHelpEngine* helpEngine, QWidget* parent = Q_NULLPTR);
    QVariant loadResource (int type, const QUrl& name);

private:
    QHelpEngine* helpEngine;
};

#endif // HELPBROWSER_H
