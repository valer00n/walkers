#include "drawgl.h"
#include <QDebug>
#include <cstdio>
#include <cmath>
#include <QDir>
#include <fstream>
#include <QPainter>
#include <string>
#include <ghost.h>

GLPainter::GLPainter() {

}
void GLPainter::thstarted() {
    this->curcalc = this->pp->p;
    QObject::connect(this, SIGNAL(ins_key(int)), this->curcalc, SLOT(ins_key(int)));
    QObject::connect(this, SIGNAL(del_key(int)), this->curcalc, SLOT(del_key(int)));
    QObject::connect(this->curcalc, SIGNAL(showW()), this, SLOT(show()));
    this->curcalc->fullscreen = false;
    this->switchmode();
    QObject::connect(this->curcalc, SIGNAL(sclose()), this, SLOT(close()));
    this->loadp1();
    this->loadp2();
    QObject::connect(this->curcalc, SIGNAL(switchmode()), this, SLOT(switchmode()));
    this->TIM = new QTimer;
    this->TIM->setInterval(1);
    QObject::connect(this->curcalc, SIGNAL(startTTT()), this->TIM, SLOT(start()));
    QObject::connect(this->curcalc, SIGNAL(stopTTT()), this->TIM, SLOT(stop()));
    QObject::connect(this->TIM, SIGNAL(timeout()), this, SLOT(update()));
    this->TIM->start();
    emit this->createdTH();
}

void GLPainter::startit(bool multiplayer, QMainWindow *par) {
    this->setMinimumSize(610, 512);
    this->setFont(QFont("serif", 15, -1, false));
    this->setMouseTracking(true);
    this->pp = new GLCalcTH;
    this->pp->mult = multiplayer;
    this->pp->par = par;
    QObject::connect(this->pp, SIGNAL(started()), this, SLOT(thstarted()));
    this->pp->start();
}

void GLPainter::loadp1() {
    this->Rmodel = new SMDloader(this);
    this->curcalc->Rmodel = this->Rmodel;
    this->Rmodel->setstay(true);
    this->Rmodel->setpath("../Textures/Player");
    this->Rmodel->loadmodel("body.smd");
    this->Rmodel->loadanimation("run2.smd");

    this->Smodel = new SMDloader(this);
    this->curcalc->Smodel = this->Smodel;
    this->Smodel->setstay(true);
    this->Smodel->setpath("../Textures/Player");
    this->Smodel->loadmodel("body.smd");
    this->Smodel->loadanimation("idle.smd");

    this->Jmodel = new SMDloader(this);
    this->curcalc->Jmodel = this->Jmodel;
    this->Jmodel->setstay(true);
    this->Jmodel->setpath("../Textures/Player");
    this->Jmodel->loadmodel("body.smd");
    this->Jmodel->loadanimation("jump.smd");

    this->Dmodel = new SMDloader(this);
    this->curcalc->Dmodel = this->Dmodel;
    this->Dmodel->setstay(true);
    this->Dmodel->setpath("../Textures/Player");
    this->Dmodel->loadmodel("body.smd");
    this->Dmodel->loadanimation("die_forwards.smd");

    this->Cmodel = new SMDloader(this);
    this->curcalc->Cmodel = this->Cmodel;
    this->Cmodel->setstay(true);
    this->Cmodel->setpath("../Textures/Player");
    this->Cmodel->loadmodel("body.smd");
    this->Cmodel->loadanimation("crawl.smd");

    this->Rarm = new SMDloader(this);
    this->curcalc->Rarm = this->Rarm;
    this->Rarm->setstay(true);
    this->Rarm->setpath("../Textures/Player");
    this->Rarm->loadmodel("arms.smd");
    this->Rarm->loadanimation("run2.smd");

    this->Sarm = new SMDloader(this);
    this->curcalc->Sarm = this->Sarm;
    this->Sarm->setstay(true);
    this->Sarm->setpath("../Textures/Player");
    this->Sarm->loadmodel("arms.smd");
    this->Sarm->loadanimation("idle.smd");

    this->Jarm = new SMDloader(this);
    this->curcalc->Jarm = this->Jarm;
    this->Jarm->setstay(true);
    this->Jarm->setpath("../Textures/Player");
    this->Jarm->loadmodel("arms.smd");
    this->Jarm->loadanimation("jump.smd");

    this->Darm = new SMDloader(this);
    this->curcalc->Darm = this->Darm;
    this->Darm->setstay(true);
    this->Darm->setpath("../Textures/Player");
    this->Darm->loadmodel("arms.smd");
    this->Darm->loadanimation("die_forwards.smd");

    this->Carm = new SMDloader(this);
    this->curcalc->Carm = this->Carm;
    this->Carm->setstay(true);
    this->Carm->setpath("../Textures/Player");
    this->Carm->loadmodel("arms.smd");
    this->Carm->loadanimation("crawl.smd");

}

