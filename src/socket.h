#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QTimer>
#include <QObject>
#include <QThread>

class Hsocket: public QObject
{
    Q_OBJECT
public:
    Hsocket();
    void writemessage(QByteArray bit);
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

class HsocketTH: public QThread
{
    Q_OBJECT
public:
    Hsocket *socketTH;
    void run();
signals:
    void startedSocket();
};

#endif // SOCKET_H
