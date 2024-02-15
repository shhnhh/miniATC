#ifndef ABONENT_H
#define ABONENT_H

#include <QString>
#include "../common/common.h"
#include <QRegularExpression>
#define PHONE_NUMBER_LENGTH 11

class Abonent
{
    QString phoneNumber;
    int status;

public:
    Abonent();
    Abonent(QString);

    QString getPhoneNumber();
    void setPhoneNumber(QString);
    int getStatus();
    void setStatus(int);

};

#endif // ABONENT_H
