#include "helpcaller.h"

HelpCaller::HelpCaller(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_GroupLeader);

    defaultPage = "index.html";

    QHelpEngine *helpEngine = new QHelpEngine(QApplication::applicationDirPath() + "/lof_system_help.qhc");
    helpEngine->setupData();
    helpEngine->registerDocumentation(QApplication::applicationDirPath() + "/lof_system_help.qhc");

    QTabWidget* tabWidget = new QTabWidget();
    tabWidget->setMaximumWidth(200);
    tabWidget->addTab(helpEngine->contentWidget(), "Contents");
    tabWidget->addTab(helpEngine->indexWidget(), "Index");
    tabWidget->setMaximumWidth(helpEngine->contentWidget()->header()->length());

    textViewer = new HelpBrowser(helpEngine);
    textViewer->setSource(QUrl("qthelp://lof.system.helpfiles/help/" + defaultPage));
    connect(helpEngine->contentWidget(), SIGNAL(linkActivated(QUrl)), textViewer, SLOT(setSource(QUrl)));
    connect(helpEngine->indexWidget(), SIGNAL(linkActivated(QUrl, QString)), textViewer, SLOT(setSource(QUrl)));

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->insertWidget(0, tabWidget);
    splitter->insertWidget(1, textViewer);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(splitter, 0, 0);
    this->setLayout(grid);
}

bool HelpCaller::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if(key->key() == Qt::Key_F1)
        {
            QWidget *widget = Q_NULLPTR;
            QString page = defaultPage;

            if (obj->isWidgetType())
                widget = static_cast<QWidget*>(obj)->focusWidget();

            QMap<QWidget*, QString>::const_iterator it = helpMap.find(widget);

            if (it != helpMap.constEnd())
                page = *it;

            textViewer->setSource(QUrl("qthelp://lof.system.helpfiles/help/" + page));

            this->showMaximized();

            return true;

        }
    }
    else
        return QObject::eventFilter(obj, event);

    return false;
}

void HelpCaller::InstallHelpFiles(QMap<QWidget*, QString> map)
{
    helpMap = map;
}

void HelpCaller::closeEvent(QCloseEvent *event)
{
    this->setHidden(true);
    event->ignore();
}
