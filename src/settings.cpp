#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QApplication *parent) :
    ui(new Ui::Settings)
{
    this->trans = new QTranslator;
    this->a = parent;
    ui->setupUi(this);
    ui->server->setText(tr("Start server"));
    ui->label->setText(tr("Players:"));
    ui->label_4->setText(tr("Name"));
    ui->label_2->setText(tr("IP adress"));
    ui->label_3->setText(tr("Port"));
    ui->multi->setText(tr("Start multiplayer"));
    ui->single->setText(tr("Start singleplayer"));
    ui->fullscreenM->setText(tr("fullscreen"));
    ui->fullscreenS->setText(tr("fullscreen"));
    QObject::connect(this->ui->comboBox, SIGNAL(currentIndexChanged(int)),this, SLOT(chL(int)));
    QObject::connect(this->ui->single, SIGNAL(clicked()), this, SLOT(startSinglePlayer()));
    QObject::connect(this->ui->multi, SIGNAL(clicked()), this, SLOT(startMultiPlayer()));
    QObject::connect(this->ui->server, SIGNAL(clicked()), this, SLOT(startServer()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::p1() {
    w->setWindowTitle("Walkers");
    if (!this->ui->fullscreenS->checkState())
        w->switchmode();
    w->curcalc->multiplayer = false;
    this->hide();
    w->show();
}

void Settings::p2() {
    QObject::connect(w->curcalc, SIGNAL(SocketCr()), this, SLOT(socketCreated()));
    w->curcalc->startmultiplayer();
}

void Settings::startSinglePlayer() {
    this->disable(false);
    w = new GLPainter();
    QObject::connect(w, SIGNAL(createdTH()), this, SLOT(p1()));
    w->startit(false, this);

}

void Settings::startMultiPlayer() {
    this->disable(false);
    w = new GLPainter();
    QObject::connect(w, SIGNAL(createdTH()), this, SLOT(p2()));
    w->startit(true, this);
}

void Settings::socketCreated() {
    w->setWindowTitle("Walkers");
    if (!this->ui->fullscreenM->checkState())
        w->switchmode();
    w->curcalc->sok->ip = this->ui->IP->text();
    w->curcalc->sok->port = this->ui->port->text().toInt();
    w->curcalc->sok->login = this->ui->login->text();
    QObject::connect(w->curcalc->sok, SIGNAL(failedtoconnect()), this, SLOT(failedtoconnect()));
    QObject::connect(this, SIGNAL(scon()), w->curcalc->sok, SLOT(startconnection()));
    emit this->scon();
//    w->curcalc->sok->startconnection();
}


void Settings::failedtoconnect() {
    this->disable(true);
//    w->deleteLater();
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
    this->ui->comboBox->setEditable(wh);
}

void Settings::chL(int lang) {
    switch (lang) {
        case 1:
            this->trans->load("../Textures/walkers_ru");
            break;
        case 0:
            this->trans->load("../Textures/walkers_en");
            break;
    }
    this->a->installTranslator(this->trans);
    ui->server->setText(tr("Start server"));
    ui->label->setText(tr("Players:"));
    ui->label_4->setText(tr("Name"));
    ui->label_2->setText(tr("IP adress"));
    ui->label_3->setText(tr("Port"));
    ui->multi->setText(tr("Start multiplayer"));
    ui->single->setText(tr("Start singleplayer"));
    ui->fullscreenM->setText(tr("fullscreen"));
    ui->fullscreenS->setText(tr("fullscreen"));
}
