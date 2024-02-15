#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>

#include "mainwidget.h"
#include "../common/communicator.h"

class Application : public QApplication
{
    Q_OBJECT

    TCommunicator *comm;
    MainWidget   *mainInterface;

public:
    Application(int&, char**);
    ~Application();

public slots:
    void fromCommunicator(QString);
    void toCommunicator(QString);

};

#endif // APPLICATION_H
