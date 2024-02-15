#include "application.h"

Application::Application(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};

    atc = new MiniATC;
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QString)), this, SLOT(recieve(QString)));
}

Application::~Application() {
    delete atc;
    delete comm;
}

void Application::recieve(QString msg)
{
    QString answer;
    QStringList arr = msg.split(separator);
    int m = arr[0].toInt();

    if (m == ABONENT_INFO_REQUEST) {
        answer << QString::number(ABONENT_INFO_ANSWER);
        int n = arr[1].toInt();
        answer << QString::number(n);
        answer << atc->getAbonent(n)->getPhoneNumber();
        answer << QString::number(atc->getAbonent(n)->getStatus());
    } else if (m == SET_NUMBER_REQUEST) {
        answer << QString::number(SET_NUMBER_ANSWER);
        int n = arr[1].toInt();
        if (atc->findAbonent(arr[2]) != 0) {
            if (atc->findAbonent(arr[2]) == n)
                answer << "1";
            else
                answer << "2";
        } else if (arr[2].contains(QRegularExpression("\\d+"))) {
            atc->getAbonent(n)->setPhoneNumber(arr[2]);
            answer << QString::number(arr[2] == atc->getAbonent(n)->getPhoneNumber());
        } else
            answer << "0";
        answer << QString::number(atc->getAbonent(n)->getStatus());
    } else if (m == LINE_INFO_REQUEST) {
        answer << QString::number(LINE_INFO_ANSWER);
        int n = arr[1].toInt();
        answer << "Линия №" + QString::number(n) + ":";
        CallLine *line = atc->getLine(n);
        if (line->getFirst() == nullptr)
            answer << "Пусто";
        else
            answer << line->getFirst()->getPhoneNumber();
        if (line->getSecond() == nullptr)
            answer << "Пусто";
        else
            answer << line->getSecond()->getPhoneNumber();
    } else if (m == CALLER_STATUS_REQUEST) {
        answer << QString::number(CALLER_STATUS_ANSWER);
        int n = arr[1].toInt();
        answer << QString::number(n);
        answer << QString::number(atc->getAbonent(n)->getStatus());
        if (atc->getAbonent(n)->getStatus() == CALL) {
            Abonent *first = atc->getAbonent(n), *second;
            CallLine *line = atc->findLine(first);
            if (line->getFirst() == first)
                second = line->getSecond();
            else
                second = line->getFirst();
            answer << QString::number(atc->findAbonent(second->getPhoneNumber()));
        }
    } else if (m == CALL_REQUEST_REQUEST) {
        answer << QString::number(CALL_REQUEST_ANSWER);
        int n = atc->findAbonent(arr[2]);
        CallLine *line = atc->getFreeLine();
        if (n == 0)
            answer << QString::number(NOT_READY);
        else if (line == nullptr)
            answer << QString::number(BUSY);
        else if (atc->getAbonent(n)->getStatus() == CALL)
            answer << QString::number(CALL);
        else if (arr[1].toInt() == n)
            answer << QString::number(SELF);
        else {
            answer << QString::number(READY);
            answer << atc->getAbonent(arr[1].toInt())->getPhoneNumber();
            answer << arr[1];
            answer << QString::number(n);
        }
    } else if (m == CALL_ANSWER_REQUEST) {
        answer << QString::number(CALL_ANSWER_ANSWER);
        CallLine *line = atc->getFreeLine();
        Abonent *first = atc->getAbonent(arr[2].toInt());
        Abonent *second = atc->getAbonent(arr[3].toInt());
        if (line == nullptr)
            answer << "2";
        else {
            answer << arr[1];
            if (arr[1].toInt()) {
                line->setFirst(first);
                line->setSecond(second);
                first->setStatus(CALL);
                second->setStatus(CALL);

            } else {
                second->setStatus(READY);
            }
        }
        answer << arr[2] << arr[3];
    } else if (m == CALL_BREAK_REQUEST) {
        answer << QString::number(CALL_BREAK_ANSWER);
        Abonent *first = atc->getAbonent(arr[1].toInt());
        Abonent *second = atc->getAbonent(arr[2].toInt());
        CallLine *line = atc->findLine(first);

        first->setStatus(READY);
        second->setStatus(READY);
        line->clear();
    } else if (m == SEND_MSG_REQUEST) {
        answer << QString::number(SEND_MSG_ANSWER);
        answer << arr[1] << arr[2];
        answer << arr[3] << arr[4];
    }

    comm->send(answer);
}
