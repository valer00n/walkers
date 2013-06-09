#ifndef GLCalc_H
#define GLCalc_H

#include <QGLWidget>
#include <smdloader.h>

#ifdef Q_OS_MAC
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

#include <QtOpenGL>
#include <QSet>
#include <QTimer>
#include <timer.h>
#include <ghost.h>
#include <socket.h>
#include <server.h>

typedef struct {
    GLfloat x, y, z;
    int interval, rest; // for 1 segment
    char direction; // UDLR
    GLfloat dist;
    GLfloat r;
    int pause;
    GLfloat stratchX, stratchY, stratchZ;
} firing;

typedef struct{
    int pause, tvis, thid;
    int x, y;
    bool visible;
    char backup;
} hidden;

typedef struct {
    QString param; // [UDLRS]
    int interval; //for 1 segment
    int x, y;
} moving;

class GLCalc : public QGLWidget
{
    Q_OBJECT

public:
    bool multiplayer;
    QVector <QPair<QString, Hevent> > players;
    QString mess[4];
public:
    GLCalc(bool multiplayer, QMainWindow *);
    ~GLCalc();

public:
    Hsocket *sok;
    HsocketTH *tmp;
    /*HELP*/
        void startmultiplayer();
    /*GL CONTROL*/
        void jump();
        void freefall();

    /*LEVEL CONTROL*/
        void finn();
        void restart();
        bool loadparam();

    /*CONTROL*/
        void searchkeys();
        bool inside_key(int key);
        void throw_key(int key);
        void die();

    /*PHYSICS*/
        bool canGO(GLfloat x, GLfloat y);
        bool canGO2(GLfloat x, GLfloat y);
        bool isfloor(GLfloat x, GLfloat y);
//        void standon();

    /*LOADING LEVEL*/
        void loadlevel();
        void levelclear();
        void loadstaticTEX();

    /*HELP*/
        GLfloat getx(GLfloat x);
        GLfloat gety(GLfloat y);
        GLfloat dist(GLfloat x, GLfloat y);
        QPixmap genpix(int w, int h, int f, QVector <QString> &mes);
        void savescore();
        Hevent generateevent();

        SMDloader *Rmodel, *Smodel, *Jmodel, *Dmodel, *Cmodel, *Rarm, *Sarm, *Jarm, *Darm, *Carm;
        SMDloader *HistoryRmodel, *HistorySmodel, *HistoryJmodel, *HistoryDmodel, *HistoryCmodel, *HistoryRarm, *HistorySarm, *HistoryJarm, *HistoryDarm, *HistoryCarm;

public:
        QMainWindow *parent;
    /*PLAYER INFO*/
        bool firstview;
        int drawindex;
        Ghost current, best;
        bool walking;
        GLint life;
        bool dead;
        GLfloat x, y, z, ry, rx;
        bool jumping, duck;
        GLint jumpiterations;
        GLfloat sx, sy, vx, vy;
        GLint timetorestart;
        GLint restime;

    /*LEVEL INFO*/
        QVector <QVector <char> > map;
        int n, m;
        int levelnomber;
        QVector <hidden> Hpanel;
        QVector <moving> Mpanel;
        QVector <firing> Fpanel;
        bool FFall;
        GLuint wall;

    /*WINDOW INFO*/
        bool fullscreen;

    /*SYSTEM*/
        GLfloat CAMERAdist;
        GLint TIME;
        QSet <int> keys_pressed;
        timer *timerT;
//        QTimer *TIM;
        GLint updatetime;
        int maxlevels;
        GLfloat mouseX, mouseY;
        GLfloat lat;
        bool mousedetected;
        GLfloat dw, dh;
        bool menuopened;
        GLint element, menel;
        QVector <QPair <QString, int> > score;
        QString nametyped, curs;
        int ttoch;


    /*TEXTURES*/
        QPixmap PIXsky, PIXwall, PIXfloor, PIXexit, PIXdanger, PIXhidden, PIXmoving, PIXhole, PIXfireball;
        QPixmap PIXmenu, PIXwin, PIXresults, PIXcred;
        QPixmap PIXmultires;
        bool stretch_sky;


private slots:
    void timeout();
    void failedtoconnect();
    void connectedOK();
    void startgame();
    void newmes(QString);
    void disconnected();
    void SocketStarted();

signals:
    void SocketCr();
    void switchmode();
    void sclose();

};

#endif // GLCalc_H