void GLPainter::loadp2() {
    GLfloat al = 0.5f;
    this->HistoryRmodel = new SMDloader(this);
    this->curcalc->HistoryRmodel = this->HistoryRmodel;
    this->HistoryRmodel->setalpha(al);
    this->HistoryRmodel->setstay(true);
    this->HistoryRmodel->setpath("../Textures/Player");
    this->HistoryRmodel->loadmodel("body.smd");
    this->HistoryRmodel->loadanimation("run2.smd");

    this->HistorySmodel = new SMDloader(this);
    this->curcalc->HistorySmodel = this->HistorySmodel;
    this->HistorySmodel->setalpha(al);
    this->HistorySmodel->setstay(true);
    this->HistorySmodel->setpath("../Textures/Player");
    this->HistorySmodel->loadmodel("body.smd");
    this->HistorySmodel->loadanimation("idle.smd");

    this->HistoryJmodel = new SMDloader(this);
    this->curcalc->HistoryJmodel = this->HistoryJmodel;
    this->HistoryJmodel->setalpha(al);
    this->HistoryJmodel->setstay(true);
    this->HistoryJmodel->setpath("../Textures/Player");
    this->HistoryJmodel->loadmodel("body.smd");
    this->HistoryJmodel->loadanimation("jump.smd");

    this->HistoryDmodel = new SMDloader(this);
    this->curcalc->HistoryDmodel = this->HistoryDmodel;
    this->HistoryDmodel->setalpha(al);
    this->HistoryDmodel->setstay(true);
    this->HistoryDmodel->setpath("../Textures/Player");
    this->HistoryDmodel->loadmodel("body.smd");
    this->HistoryDmodel->loadanimation("die_forwards.smd");

    this->HistoryCmodel = new SMDloader(this);
    this->curcalc->HistoryCmodel = this->HistoryCmodel;
    this->HistoryCmodel->setalpha(al);
    this->HistoryCmodel->setstay(true);
    this->HistoryCmodel->setpath("../Textures/Player");
    this->HistoryCmodel->loadmodel("body.smd");
    this->HistoryCmodel->loadanimation("crawl.smd");

    this->HistoryRarm = new SMDloader(this);
    this->curcalc->HistoryRarm = this->HistoryRarm;
    this->HistoryRarm->setalpha(al);
    this->HistoryRarm->setstay(true);
    this->HistoryRarm->setpath("../Textures/Player");
    this->HistoryRarm->loadmodel("arms.smd");
    this->HistoryRarm->loadanimation("run2.smd");

    this->HistorySarm = new SMDloader(this);
    this->curcalc->HistorySarm = this->HistorySarm;
    this->HistorySarm->setalpha(al);
    this->HistorySarm->setstay(true);
    this->HistorySarm->setpath("../Textures/Player");
    this->HistorySarm->loadmodel("arms.smd");
    this->HistorySarm->loadanimation("idle.smd");

    this->HistoryJarm = new SMDloader(this);
    this->curcalc->HistoryJarm = this->HistoryJarm;
    this->HistoryJarm->setalpha(al);
    this->HistoryJarm->setstay(true);
    this->HistoryJarm->setpath("../Textures/Player");
    this->HistoryJarm->loadmodel("arms.smd");
    this->HistoryJarm->loadanimation("jump.smd");

    this->HistoryDarm = new SMDloader(this);
    this->curcalc->HistoryDarm = this->HistoryDarm;
    this->HistoryDarm->setalpha(al);
    this->HistoryDarm->setstay(true);
    this->HistoryDarm->setpath("../Textures/Player");
    this->HistoryDarm->loadmodel("arms.smd");
    this->HistoryDarm->loadanimation("die_forwards.smd");

    this->HistoryCarm = new SMDloader(this);
    this->curcalc->HistoryCarm = this->HistoryCarm;
    this->HistoryCarm->setalpha(al);
    this->HistoryCarm->setstay(true);
    this->HistoryCarm->setpath("../Textures/Player");
    this->HistoryCarm->loadmodel("arms.smd");
    this->HistoryCarm->loadanimation("crawl.smd");

}

void GLPainter::Begin2D ()
{
    glEnable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(this->curcalc->dw, this->width() - this->curcalc->dw, this->curcalc->dh, this->height() - this->curcalc->dh);
}

void GLPainter::End2D ()
{
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_BLEND);
}

