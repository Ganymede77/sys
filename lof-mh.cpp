#include <lof-mh.h>
#include <iostream>
#include <unistd.h>
#include <QProcess>

Worker::Worker(std::string exeWithPath, std::string Path)
{
    path = Path;
    exe = exeWithPath;
}

Worker::~Worker()
{
    // free resources
}

void Worker::process()
{
    QProcess xprocess;
    QStringList arguments;
    arguments.append(exe.c_str());
    xprocess.setWorkingDirectory(exe.c_str());
    xprocess.setProgram(QString::fromStdString(path)+"/control/lof-mh.exe");
    xprocess.setArguments(arguments);
    xprocess.start();
    xprocess.waitForFinished(-1);
    //lofmh(exe.c_str());
    emit finished();
}
