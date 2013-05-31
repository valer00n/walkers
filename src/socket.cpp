#include "socket.h"

socket::socket()
{
    this->connected = false;
    this->soc = new QTcpSocket;
    this->TIM = new QTimer;
    this->TIM->setInterval(4000);
    this->TIM->stop();
    QObject::connect(this->TIM, SIGNAL(timeout()), this, SLOT(timeout()));
    QObject::connect(this->soc, SIGNAL(connected()), this, SLOT(onconnected()));
    QObject::connect(this->soc, SIGNAL(disconnected()), this, SLOT(ondisconnected()));
    QObject::connect(this->soc, SIGNAL(readyRead()), this, SLOT(onreadyread()));
}
void socket::onconnected() {
    this->connected = true;
}

void socket::ondisconnected() {
    this->connected = false;
}

void socket::onreadyread() {
    QByteArray bit;
    bit = this->soc->read(256);
    emit this->newmes(QString::fromLocal8Bit(bit));
}

void socket::startconnection() {
    this->TIM->start();
    this->soc->connectToHost(this->ip, this->port);
}

void socket::timeout() {
    this->TIM->stop();
}
