#include "drawgl.h"
#include <QDebug>
#include <cstdio>
#include <cmath>
#include <QDir>
#include <fstream>
#include <QPainter>
#include <string>
#include <ghost.h>

void GLPainter::loadp1() {
    this->Rmodel = new SMDloader(this);
    this->Rmodel->setstay(true);
    this->Rmodel->setpath("../Textures/Player");
    this->Rmodel->loadmodel("body.smd");
    this->Rmodel->loadanimation("run2.smd");

    this->Smodel = new SMDloader(this);
    this->Smodel->setstay(true);
    this->Smodel->setpath("../Textures/Player");
    this->Smodel->loadmodel("body.smd");
    this->Smodel->loadanimation("idle.smd");

    this->Jmodel = new SMDloader(this);
    this->Jmodel->setstay(true);
    this->Jmodel->setpath("../Textures/Player");
    this->Jmodel->loadmodel("body.smd");
    this->Jmodel->loadanimation("jump.smd");

    this->Dmodel = new SMDloader(this);
    this->Dmodel->setstay(true);
    this->Dmodel->setpath("../Textures/Player");
    this->Dmodel->loadmodel("body.smd");
    this->Dmodel->loadanimation("die_forwards.smd");

    this->Cmodel = new SMDloader(this);
    this->Cmodel->setstay(true);
    this->Cmodel->setpath("../Textures/Player");
    this->Cmodel->loadmodel("body.smd");
    this->Cmodel->loadanimation("crawl.smd");

    this->Rarm = new SMDloader(this);
    this->Rarm->setstay(true);
    this->Rarm->setpath("../Textures/Player");
    this->Rarm->loadmodel("arms.smd");
    this->Rarm->loadanimation("run2.smd");

    this->Sarm = new SMDloader(this);
    this->Sarm->setstay(true);
    this->Sarm->setpath("../Textures/Player");
    this->Sarm->loadmodel("arms.smd");
    this->Sarm->loadanimation("idle.smd");

    this->Jarm = new SMDloader(this);
    this->Jarm->setstay(true);
    this->Jarm->setpath("../Textures/Player");
    this->Jarm->loadmodel("arms.smd");
    this->Jarm->loadanimation("jump.smd");

    this->Darm = new SMDloader(this);
    this->Darm->setstay(true);
    this->Darm->setpath("../Textures/Player");
    this->Darm->loadmodel("arms.smd");
    this->Darm->loadanimation("die_forwards.smd");

    this->Carm = new SMDloader(this);
    this->Carm->setstay(true);
    this->Carm->setpath("../Textures/Player");
    this->Carm->loadmodel("arms.smd");
    this->Carm->loadanimation("crawl.smd");

}

