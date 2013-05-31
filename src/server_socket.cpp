#include "server_socket.h"

server_socket::server_socket(QTcpSocket *sender) {
    this->soc = sender;
    QObject::connect(this->soc, SIGNAL(readyRead()), this, SLOT(onreadyread()));
    QObject::connect(this->soc, SIGNAL(disconnected()), this, SLOT(ondisconnected()));
}

void server_socket::onreadyread() {
    emit this->newmes(this->soc->read(256), this);
}

void server_socket::ondisconnected() {
    emit this->disconnected(this);
}
