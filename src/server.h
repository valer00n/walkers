#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>

class server : public QTcpServer
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SERVER_H