void GLPainter::loadp2() {
    GLfloat al = 0.5f;
    this->HistoryRmodel = new SMDloader(this);
    this->HistoryRmodel->setalpha(al);
    this->HistoryRmodel->setstay(true);
    this->HistoryRmodel->setpath("../Textures/Player");
    this->HistoryRmodel->loadmodel("body.smd");
    this->HistoryRmodel->loadanimation("run2.smd");

    this->HistorySmodel = new SMDloader(this);
    this->HistorySmodel->setalpha(al);
    this->HistorySmodel->setstay(true);
    this->HistorySmodel->setpath("../Textures/Player");
    this->HistorySmodel->loadmodel("body.smd");
    this->HistorySmodel->loadanimation("idle.smd");

    this->HistoryJmodel = new SMDloader(this);
    this->HistoryJmodel->setalpha(al);
    this->HistoryJmodel->setstay(true);
    this->HistoryJmodel->setpath("../Textures/Player");
    this->HistoryJmodel->loadmodel("body.smd");
    this->HistoryJmodel->loadanimation("jump.smd");

    this->HistoryDmodel = new SMDloader(this);
    this->HistoryDmodel->setalpha(al);
    this->HistoryDmodel->setstay(true);
    this->HistoryDmodel->setpath("../Textures/Player");
    this->HistoryDmodel->loadmodel("body.smd");
    this->HistoryDmodel->loadanimation("die_forwards.smd");

    this->HistoryCmodel = new SMDloader(this);
    this->HistoryCmodel->setalpha(al);
    this->HistoryCmodel->setstay(true);
    this->HistoryCmodel->setpath("../Textures/Player");
    this->HistoryCmodel->loadmodel("body.smd");
    this->HistoryCmodel->loadanimation("crawl.smd");

    this->HistoryRarm = new SMDloader(this);
    this->HistoryRarm->setalpha(al);
    this->HistoryRarm->setstay(true);
    this->HistoryRarm->setpath("../Textures/Player");
    this->HistoryRarm->loadmodel("arms.smd");
    this->HistoryRarm->loadanimation("run2.smd");

    this->HistorySarm = new SMDloader(this);
    this->HistorySarm->setalpha(al);
    this->HistorySarm->setstay(true);
    this->HistorySarm->setpath("../Textures/Player");
    this->HistorySarm->loadmodel("arms.smd");
    this->HistorySarm->loadanimation("idle.smd");

    this->HistoryJarm = new SMDloader(this);
    this->HistoryJarm->setalpha(al);
    this->HistoryJarm->setstay(true);
    this->HistoryJarm->setpath("../Textures/Player");
    this->HistoryJarm->loadmodel("arms.smd");
    this->HistoryJarm->loadanimation("jump.smd");

    this->HistoryDarm = new SMDloader(this);
    this->HistoryDarm->setalpha(al);
    this->HistoryDarm->setstay(true);
    this->HistoryDarm->setpath("../Textures/Player");
    this->HistoryDarm->loadmodel("arms.smd");
    this->HistoryDarm->loadanimation("die_forwards.smd");

    this->HistoryCarm = new SMDloader(this);
    this->HistoryCarm->setalpha(al);
    this->HistoryCarm->setstay(true);
    this->HistoryCarm->setpath("../Textures/Player");
    this->HistoryCarm->loadmodel("arms.smd");
    this->HistoryCarm->loadanimation("crawl.smd");

}

GLPainter::GLPainter(QWidget *parent)
    : QGLWidget(parent)
{
    this->firstview = false;
    this->CAMERAdist = .5;
    this->loadp1();
    this->loadp2();
    this->curs = "";
    this->setFont(QFont("serif", 15, -1, false));
    this->timerT = new timer;
    this->timerT->start();
    this->timerT->TIM = new QTimer;
    QObject::connect(this->timerT->TIM, SIGNAL(timeout()), this, SLOT(timeout()));
    this->timerT->TIM->start();
    this->jumping = false;
    this->rx = 0;
    this->mousedetected = false;
    this->setMouseTracking(true);
    this->levelnomber = -1;
    this->TIME = 0;
    this->fullscreen = false;
    this->setMinimumSize(610, 512);
    this->restime = 1500;
    this->menuopened = false;
    this->duck = false;
    this->loadparam();
    this->loadstaticTEX();
    this->FFall = false;
    this->life = 0;
    finn();
}

GLPainter::~GLPainter()
{

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
    gluOrtho2D(this->dw, this->width() - this->dw, this->dh, this->height() - this->dh);
}

void GLPainter::End2D ()
{
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_BLEND);
}

bool GLPainter::inside_key(int key) {
    return (this->keys_pressed.find(key) != this->keys_pressed.end());
}