QPair <GLfloat, GLfloat> getposs(GLint TIME, moving panel) {
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

void GLPainter::loadLists() {

    this->curcalc->wall = glGenLists(1);

    GLint a = 1, b = 1, c = 1;

    glNewList(this->curcalc->wall, GL_COMPILE);
        glColor4f(1.0f, 1.0f, 1.0f, .0f);
        glBegin(GL_QUADS);
                glTexCoord2f(1, 0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord2f(1, 1);
                glVertex3f(.0f, b, 0.0f);
                glTexCoord2f(0, 1);
                glVertex3f(a, b, 0.0f);
                glTexCoord2f(0, 0);
                glVertex3f(a, 0.0f, 0.0f);
         glEnd();

        glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(0.0f, 0.0f, c);
                glTexCoord2f(1, 0);
                glVertex3f(a, 0.0f, c);
                glTexCoord2f(1, 1);
                glVertex3f(a, b, c);
                glTexCoord2f(0, 1);
                glVertex3f(.0f, b, c);
         glEnd();


         glBegin(GL_QUADS);
                glTexCoord2f(1, 0);
                glVertex3f(a, .0f, .0f);
                glTexCoord2f(1, 1);
                glVertex3f(a, b, .0f);
                glTexCoord2f(0, 1);
                glVertex3f(a, b, c);
                glTexCoord2f(0, 0);
                glVertex3f(a, .0f, c);
         glEnd();


         glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(.0f, .0f, .0f);
                glTexCoord2f(1, 0);
                glVertex3f(.0f, .0f, c);
                glTexCoord2f(1, 1);
                glVertex3f(.0f, b, c);
                glTexCoord2f(0, 1);
                glVertex3f(.0f, b, .0f);
          glEnd();
    //--------------------------------------------------
            glBegin(GL_QUADS);
                glTexCoord2f(0, 1);
                glVertex3f(.0f, b, .0f);
                glTexCoord2f(0, 0);
                glVertex3f(.0f, b, c);
                glTexCoord2f(1, 0);
                glVertex3f(a, b, c);
                glTexCoord2f(1, 1);
                glVertex3f(a, b, .0f);

            glEnd();

            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(.0f, .0f, .0f);
                glTexCoord2f(1, 0);
                glVertex3f(a, .0f, .0f);
                glTexCoord2f(1, 1);
                glVertex3f(a, .0f, c);
                glTexCoord2f(0, 1);
                glVertex3f(.0f, .0f, c);
            glEnd();

    glEndList();
}


void GLPainter::initializeGL() {
    glEnable(GL_TEXTURE_2D);
    glEnable( GL_DEPTH_TEST );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth( 1.0f );

    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthFunc( GL_LESS );
    glShadeModel( GL_SMOOTH );
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, 0.4f);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_START, 0.0f);
    this->loadLists();
}

void GLPainter::resizeGL(int w, int h) {

    GLfloat scale = std::min((GLfloat) w / 16, (GLfloat) h / 9);
    this->curcalc->dw = (w - 16 * scale) / 2;
    this->curcalc->dh = (h - 9 * scale) / 2;
    glViewport(this->curcalc->dw, this->curcalc->dh, 16 * scale, 9 * scale);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
    glMatrixMode(GL_MODELVIEW );
    glLoadIdentity();
}

