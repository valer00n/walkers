#include "server_socket.h"

server_socket::server_socket(QTcpSocket *sender) {
    this->soc = sender;
    QObject::connect(this->soc, SIGNAL(readyRead()), this, SLOT(onreadyread()));
    QObject::connect(this->soc, SIGNAL(disconnected()), this, SLOT(ondisconnected()));
}

void server_socket::onreadyread() {
    while (this->soc->bytesAvailable() != 0) {
        QByteArray ar;
        QByteArray p = this->soc->read(1);
        while (p[0] != '~') {
            ar.append(p[0]);
            p = this->soc->read(1);
        }
        emit this->newmes(ar, this);
    }
}

void server_socket::ondisconnected() {
    emit this->disconnected(this);
}
