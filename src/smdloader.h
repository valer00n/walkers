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
private:
    smdmodel model, animation;
    QVector <GLuint> compiled;
    QString path;
    QGLWidget *parent;
    GLfloat alpha;
    bool stay;
public:
    void setpatent(QGLWidget *parent);
    GLint getanimationlength();
    void setstay(bool stay);
    void setalpha(GLfloat alpha);
    GLfloat getalpha();
    bool getstay();
    explicit SMDloader(QGLWidget *);
    void loadmodel(QString name);
    void loadanimation(QString name);
    void draw(int sceneindex);
    void draw_skeleton(int sceneindex);
    void setpath(QString s);
};

#endif // SMDLOADER_H
