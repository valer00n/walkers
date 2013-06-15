#include "drawgl.h"
#include <QDebug>
#include <cstdio>
#include <cmath>
#include <QDir>
#include <fstream>
#include <QPainter>
#include <string>
#include <ghost.h>

void GLCalcTH::run() {
    this->p = new GLCalc(this->mult, this->par);
    emit this->started();
    this->exec();
//    qDebug() << "run";
}

void GLCalc::ins_key(int ev) {
     this->keys_pressed.insert(ev);
}

void GLCalc::del_key(int ev) {
    if (this->keys_pressed.find(ev) != this->keys_pressed.end())
        this->keys_pressed.erase(this->keys_pressed.find(ev));
}

void GLCalc::newmes(QString mes) {
    if (mes[0] == 'e') {
        int i = 2;
        QString sender = "";
        while (mes[i] != ' ') {
            sender += mes[i];
            i++;
        }
        i++;
        Hevent ev = getEvent(mes.right(mes.length() - i));
//        qDebug() << ev.time;
        bool found = false;
        for (int i = 0; i < this->players.size(); i++)
            if (this->players[i].first == sender) {
                found = true;
                this->players[i].second = ev;
            }
        if (!found) {
            this->players.push_back(QPair <QString, Hevent> (sender, ev));
        }
    }
    if (mes[0] == 'f') {
        QVector <QString> me(0);
        QVector <QString> names(0);
        QVector <int> resu(0);
        QString s;
        int i = 2;
        int cnt;
        while (mes[i] != ' ') {
            s += mes[i];
            i++;
        }
        cnt = s.toInt();
        for (int j = 0; j < cnt; j++) {
            int res;
            QString name = "";
            s = "";
            i++;
            while (mes[i] != ' ') {
                s += mes[i];
                i++;
            }
            res = s.toInt();
            i++;
            i++;
            s = "";
            while (mes[i] != '\"') {
                s += mes[i];
                i++;
            }
            name = s;
            i++;
            resu.push_back(res);
            names.push_back(name);
        }
        int mm = 0;
        for (int i = 0; i < names.size(); i++)
            mm = std::max(mm, names[i].length());
        for (int i = 0; i < names.size(); i++)
            while (names[i].length() != mm)
                names[i] += " ";
        for (int i = 0; i < names.size(); i++)
            me.push_back(names[i] + " :: " + QString::number(resu[i]));
        me.push_back(tr("<Press Esc. to exit>"));
        this->PIXmultires = this->genpix(1024, 1024, 40, me);
    }
    if (mes[0] == 'm') {
        this->mess[3] = this->mess[2];
        this->mess[2] = this->mess[1];
        this->mess[1] = this->mess[0];
        this->mess[0] = mes.right(mes.length() - 2);
    }
}

GLCalc::GLCalc(bool multiplayer, QMainWindow *parent)
{
    this->secure = true;
    this->mess[0] = this->mess[1] = this->mess[2] = this->mess[3] = "";
    this->lat = 20.0f;
    this->multiplayer = multiplayer;
    this->parent = parent;
    this->lat = lat;
    if (!QDir("../Results").exists())
        QDir().mkdir("../Results");
    std::ifstream in;
    in.open("../Results/results.walk");
    if (!in.is_open()) {
        std::ofstream out;
        out.open("../Results/results.walk");
        out << "Daniel\"6250\"";
        out << "Rudolf\"4274\"";
        out << "Eric\"4032\"";
        out << "John\"3861\"";
        out << "Steve\"3424\"";
        out << "Frank\"3367\"";
        out << "Ben\"3048\"";
        out << "Mike\"2380\"";
        out << "Alexey\"1269\"";
        out << "Bill\"1000\"";
        out.close();
        in.open("../Results/results.walk");
    }
    in.close();
    this->firstview = false;
    this->CAMERAdist = .5;
    this->curs = "";
    this->timerT = new timer;
    this->timerT->TIM = new QTimer;
    this->timerT->TIM->stop();
    this->timerT->TIM->setInterval(17);

//    this->timerT->TIM->start();
    this->jumping = false;
    this->rx = 0;
    this->mousedetected = false;
    this->levelnomber = -1;
    this->TIME = 0;
    this->onthislevel = 0;
    this->fullscreen = true;
    this->restime = 1500;
    this->menuopened = false;
    this->duck = false;
    this->loadparam();
    this->loadstaticTEX();
    this->FFall = false;
    this->life = 0;
    if (!this->multiplayer) {
      QObject::connect(this->timerT->TIM, SIGNAL(timeout()), this, SLOT(timeout()));
      finn();
    }
}

