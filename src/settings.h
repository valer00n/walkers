#ifndef SETTINGS_H
#define SETTINGS_H

#include <drawgl.h>
#include <QMainWindow>
#include <game_server.h>

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
};

#endif // SETTINGS_H
