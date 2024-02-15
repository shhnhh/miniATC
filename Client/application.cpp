#include "application.h"

Application::Application(int& argc, char *argv[])
            : QApplication(argc, argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10001,
                         QHostAddress("127.0.0.1"), 10000};
    comm = new TCommunicator(pars, this);

    mainInterface = new MainWidget();
    mainInterface->show();

    connect(comm, SIGNAL(recieved(QString)), this,
            SLOT(fromCommunicator(QString)));
    connect(mainInterface->control_widget, SIGNAL(request(QString)),
            this, SLOT(toCommunicator(QString)));
    connect(mainInterface->status_widget, SIGNAL(request(QString)),
            this, SLOT(toCommunicator(QString)));

}

Application::~Application() {
    delete mainInterface;
    delete comm;
}

void Application::fromCommunicator(QString msg)
{
    int m = msg.split(separator)[0].toInt();
    switch (m) {
        case ABONENT_INFO_ANSWER:
        case SET_NUMBER_ANSWER:
        case LINE_INFO_ANSWER:
            mainInterface->control_widget->answer(msg);
            break;
        case CALLER_STATUS_ANSWER:
        case CALL_REQUEST_ANSWER:
        case CALL_ANSWER_ANSWER:
        case CALL_BREAK_ANSWER:
        case SEND_MSG_ANSWER:
            mainInterface->status_widget->answer(msg);
            break;
    }
}

void Application::toCommunicator(QString msg)
{
    comm->send(msg);
}