void GLCalc::startmultiplayer() {
    if (this->multiplayer) {
        this->tmp = new HsocketTH();
        QObject::connect(this->tmp, SIGNAL(startedSocket()), this, SLOT(SocketStarted()));
        this->tmp->start();
    }
}

void GLCalc::SocketStarted() {
    this->sok = this->tmp->socketTH;
    QObject::connect(this->sok, SIGNAL(failedtoconnect()), this, SLOT(failedtoconnect()));
    QObject::connect(this->sok, SIGNAL(connectedOK()), this, SLOT(connectedOK()));
    QObject::connect(this->sok, SIGNAL(startgame()), this, SLOT(startgame()));
    QObject::connect(this->sok, SIGNAL(newmes(QString)), this, SLOT(newmes(QString)));
    QObject::connect(this->sok, SIGNAL(disconnected()), this, SLOT(disconnected()));
    emit this->SocketCr();
}

void GLCalc::disconnected() {
    this->mess[3] = "";
    this->mess[2] = "";
    this->mess[1] = "";
    this->mess[0] = tr("Lost connection to server ='(");
}

void GLCalc::startgame() {
    this->FFall = true;
}

void GLCalc::connectedOK() {
    this->parent->hide();
    emit this->showW();
    QObject::connect(this->timerT->TIM, SIGNAL(timeout()), this, SLOT(timeout()));
    finn();
}

void GLCalc::failedtoconnect() {
//    this->close();
}

GLCalc::~GLCalc()
{
    emit this->sclose();
}

bool GLCalc::inside_key(int key) {
    return (this->keys_pressed.find(key) != this->keys_pressed.end());
}

void GLCalc::throw_key(int key) {
    if (this->keys_pressed.find(key) != this->keys_pressed.end())
        this->keys_pressed.erase(this->keys_pressed.find(key));
}

bool canstand(GLfloat x, GLfloat y, GLfloat x1, GLfloat y1) {
    y = -y - 1;
    return (fabs(x - x1) < 0.65f) && (fabs(y - y1) <= 0.65);
}

QPair <GLfloat, GLfloat> getpos(GLint TIME, moving panel) {
    GLfloat x = panel.x;
    GLfloat y = panel.y;

    int pt = (TIME) % (panel.param.length() * panel.interval);
    for (int j = 0; j < pt / (panel.interval); j++) {
        if (panel.param[j] == 'U')
            x--;
        if (panel.param[j] == 'D')
            x++;
        if (panel.param[j] == 'R')
            y++;
        if (panel.param[j] == 'L')
            y--;
    }
    QChar dir = panel.param[pt / (panel.interval)];
    GLfloat delta = (GLfloat) (pt % (panel.interval)) / panel.interval;
    if (dir == 'U')
        x -= delta;
    if (dir == 'D')
        x += delta;
    if (dir == 'R')
        y += delta;
    if (dir == 'L')
        y -= delta;
    return QPair <GLfloat, GLfloat> (x, y);
}

QPair <GLfloat, GLfloat> getdir(GLint TIME, moving panel) {
    GLfloat x = 0;
    GLfloat y = 0;

    int pt = (TIME) % (panel.param.length() * panel.interval);
    QChar dir = panel.param[pt / (panel.interval)];
    if (dir == 'U')
        x = -1;
    if (dir == 'D')
        x = 1;
    if (dir == 'R')
        y = 1;
    if (dir == 'L')
        y = -1;
    return QPair <GLfloat, GLfloat> (x, y);
}

bool GLCalc::loadparam() {
    std::ifstream in;
    in.open("../Levels/param.walk");
    if (! in.is_open()) {
        std::ofstream out;
        out.open("../Levels/param.walk");
        int n = 1;
        while (QFile("../Levels/" + QString::number(n) + ".lvl").exists())
            n++;          
        n--;
        out << n;
        out.close();
        in.open("../Levels/param.walk");
    }
    in >> this->maxlevels;
    in.close();
    this->updatetime = 17;
//    this->lat = 20.0f;
    return true;
}


GLfloat fabs(GLfloat a) {
    if (a < 0)
        return -a;
    else
        return a;
}


bool GLCalc::canGO (GLfloat x, GLfloat y) {
    return
            this->canGO2(x + 1e-1, y + 1e-1) &&
            this->canGO2(x + 1e-1, y - 1e-1) &&
            this->canGO2(x - 1e-1, y + 1e-1) &&
            this->canGO2(x - 1e-1, y - 1e-1);
}

bool GLCalc::canGO2(GLfloat x, GLfloat y) {
    if ((x >= 0) && (x < n) && (y >= 0) && (y  < m) && (this->map[(GLint)floor(x)][(GLint)floor(y)] == 'E')) {
        this->finn();
        return false;
    }
    return (x >= 0) && (x < n) && (y >= 0) && (y < m) && (this->map[(GLint)floor(x)][(GLint)floor(y)] != '*');
}

