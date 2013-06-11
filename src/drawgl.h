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
#include <time.h>

class GLPainter : public QGLWidget
{
    Q_OBJECT
public:
    Hevent last;
    explicit GLPainter();
    void loadLists();
    void savescore();
    GLCalc *curcalc;
    GLCalcTH *pp;
    /*GL CONTROL*/
    SMDloader *Rmodel, *Smodel, *Jmodel, *Dmodel, *Cmodel, *Rarm, *Sarm, *Jarm, *Darm, *Carm;
    SMDloader *HistoryRmodel, *HistorySmodel, *HistoryJmodel, *HistoryDmodel, *HistoryCmodel, *HistoryRarm, *HistorySarm, *HistoryJarm, *HistoryDarm, *HistoryCarm;
        QTimer *TIM;
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
        void drawplayer(Hevent ev);
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
        Hevent generateevent();
public slots:
        void switchmode();
        void thstarted();
        void startit(bool multiplayer, QMainWindow *par);

signals:
        void ins_key(int key);
        void del_key(int key);
        void createdTH();
};


#endif // GLPainter_H
