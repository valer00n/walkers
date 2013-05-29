#ifndef SMDLOADER_H
#define SMDLOADER_H

#include <QVector>
#include <QtOpenGL>
#include <QString>
#include <../Projects/walkers/src/matrix.h>

typedef struct{
    GLfloat x, y, z, nx, ny, nz, s, t;
    int anc;
} vertex;
typedef struct {
    GLfloat x, y, z, rotx, roty, rotz;
} node;
typedef struct {
    QPixmap PIX;
    vertex nodes[3];
} triangle;

typedef struct {
    QVector <int> nodes;
    QVector <QVector<node> > skeleton;
    QVector <triangle> triangles;
} smdmodel;


class SMDloader {
public:
    smdmodel model, animation;
    QGLWidget *parent;
    explicit SMDloader(QGLWidget *);
    void loadmodel(QString path);
    void loadanimation(QString path);
    void draw(int sceneindex);
    void draw_main();
};

#endif // SMDLOADER_H
