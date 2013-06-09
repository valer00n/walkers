#include "socket.h"

Hsocket::Hsocket()
{

}


void HsocketTH::run() {
    this->socketTH = new Hsocket();
    this->socketTH->soc = new QTcpSocket;
    this->socketTH->connected = false;
    this->socketTH->TIM = new QTimer;
    this->socketTH->TIM->setInterval(4000);
    this->socketTH->TIM->stop();
    QObject::connect(this->socketTH->TIM, SIGNAL(timeout()), this->socketTH, SLOT(timeout()));
    QObject::connect(this->socketTH->soc, SIGNAL(connected()), this->socketTH, SLOT(onconnected()));
    QObject::connect(this->socketTH->soc, SIGNAL(disconnected()), this->socketTH, SLOT(ondisconnected()));
    QObject::connect(this->socketTH->soc, SIGNAL(readyRead()), this->socketTH, SLOT(onreadyread()));
    emit startedSocket();
    this->exec();
}

void Hsocket::onconnected() {
    this->writemessage(QString("l " + this->login + "~").toLocal8Bit());
}

void Hsocket::ondisconnected() {
    this->connected = false;
    emit this->disconnected();
}

void Hsocket::onreadyread() {
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

void Hsocket::startconnection() {
    this->TIM->start();
    this->soc->connectToHost(this->ip, this->port);
    this->soc->waitForConnected(4000);
}

void Hsocket::timeout() {
    this->TIM->stop();
    if (!this->connected) {
        emit this->failedtoconnect();
    }
}

void Hsocket::writemessage(QByteArray bit) {
    this->soc->write(bit);
}
