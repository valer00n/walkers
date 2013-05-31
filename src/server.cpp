#include "server.h"

server::server()
{
    this->ser = new QTcpServer();
    QObject::connect(this->ser, SIGNAL(newConnection()), this, SLOT(newconnection()));
    if (! this->ser->listen(QHostAddress::Any, 7777))
        if (!this->ser->listen(QHostAddress::Any, 0))
            qDebug() << "Unable to start server";
     QList<QHostAddress> addr = QNetworkInterface::allAddresses();
     qDebug() << "Server started on:";
     for (QList<QHostAddress>::iterator i = addr.begin(); i < addr.end(); i++ )
         if (! ((*i).protocol())) // if IPv4
             qDebug() << QString((*i).toString() + ":" + QString::number(this->ser->serverPort()));

}

void server::newconnection() {
    while (this->ser->hasPendingConnections()) {
        server_socket *a = new server_socket(this->ser->nextPendingConnection());
        this->connections.push_back(a);
        QObject::connect(this->connections[this->connections.size() - 1], SIGNAL(newmes(QByteArray, server_socket *)), this, SLOT(newmes(QByteArray, server_socket*)));
        QObject::connect(this->connections[this->connections.size() - 1], SIGNAL(disconnected(server_socket *)), this, SLOT(disconnected(server_socket*)));
    }
}

void server::newmes(QByteArray mes, server_socket *sender) {
    for (int i = 0; i < this->connections.size(); i++)
        if (this->connections[i] != sender)
            this->connections[i]->soc->write(mes);
}

void server::disconnected(server_socket *sender) {
    int i = 0;
    while (this->connections[i] != sender)
        i++;
    for (int j = i; j < this->connections.size() - 1; j++)
        this->connections[j] = this->connections[j + 1];
    this->connections.resize(this->connections.size() - 1);
}
