#include "game_server.h"
#include "ui_game_server.h"

Game_server::Game_server(int players, QMainWindow *parent) :
    ui(new Ui::Game_server)
{
    ui->setupUi(this);
    this->players = players;
    this->parent = parent;
    this->serv = new server();
    QObject::connect(this->serv, SIGNAL(gamestarted()), this, SLOT(gamestarted()));
    QObject::connect(this->serv, SIGNAL(newnumber(int)), this, SLOT(newnumber(int)));
    QObject::connect(this->serv, SIGNAL(chplayer(QString, bool)), this, SLOT(chplayer(QString, bool)));
    this->serv->maxnumber = players;
    this->ui->listWidget->clear();
    if (!this->serv->ser->isListening())  {
        this->ui->listWidget->addItem("Unable to start server");
        this->parent->close();
    }
    this->ui->listWidget->addItem("Started server");
    this->ui->listWidget->addItem("Number of players: " + QString::number(this->players));
    QList<QHostAddress> addr = QNetworkInterface::allAddresses();
    for (QList<QHostAddress>::iterator i = addr.begin(); i < addr.end(); i++ )
        if (! ((*i).protocol())) // if IPv4
            this->ui->listWidget->addItem(QString("Server started on: " + (*i).toString() + ":" + QString::number(this->serv->ser->serverPort())));
}

Game_server::~Game_server()
{
    for (int i = 0; i < this->serv->connections.size(); i++)
        this->serv->connections[i]->soc->disconnectFromHost();
    this->parent->close();
    delete ui;
}

void Game_server::newnumber(int nn) {
    this->allcon = nn;
//    this->ui->listWidget->addItem(QString::number(nn) + "/" + QString::number(this->players) + " connected");
}

void Game_server::chplayer(QString s, bool con) {
    if (con)
        this->ui->listWidget->addItem(s + " connected [" + QString::number(this->allcon) + "/" + QString::number(this->players) + " online]");
    else
        this->ui->listWidget->addItem(s + " disconnected [" + QString::number(this->allcon) + "/" + QString::number(this->players) + " online]");
}

void Game_server::gamestarted() {
    this->ui->listWidget->addItem("Game started!");
}