void GLPainter::paintGL() {
    if (this->curcalc->current.gethistorylength() != 0)
        this->last = this->curcalc->current.getHevent(this->curcalc->current.gethistorylength() - 1);
    if ((this->curcalc->levelnomber < 1) || (this->curcalc->levelnomber > this->curcalc->maxlevels))
        this->last.ry = 0;
    this->drawindex = this->curcalc->drawindex;
//    qDebug() << "<";
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth( 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    this->fogg(false);
    if ((this->curcalc->levelnomber > this->curcalc->maxlevels) || (this->curcalc->levelnomber == 0)) {
        glRotatef(-this->curcalc->rx, 1.0f, .0f, .0f);
        glRotatef(-this->last.ry, .0f, 1.0f, .0f);
    }
    if ((this->curcalc->levelnomber <= this->curcalc->maxlevels) && (this->curcalc->levelnomber != 0))
        glTranslatef(-.5f, -.5f, 1.5f);
    else
        glTranslatef(-this->curcalc->x, -.5f - this->curcalc->z, -this->curcalc->y);
    if (this->curcalc->levelnomber == 0) {
        this->mainmenu();
    }
    else
    if (this->curcalc->levelnomber <= this->curcalc->maxlevels) {

        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
            GLfloat dist = this->curcalc->CAMERAdist;
            if (this->curcalc->firstview) {
                dist = .0f;
                glRotatef(-this->curcalc->rx, 1.0f, .0f, .0f);
                glTranslatef(.0f, -this->last.z , .0f);
                glRotatef(-this->last.ry, .0f, 1.0f, .0f);
            }
            else
                gluLookAt(dist * sin(this->last.ry * 3.15149265 / 180), .1f, dist * cos(this->last.ry * 3.15149265 / 180),
                      (dist - .1f) * sin(this->last.ry * 3.15149265 / 180), .1f + this->curcalc->rx / 300, (dist - .1f) * cos(this->last.ry * 3.15149265 / 180), 0, 1, 0);
//            gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
        glMatrixMode(GL_MODELVIEW);

        glTranslatef(-this->last.x + .5f, .0f, -this->last.y - 1.5f);
        this->drawSKY();
        this->drawmap();
        if ((!this->curcalc->firstview) && (this->curcalc->current.gethistorylength() != 0))
            this->drawplayer(this->last);
        if (!this->curcalc->multiplayer){
            if ((this->drawindex >= 0) && (this->drawindex < this->curcalc->best.gethistorylength() - 1))
                this->drawhistory(this->curcalc->best.getHevent(this->drawindex));
        }
        else
        {
            for (int i = 0; i < this->curcalc->players.size(); i++) {
                if (this->curcalc->players[i].second.levelnumber == this->curcalc->levelnomber)
                    this->drawhistory(this->curcalc->players[i].second);
            }
        }
        this->drawinfo();



    }
    else
        if (this->curcalc->levelnomber == this->curcalc->maxlevels + 1)
            this->drawNOTHING(-50, -100, -50, 100, 0, 100, this->curcalc->PIXwin);
        else if (!this->curcalc->multiplayer)
                 this->savescore();
             else {
                 this->drawNOTHING(-50, -100, -50, 100, 0, 100, this->curcalc->PIXmultires);
//            asd
        }
//    qDebug() << ">";
}

void GLPainter::drawplayer(Hevent ev) {
    glTranslatef(ev.x, .39f, ev.y);
                    glRotatef(ev.ry, .0f, 1.0f, .0f);
    glScalef(0.008f, 0.008f, 0.008f);
    glRotatef(-90.0f, 1.0f, .0f, .0f);
    glRotatef(180.0f, .0f, .0f, 1.0f);
    glTranslatef(.0f, .0f ,125 * ev.z);
    if (ev.player == Hdead) {
        this->Dmodel->draw(ev.sceneindex);
        this->Darm->draw(ev.sceneindex);
    }
    else
    if (ev.player == Hjump) {
        this->Jmodel->draw(ev.sceneindex);
        this->Jarm->draw(ev.sceneindex);
    }
    else
    if (ev.player == Hcrouch) {
        glTranslatef(.0f, .0f, .2f * 125);
        this->Cmodel->draw(ev.sceneindex);
        this->Carm->draw(ev.sceneindex);
        glTranslatef(.0f, .0f, -.2f * 125);
    }
    else
    if (ev.player == Hwalk) {
        this->Rmodel->draw(ev.sceneindex);
        this->Rarm->draw(ev.sceneindex);
    }
    else {
        this->Smodel->draw(ev.sceneindex);
        this->Sarm->draw(ev.sceneindex);
    }
    glTranslatef(.0f,.0f, -125 * ev.z);
    glRotatef(-180.0f, .0f, .0f, 1.0f);
    glRotatef(90.0f, 1.0f, .0f, .0f);
    glScalef(125.0f, 125.0f, 125.0f);
    glRotatef(-ev.ry, .0f, 1.0f, .0f);
    glTranslatef(-ev.x, -.39f, -ev.y);
}

void GLPainter::savescore() {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    int newscore = 1000000 / (this->curcalc->timerT->globaltime / 1000 + 10 * this->curcalc->life + 1);
    int i = 0;
    while (this->curcalc->score[i].second >= newscore)
        i++;
    renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 30, "New record! Your place: " + QString::number(i + 1));
    renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 60, "Enter your name: " + this->curcalc->nametyped + this->curcalc->curs);
    renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 90, "<Press Enter to save>");
    renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 110, "<Press Esc to exit>");


}

void GLPainter::keyPressEvent(QKeyEvent *ev) {
    if ((!this->curcalc->multiplayer) && (this->curcalc->FFall) && (this->curcalc->levelnomber == 0) && (ev->key() == Qt::Key_Escape))
        this->curcalc->jumpiterations = 1000;
//    qDebug() << "+" << ev->key();
    if ((this->curcalc->multiplayer) && (this->curcalc->levelnomber == this->curcalc->maxlevels + 2) && (ev->key() == Qt::Key_Escape))
        this->curcalc->parent->close();
    if ((!this->curcalc->multiplayer) && (this->curcalc->levelnomber == this->curcalc->maxlevels + 2)) {
        if (ev->key() == Qt::Key_Backspace)
            this->curcalc->nametyped = this->curcalc->nametyped.left(this->curcalc->nametyped.length() - 1);
        else
            if ((ev->text() != "\"") && (ev->key() != Qt::Key_Escape) && (ev->key() != Qt::Key_Return))
            this->curcalc->nametyped += ev->text();
        else
            emit this->ins_key(ev->key());
        this->curcalc->nametyped = this->curcalc->nametyped.left(10);
    }
    else
       emit this->ins_key(ev->key());
}