void GLPainter::throw_key(int key) {
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

bool GLPainter::loadparam() {
    std::ifstream in;
    in.open("../Param/param.walk");
    if (in == NULL) {
        qDebug() << "param.walk not found!";
        return false;
    }
    in >> this->maxlevels >> this->updatetime >>  this->lat;
    in.close();
    return true;
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
    this->switchmode();
}

void GLPainter::loadLists() {

    this->wall = glGenLists(1);

    GLint a = 1, b = 1, c = 1;

    glNewList(this->wall, GL_COMPILE);
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

void GLPainter::resizeGL(int w, int h) {

    GLfloat scale = std::min((GLfloat) w / 16, (GLfloat) h / 9);
    this->dw = (w - 16 * scale) / 2;
    this->dh = (h - 9 * scale) / 2;
    glViewport(this->dw, this->dh, 16 * scale, 9 * scale);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
    glMatrixMode(GL_MODELVIEW );
    glLoadIdentity();
}

void GLPainter::paintGL() {
    this->fogg(false);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth( 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if ((this->levelnomber > this->maxlevels) || (this->levelnomber == 0)) {
        glRotatef(-this->rx, 1.0f, .0f, .0f);
        glRotatef(-this->ry, .0f, 1.0f, .0f);
    }
    if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0))
        glTranslatef(-.5f, -.5f, 1.5f);
    else
        glTranslatef(-this->x, -.5f - this->z, -this->y);
    if (this->levelnomber == 0) {
        this->mainmenu();
    }
    else
    if (this->levelnomber <= this->maxlevels) {

        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
            GLfloat dist = this->CAMERAdist;
            while ((dist <= 1.0f) && canGO(this->x + dist * sin(this->ry * 3.15149265 / 180), -this->y - dist * cos(this->ry * 3.15149265 / 180)))
                dist += .05f;
            while ((dist >= .1f) && !canGO(this->x + dist * sin(this->ry * 3.15149265 / 180), -this->y - dist * cos(this->ry * 3.15149265 / 180)))
                dist -= .05f;
            this->CAMERAdist = std::min(dist, 1.0f);
            this->CAMERAdist = std::max(this->CAMERAdist, .1f);
            dist = this->CAMERAdist;
            if (this->firstview) {
                dist = .0f;
                gluLookAt(dist * sin(this->ry * 3.15149265 / 180), this->z - .05f, dist * cos(this->ry * 3.15149265 / 180),
                          (dist - .1f) * sin(this->ry * 3.15149265 / 180), this->z - .05f + this->rx / 300, (dist - .1f) * cos(this->ry * 3.15149265 / 180), 0, 1, 0);
            }
            else
            gluLookAt(dist * sin(this->ry * 3.15149265 / 180), .1f, dist * cos(this->ry * 3.15149265 / 180),
                      (dist - .1f) * sin(this->ry * 3.15149265 / 180), .1f + this->rx / 300, (dist - .1f) * cos(this->ry * 3.15149265 / 180), 0, 1, 0);
//            gluPerspective(45.0f, 16.0 / 9, 0.01f, 200.0f );
        glMatrixMode(GL_MODELVIEW);

        glTranslatef(-this->x + .5f, .0f, -this->y - 1.5f);
        this->drawSKY();
        this->drawmap();
        if ((this->drawindex >= 0) && (this->drawindex < this->best.gethistorylength() - 1)) {
            this->drawhistory(this->best.getHevent(this->drawindex));
//            qDebug() << this->current.gethistorylength();
        }
        if (!this->firstview)
            this->drawplayer();
        this->drawinfo();



    }
    else {

        if (this->levelnomber == this->maxlevels + 1)
            this->drawNOTHING(-50, -100, -50, 100, 0, 100, this->PIXwin);
        else
            this->savescore();
   }
}

void GLPainter::drawplayer() {
    glTranslatef(this->x, .39f, this->y);
                    glRotatef(this->ry, .0f, 1.0f, .0f);
//        glTranslatef(.0f, .0f, -1.0f);
    glScalef(0.008f, 0.008f, 0.008f);
    glRotatef(-90.0f, 1.0f, .0f, .0f);
    glRotatef(180.0f, .0f, .0f, 1.0f);
//    qDebug() << this->z;
    glTranslatef(.0f, .0f ,125 * this->z);
    if (this->dead) {
//        qDebug() << (trunc((this->timetorestart / this->restime) * (this->Dmodel->getanimationlength() - 1)));
        GLint nu = (this->Dmodel->getanimationlength() - 1) - trunc(((GLfloat) this->timetorestart / this->restime) * (this->Dmodel->getanimationlength() - 1));
        this->Dmodel->draw(nu);
        this->Darm->draw(nu);
    }
    else
    if (this->jumping) {
        GLint nu = trunc(((GLfloat)this->jumpiterations / 37) * (this->Jmodel->getanimationlength() - 1));
        this->Jmodel->draw(nu);
        this->Jarm->draw(nu);
    }
    else
    if (this->duck) {
        glTranslatef(.0f, .0f, .2f * 125);
        GLint nu = (this->TIME / 30) % this->Cmodel->getanimationlength();
        if (!this->walking)
            nu = 0;
        this->Cmodel->draw(nu);
        this->Carm->draw(nu);
        glTranslatef(.0f, .0f, -.2f * 125);
    }
    else
    if (this->walking) {
        GLint nu = (this->TIME / 20) % this->Rmodel->getanimationlength();
        this->Rmodel->draw(nu);
        this->Rarm->draw(nu);
    }
    else {
        GLint nu = (this->TIME / 100) % this->Smodel->getanimationlength();
        this->Smodel->draw(nu);
        this->Sarm->draw(nu);
    }
            glTranslatef(.0f,.0f, -125 * this->z);
    glRotatef(-180.0f, .0f, .0f, 1.0f);
    glRotatef(90.0f, 1.0f, .0f, .0f);
    glScalef(125.0f, 125.0f, 125.0f);
//        glTranslatef(.0f, .0f, -1.0f);
                    glRotatef(-this->ry, .0f, 1.0f, .0f);
    glTranslatef(-this->x, -.39f, -this->y);
}

void GLPainter::savescore() {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    int newscore = 1000000 / (this->timerT->globaltime / 1000 + 10 * this->life + 1);
    if (newscore <= this->score[9].second) {
        this->finn();
        return;
    }
    int i = 0;
    while (this->score[i].second >= newscore)
        i++;
    renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 30, "New record! Your place: " + QString::number(i + 1));
    renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 60, "Enter your name: " + this->nametyped + this->curs);
    renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 90, "<Press Enter to save>");
    renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 110, "<Press Esc to exit>");


}

