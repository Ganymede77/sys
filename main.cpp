#include "mainwindow.h"
#include <QApplication>

//#define __TESTETHREAD__
#ifdef  __TESTETHREAD__
#include "lof-mh.h"
#endif

int main(int argc, char *argv[])
{
    #ifndef __TESTETHREAD__
    /*! \mainpage notitle

        \section Introduction

        This is the documentation of the LOf-MH GUI code. Here you will find
        all the info needed to understand and edit the LOF-MH GUI code.
        It has near 17 thousand lines scattered around 10 constructed classes.
        It uses QtCreator due to its high acceptance, ease of use and being multi-platform.
    */
    QApplication app(argc, argv);
    app.setOrganizationName("IEAv");
    app.setOrganizationDomain("LEV");
    app.setApplicationName("LOF-SYSTEM");
    MainWindow *w = new MainWindow();
    w->show();
    return app.exec();
    #else

    QCoreApplication a(argc, argv);
#if 0
    // Create a worker object
    //Worker worker("c:/Users/lev/Downloads/SHORT/OK_ACKLEY_0_SINECOSINE_3/result/teste_0/");
    Worker worker("c:/Users/lev/Downloads/SHORT/OK_ACKLEY_0_PARTICLESWARM_5/result/teste_0/");

    // Create a thread object
    QThread thread;

    // Move the worker object to the thread
    worker.moveToThread(&thread);

    // Connect the worker's doWork() slot to the thread's started() signal
    QObject::connect(&thread, &QThread::started, &worker, &Worker::process);

    // Start the thread
    thread.start();

    // Wait for the thread to finish
    thread.wait();
#endif
    //lofmh("c:/Users/lev/Downloads/SHORT/OK_ACKLEY_0_PARTICLESWARM_5/result/teste_0/");
    //lofmh("c:/Users/lev/Downloads/SHORT/OK_ACKLEY_0_SINECOSINE_3/result/teste_0/");

    return 0;
    #endif
}
