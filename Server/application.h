#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "../common/communicator.h"
#include "../common/common.h"
#include "miniatc.h"

class Application : public QCoreApplication
{
    Q_OBJECT

    MiniATC *atc;
    TCommunicator *comm;

public:

    Application(int, char**);
    ~Application();

public slots:

    void recieve(QString);

};

#endif // APPLICATION_H