void GLPainter::keyReleaseEvent(QKeyEvent *ev) {
//    qDebug() << "-" << ev->key();
    emit this->del_key(ev->key());
}

void GLPainter::drawQUBE(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture) {

    GLuint ap = bindTexture(texture, GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ap);
    glTranslatef(x, y, z);
    glColor4f(1.0f, 1.0f, 1.0f, .0f);
    glScalef(a, b, c);
    glCallList(this->curcalc->wall);
    glScalef(1.0f / a, 1.0f / b, 1.0f / c);
    glTranslatef(-x, -y, -z);
    glColor4f(.0f, .0f, .0f, 1.0f);
}

void GLPainter::drawNOTHING(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture) {
    b = b;
    drawQUBE(x, y, z, a, .1f, c, texture);
}

bool getstate(int TIME, hidden panel) {
    if (TIME < panel.pause)
       return panel.visible;
    if ((TIME - panel.pause) % (panel.thid + panel.tvis) <= panel.tvis)
        return !panel.visible;
    else
        return panel.visible;
}

void GLPainter::drawmap() {
    for (int i = 0; i < this->curcalc->Hpanel.size(); i++)
        if (getstate(this->last.time, this->curcalc->Hpanel[i]))
            this->curcalc->map[this->curcalc->Hpanel[i].x][this->curcalc->Hpanel[i].y] = 'H';
        else
            this->curcalc->map[this->curcalc->Hpanel[i].x][this->curcalc->Hpanel[i].y] = this->curcalc->Hpanel[i].backup;
    for (int i = -1; i <= this->curcalc->n; i++) {
        this->drawQUBE(i, .0f, 1 - 1, 1, 1, 1, this->curcalc->PIXwall);
        this->drawQUBE(i, .0f, -this->curcalc->m - 1, 1, 1, 1, this->curcalc->PIXwall);
    }
    for (int j = -1; j <= this->curcalc->m; j++) {
        this->drawQUBE(-1, .0f, -j - 1, 1, 1, 1, this->curcalc->PIXwall);
        this->drawQUBE(this->curcalc->n, .0f, -j - 1, 1, 1, 1, this->curcalc->PIXwall);
    }


    for (int i = 0; i < this->curcalc->n; i++)
        for (int j = 0; j < this->curcalc->m; j++) {
            if (this->curcalc->map[i][j] == '*')
                this->drawQUBE(i, .0f, -j - 1, 1, 1, 1, this->curcalc->PIXwall);
            if (this->curcalc->map[i][j] == 'E')
                this->drawQUBE(i, .0f, -j - 1, 1, 1, 1, this->curcalc->PIXexit);
            if (this->curcalc->map[i][j] == '.')
                this->drawNOTHING(i, .0f, -j - 1, 1, 1, 1, this->curcalc->PIXfloor);
            if (this->curcalc->map[i][j] == '0')
                this->drawNOTHING(i, -.1f, -j - 1, 1, 1, 1, this->curcalc->PIXdanger);
            if (this->curcalc->map[i][j] == 'H')
                this->drawNOTHING(i, .0f, -j - 1, 1, 1, 1, this->curcalc->PIXhidden);
           }
    for (int i = 0; i < this->curcalc->Mpanel.size(); i++) {
        QPair <GLfloat, GLfloat> res = getposs(this->last.time, this->curcalc->Mpanel[i]);
       this->drawNOTHING(res.first + .01f, .0f, -res.second - 1 - .01f , 1.0f, 1, 1.0f, this->curcalc->PIXmoving);
    }
    GLUquadricObj *q;
    q = gluNewQuadric();

    for (int i = 0; i < this->curcalc->Fpanel.size(); i++) {
        GLuint tex = bindTexture(this->curcalc->PIXhole, GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glEnable(GL_BLEND);
        glColor4f(.0f, .0, .0, 1.0);
        char d = this->curcalc->Fpanel[i].direction;

        glTranslatef(this->curcalc->Fpanel[i].x, this->curcalc->Fpanel[i].z, -this->curcalc->Fpanel[i].y);
        if (d == 'R')
            glRotatef(-180, .0f, 1.0f, .0f);
        if (d == 'U')
            glRotatef(-90, .0f, 1.0f, .0f);
        if (d == 'D')
            glRotatef(90, .0f, 1.0f, .0f);
        glTranslatef(.0f, .0f, + 1e-2);
        glScalef(this->curcalc->Fpanel[i].stratchX, this->curcalc->Fpanel[i].stratchZ, this->curcalc->Fpanel[i].stratchY);
        glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(this->curcalc->Fpanel[i].r + 0.08, this->curcalc->Fpanel[i].r + 0.08, 0);
                glTexCoord2f(1, 0);
                glVertex3f(-this->curcalc->Fpanel[i].r - 0.08, this->curcalc->Fpanel[i].r + 0.08, 0);
                glTexCoord2f(1, 1);
                glVertex3f(-this->curcalc->Fpanel[i].r - 0.08, -this->curcalc->Fpanel[i].r - 0.08, 0);
                glTexCoord2f(0, 1);
                glVertex3f(this->curcalc->Fpanel[i].r + 0.08, -this->curcalc->Fpanel[i].r - 0.08, 0);
         glEnd();
         glScalef(1.0f / this->curcalc->Fpanel[i].stratchX, 1.0f / this->curcalc->Fpanel[i].stratchZ, 1.0f / this->curcalc->Fpanel[i].stratchY);
         glTranslatef(.0f, .0f, - 1e-2);
         if (d == 'R')
         glRotatef(180, .0f, 1.0f, .0f);
         if (d == 'U')
             glRotatef(90, .0f, 1.0f, .0f);
         if (d == 'D')
             glRotatef(-90, .0f, 1.0f, .0f);
         glTranslatef(-this->curcalc->Fpanel[i].x, -this->curcalc->Fpanel[i].z, this->curcalc->Fpanel[i].y);

        glDisable(GL_BLEND);

        tex = bindTexture(this->curcalc->PIXfireball, GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glColor3f(1.0f, 1.0f, 1.0f);
            GLint f = 0;
            GLfloat p = (GLfloat) ((this->last.time + this->curcalc->Fpanel[i].rest - this->curcalc->Fpanel[i].pause) % this->curcalc->Fpanel[i].rest) / this->curcalc->Fpanel[i].interval;
            GLfloat dl = (GLfloat) this->curcalc->Fpanel[i].rest / this->curcalc->Fpanel[i].interval;
            glTranslatef(this->curcalc->Fpanel[i].x, this->curcalc->Fpanel[i].z, -this->curcalc->Fpanel[i].y);
            if (d == 'R')
                glRotatef(-180, .0f, 1.0f, .0f);
            if (d == 'U')
                glRotatef(-90, .0f, 1.0f, .0f);
            if (d == 'D')
                glRotatef(90, .0f, 1.0f, .0f);


            glTranslatef(.0f, .0f, p);
            while (p + f * dl < this->curcalc->Fpanel[i].dist) {
                gluQuadricTexture(q, GL_TRUE);
                glScalef(this->curcalc->Fpanel[i].stratchX, this->curcalc->Fpanel[i].stratchZ, this->curcalc->Fpanel[i].stratchY);
                gluSphere(q, this->curcalc->Fpanel[i].r, 20, 20);
                glScalef(1.0f / this->curcalc->Fpanel[i].stratchX, 1.0f / this->curcalc->Fpanel[i].stratchZ, 1.0f / this->curcalc->Fpanel[i].stratchY);
                glTranslatef(.0f, .0f, dl);
                f++;
            }
            glTranslatef(.0f, .0f, -p - dl * f);
            if (d == 'R')
            glRotatef(180, .0f, 1.0f, .0f);
            if (d == 'U')
                glRotatef(90, .0f, 1.0f, .0f);
            if (d == 'D')
                glRotatef(-90, .0f, 1.0f, .0f);
            glTranslatef(-this->curcalc->Fpanel[i].x, -this->curcalc->Fpanel[i].z, this->curcalc->Fpanel[i].y);
    }
    gluDeleteQuadric(q);
}

void GLPainter::drawaxes() {
    glLineWidth(3.0f);
    glColor4f(1.0f, .0f, .0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(100, 0, 0);
    glEnd();

    glColor4f(.0f, 1.0f, .0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 100, 0);
    glEnd();

    glColor4f(.0f, .0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 100);
    glEnd();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void GLPainter::drawSKY() {
    this->fogg(this->curcalc->dead);
    if (this->curcalc->stretch_sky)
         this->drawNOTHING(-1, 1, 1, this->curcalc->n + 2, 0, -this->curcalc->m - 2, this->curcalc->PIXsky);
    else
    for (int i = 0; i < this->curcalc->n; i++)
        for (int j = 0; j < this->curcalc->m; j++)
            this->drawQUBE(i, 1.0f, -j - 1, 1, 1, 1, this->curcalc->PIXsky);
}

void GLPainter::mouseMoveEvent(QMouseEvent *ev) {
    if (!this->curcalc->fullscreen)
        return;
    if (this->curcalc->menuopened)
        return;
    if (!this->curcalc->fullscreen)
        return;
    if (this->curcalc->levelnomber > this->curcalc->maxlevels)
        return;

    if (! this->curcalc->mousedetected) {
        this->curcalc->mouseX = ev->x();
        this->curcalc->mouseY = ev->y();
        this->curcalc->mousedetected = true;
    }
    QPoint NP(ev->x(), ev->y());
//    qDebug() << (this->curcalc->mouseX - ev->x()) / 100 * this->curcalc->lat << (this->curcalc->mouseY - ev->y()) / 100 * this->curcalc->lat;
    this->curcalc->rx += (this->curcalc->mouseY - ev->y()) / 100 * this->curcalc->lat;
    if (this->curcalc->levelnomber != 0)
        this->curcalc->ry += (this->curcalc->mouseX - ev->x()) / 100 * this->curcalc->lat;

    if (ev->x() == this->width() - 1) {
        this->cursor().setPos(1, ev->y());
        NP.setX(1);
    }
    if (ev->y() == this->height() - 1) {
        this->cursor().setPos(ev->x(), 1);
        NP.setY(1);
    }
    if (ev->x() == 0) {
        this->cursor().setPos(this->width() - 2, ev->y());
        NP.setX(this->width() - 2);
    }
    if (ev->y() == 0) {
        this->cursor().setPos(ev->x(), this->height() - 2);
        NP.setY(this->height() - 2);
    }
    this->curcalc->mouseX = NP.x();
    this->curcalc->mouseY = NP.y();
//    qDebug() << this->curcalc->timerT->globaltime << this->curcalc->rx << this->curcalc->ry;

}

void GLPainter::switchmode() {
    this->curcalc->fullscreen = !this->curcalc->fullscreen;
    setWindowState(this->curcalc->fullscreen ? Qt::WindowFullScreen : Qt::WindowNoState);
    if (this->curcalc->fullscreen)
        this->setCursor(QCursor(Qt::BlankCursor));
    else
        this->setCursor(QCursor(Qt::ArrowCursor));

}

void GLPainter::fogg(bool start) {
    GLfloat fogColor[4] = {(GLfloat) this->curcalc->timetorestart / this->curcalc->restime, .0f, .0f, 1.0f};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_END, (GLfloat) this->curcalc->timetorestart / this->curcalc->restime);
    if (start)
        glEnable(GL_FOG);
    else
        glDisable(GL_FOG);
}

void GLPainter::drawinfo() {
    this->Begin2D();
    if (!this->curcalc->dead) {
      glColor4f(.0f, .0f, .0f, .8f);
      glBegin (GL_QUADS);
        glVertex2f (this->curcalc->dw + 0, -this->curcalc->dh + this->height());
        glVertex2f (this->curcalc->dw + 0,-this->curcalc->dh +  this->height() - 100);
        glVertex2f (this->curcalc->dw + 220, -this->curcalc->dh + this->height() - 100);
        glVertex2f (this->curcalc->dw + 220, -this->curcalc->dh + this->height());
      glEnd();
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);      
      renderText(this->curcalc->dw + 5,this->curcalc->dh + 25, "Level: " + QString::number(this->curcalc->levelnomber) + "/" + QString::number(this->curcalc->maxlevels));
      renderText(this->curcalc->dw + 5,this->curcalc->dh + 45, "Extra lifes taken: " + QString::number(this->curcalc->life));
      renderText(this->curcalc->dw + 5,this->curcalc->dh + 65, "Time: " + QString::number(this->curcalc->timerT->globaltime / 1000) + "s.");
      renderText(this->curcalc->dw + 5,this->curcalc->dh + 85, "On this level: " + QString::number(this->curcalc->TIME / 1000) + "s.");
      }
      else {
       glColor4f(std::min((GLfloat) this->curcalc->timetorestart / this->curcalc->restime + 0.05f, 1.0f), 0.0f, 0.0f, 0.8f);
          glBegin (GL_QUADS);
            glVertex2f (this->curcalc->dw + 0,-this->curcalc->dh + this->height());
            glVertex2f (this->curcalc->dw + 0,-this->curcalc->dh + this->height() - 100);
            glVertex2f (this->curcalc->dw + 300,-this->curcalc->dh + this->height() - 100);
            glVertex2f (this->curcalc->dw + 300,-this->curcalc->dh + this->height());
          glEnd();
          glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
          this->setFont(QFont("serif", 15, -1, false));
          renderText(this->curcalc->dw + 20, this->curcalc->dh + 40, "You are dead...");
          renderText(this->curcalc->dw + 20, this->curcalc->dh + 60, "Time to restart: " + QString::number((GLfloat)this->curcalc->timetorestart / 1000));
      }
    if (this->curcalc->menuopened) {
        glColor4f(.0f, .0f, .0f, .8f);
        glBegin (GL_QUADS);
          glVertex2f (this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 + 50);
          glVertex2f (this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50);
          glVertex2f (this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 + 125, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50);
          glVertex2f (this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 + 125, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 + 50);
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        this->setFont(QFont("serif", 15, -1, false));
        renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 30, "PAUSE");
        renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 60, "Press Enter to exit    ");
        renderText(this->curcalc->dw + (this->width() - this->curcalc->dw * 2) / 2 - 125 + 15, this->curcalc->dh + (this->height() - this->curcalc->dh * 2) / 2 - 50 + 80, "Press Esc. to continue");
    }

    if (this->curcalc->multiplayer) {
     glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
        glBegin (GL_QUADS);
          glVertex2f (this->width() - this->curcalc->dw - 300,-this->curcalc->dh + this->height());
          glVertex2f (this->width() - this->curcalc->dw - 300,-this->curcalc->dh + this->height() - 100);
          glVertex2f (this->width() - this->curcalc->dw + 0,-this->curcalc->dh + this->height() - 100);
          glVertex2f (this->width() - this->curcalc->dw + 0,-this->curcalc->dh + this->height());
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        this->setFont(QFont("serif", 15, -1, false));
        renderText(this->width() - this->curcalc->dw - 300, this->curcalc->dh + 25, this->curcalc->mess[0]);
        renderText(this->width() - this->curcalc->dw - 300, this->curcalc->dh + 45, this->curcalc->mess[1]);
        renderText(this->width() - this->curcalc->dw - 300, this->curcalc->dh + 65, this->curcalc->mess[2]);
        renderText(this->width() - this->curcalc->dw - 300, this->curcalc->dh + 85, this->curcalc->mess[3]);
    }

    this->End2D();


}

