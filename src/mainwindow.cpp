#include "mainwindow.h"
#include <QDebug>
#include <cstdio>
#include <cmath>
#include <QDir>
#include <fstream>

bool MainWindow::inside_key(int key) {
    return (this->keys_pressed.find(key) != this->keys_pressed.end());
}

void MainWindow::throw_key(int key) {
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

void MainWindow::loadparam() {
    std::ifstream in;
    in.open("../param.walk");
    in >>  this->maxlevels >> this->updatetime >>  this->lat >> this->life;
    in.close();
}

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    this->TIM = new QTimer;
    QObject::connect(this->TIM, SIGNAL(timeout()), this, SLOT(timeout()));
    this->TIM->start();
//    this->jumping = false;
    this->rx = 0;
    this->mousedetected = false;
    this->setMouseTracking(true);
    this->levelnomber = 0;
    this->TIME = 0;
    this->fullscreen = false;
//    this->timetorestart = 3000;
    this->loadparam();
    finn();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::initializeGL() {
    glEnable(GL_TEXTURE_2D);
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glShadeModel( GL_SMOOTH );
    glFogi(GL_FOG_MODE, GL_EXP);
    GLfloat fogColor[4]= {1.0f, .0f, .0f, 1.0f};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.4f);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 1.0f);
    glFogf(GL_FOG_END, 5.0f);
    this->switchmode();
}

void MainWindow::resizeGL(int w, int h) {
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.01f, 200.0f );
    glMatrixMode(GL_MODELVIEW );
    glLoadIdentity();
}

void MainWindow::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth( 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-this->rx, 1.0f, .0f, .0f);
    glRotatef(-this->ry, .0f, 1.0f, .0f);
    glTranslatef(-this->x, -.5f - this->z, -this->y);
    GLfloat p = 100;
    if (this->levelnomber <= this->maxlevels) {
        this->drawSKY();
        this->drawmap();
    }
    else
        if (this->life > 0)
            this->drawNOTHING(-p, -p, -p, 2 * p, 0, 2 * p, PIXwin);
        else
            this->drawNOTHING(-p, -p, -p, 2 * p, 0, 2 * p, PIXlose);
//    this->drawQUBE(0, .0f, -10, 1, 1, 1, TEXwall);
}

GLfloat fabs(GLfloat a) {
    if (a < 0)
        return -a;
    else
        return a;
}