void GLCalc::finn() {
    this->timerT->TIM->stop();
//    emit this->stopTTT();
    this->CAMERAdist = 0;
    this->secure = false;
//    this->keys_pressed.clear();
    if (this->multiplayer && (this->levelnomber == this->maxlevels)) {
        this->sok->writemessage(QString("m " + this->sok->login + " finished game~").toLocal8Bit());
        this->levelnomber = this->maxlevels + 2;
        this->sok->writemessage(QString("e " + this->sok->login + " " + getByte(this->generateevent()) + "~").toLocal8Bit());
        this->levelclear();
        int newscore = 1000000 / (this->timerT->globaltime / 1000 + 10 * this->life + 1);
        this->sok->writemessage(QString("f " + QString::number(newscore) + "~").toLocal8Bit());
        this->restart();
//        emit this->startTTT();
        this->secure = true;
        return;
    }
    this->nametyped = "";
    if ((this->levelnomber > 0) && (this->levelnomber <= this->maxlevels))
        if ((this->current.gethistorylength() < this->best.gethistorylength()) || (this->best.gethistorylength() == 0))
            this->current.save("../Results/Best/" + QString::number(this->levelnomber) + ".gst");
    this->levelnomber++;
//    if (this->levelnomber == this->maxlevels + 1)
//        this->levelnomber++;
    if (this->levelnomber > this->maxlevels + 2)
        this->levelnomber = 0;
    if (this->levelnomber <= 1) {
        this->timerT->globaltime = 0;
        this->life = 0;
        this->loadparam();
        this->loadstaticTEX();
    }
    this->levelclear();
    if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0)) {
        if ((this->levelnomber != 1) && (this->multiplayer))
            this->sok->writemessage(QString("m " + this->sok->login + " is on level " + QString::number(this->levelnomber) + "~").toLocal8Bit());
        this->loadlevel();
        if (! QDir("../Results/Best").exists()) {
            QDir().mkdir("../Results/Best/");
        }
        this->best.load("../Results/Best/" + QString::number(this->levelnomber) + ".gst");
    }
    this->TIME = 0;
    this->onthislevel = 0;
    this->restart();
    this->timerT->TIM->start();
//    emit this->startTTT();
    this->secure = true;
}

