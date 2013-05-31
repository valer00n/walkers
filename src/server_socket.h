#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <QTcpSocket>

class server_socket : public QObject
{
    Q_OBJECT
public:
    explicit server_socket(QTcpSocket *sender);
    QTcpSocket *soc;
signals:
    void newmes(QByteArray ar, server_socket *sender);
    void disconnected(server_socket *sender);
public slots:
    void onreadyread();
    void ondisconnected();
    
};

#endif // SERVER_SOCKET_H
