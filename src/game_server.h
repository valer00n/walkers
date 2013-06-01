#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <drawgl.h>
#include <QMainWindow>
#include <server.h>

namespace Ui {
class Game_server;
}

class Game_server : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Game_server(int players, QMainWindow *parent);
    ~Game_server();
    void disable(bool wh);
    
private:
    Ui::Game_server *ui;
    QMainWindow *parent;
    int players, allcon;
    server *serv;

public slots:
    void newnumber(int);
    void chplayer(QString, bool);
    void gamestarted();
};

#endif // Game_server_H
