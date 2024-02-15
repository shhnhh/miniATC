#ifndef CALLLINE_H
#define CALLLINE_H

#include "abonent.h"

class CallLine
{

    Abonent *first;
    Abonent *second;

public:
    CallLine();
    Abonent* getFirst();
    void setFirst(Abonent*);
    Abonent* getSecond();
    void setSecond(Abonent*);
    void clear();
};

#endif // CALLLINE_H
