#include "server.h"

server::server()
{
    this->started = false;
    this->ser = new QTcpServer();
    QObject::connect(this->ser, SIGNAL(newConnection()), this, SLOT(newconnection()));
    if (! this->ser->listen(QHostAddress::Any, 7777))
        if (!this->ser->listen(QHostAddress::Any, 0))
            qDebug() << "Unable to start server";

}

void server::newconnection() {
    while (this->ser->hasPendingConnections()) {
        server_socket *a = new server_socket(this->ser->nextPendingConnection());
        this->pending.push_back(a);
        QObject::connect(this->pending[this->pending.size() - 1], SIGNAL(newmes(QByteArray, server_socket *)), this, SLOT(newlogin(QByteArray,server_socket*)));
    }
}

void server::newlogin(QByteArray mes, server_socket *sender) {
    QString s = QString::fromLocal8Bit(mes);
    bool r = true;
    for (int i = 0; i < this->names.size(); i++)
        if (this->names[i] == s.right(s.length() - 2))
            r = false;
    if (s[0] == 'l') {
        for (int i = 0; i < this->pending.size(); i++)
            if (this->pending[i] == sender) {
                if (r) {
                    if (this->started)
                        return;
                    emit this->newnumber(this->connections.size() + 1);
                    emit this->chplayer(s.right(s.length() - 2), true);
                    this->names.push_back(s.right(s.length() - 2));
                    this->connections.push_back(this->pending[i]);
                    this->finished.push_back(false);
                    QObject::disconnect(this->pending[i], SIGNAL(newmes(QByteArray, server_socket *)), this, SLOT(newlogin(QByteArray,server_socket*)));
                    QObject::connect(this->connections[this->connections.size() - 1], SIGNAL(newmes(QByteArray, server_socket *)), this, SLOT(newmes(QByteArray, server_socket*)));
                    QObject::connect(this->connections[this->connections.size() - 1], SIGNAL(disconnected(server_socket *)), this, SLOT(disconnected(server_socket*)));
                    this->pending[i]->soc->write(QString("Y~").toLocal8Bit());
                    for (int j = 0; j < this->pending.size() - 1; j++)
                        this->pending[j] = this->pending[j + 1];
                    this->pending.resize(this->pending.size() - 1);
                    if (this->connections.size() == this->maxnumber) {
                        for (int i = 0; i < this->connections.size(); i++)
                            this->connections[i]->soc->write(QString("s~").toLocal8Bit());
                        this->started = true;
                        emit this->gamestarted();
                    }
                }
                else
                    this->pending[i]->soc->write(QString("N~").toLocal8Bit());
                break;
            }
    }
}

void server::newmes(QByteArray mes, server_socket *sender) {
    QString s = QString::fromLocal8Bit(mes);
    if (s[0] == 'f') {
        for (int i = 0; i < this->connections.size(); i++)
            if (this->connections[i] == sender) {
                this->results.push_back(QPair <int, QString> (s.right(s.length() - 2).toInt(), this->names[i]));
                this->finished[i] = true;
            }
        std::sort(results.begin(), results.end());
        QString res = "f " + QString::number(this->results.size()) + " ";
        for (int i = results.size() - 1; i >= 0; i--)
            res += QString::number(this->results[i].first) + " \"" + this->results[i].second+ "\"";
        res += "~";
        for (int i = 0; i < this->connections.size(); i++)
            if (this->finished[i])
                this->connections[i]->soc->write(res.toLocal8Bit());
    }
    else
        if (s[0] == 'e') {
            mes = QString(QString::fromLocal8Bit(mes) + "~").toLocal8Bit();
            for (int i = 0; i < this->connections.size(); i++)
                if (this->connections[i] != sender)
                    this->connections[i]->soc->write(mes);
        }
}

void server::disconnected(server_socket *sender) {
    int i = 0;
    while (this->connections[i] != sender)
        i++;
    emit this->newnumber(this->connections.size() - 1);
    emit this->chplayer(this->names[i], false);
    for (int j = i; j < this->connections.size() - 1; j++) {
        this->connections[j] = this->connections[j + 1];
        this->names[j] = this->names[j + 1];
        this->finished[j] = this->finished[j + 1];
    }
    this->connections.resize(this->connections.size() - 1);
    this->names.resize(this->names.size() - 1);
}
