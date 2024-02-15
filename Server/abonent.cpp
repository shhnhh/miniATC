#include "abonent.h"

Abonent::Abonent() {
    phoneNumber = QString("x").repeated(PHONE_NUMBER_LENGTH);
    status = NOT_READY;
}

Abonent::Abonent(QString number) {
    if (status == CALL)
        return;
    if (number.length() == PHONE_NUMBER_LENGTH) {
        phoneNumber = number;
        if (number.contains("\\d+"))
            status = READY;
        else
            status = NOT_READY;
    } else {
        phoneNumber = QString("x").repeated(PHONE_NUMBER_LENGTH);
        status = NOT_READY;
    }
}

QString Abonent::getPhoneNumber() {
    return phoneNumber;
}

void Abonent::setPhoneNumber(QString number) {
    if (number.length() == PHONE_NUMBER_LENGTH) {
        phoneNumber = number;
        status = READY;
    } else {
        phoneNumber = QString("x").repeated(PHONE_NUMBER_LENGTH);
        status = NOT_READY;
    }
}

int Abonent::getStatus() {
    return status;
}

void Abonent::setStatus(int new_status) {
    status = new_status;
}
