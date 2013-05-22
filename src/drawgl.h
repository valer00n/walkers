#ifndef GLPAINTER_H
#define GLPAINTER_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QtOpenGL>
#include <QSet>
#include <QTimer>
#include <timer.h>

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

class GLPainter : public QGLWidget
{
    Q_OBJECT

public:
    GLPainter(QWidget *parent = 0);
    ~GLPainter();

protected:

    /*HELP*/
        void loadLists();
    /*GL CONTROL*/
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void jump();
        void freefall();
        void Begin2D();
        void End2D();

    /*LEVEL CONTROL*/
        void finn();
        void restart();
        bool loadparam();

    /*CONTROL*/
        void keyPressEvent(QKeyEvent *ev);
        void keyReleaseEvent(QKeyEvent *ev);
        void switchmode();
        void searchkeys();
        void mouseMoveEvent(QMouseEvent *ev);
        bool inside_key(int key);
        void throw_key(int key);
        void die();

    /*PHYSICS*/
        bool canGO(GLfloat x, GLfloat y);
        bool canGO2(GLfloat x, GLfloat y);
        bool isfloor(GLfloat x, GLfloat y);
//        void standon();

    /*DRAWING SCENE*/
        void drawQUBE(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture);
        void drawNOTHING(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture);
        void drawmap();
        void drawaxes();
        void drawSKY();
        void fogg(bool start);
        void drawinfo();
        void mainmenu();

    /*LOADING LEVEL*/
        void loadlevel();
        void levelclear();
        void loadstaticTEX();

    /*HELP*/
        GLfloat getx(GLfloat x);
        GLfloat gety(GLfloat y);
        GLfloat dist(GLfloat x, GLfloat y);
        QPixmap genpix(int w, int h, int f, QVector <QString> &mes);

private:

    /*PLAYER INFO*/
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


    /*TEXTURES*/
        QPixmap PIXsky, PIXwall, PIXfloor, PIXexit, PIXdanger, PIXhidden, PIXmoving, PIXhole, PIXfireball;
        QPixmap PIXmenu, PIXwin;
        bool stretch_sky;


private slots:
    void timeout();

};

#endif // GLPainter_H