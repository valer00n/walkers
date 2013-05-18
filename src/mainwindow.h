#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QtOpenGL>
#include <QSet>
#include <QTimer>

typedef struct{
    int pause, tvis, thid;
    int x, y;
    bool visible;
    char backup;
} hidden;

typedef struct {
    QString param;
    int interval; //for 1 segment
    int x, y;
} moving;

class MainWindow : public QGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

    /*GL CONTROL*/
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void jump();
        void freefall();

    /*LEVEL CONTROL*/
        void finn();
        void restart();
        void loadparam();

    /*CONTROL*/
        void keyPressEvent(QKeyEvent *ev);
        void keyReleaseEvent(QKeyEvent *ev);
        void switchmode();
        void searchkeys();
        void mouseMoveEvent(QMouseEvent *ev);
        bool inside_key(int key);
        void throw_key(int key);

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

    /*LOADING LEVEL*/
        void loadlevel();

private:

    /*PLAYER INFO*/
        bool dead;
        GLfloat x, y, z, ry, rx;
        bool jumping;
        GLint jumpiterations;

    /*LEVEL INFO*/
        QVector <QVector <char> > map;
        int n, m;
        int levelnomber;
        QVector <hidden> Hpanel;
        QVector <moving> Mpanel;

    /*WINDOW INFO*/
        bool fullscreen;

    /*SYSTEM*/
        GLint TIME;
        QSet <int> keys_pressed;
        QTimer *TIM;
        GLint updatetime;
        int maxlevels;
        GLfloat mouseX, mouseY;
        GLfloat lat;
        bool mousedetected;

    /*TEXTURES*/
        QPixmap PIXsky, PIXwall, PIXfloor, PIXdrop, PIXexit, PIXdanger, PIXhidden, PIXmoving;



private slots:
    void timeout();

};

#endif // MAINWINDOW_H
