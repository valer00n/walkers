#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QVector>
#include <server_socket.h>
#include <QDebug>
#include <QNetworkInterface>
#include <algorithm>

class server : public QObject
{
    Q_OBJECT
public:
    server();
    QTcpServer *ser;
    QVector <server_socket *> pending;
    QVector <server_socket *> connections;
    QVector <bool> finished;
    QVector <QString> names;
    QVector <QPair <int, QString> > results;
    server_socket newclient(QTcpSocket *sender);
    int maxnumber;
    bool started;
signals:
    void newnumber(int);
    void chplayer(QString mes, bool con);
    void gamestarted();
    
public slots:
    void newconnection();
    void newmes(QByteArray mes, server_socket *ssender);
    void newlogin(QByteArray mes, server_socket *ssender);
    void disconnected(server_socket *sender);
    
};

#endif // SERVER_H
