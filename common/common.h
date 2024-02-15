#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum modes
{
    NOT_READY = 0,
    READY,
    BUSY,
    CALL,
    SELF,
};

QString getModeName(int);

enum messages
{
    ABONENT_INFO_REQUEST = 1,
    ABONENT_INFO_ANSWER,
    SET_NUMBER_REQUEST,
    SET_NUMBER_ANSWER,
    LINE_INFO_REQUEST,
    LINE_INFO_ANSWER,
    CALLER_STATUS_REQUEST,
    CALLER_STATUS_ANSWER,
    CALL_REQUEST_REQUEST,
    CALL_REQUEST_ANSWER,
    CALL_ANSWER_REQUEST,
    CALL_ANSWER_ANSWER,
    CALL_BREAK_REQUEST,
    CALL_BREAK_ANSWER,
    SEND_MSG_REQUEST,
    SEND_MSG_ANSWER,
};

extern const QChar separator;
QString& operator<<(QString&, const QString&);

#endif // COMMON_H
