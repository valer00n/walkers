#ifndef SETTINGS_H
#define SETTINGS_H

#include <drawgl.h>
#include <QMainWindow>
#include <game_server.h>
#include <calcgl.h>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    void disable(bool wh);

private:
    Ui::Settings *ui;
    GLPainter *w;
    Game_server *s;


public slots:
    void startSinglePlayer();
    void startServer();
    void startMultiPlayer();
    void failedtoconnect();
    void socketCreated();
    void p1();
    void p2();

signals:
    void scon();
};

#endif // SETTINGS_H