#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QTimer>

class timer : public QThread
{
    Q_OBJECT
public:
    explicit timer(QObject *parent = 0);
    QTimer *TIM;
    int globaltime;
};

#endif // TIMER_H