void GLCalc::searchkeys() {
        this->walking = false;
//    if (this->menuopened) {
//        if (this->inside_key('+')) {
//            this->life++;
//            this->throw_key('+');
//        }
//        if (this->inside_key('-')) {
//            this->throw_key('-');
//            this->finn();
//            return;
//        }
//    }

    if (this->inside_key(Qt::Key_Escape)) {
        if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0)) {
            this->menuopened = !this->menuopened;
            this->element = 0;
        }
        else
            if ((!this->FFall) && (this->levelnomber == 0)) {
                emit this->sclose();
                return;
            }
        if (this->levelnomber == this->maxlevels + 2) {
            if (!this->multiplayer)
                this->finn();
            else
                emit this->sclose();
        }
        this->throw_key(Qt::Key_Escape);
    }
        if (this->inside_key(Qt::Key_Return)) {
            this->throw_key(Qt::Key_Return);
            if ((!this->multiplayer) && (this->levelnomber == 0)) {
                this->FFall = true;
                return;
            }
            if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0)) {
                if (this->menuopened) {
                    if (!this->multiplayer) {
                        this->levelnomber = -1;
                        finn();
                    }
                    else
                        emit this->sclose();
                }
            }
            if ((!this->multiplayer) && (this->levelnomber == this->maxlevels + 2) && (this->nametyped != "")) {
                int newscore = 1000000 / (this->timerT->globaltime / 1000 + 10 * this->life + 1);
                if (newscore <= this->score[9].second) {
                    this->finn();
                    return;
                }
                int i = 0;
                while (this->score[i].second >= newscore)
                    i++;
                QFile out("../Results/results.walk");
                out.open(QIODevice::WriteOnly);
                for (int j = 0; j < i; j++) {
                    out.write(QString(this->score[j].first + "\"").toLocal8Bit());
                    out.write(QString(QString::number(this->score[j].second) + "\"").toLocal8Bit());
                }
                out.write(QString(this->nametyped + "\"").toLocal8Bit());
                out.write(QString(QString::number(newscore) + "\"").toLocal8Bit());
                for (int j = i; j < 9; j++) {
                    out.write(QString(this->score[j].first + "\"").toLocal8Bit());
                    out.write(QString(QString::number(this->score[j].second) + "\"").toLocal8Bit());
                }
                out.close();
                this->finn();
            }
        }
    if ((this->inside_key('Z')) || (this->inside_key(1071))){
        emit this->switchmode();
        this->throw_key('Z');
        this->throw_key(1071);
    }

    if (this->inside_key('C') || this->inside_key(1057)) {
        this->firstview = !this->firstview;
        this->throw_key('C');
        this->throw_key(1057);
    }

    if (this->menuopened)
        return;
    if (this->levelnomber > this->maxlevels)
        return;

    if (this->inside_key(Qt::Key_Up))
        this->rx += 2.0f;
    if (this->inside_key(Qt::Key_Down))
        this->rx -= 2.0f;
    if (this->rx > 90)
        this->rx = 90;
    if (this->levelnomber == 0)
        if (this->rx > -40)
            this->rx = -40;
    if (this->levelnomber == 0)
        if (this->rx < -130)
            this->rx = -130;
    if (this->levelnomber == 0)
        return;

    if (this->rx < -90)
        this->rx = -90;

    if (this->dead)
        return;
    if (this->inside_key(Qt::Key_Left)) {
        this->walking = true;
        this->ry += 5.0f;

    }
    if (this->inside_key(Qt::Key_Right)) {
        this->ry -= 5.0f;
        this->walking = true;
    }



    //WHILE ALIVE

    if ((!this->jumping) && (this->inside_key(Qt::Key_Space))) {
        this->jumping = true;
        this->jumpiterations = 0;
    }

    GLfloat dy = 0, dx = 0;

    if (!this->jumping) {
        this->duck = this->inside_key(Qt::Key_Shift);
        if (this->duck)
            this->z = -.3f;
        else
            this->z = 0;
    }
    if (this->inside_key('W') || this->inside_key(1062)) {
        dy -= .05f;
        this->walking = true;
    }
    if (this->inside_key('S') || this->inside_key(1067)) {
        dy += .05f;
        this->walking = true;
    }
    if (this->inside_key('A') || this->inside_key(1060)) {
        dx -= .05f;
        this->walking = true;
    }
    if (this->inside_key('D') || this->inside_key(1042)) {
        dx += .05f;
        this->walking = true;
    }
    if (this->duck) {
        dx /= 5;
        dy /= 5;
    }
    if ((fabs(dx) > 1e-8) && (fabs(dy) > 1e-8)) {
        dx /= sqrt(2);
        dy /= sqrt(2);
    }
    if (!this->jumping)
           this->vx = this->vy = 0;

    if (this->canGO((this->x + dy * sin(ry / 360 * 2 * 3.14159265)), -(this->y ))) {
        this->x += dy * sin(ry / 360 * 2 * 3.14159265);
//        this->vx += dy * sin(ry / 360 * 2 * 3.14159265);
    }
    if (this->canGO(this->x , -(this->y + dy * cos(ry / 360 * 2 * 3.14159265)))) {
        this->y += dy * cos(ry / 360 * 2 * 3.14159265);
//        this->vy += dy * cos(ry / 360 * 2 * 3.14159265);
    }

    if (this->canGO((this->x + dx * cos(ry / 360 * 2 * 3.14159265)),(-this->y))) {
        this->x += dx * cos(ry / 360 * 2 * 3.14159265);
//        this->vx += dx * cos(ry / 360 * 2 * 3.14159265);
    }
    if (this->canGO((this->x),(-this->y + dx * sin(ry / 360 * 2 * 3.14159265)))) {
        this->y -= dx * sin(ry / 360 * 2 * 3.14159265);
//        this->vy -= dx * sin(ry / 360 * 2 * 3.14159265);
    }

//    if (dx != 0)
//        this->ry = this->ry - atan(dy / dx);

    if (this->jumping)
        return;

    dx = 0;
    dy = 0;

    for (int i = 0; i < this->Mpanel.size(); i++) {
        QPair <GLfloat, GLfloat> pos = getpos(this->TIME, this->Mpanel[i]);
        pos.second -= .5f;
        pos.first += .5f;
        if (canstand(this->x, this->y, pos.first, pos.second)) {
            QPair <GLfloat, GLfloat> dis = getdir(this->TIME, this->Mpanel[i]);
            dx += dis.first * this->updatetime / this->Mpanel[i].interval;
            dy -= dis.second * this->updatetime / this->Mpanel[i].interval;
        }
    }

    if (this->canGO((this->x + dy * sin(0 / 360 * 2 * 3.14159265)), -(this->y ))) {
        this->x += dy * sin(0 / 360 * 2 * 3.14159265);
        this->vx += dy * sin(0 / 360 * 2 * 3.14159265);
    }
    if (this->canGO(this->x , -(this->y + dy * cos(0 / 360 * 2 * 3.14159265)))) {
        this->y += dy * cos(0 / 360 * 2 * 3.14159265);
        this->vy += dy * cos(0 / 360 * 2 * 3.14159265);
    }
    if (this->canGO((this->x + dx * cos(0 / 360 * 2 * 3.14159265)),(-this->y))) {
        this->x += dx * cos(0 / 360 * 2 * 3.14159265);
        this->vx += dx * cos(0 / 360 * 2 * 3.14159265);
    }
    if (this->canGO((this->x),(-this->y + dx * sin(0 / 360 * 2 * 3.14159265)))) {
        this->y -= dx * sin(0 / 360 * 2 * 3.14159265);
        this->vy -= dx * sin(0 / 360 * 2 * 3.14159265);
    }

}

