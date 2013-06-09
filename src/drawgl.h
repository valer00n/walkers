#ifndef GLPAINTER_H
#define GLPAINTER_H

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
#include <calcgl.h>

class GLPainter : public QGLWidget
{
    Q_OBJECT
public:
    void loadLists();
    void savescore();
    GLPainter(bool multiplayer, QMainWindow *);
    GLCalc *curcalc;
    /*GL CONTROL*/
    SMDloader *Rmodel, *Smodel, *Jmodel, *Dmodel, *Cmodel, *Rarm, *Sarm, *Jarm, *Darm, *Carm;
    SMDloader *HistoryRmodel, *HistorySmodel, *HistoryJmodel, *HistoryDmodel, *HistoryCmodel, *HistoryRarm, *HistorySarm, *HistoryJarm, *HistoryDarm, *HistoryCarm;
        timer *timerT;
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void Begin2D();
        void End2D();
        void keyPressEvent(QKeyEvent *ev);
        void keyReleaseEvent(QKeyEvent *ev);
        void mouseMoveEvent(QMouseEvent *ev);
        void drawQUBE(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture);
        void drawNOTHING(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture);
        void drawmap();
        void drawaxes();
        void drawplayer();
        void drawSKY();
        void fogg(bool start);
        void drawinfo();
        void mainmenu();
        void loadstaticTEX();
        void loadp1();
        void loadp2();
        GLfloat getx(GLfloat x);
        GLfloat gety(GLfloat y);
        void drawhistory(Hevent ev);

public slots:
        void switchmode();
};

#endif // GLPainter_H
