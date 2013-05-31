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
    this->ip = "127.0.0.1";
    this->port = 7777;
    this->startconnection();
}
void socket::onconnected() {
    qsrand(time(0));
    this->wirtemessage((QByteArray) (QString::number(qrand() % 123).toLocal8Bit()));
    this->connected = true;
    emit this->connectedOK();
}

void socket::ondisconnected() {
    this->connected = false;
    emit this->disconnected();
}

void socket::onreadyread() {
    QByteArray bit;
    bit = this->soc->read(256);
    emit this->newmes(QString::fromLocal8Bit(bit));
}

void socket::startconnection() {
    this->TIM->start();
    this->soc->connectToHost(this->ip, this->port);
    this->soc->waitForConnected(4000);
}

void socket::timeout() {
    this->TIM->stop();
    if (!this->connected) {
        emit this->failedtoconnect();
    }
}

void socket::wirtemessage(QByteArray bit) {
    this->soc->write(bit);
}