void GLCalc::die() {
    if ((this->multiplayer) && (!this->dead))
        this->sok->writemessage(QString("m " + this->sok->login + " died~").toLocal8Bit());
    this->dead = true;
}

void GLCalc::timeout() {
//    qDebug() << "!" << this->timerT->globaltime;
//    qDebug() << "(";
    if (this->levelnomber == this->maxlevels + 2) {
        int newscore = 1000000 / (this->timerT->globaltime / 1000 + 10 * this->life + 1);
        if (newscore <= this->score[9].second) {
            this->finn();
            return;
        }
    }
    if (!this->dead)
           for (int i = 0; i < this->Fpanel.size(); i++) {
               char d = this->Fpanel[i].direction;
               GLint f = 0;
               GLfloat p = (GLfloat) ((this->TIME + this->Fpanel[i].rest - this->Fpanel[i].pause) % this->Fpanel[i].rest) / Fpanel[i].interval;
               GLfloat dl = (GLfloat) this->Fpanel[i].rest / this->Fpanel[i].interval;
               GLfloat dx = 0, dy = 0;
               while (p + f * dl < this->Fpanel[i].dist) {
                   if (d == 'L')
                       dy = - p - dl * f;
                   if (d == 'R')
                       dy = p + dl * f;
                   if (d == 'D')
                       dx = p + dl * f;
                   if (d == 'U')
                       dx = - p - dl * f;
                   GLfloat FF = (this->x - this->Fpanel[i].x - dx) * (this->x - this->Fpanel[i].x - dx) / (this->Fpanel[i].stratchX * this->Fpanel[i].stratchX) + (-this->y - this->Fpanel[i].y - dy) * (-this->y - this->Fpanel[i].y - dy) / (this->Fpanel[i].stratchY * this->Fpanel[i].stratchY);
                   if (FF < (this->Fpanel[i].r * this->Fpanel[i].r)) {
                       GLfloat PP = ((this->Fpanel[i].r * this->Fpanel[i].r) - FF) * (this->Fpanel[i].stratchZ * this->Fpanel[i].stratchZ);
                       GLfloat P1 = std::sqrt(PP) + this->Fpanel[i].z - .5f;
                       GLfloat P2 =-std::sqrt(PP) + this->Fpanel[i].z - .5f;
                       if (std::min(this->z + 0.15f, P1) >= std::max(this->z - 0.5f, P2)) {
                           this->z = -.3f;
                           die();
                        }
                    }
                   f++;
               }
       }
    if ((this->levelnomber > 0) && (this->levelnomber <= this->maxlevels) && (!this->menuopened || this->multiplayer)) {
        this->current.pushHevent(this->generateevent());
        if (this->multiplayer) {
            Hevent ev = this->generateevent();
            ev.time = this->timerT->globaltime;
            this->sok->writemessage(QString("e " + this->sok->login + " " + getByte(ev) + "~").toLocal8Bit());
        }
        if (this->drawindex < this->best.gethistorylength() - 1)
            this->drawindex++;
    }
    this->ttoch--;
    if (this->ttoch < 0)
        this->ttoch = 30;
    if (this->ttoch == 0) {
    if (this->curs == "_")
        this->curs = "";
    else
        this->curs = "_";
    }
//    qDebug() << this->timerT->globaltime;
    this->searchkeys();
    if ((this->levelnomber == this->maxlevels + 1) || this->FFall)
        this->freefall();
//    if (this->levelnomber == 0)
//        this->freefall();
    if (this->dead) {
                this->TIME += this->updatetime;
                this->onthislevel += this->updatetime;
                if (!this->menuopened || this->multiplayer)
                    this->timetorestart -= this->updatetime;
                if (this->timetorestart <= 0) {
                    this->life++;
                    this->restart();
                }
        }
    else {
        if (!this->menuopened || this->multiplayer) {
            this->TIME += this->updatetime;
            this->onthislevel += this->updatetime;
            if (this->levelnomber <= this->maxlevels)
            this->timerT->globaltime += this->updatetime;
        }
        if ((this->levelnomber != 0) && (this->levelnomber <= this->maxlevels) && (!this->jumping) && (!this->isfloor(this->x, this->y))) {
            this->z = -.4f;
            this->die();

        }
    }
    if (this->jumping)
        this->jump();

    GLfloat dist = this->CAMERAdist;
    while ((dist <= 1.0f) && canGO(this->x + dist * sin(this->ry * 3.15149265 / 180), -this->y - dist * cos(this->ry * 3.15149265 / 180)))
        dist += .05f;
    while ((dist >= .1f) && !canGO(this->x + dist * sin(this->ry * 3.15149265 / 180), -this->y - dist * cos(this->ry * 3.15149265 / 180)))
        dist -= .05f;
    this->CAMERAdist = std::min(dist, 1.0f);
    this->CAMERAdist = std::max(this->CAMERAdist, .1f);

    if (this->z < -100.0f) {
        finn();
    }
//    qDebug() << ")";
}

