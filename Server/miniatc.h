#ifndef MINIATC_H
#define MINIATC_H

#include "abonent.h"
#include "callline.h"
#include <QVector>

class MiniATC
{

    QVector <Abonent> abonents;
    QVector <CallLine> lines;

public:
    MiniATC();
    Abonent* getAbonent(int);
    int findAbonent(QString);
    CallLine* getLine(int);
    CallLine* getFreeLine();
    CallLine* findLine(Abonent*);
};

#endif // MINIATC_H
