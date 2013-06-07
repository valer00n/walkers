#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    QObject::connect(this->ui->single, SIGNAL(clicked()), this, SLOT(startSinglePlayer()));
    QObject::connect(this->ui->multi, SIGNAL(clicked()), this, SLOT(startMultiPlayer()));
    QObject::connect(this->ui->server, SIGNAL(clicked()), this, SLOT(startServer()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::startSinglePlayer() {
        this->disable(false);
        w = new GLPainter(false, this);
        w->setWindowTitle("Walkers");
        if (!this->ui->fullscreenS->checkState())
            w->switchmode();
        w->multiplayer = false;
        this->hide();
        w->show();

}

void Settings::startMultiPlayer() {
        this->disable(false);
        w = new GLPainter(true, this);
        QObject::connect(w, SIGNAL(SocketCr()), this, SLOT(socketCreated()));
        w->startmultiplayer();

//        w->show();
//        this->hide();
}

void Settings::socketCreated() {
    w->setWindowTitle("Walkers");
    if (!this->ui->fullscreenM->checkState())
        w->switchmode();
    w->sok->ip = this->ui->IP->text();
    w->sok->port = this->ui->port->text().toInt();
    w->sok->login = this->ui->login->text();
    w->sok->startconnection();
    QObject::connect(w->sok, SIGNAL(failedtoconnect()), this, SLOT(failedtoconnect()));
}

void Settings::failedtoconnect() {
    this->disable(true);
}

void Settings::startServer() {
    this->s = new Game_server(this->ui->playerN->value(), this);
    this->s->show();
    this->hide();
}

void Settings::disable(bool wh) {
    this->ui->single->setEnabled(wh);
    this->ui->multi->setEnabled(wh);
    this->ui->server->setEnabled(wh);
    this->ui->IP->setReadOnly(!wh);
    this->ui->port->setReadOnly(!wh);
    this->ui->login->setReadOnly(!wh);
    this->ui->playerN->setEnabled(wh);
    this->ui->fullscreenM->setEnabled(wh);
    this->ui->fullscreenS->setEnabled(wh);

}
