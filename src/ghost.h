#ifndef GHOSH_H
#define GHOSH_H

#include <QString>
#include <QtOpenGL>
#include <fstream>

enum Hstatus {Hstay, Hwalk, Hjump, Hcrouch, Hdead};

typedef struct {
    GLint time;
    float x, y, z, ry;
    Hstatus player;
    int sceneindex;
    int levelnumber;
} Hevent;

QString getByte(Hevent ev);
Hevent getEvent(QString bit);

class Ghost
{
private:
    QVector <Hevent> history;
public:
    Ghost();
    void load(QString path);
    void save(QString path);
    Hevent getHevent(int Heventindex);
    int gethistorylength();
    void pushHevent(Hevent ev);
    void pushHevent(GLint time, float x, float y, float z, float ry, Hstatus player, int sceneindex, int levelnumber);
    void clear();
};

#endif // GHOSH_H
