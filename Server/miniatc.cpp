#include "miniatc.h"

MiniATC::MiniATC() {
    for (int i = 0; i < 15; i++)
        abonents.push_back(Abonent());
    for (int i = 0; i < 4; i++)
        lines.push_back(CallLine());
}

Abonent* MiniATC::getAbonent(int n) {
    return &abonents[n - 1];
}

int MiniATC::findAbonent(QString number) {
    for (int i = 0; i < 15; i++)
        if (abonents[i].getPhoneNumber() == number)
            return i + 1;
    return 0;
}

CallLine* MiniATC::getLine(int n) {
    return &lines[n - 1];
}

CallLine* MiniATC::getFreeLine() {
    for (int i = 0; i < 4; i++) {
        if (lines[i].getFirst() == nullptr && lines[i].getSecond() == nullptr)
            return &lines[i];
    }
    return nullptr;
}

CallLine* MiniATC::findLine(Abonent *abonent) {
    for (int i = 0; i < 4; i++)
        if (lines[i].getFirst() == abonent || lines[i].getSecond() == abonent)
            return &lines[i];
    return nullptr;
}