void MainWindow::keyPressEvent(QKeyEvent *ev) {
//    qDebug() << ev->text() << ev->key();
    this->keys_pressed.insert(ev->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev) {
    if (this->keys_pressed.find(ev->key()) != this->keys_pressed.end())
        this->keys_pressed.erase(this->keys_pressed.find(ev->key()));
}

void MainWindow::drawQUBE(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture) {

    GLuint ap = bindTexture(texture, GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ap);
    glTranslatef(x, y, z);
//    qsrand(0);
//    glColor3f((float) (qrand() % 255) / 255, (float) (qrand() % 255) / 255, (float) (qrand() % 255) / 255);
    glColor4f(1.0f, 1.0f, 1.0f, .0f);
    glBegin(GL_QUADS);
            glTexCoord2f(1, 0);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(0, 0);
            glVertex3f(a, 0.0f, 0.0f);
            glTexCoord2f(0, 1);
            glVertex3f(a, b, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(.0f, b, 0.0f);
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


      glBegin(GL_QUADS);
              glTexCoord2f(0, 0);
              glVertex3f(0.0f, 0.0f, c);
              glTexCoord2f(0, 1);
              glVertex3f(.0f, b, c);
              glTexCoord2f(1, 1);
              glVertex3f(a, b, c);
              glTexCoord2f(1, 0);
              glVertex3f(a, 0.0f, c);
       glEnd();

//--------------------------------------------------
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(.0f, b, .0f);
            glTexCoord2f(1, 0);
            glVertex3f(a, b, .0f);
            glTexCoord2f(1, 1);
            glVertex3f(a, b, c);
            glTexCoord2f(0, 1);
            glVertex3f(.0f, b, c);
        glEnd();

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(.0f, .0f, .0f);
            glTexCoord2f(0, 1);
            glVertex3f(.0f, .0f, c);
            glTexCoord2f(1, 1);
            glVertex3f(a, .0f, c);
            glTexCoord2f(1, 0);
            glVertex3f(a, .0f, .0f);
        glEnd();

       glTranslatef(-x, -y, -z);
       glColor4f(.0f, .0f, .0f, 1.0f);
}

void MainWindow::drawNOTHING(GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat b, GLfloat c, QPixmap &texture) {
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



void MainWindow::drawmap() {
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
       this->drawNOTHING(res.first + .01f, .0f, -res.second - 1 - .01f , .98f, 1, .98f, this->PIXmoving);
    }
}

void MainWindow::drawaxes() {
    glLineWidth(3.0f);
    glColor3f(1.0f, .0f, .0f);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(100, 0, 0);
    glEnd();

    glColor3f(.0f, 1.0f, .0f);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 100, 0);
    glEnd();

    glColor3f(.0f, .0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 100);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
}

bool MainWindow::canGO (GLfloat x, GLfloat y) {
    return
            this->canGO2(x + 1e-1, y + 1e-1) &&
            this->canGO2(x + 1e-1, y - 1e-1) &&
            this->canGO2(x - 1e-1, y + 1e-1) &&
            this->canGO2(x - 1e-1, y - 1e-1);
}

bool MainWindow::canGO2(GLfloat x, GLfloat y) {
//    qDebug() << this->x << this->y;
    if ((x >= 0) && (x < n) && (y >= 0) && (y  < m) && (this->map[(GLint)floor(x)][(GLint)floor(y)] == 'E')) {
        this->finn();
        return false;
    }
//    qDebug() << x << y;
//    qDebug() << x << y;
    return (x >= 0) && (x < n) && (y >= 0) && (y < m) && (this->map[(GLint)floor(x)][(GLint)floor(y)] != '*');
}

void MainWindow::finn() {
    this->TIM->stop();
    this->levelnomber++;
//    qDebug() << this->levelnomber << this->maxlevels;
    if (this->levelnomber > this->maxlevels + 1) {
        this->close();
        return;
    }
    this->levelclear();
    if (this->levelnomber <= this->maxlevels)
        this->loadlevel();
    this->restart();
    this->TIM->start();
}

void MainWindow::searchkeys() {
    //ALWAYS
//    if (this->keys_pressed.find('Q') != this->keys_pressed.end()) {
//        this->keys_pressed.erase(this->keys_pressed.find('Q'));
//        this->restart();
//    }
    if (this->inside_key(Qt::Key_Escape))
        this->close();
    if (this->inside_key('Z') || this->inside_key(1071)){
        this->switchmode();
        this->throw_key('Z');
        this->throw_key(1071);
    }

    if (this->levelnomber > this->maxlevels)
        return;

    if (this->inside_key(Qt::Key_Left))
        this->ry += 2.0f;
    if (this->inside_key(Qt::Key_Right))
        this->ry -= 2.0f;
    if (this->inside_key(Qt::Key_Up))
        this->rx += 2.0f;
    if (this->inside_key(Qt::Key_Down))
        this->rx -= 2.0f;
    if (this->rx > 90)
        this->rx = 90;
    if (this->rx < -90)
        this->rx = -90;

    if (this->dead)
        return;
    //WHILE ALIVE

    if ((!this->jumping) && (this->inside_key(Qt::Key_Space))) {
        this->jumping = true;
        this->jumpiterations = 0;
        this->throw_key(Qt::Key_Space);
    }

    GLfloat dy = 0, dx = 0;

    if (!this->jumping) {
        if (this->inside_key(Qt::Key_Control))
            this->z = -.3f;
        else
            this->z = 0;
    }

//    if (this->jumping)
//        return;

    if (this->inside_key('W') || this->inside_key(1062))
        dy -= .05f;
    if (this->inside_key('S') || this->inside_key(1067))
        dy += .05f;
    if (this->inside_key('A') || this->inside_key(1060))
        dx -= .05f;
    if (this->inside_key('D') || this->inside_key(1042))
        dx += .05f;

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
//    qDebug() << this->vx << this->vy;

}

void MainWindow::die() {
    this->dead = true;
    this->life--;
    qDebug() << "Life:" << this->life;
    if (this->life == 0) {
        this->levelnomber = this->maxlevels + 1;
        this->restart();
    }
}

void MainWindow::timeout() {
    this->TIME += this->updatetime;
    if (this->levelnomber > this->maxlevels)
        this->freefall();
    if (this->dead) {
        this->rx = 0;
        this->timetorestart -= this->updatetime;
        if (this->timetorestart <= 0)
            this->restart();
    }
    else
        if ((!this->jumping) && (!this->isfloor(this->x, this->y))) {
            this->z = -.4f;
            this->die();

        }
    this->searchkeys();
    if (this->jumping)
        this->jump();

    this->update();
//    if (this->z < -25.0f)
//        if (this->levelnomber <= this->maxlevels) {
//            this->rx = 0;
//            this->restart();
//         }

    if (this->z < -110.0f) {
        if (this->levelnomber > this->maxlevels)
            this->close();
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



void MainWindow::drawSKY() {
    this->fogg(this->dead);
    GLint p = 100;
//    this->drawQUBE(-p, -p, -p, 2 * p, 2 * p, 2 * p, PIXdrop);
    this->drawNOTHING(-1, 1, 1, this->n + 2, 0, -this->m - 2, PIXsky);
}


void MainWindow::restart() {
    this->timetorestart = 2000;
    this->jumpiterations = 0;
    this->jumping = false;
    this->z = 0;
    this->TIM->stop();
    this->TIME = 0;
    this->dead = false;
    this->x = this->sx + .5f;
    this->y = -this->sy - .5f;
    this->vx = this->vy = 0;
    this->ry = 0;
    if (this->levelnomber > this->maxlevels)
        this->rx = -90;
    this->TIM->setInterval(this->updatetime);
    this->TIM->start();
}

void MainWindow::jump() {
    const GLfloat v = 3.0f, g = 9.8f;
    if (canGO(this->x + this->vx, -this->y))
        this->x += this->vx;
    if (canGO(this->x, -this->y - this->vy))
        this->y += this->vy;
//    if (this->z == 0) {
//        this->jumpiterations = 0;
//    }
    this->jumpiterations++;
    GLfloat t = (GLfloat) (this->jumpiterations * this->updatetime) / 1000;
    this->z = v * t - g * t * t / 2;
    if (this->z <= 0) {
        this->z = 0;
        this->jumping = false;
        if (! isfloor(this->x, this->y)) {
            this->z = -.4f;
            this->die();
        }
        else
            this->jumpiterations = 0;
    }

}

bool MainWindow::isfloor(GLfloat x, GLfloat y) {
//    qDebug() << x - floor(x) << -y - floor(-y) << (this->map[floor(x)][floor(-y)] == '0');
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

void MainWindow::freefall() {
    const GLfloat g = 9.8f;
//    this->ry += .05f;
//    this->dead = true;
//    if (this->z == 0)
//        this->jumpiterations = 0;
    this->jumpiterations++;
    GLfloat t = (GLfloat) this->jumpiterations * this->updatetime / 1000;
//    qDebug() << t << this->z << "->" << -g * t * t / 2;
    this->z = -g * t * t / 2;
    this->x += this->vx;
    this->y += this->vy;
//    qDebug() << this->x;
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev) {
    if (!this->fullscreen)
        return;
    if (! this->mousedetected) {
        this->mouseX = ev->x();
        this->mouseY = ev->y();
        this->mousedetected = true;
    }
    QPoint NP(ev->x(), ev->y());
    this->ry += (this->mouseX - ev->x()) / 100 * this->lat;
    this->rx += (this->mouseY - ev->y()) / 100 * this->lat;
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
}

void MainWindow::switchmode() {
    this->fullscreen = !this->fullscreen;
    setWindowState(this->fullscreen ? Qt::WindowFullScreen : Qt::WindowNoState);
    if (this->fullscreen)
        this->setCursor(QCursor(Qt::BlankCursor));
    else
        this->setCursor(QCursor(Qt::ArrowCursor));

}

void MainWindow::levelclear() {
    this->sx = this->sy = 0;
    this->Hpanel.clear();
    this->Mpanel.clear();
}

void MainWindow::loadlevel() {
    FILE *inp;
    inp = fopen(QString("../Levels/" + (QString::number(this->levelnomber))).toStdString().c_str(), "r");
    if (inp == NULL) {
        qDebug() << "file with map not found. Halting!";
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
            fscanf(inp, "%d %d %d %d %d %d\n", &p.pause, &p.tvis, &p.thid, &p.x, &p.y, &bol);
            p.visible = (bol != 0);
            p.backup = this->map[p.x][p.y];
            this->Hpanel.push_back(p);
        }
        if (ch == 'M') {
            moving p;
            char s[256];
            fscanf(inp, "%d %d %d %s\n", &p.x, &p.y, &p.interval, &s);
            p.param = QString::fromStdString(s);
            this->Mpanel.push_back(p);
        }
    }
//    qDebug() << this->n << this->m;
//    for (int i = 0; i < n; i++)
//        qDebug() << this->map[i];
    char s[256];
    fscanf(inp, "%s\n", &s);
    this->PIXsky = QPixmap("../Textures/" + QString(s));


    fscanf(inp, "%s\n", &s);
    this->PIXwall = QPixmap("../Textures/" + QString(s));
    fscanf(inp, "%s\n", &s);
    this->PIXexit = QPixmap("../Textures/" + QString(s));

    fscanf(inp, "%s\n", &s);
    this->PIXfloor = QPixmap("../Textures/" + QString(s));
    fscanf(inp, "%s\n", &s);
    this->PIXdanger = QPixmap("../Textures/" + QString(s));
    fscanf(inp, "%s\n", &s);
    this->PIXhidden = QPixmap("../Textures/" + QString(s));
    fscanf(inp, "%s\n", &s);
    this->PIXmoving = QPixmap("../Textures/" + QString(s));

    this->PIXwin = QPixmap("../Textures/win.jpg");
    this->PIXlose = QPixmap("../Textures/lose.jpg");

    fclose(inp);
}


void MainWindow::fogg(bool start) {
    if (start)
        glEnable(GL_FOG);
    else
        glDisable(GL_FOG);
}
