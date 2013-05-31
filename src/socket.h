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
private:
    QTcpSocket *soc;
    QString ip;
    int port;
    QTimer *TIM;
    bool connected;

signals:
    void newmes(QString mes);
    void failedtoconnect();
    void connectedOK();
    void disconnected();
public slots:
    void onconnected();
    void onreadyread();
    void ondisconnected();
    void startconnection();
    void timeout();
    
};

#endif // SOCKET_H