GLfloat fabs(GLfloat a) {
    if (a < 0)
        return -a;
    else
        return a;
}

void GLPainter::keyPressEvent(QKeyEvent *ev) {
    if ((this->FFall) && (this->levelnomber == 0) && (ev->key() == Qt::Key_Escape))
        this->jumpiterations = 1000;
//    qDebug() << "+" << ev->key();
    if (this->levelnomber == this->maxlevels + 2) {
        if (((ev->text() >= "0") && (ev->text() <= "9")) || ((ev->text() >= "a") && (ev->text() <= "z")) || ((ev->text() >= "A") && (ev->text() <= "Z")) || (ev->text() == "_"))
            this->nametyped += ev->text();
        else
        if (ev->key() == Qt::Key_Backspace)
            this->nametyped = this->nametyped.left(this->nametyped.length() - 1);
        else
            this->keys_pressed.insert(ev->key());
        this->nametyped = this->nametyped.left(10);
    }
    else
        this->keys_pressed.insert(ev->key());
}

void GLPainter::keyReleaseEvent(QKeyEvent *ev) {
//    qDebug() << "-" << ev->key();
    if (this->keys_pressed.find(ev->key()) != this->keys_pressed.end())
        this->keys_pressed.erase(this->keys_pressed.find(ev->key()));
}

