#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QTimer>
#include <QObject>

class socket: public QObject
{
    Q_OBJECT
public:
    socket();
    void wirtemessage(QByteArray bit);
public:
    QTcpSocket *soc;
    QString ip, login;
    int port;
    QTimer *TIM;
    bool connected;

signals:
    void newmes(QString mes);
    void failedtoconnect();
    void connectedOK();
    void disconnected();
    void startgame();
public slots:
    void onconnected();
    void onreadyread();
    void ondisconnected();
    void startconnection();
    void timeout();
    
};

#endif // SOCKET_H
