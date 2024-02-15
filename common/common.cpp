#include "common.h"

const QChar separator(';');

QString& operator<<(QString& m, const QString& s)
{
    m += s + separator;
    return m;
}

QString getModeName(int m) {
    QString ans;
    switch (m) {
        case NOT_READY:
            ans = "не готов";
            break;
        case READY:
            ans = "готов";
            break;
        case BUSY:
            ans = "линии заняты";
            break;
        case CALL:
            ans = "разговаривает";
            break;
    }
    return ans;
}
