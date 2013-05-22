#include "timer.h"

timer::timer(QObject *parent) :
    QThread(parent)
{
    this->globaltime = 0;
}
