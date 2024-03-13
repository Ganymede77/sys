#ifndef LOFMHTHREAD_H
#define LOFMHTHREAD_H

#include <QObject>
#include <QThread>
#include "../lof-mh/code/mainLib.h"
#include "../lof-mh/code/common/commondefines.h"


class Worker : public QObject {

    Q_OBJECT

public:

    Worker(std::string exeWithPath, std::string Path);
    ~Worker();
    std::string message(void)
    {
        return exe;
    }

private:
    std::string exe;
    std::string path;

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
};


#endif // LOFMHTHREAD_H
