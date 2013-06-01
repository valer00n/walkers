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
    this->writemessage(QString("l " + this->login + "~").toLocal8Bit());
}

void socket::ondisconnected() {
    this->connected = false;
    emit this->disconnected();
}

void socket::onreadyread() {
    while (this->soc->bytesAvailable() != 0) {
        QByteArray bit;
        QByteArray p = this->soc->read(1);
        while (p[0] != '~') {
            bit.append(p[0]);
            p = this->soc->read(1);
        }
        if (bit[0] == 'Y') {
            this->connected = true;
            emit this->connectedOK();
        }
        else if (bit[0] == 'N') {
            this->connected = false;
            emit this->failedtoconnect();
        }
        else if (bit[0] == 's') {
            emit  this->startgame();
        }
        else
            emit this->newmes(QString::fromLocal8Bit(bit));
    }
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

void socket::writemessage(QByteArray bit) {
    this->soc->write(bit);
}
