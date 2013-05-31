#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QVector>
#include <server_socket.h>
#include <QDebug>
#include <QNetworkInterface>

class server : public QObject
{
    Q_OBJECT
public:
    server();
    QTcpServer *ser;
    QVector <server_socket *> connections;
    server_socket newclient(QTcpSocket *sender);
signals:
    
public slots:
    void newconnection();
    void newmes(QByteArray mes, server_socket *ssender);
    void disconnected(server_socket *sender);
    
};

#endif // SERVER_H
