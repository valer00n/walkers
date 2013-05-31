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
        w->show();
        this->hide();
}

void Settings::startMultiPlayer() {
        this->disable(false);
        w = new GLPainter(true, this);
        w->setWindowTitle("Walkers");
        if (!this->ui->fullscreenM->checkState())
            w->switchmode();
        w->multiplayer = true;
        w->show();
        this->hide();
}

void Settings::startServer() {

}

void Settings::disable(bool wh) {
    this->ui->single->setEnabled(wh);
    this->ui->multi->setEnabled(wh);
    this->ui->server->setEnabled(wh);
}