bool isin(int x, int y, int n, int m) {
    return (x >= 0) && (y >= 0) && (x < n) && (y < m);
}

hidden new_hidden(GLfloat pause,GLfloat tvis,GLfloat thid, GLint x, GLint y, bool visible) {
    hidden res;
    res.pause = pause;
    res.tvis = tvis;
    res.thid = thid;
    res.x = x;
    res.y = y;
    res.visible = visible;
    return res;
}

void GLCalc::restart() {
    this->FFall = false;
    this->menuopened = false;
    this->timetorestart = this->restime;
    this->jumpiterations = 0;
    this->jumping = false;
    this->z = 0;
    this->timerT->TIM->stop();
    this->TIME = 0;
    this->dead = false;
    this->x = this->sx + .5f;
    this->y = -this->sy - .5f;
    this->vx = this->vy = 0;
    this->ry = 0;
    this->rx = 0;
    if (this->levelnomber > this->maxlevels)
        this->rx = -90;
    if (this->levelnomber == 0)
        this->rx = -90;
    this->timerT->TIM->setInterval(this->updatetime);
    this->timerT->TIM->start();
}

void GLCalc::jump() {
    if (this->dead)
        return;
    const GLfloat v = 3.0f, g = 9.8f;
    if (canGO(this->x + this->vx, -this->y))
        this->x += this->vx;
    if (canGO(this->x, -this->y - this->vy))
        this->y += this->vy;
    this->jumpiterations++;
    GLfloat t = (GLfloat) (this->jumpiterations * this->updatetime) / 1000;
    this->z = v * t - g * t * t / 2;
    if (this->z <= 0) {
        this->z = 0;
        this->jumping = false;
//        qDebug() << this->jumpiterations;
        if (! isfloor(this->x, this->y)) {
            this->z = -.4f;
            this->die();
        }
        else
            this->jumpiterations = 0;
    }

}

bool GLCalc::isfloor(GLfloat x, GLfloat y) {
    if (this->map[floor(x)][floor(-y)] != '0')
            return true;
    if ((x - floor(x) < 0.15f) && isin(floor(x) - 1, floor(-y), this->n, this->m) && (this->map[floor(x) - 1][floor(-y)] != '*') && (this->map[floor(x) - 1][floor(-y)] != '0'))
        return true;
    if ((x - floor(x) > 0.85f) && isin(floor(x) + 1, floor(-y), this->n, this->m) && (this->map[floor(x) + 1][floor(-y)] != '*')  && (this->map[floor(x) + 1][floor(-y)] != '0'))
        return true;
    if ((-y - floor(-y) < 0.15f) && isin(floor(x), floor(-y - 1), this->n, this->m) && (this->map[floor(x)][floor(-y - 1)] != '*') && (this->map[floor(x)][floor(-y - 1)] != '0'))
        return true;
    if ((-y - floor(-y) > 0.85f) && isin(floor(x), floor(-y + 1), this->n, this->m) && (this->map[floor(x)][floor(-y + 1)] != '*') && (this->map[floor(x)][floor(-y + 1)] != '0'))
        return true;
    for (int i = 0; i < this->Mpanel.size(); i++) {
        QPair <GLfloat, GLfloat> pos = getpos(this->TIME, this->Mpanel[i]);
        pos.first += .5f;
        pos.second -= .5f;
        if (canstand(this->x, this->y, pos.first, pos.second))
            return true;
    }
    return false;
}

void GLCalc::freefall() {
    this->rx = -90;
    this->ry = 0;
    const GLfloat g = 9.8f;
    this->jumpiterations++;
    GLfloat t = (GLfloat) this->jumpiterations * this->updatetime / 1000;
    this->z = -g * t * t / 2;
    this->x += this->vx;
    this->y += this->vy;
}