GLfloat GLPainter::getx(GLfloat x) {
    return (2 * x) / this->width();
}

GLfloat GLPainter::gety(GLfloat y) {
    return (2 * y) / this->height();
}

void GLPainter::mainmenu() {;
    this->drawQUBE(-50, -100, -50, 100, 0.1f, 100, this->curcalc->PIXmenu);
    this->drawQUBE(-50, -100, -50, 100, 100, 0.1f, this->curcalc->PIXresults);
    this->drawQUBE(50, 0, 50, -100, -100, 0.1f, this->curcalc->PIXcred);
}

void GLPainter::drawhistory(Hevent ev) {
    glTranslatef(ev.x, .39f, ev.y);
                    glRotatef(ev.ry, .0f, 1.0f, .0f);
    glScalef(0.008f, 0.008f, 0.008f);
    glRotatef(-90.0f, 1.0f, .0f, .0f);
    glRotatef(180.0f, .0f, .0f, 1.0f);
    glTranslatef(.0f, .0f ,125 * ev.z);
    if (ev.player == Hdead) {
        this->HistoryDmodel->draw(ev.sceneindex);
        this->HistoryDarm->draw(ev.sceneindex);
    }
    else
    if (ev.player == Hjump) {
        this->HistoryJmodel->draw(ev.sceneindex);
        this->HistoryJarm->draw(ev.sceneindex);
    }
    else
    if (ev.player == Hcrouch) {
        glTranslatef(.0f, .0f, .2f * 125);
        this->HistoryCmodel->draw(ev.sceneindex);
        this->HistoryCarm->draw(ev.sceneindex);
        glTranslatef(.0f, .0f, -.2f * 125);
    }
    else
    if (ev.player == Hwalk) {
        this->HistoryRmodel->draw(ev.sceneindex);
        this->HistoryRarm->draw(ev.sceneindex);
    }
    else {
        this->HistorySmodel->draw(ev.sceneindex);
        this->HistorySarm->draw(ev.sceneindex);
    }
    glTranslatef(.0f,.0f, -125 * ev.z);
    glRotatef(-180.0f, .0f, .0f, 1.0f);
    glRotatef(90.0f, 1.0f, .0f, .0f);
    glScalef(125.0f, 125.0f, 125.0f);
    glRotatef(-ev.ry, .0f, 1.0f, .0f);
    glTranslatef(-ev.x, -.39f, -ev.y);
}