void GLPainter::drawQUBE(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture) {

    GLuint ap = bindTexture(texture, GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ap);
    glTranslatef(x, y, z);
    glColor4f(1.0f, 1.0f, 1.0f, .0f);
    glScalef(a, b, c);
    glCallList(this->wall);
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
    for (int i = 0; i < this->Hpanel.size(); i++)
        if (getstate(this->TIME, this->Hpanel[i]))
            this->map[this->Hpanel[i].x][this->Hpanel[i].y] = 'H';
        else
            this->map[this->Hpanel[i].x][this->Hpanel[i].y] = this->Hpanel[i].backup;
    for (int i = -1; i <= n; i++) {
        this->drawQUBE(i, .0f, 1 - 1, 1, 1, 1, this->PIXwall);
        this->drawQUBE(i, .0f, -m - 1, 1, 1, 1, this->PIXwall);
    }
    for (int j = -1; j <= m; j++) {
        this->drawQUBE(-1, .0f, -j - 1, 1, 1, 1, this->PIXwall);
        this->drawQUBE(n, .0f, -j - 1, 1, 1, 1, this->PIXwall);
    }


    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (this->map[i][j] == '*')
                this->drawQUBE(i, .0f, -j - 1, 1, 1, 1, this->PIXwall);
            if (this->map[i][j] == 'E')
                this->drawQUBE(i, .0f, -j - 1, 1, 1, 1, this->PIXexit);
            if (this->map[i][j] == '.')
                this->drawNOTHING(i, .0f, -j - 1, 1, 1, 1, this->PIXfloor);
            if (this->map[i][j] == '0')
                this->drawNOTHING(i, -.1f, -j - 1, 1, 1, 1, this->PIXdanger);
            if (this->map[i][j] == 'H')
                this->drawNOTHING(i, .0f, -j - 1, 1, 1, 1, this->PIXhidden);
           }
    for (int i = 0; i < this->Mpanel.size(); i++) {
        QPair <GLfloat, GLfloat> res = getpos(this->TIME, this->Mpanel[i]);
       this->drawNOTHING(res.first + .01f, .0f, -res.second - 1 - .01f , 1.0f, 1, 1.0f, this->PIXmoving);
    }
    GLUquadricObj *q;
    q = gluNewQuadric();

    for (int i = 0; i < this->Fpanel.size(); i++) {
        GLuint tex = bindTexture(this->PIXhole, GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glEnable(GL_BLEND);
        glColor4f(.0f, .0, .0, 1.0);
        char d = this->Fpanel[i].direction;

        glTranslatef(this->Fpanel[i].x, this->Fpanel[i].z, -this->Fpanel[i].y);
        if (d == 'R')
            glRotatef(-180, .0f, 1.0f, .0f);
        if (d == 'U')
            glRotatef(-90, .0f, 1.0f, .0f);
        if (d == 'D')
            glRotatef(90, .0f, 1.0f, .0f);
        glTranslatef(.0f, .0f, + 1e-2);
        glScalef(this->Fpanel[i].stratchX, this->Fpanel[i].stratchZ, this->Fpanel[i].stratchY);
        glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(this->Fpanel[i].r + 0.08, this->Fpanel[i].r + 0.08, 0);
                glTexCoord2f(1, 0);
                glVertex3f(-this->Fpanel[i].r - 0.08, this->Fpanel[i].r + 0.08, 0);
                glTexCoord2f(1, 1);
                glVertex3f(-this->Fpanel[i].r - 0.08, -this->Fpanel[i].r - 0.08, 0);
                glTexCoord2f(0, 1);
                glVertex3f(this->Fpanel[i].r + 0.08, -this->Fpanel[i].r - 0.08, 0);
         glEnd();
         glScalef(1.0f / this->Fpanel[i].stratchX, 1.0f / this->Fpanel[i].stratchZ, 1.0f / this->Fpanel[i].stratchY);
         glTranslatef(.0f, .0f, - 1e-2);
         if (d == 'R')
         glRotatef(180, .0f, 1.0f, .0f);
         if (d == 'U')
             glRotatef(90, .0f, 1.0f, .0f);
         if (d == 'D')
             glRotatef(-90, .0f, 1.0f, .0f);
         glTranslatef(-this->Fpanel[i].x, -this->Fpanel[i].z, this->Fpanel[i].y);

        glDisable(GL_BLEND);

        tex = bindTexture(this->PIXfireball, GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glColor3f(1.0f, 1.0f, 1.0f);
            GLint f = 0;
            GLfloat p = (GLfloat) ((this->TIME + this->Fpanel[i].rest - this->Fpanel[i].pause) % this->Fpanel[i].rest) / Fpanel[i].interval;
            GLfloat dl = (GLfloat) this->Fpanel[i].rest / this->Fpanel[i].interval;
            glTranslatef(this->Fpanel[i].x, this->Fpanel[i].z, -this->Fpanel[i].y);
            if (d == 'R')
                glRotatef(-180, .0f, 1.0f, .0f);
            if (d == 'U')
                glRotatef(-90, .0f, 1.0f, .0f);
            if (d == 'D')
                glRotatef(90, .0f, 1.0f, .0f);


            glTranslatef(.0f, .0f, p);
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

                gluQuadricTexture(q, GL_TRUE);
                glScalef(this->Fpanel[i].stratchX, this->Fpanel[i].stratchZ, this->Fpanel[i].stratchY);
                gluSphere(q, this->Fpanel[i].r, 20, 20);
                glScalef(1.0f / this->Fpanel[i].stratchX, 1.0f / this->Fpanel[i].stratchZ, 1.0f / this->Fpanel[i].stratchY);
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
            glTranslatef(-this->Fpanel[i].x, -this->Fpanel[i].z, this->Fpanel[i].y);
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

bool GLPainter::canGO (GLfloat x, GLfloat y) {
    return
            this->canGO2(x + 1e-1, y + 1e-1) &&
            this->canGO2(x + 1e-1, y - 1e-1) &&
            this->canGO2(x - 1e-1, y + 1e-1) &&
            this->canGO2(x - 1e-1, y - 1e-1);
}

bool GLPainter::canGO2(GLfloat x, GLfloat y) {
    if ((x >= 0) && (x < n) && (y >= 0) && (y  < m) && (this->map[(GLint)floor(x)][(GLint)floor(y)] == 'E')) {
        this->finn();
        return false;
    }
    return (x >= 0) && (x < n) && (y >= 0) && (y < m) && (this->map[(GLint)floor(x)][(GLint)floor(y)] != '*');
}

void GLPainter::finn() {
//    this->keys_pressed.clear();
    this->nametyped = "";
    this->timerT->TIM->stop();
    if ((this->levelnomber > 0) && (this->levelnomber <= this->maxlevels))
        if ((this->current.gethistorylength() < this->best.gethistorylength()) || (this->best.gethistorylength() == 0))
            this->current.save("../Param/Best/" + QString::number(this->levelnomber));
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
    if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0))
        this->loadlevel();
    this->best.load("../Param/Best/" + QString::number(this->levelnomber));
    this->TIME = 0;
    this->restart();
    this->timerT->TIM->start();
}

void GLPainter::searchkeys() {
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
            if ((!this->FFall) && (this->levelnomber == 0))
                this->close();
        if (this->levelnomber == this->maxlevels + 2)
            this->finn();
        this->throw_key(Qt::Key_Escape);
    }
    if (this->inside_key(Qt::Key_Return)) {
        this->throw_key(Qt::Key_Return);\
        if (this->levelnomber == 0) {
            this->FFall = true;
            return;
        }
        if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0)) {
            if (this->menuopened) {
                this->levelnomber = -1;
                finn();
//                 this->close();
            }
        }
        if ((this->levelnomber == this->maxlevels + 2) && (this->nametyped != "")) {
            int newscore = 1000000 / (this->timerT->globaltime / 1000 + 10 * this->life + 1);
            if (newscore <= this->score[9].second) {
                this->finn();
                return;
            }
            int i = 0;
            while (this->score[i].second >= newscore)
                i++;
            std::ofstream out;
            out.open("../Param/results.walk");
            for (int j = 0; j < i; j++)
                out << this->score[j].first.toStdString() << " " << this->score[j].second << " ";
            out << this->nametyped.toStdString() << " " << newscore << " ";
            for (int j = i; j < 9; j++)
                out << this->score[j].first.toStdString() << " " << this->score[j].second << " ";
            out.close();
            this->finn();
        }
    }
    if ((this->inside_key('Z')) || (this->inside_key(1071))){
        this->switchmode();
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

void GLPainter::die() {
    this->dead = true;
}

void GLPainter::timeout() {

    if ((this->levelnomber > 0) && (this->levelnomber <= this->maxlevels) && (!this->menuopened)) {
        this->current.pushHevent(this->generateevent());
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
                if (!this->menuopened)
                    this->timetorestart -= this->updatetime;
                if (this->timetorestart <= 0) {
                    this->life++;
                    this->restart();
                }
        }
    else {
        if (!this->menuopened) {
            this->TIME += this->updatetime;
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
    this->update();

    if (this->z < -100.0f) {
        finn();
    }
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

void GLPainter::drawSKY() {
    this->fogg(this->dead);
    if (this->stretch_sky)
         this->drawNOTHING(-1, 1, 1, this->n + 2, 0, -this->m - 2, PIXsky);
    else
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->drawQUBE(i, 1.0f, -j - 1, 1, 1, 1, this->PIXsky);
}

void GLPainter::restart() {
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

void GLPainter::jump() {
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

bool GLPainter::isfloor(GLfloat x, GLfloat y) {
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

void GLPainter::freefall() {
    this->rx = -90;
    this->ry = 0;
    const GLfloat g = 9.8f;
    this->jumpiterations++;
    GLfloat t = (GLfloat) this->jumpiterations * this->updatetime / 1000;
    this->z = -g * t * t / 2;
    this->x += this->vx;
    this->y += this->vy;
}

void GLPainter::mouseMoveEvent(QMouseEvent *ev) {

    if (this->menuopened)
        return;
    if (!this->fullscreen)
        return;
    if (this->levelnomber > this->maxlevels)
        return;

    if (! this->mousedetected) {
        this->mouseX = ev->x();
        this->mouseY = ev->y();
        this->mousedetected = true;
    }
    QPoint NP(ev->x(), ev->y());
//    qDebug() << (this->mouseX - ev->x()) / 100 * this->lat << (this->mouseY - ev->y()) / 100 * this->lat;
    this->rx += (this->mouseY - ev->y()) / 100 * this->lat;
    if (this->levelnomber != 0)
        this->ry += (this->mouseX - ev->x()) / 100 * this->lat;

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
    this->mouseX = NP.x();
    this->mouseY = NP.y();
//    qDebug() << this->timerT->globaltime << this->rx << this->ry;

}

void GLPainter::switchmode() {
    this->fullscreen = !this->fullscreen;
    setWindowState(this->fullscreen ? Qt::WindowFullScreen : Qt::WindowNoState);
    if (this->fullscreen)
        this->setCursor(QCursor(Qt::BlankCursor));
    else
        this->setCursor(QCursor(Qt::ArrowCursor));

}

void GLPainter::levelclear() {
    this->current.clear();
    this->best.clear();
    this->sx = this->sy = 0;
    this->Hpanel.clear();
    this->Mpanel.clear();
    this->Fpanel.clear();
    this->drawindex = -1;
}

void GLPainter::loadlevel() {
    FILE *inp;
    inp = fopen(QString("../Levels/" + (QString::number(this->levelnomber))).toStdString().c_str(), "r");
    if (inp == NULL) {
        qDebug() << "file with map" << this->levelnomber << "not found. Halting!";
        this->close();
    }
    fscanf(inp, "%d %d\n", &this->n, &this->m);
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
    fclose(inp);
}

QPixmap GLPainter::genpix(int w, int h, int f, QVector<QString> &mes) {
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
//    qDebug() << dx << dy;
//    dy = 0;
//    p.drawText(40, 40, "ASDD);
    for (int i = 0; i < mes.size(); i++)
        p.drawText(dx, dy + b * (i), mes[i]);
    br.setColor(QColor("white"));
    p.setBrush(br);
    p.drawRect(w / 2 - 50, 0, 100, 150);
    p.drawRect(w / 2 - 50, h - 220, 100, 220);
    br.setColor(QColor("black"));
    p.setBrush(br);
    p.drawRect(w / 2 - 5, 0 , 10, 150);
    p.drawRect(w / 2 - 5, h - 220, 10, 220);
    p.end();
    return *menu;
}

void GLPainter::loadstaticTEX() {
    this->PIXwin = QPixmap("../Textures/win.jpg");
    this->PIXhole = QPixmap("../Textures/hole.png");
    this->PIXfireball = QPixmap("../Textures/fireball.jpg");
    QVector <QString> mes (11);
    mes[0] = "WASD   :: move";
    mes[1] = "arrows :: rotate camera";
    mes[2] = "Space  :: jump";
    mes[3] = "Shift  :: crouch";
    mes[4] = "Esc    :: pause";
    mes[5] = "Z      :: fullscreen";
    mes[6] = "C      :: change view";
    mes[7] = "Reach finish...";
    mes[8] = "<Press ENTER to Start>";
    mes[9] = "         or";
    mes[10] = "<Press Esc to exit>";
    this->PIXmenu = this->genpix(1024, 1024, 40, mes);

    mes.resize(3);
    mes[0] = "You won!";
    mes[1] = "Thank you for playing Walkers!";
    mes[2] = "                     by danpol";
    this->PIXwin = this->genpix(1024, 1024, 40, mes);

    mes.clear();
    std::ifstream inp;
    inp.open("../Param/results.walk");
    QVector <QPair <QString, int> > res;
    for (int i = 0; i < 10; i++) {
        std::string a;
        int b;
        inp >> a >> b;
        res.push_back(QPair <QString, int> (QString::fromStdString(a), b));
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

void GLPainter::fogg(bool start) {
    GLfloat fogColor[4] = {(GLfloat) this->timetorestart / this->restime, .0f, .0f, 1.0f};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_END, (GLfloat) this->timetorestart / this->restime);
    if (start)
        glEnable(GL_FOG);
    else
        glDisable(GL_FOG);
}

void GLPainter::drawinfo() {
    this->Begin2D();
    if (!this->dead) {
      glColor4f(.0f, .0f, .0f, .8f);
      glBegin (GL_QUADS);
        glVertex2f (this->dw + 0, -this->dh + this->height());
        glVertex2f (this->dw + 0,-this->dh +  this->height() - 100);
        glVertex2f (this->dw + 220, -this->dh + this->height() - 100);
        glVertex2f (this->dw + 220, -this->dh + this->height());
      glEnd();
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);      
      renderText(this->dw + 5,this->dh + 25, "Level: " + QString::number(this->levelnomber) + "/" + QString::number(this->maxlevels));
      renderText(this->dw + 5,this->dh + 45, "Extra lifes taken: " + QString::number(this->life));
      renderText(this->dw + 5,this->dh + 65, "Time: " + QString::number(this->timerT->globaltime / 1000) + "s.");
      renderText(this->dw + 5,this->dh + 85, "On this level: " + QString::number(this->TIME / 1000) + "s.");
      }
      else {
       glColor4f(std::min((GLfloat) this->timetorestart / this->restime + 0.05f, 1.0f), 0.0f, 0.0f, 0.8f);
          glBegin (GL_QUADS);
            glVertex2f (this->dw + 0,-this->dh + this->height());
            glVertex2f (this->dw + 0,-this->dh + this->height() - 100);
            glVertex2f (this->dw + 300,-this->dh + this->height() - 100);
            glVertex2f (this->dw + 300,-this->dh + this->height());
          glEnd();
          glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
          this->setFont(QFont("serif", 15, -1, false));
          renderText(this->dw + 20, this->dh + 40, "You are dead...");
          renderText(this->dw + 20, this->dh + 60, "Time to restart: " + QString::number((GLfloat)this->timetorestart / 1000));
      }
    if (this->menuopened) {
        glColor4f(.0f, .0f, .0f, .8f);
        glBegin (GL_QUADS);
          glVertex2f (this->dw + (this->width() - this->dw * 2) / 2 - 125, this->dh + (this->height() - this->dh * 2) / 2 + 50);
          glVertex2f (this->dw + (this->width() - this->dw * 2) / 2 - 125, this->dh + (this->height() - this->dh * 2) / 2 - 50);
          glVertex2f (this->dw + (this->width() - this->dw * 2) / 2 + 125, this->dh + (this->height() - this->dh * 2) / 2 - 50);
          glVertex2f (this->dw + (this->width() - this->dw * 2) / 2 + 125, this->dh + (this->height() - this->dh * 2) / 2 + 50);
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        this->setFont(QFont("serif", 15, -1, false));
        renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 30, "PAUSE");
        renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 60, "Press Enter to exit    ");
        renderText(this->dw + (this->width() - this->dw * 2) / 2 - 125 + 15, this->dh + (this->height() - this->dh * 2) / 2 - 50 + 80, "Press Esc. to continue");
    }
    this->End2D();


}

GLfloat GLPainter::getx(GLfloat x) {
    return (2 * x) / this->width();
}

GLfloat GLPainter::gety(GLfloat y) {
    return (2 * y) / this->height();
}

GLfloat GLPainter::dist(GLfloat x, GLfloat y) {
    return (this->x - x) * (this->x - x) + (this->y + y) * (this->y + y);
}

void GLPainter::mainmenu() {;
    this->drawQUBE(-50, -100, -50, 100, 0.1f, 100, this->PIXmenu);
    this->drawQUBE(-50, -100, -50, 100, 100, 0.1f, this->PIXresults);
    this->drawQUBE(50, 0, 50, -100, -100, 0.1f, this->PIXcred);
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

Hevent GLPainter::generateevent() {
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
    return ev;
}