void GLCalc::levelclear() {
    this->current.clear();
    this->best.clear();
    this->sx = this->sy = 0;
    this->Hpanel.clear();
    this->Mpanel.clear();
    this->Fpanel.clear();
    this->drawindex = -1;
}

void GLCalc::loadlevel() {
    int n, m;
    FILE *inp;
    inp = fopen(QString("../Levels/" + QString::number(this->levelnomber) + ".lvl").toStdString().c_str(), "r");
    if (inp == NULL) {
        qDebug() << "file with map" << this->levelnomber << "not found. Halting!";
        emit this->sclose();
    }
    this->n = 0;
    this->m = 0;
    fscanf(inp, "%d %d\n", &n, &m);

    this->map.resize(n);
    for (int i = 0; i < n; i++)
        this->map[i].resize(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(inp, "%c", &this->map[i][j]);
            if (this->map[i][j] == 'P') {
                this->map[i][j] = '.';
                this->sx = i;
                this->sy = j;
            }
        }
        fscanf(inp, "\n");
    }
    int cmd;
    char ch;
    fscanf(inp, "%d\n ", &cmd);
    for (int i = 0; i < cmd; i++) {
        fscanf(inp, "%c", &ch);
        if (ch == 'H') {
            hidden p;
            int bol;
            fscanf(inp, "%d %d %d %d %d %d\n", &p.x, &p.y, &p.pause, &p.tvis, &p.thid, &bol);
            p.visible = (bol != 0);
            p.backup = this->map[p.x][p.y];
            this->Hpanel.push_back(p);
        }
        if (ch == 'M') {
            moving p;
            char s[256];
            fscanf(inp, "%d %d %d %s\n", &p.x, &p.y, &p.interval, s);
            p.param = QString::fromStdString(s);
            this->Mpanel.push_back(p);
        }
        if (ch == 'F') {
            firing p;
            int x, y, z, r, dist, sx, sy, sz;
            fscanf(inp, "%d %d %d %d %c %d %d %d %d %d %d %d\n", &x, &y, &z, &r, &p.direction, &p.interval, &p.rest, &dist, &p.pause, &sx, &sy, &sz);
            p.x =  (GLfloat) x / 100;
            p.y =  (GLfloat) y / 100;
            p.z =  (GLfloat) z / 100;
            p.r = (GLfloat) r / 100;
            p.dist = (GLfloat) dist / 100;
            p.stratchX = (GLfloat) sx / 100;
            p.stratchY = (GLfloat) sy / 100;
            p.stratchZ = (GLfloat) sz / 100;
            this->Fpanel.push_back(p);
        }
    }
//    for (int i = 0; i < n; i++)
//        qDebug() << this->map[i];
    fscanf(inp, "%d\n", &cmd);
    for (int i = 0; i < cmd; i++) {
        char s[256], sp[256];
        fscanf(inp, "%s", sp);
        fscanf(inp, "%s", s);
        QString s1 = QString(sp);
        if (s1 == "sky") {
            int b;
            fscanf(inp, "%d", &b);
            this->stretch_sky = (b == 1);
            this->PIXsky = QPixmap("../Textures/" + QString(s));
        }
        if (s1 == "wall")
            this->PIXwall = QPixmap("../Textures/" + QString(s));
        if (s1 == "exit")
            this->PIXexit = QPixmap("../Textures/" + QString(s));
        if (s1 == "floor")
            this->PIXfloor = QPixmap("../Textures/" + QString(s));
        if (s1 == "danger")
            this->PIXdanger = QPixmap("../Textures/" + QString(s));
        if (s1 == "hidden")
            this->PIXhidden = QPixmap("../Textures/" + QString(s));
        if (s1 == "moving")
            this->PIXmoving = QPixmap("../Textures/" + QString(s));
    }
    this->n = n;
    this->m = m;
    fclose(inp);
}

QPixmap GLCalc::genpix(int w, int h, int f, QVector<QString> &mes, bool center) {
    QPixmap *menu = new QPixmap(w, h);
    QPainter p(menu);
    p.setFont(QFont("Liberation Mono", f, -1, false));

    QPen pn = p.pen();
    pn.setColor(QColor("white"));
    p.setPen(pn);
    QBrush br = p.brush();
    br.setStyle(Qt::SolidPattern);
    br.setColor(QColor("black"));
    p.setBrush(br);
    p.drawRect(0, 0, w, h);
    int a = 0;
    int b = 0;
    for (int i = 0; i < mes.size(); i++) {
        a = std::max(a, p.fontMetrics().width(mes[i]));
        b = std::max(b, p.fontMetrics().height());
    }
//    qDebug() << a << b;
    int dx = (w - a) / 2;
    int dy = (h - b * mes.size()) / 2;
    if (!center)
        dx = 5;
//    qDebug() << dx << dy;
//    dy = 0;
//    p.drawText(40, 40, "ASDD);
    for (int i = 0; i < mes.size(); i++)
        p.drawText(dx, dy + b * (i), mes[i]);
    br.setColor(QColor("white"));
    p.setBrush(br);
    p.drawRect(w / 2 - 50, 0, 100, 140);
    p.drawRect(w / 2 - 50, h - 220, 100, 220);
    br.setColor(QColor("black"));
    p.setBrush(br);
    p.drawRect(w / 2 - 5, 0 , 10, 140);
    p.drawRect(w / 2 - 5, h - 220, 10, 220);
    p.end();
    return *menu;
}

