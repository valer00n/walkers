#ifndef SMDLOADER_H
#define SMDLOADER_H

#include <QVector>
#include <QtOpenGL>
#include <QString>
#include <matrix.h>

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
    QString path;
    QGLWidget *parent;
    bool stay;
    explicit SMDloader(QGLWidget *);
    void loadmodel(QString name);
    void loadanimation(QString name);
    void draw(int sceneindex);
    void draw_main();
    void setpath(QString s);
};

#endif // SMDLOADER_H
