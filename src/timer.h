#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class timer: QObject
{
    Q_OBJECT
public:
    explicit timer();
    QTimer *TIM;
    int globaltime;
};

#endif // TIMER_H