void GLCalc::loadstaticTEX() {
    this->PIXwin = QPixmap("../Textures/win.jpg");
    this->PIXhole = QPixmap("../Textures/hole.png");
    this->PIXfireball = QPixmap("../Textures/fireball.jpg");
    QVector <QString> mes (11);
    mes[0] = tr("WASD   :: move");
    mes[1] = tr("arrows :: rotate camera");
    mes[2] = tr("Space  :: jump");
    mes[3] = tr("Shift  :: crouch");
    mes[4] = tr("Esc    :: pause");
    mes[5] = tr("Z      :: fullscreen");
    mes[6] = tr("C      :: change view");
    mes[7] = tr("Reach finish...");
    if (!this->multiplayer) {
        mes[8] = tr("<Press ENTER to Start>");
        mes[9] = tr("         or");
        mes[10] = tr("<Press Esc to exit>");
    }
    else
        mes[9] = tr("Waiting for other players...");
    this->PIXmenu = this->genpix(1024, 1024, 40, mes);

    mes.resize(3);
    mes[0] = tr("You won!");
    mes[1] = tr("Thank you for playing Walkers!");
    mes[2] = "                      by danpol";
    this->PIXwin = this->genpix(1024, 1024, 40, mes, false);

    mes.clear();
    QFile inp("../Results/results.walk");
    inp.open(QIODevice::ReadOnly);
    QVector <QPair <QString, int> > res;
    for (int i = 0; i < 10; i++) {
        QByteArray p, w;
        w.resize(0);
        p = inp.read(1);
        while (p[0] != '\"') {
            w.append(p);
            p = inp.read(1);
        }
        QString a = QString::fromLocal8Bit(w);
        w.resize(0);
        p = inp.read(1);
        while (p[0] != '\"') {
            w.append(p);
            p = inp.read(1);
        }
        int b = QString::fromLocal8Bit(w).toInt();
        res.push_back(QPair <QString, int> (a, b));
//        qDebug() << res[i];
    }
    int m = 0;
    for (int i = 0; i < 10; i++)
        m = std::max(m, res[i].first.length());
    for (int i = 0; i < 10; i++) {
        while (res[i].first.length() != m)
            res[i].first += ' ';
        mes.push_back(res[i].first + " :: " + QString::number(res[i].second));
    }
    inp.close();

    this->score = res;
//    qDebug() << this->score;

    this->PIXresults = this->genpix(1024, 1024, 40, mes);
    mes.clear();
    mes.push_back("Walkers");
    mes.push_back("        by danpol");
    this->PIXcred = this->genpix(1024, 1024, 50, mes);

}

GLfloat GLCalc::dist(GLfloat x, GLfloat y) {
    return (this->x - x) * (this->x - x) + (this->y + y) * (this->y + y);
}

Hevent GLCalc::generateevent() {
    Hevent ev;
    ev.time = this->TIME;
    ev.x = x;
    ev.y = y;
    ev.z = z;
    ev.ry = ry;
    if (this->dead) {
        ev.player = Hdead;
        ev.sceneindex = (this->Dmodel->getanimationlength() - 1) - trunc(((GLfloat) this->timetorestart / this->restime) * (this->Dmodel->getanimationlength() - 1));
    }
    else
    if (this->jumping) {
        ev.player = Hjump;
        ev.sceneindex = trunc(((GLfloat)this->jumpiterations / 37) * (this->Jmodel->getanimationlength() - 1));
    }
    else
    if (this->duck) {
        ev.player = Hcrouch;
        ev.sceneindex = (this->TIME / 30) % this->Cmodel->getanimationlength();
        if (!this->walking)
            ev.sceneindex = 0;
    }
    else
    if (this->walking) {
        ev.player = Hwalk;
        ev.sceneindex = (this->TIME / 20) % this->Rmodel->getanimationlength();
    }
    else {
        ev.player = Hstay;
        ev.sceneindex = (this->TIME / 100) % this->Smodel->getanimationlength();
    }
    ev.levelnumber = this->levelnomber;
    return ev;
}
