#include "callline.h"

CallLine::CallLine() {
    first = second = nullptr;
}

Abonent* CallLine::getFirst() {
    return first;
}

void CallLine::setFirst(Abonent *line) {
    first = line;
}

Abonent* CallLine::getSecond() {
    return second;
}

void CallLine::setSecond(Abonent *line) {
    second = line;
}

void CallLine::clear() {
    first = second = nullptr;
}
