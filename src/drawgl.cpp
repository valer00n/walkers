#include "drawgl.h"
#include <QDebug>
#include <cstdio>
#include <cmath>
#include <QDir>
#include <fstream>
#include <QPainter>

GLPainter::GLPainter(QWidget *parent)
    : QGLWidget(parent)
{
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
    this->restime = 3000;
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
    in.open("../param.walk");
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-this->rx, 1.0f, .0f, .0f);
    glRotatef(-this->ry, .0f, 1.0f, .0f);
    glTranslatef(-this->x, -.5f - this->z, -this->y);
    GLfloat p = 100;
    if (this->levelnomber == 0) {
        this->mainmenu();
    }
    else
    if (this->levelnomber <= this->maxlevels) {
        this->drawSKY();
        this->drawmap();
        this->drawinfo();
    }
    else
        this->drawNOTHING(-50, -100, -50, 100, 0, 100, this->PIXwin);
}

GLfloat fabs(GLfloat a) {
    if (a < 0)
        return -a;
    else
        return a;
}

void GLPainter::keyPressEvent(QKeyEvent *ev) {
    this->keys_pressed.insert(ev->key());
}

void GLPainter::keyReleaseEvent(QKeyEvent *ev) {
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
                    if (std::min(this->z + 0.15f, P1) >= std::max(this->z - 0.5f, P2))
                        die();
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
    if (this->levelnomber == 0) {
        this->timerT->globaltime = 0;
        this->loadparam();
    }
    this->timerT->TIM->stop();
    this->levelnomber++;
    if (this->levelnomber > this->maxlevels + 1)
        this->levelnomber = 0;
    this->levelclear();
    if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0))
        this->loadlevel();
    this->restart();
    this->timerT->TIM->start();
}

void GLPainter::searchkeys() {
    if (this->menuopened) {
        if (this->inside_key('+')) {
            this->life++;
            this->throw_key('+');
        }
        if (this->inside_key('-')) {
            this->throw_key('-');
            this->finn();
            return;
        }
    }
    if (this->inside_key(Qt::Key_Escape)) {
        if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0)) {
            this->menuopened = !this->menuopened;
            this->element = 0;
        }
        else
            if ((!this->FFall) && (this->levelnomber == 0))
                this->close();
        this->throw_key(Qt::Key_Escape);
    }
    if (this->inside_key(Qt::Key_Return)) {
        this->throw_key(Qt::Key_Return);
        if ((this->levelnomber <= this->maxlevels) && (this->levelnomber != 0)) {
            if (this->menuopened)
                 this->close();
        }
        if (this->levelnomber == 0) {
            this->FFall = true;
            return;
        }
    }
    if ((this->inside_key('Z')) || (this->inside_key(1071))){
        this->switchmode();
        this->throw_key('Z');
        this->throw_key(1071);
    }

    if (this->menuopened)
        return;
    if (this->dead)
        return;
    if (this->levelnomber > this->maxlevels)
        return;
    if (this->levelnomber == 0)
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
    }

    GLfloat dy = 0, dx = 0;

    if (!this->jumping) {
        if (this->duck = this->inside_key(Qt::Key_Control))
            this->z = -.3f;
        else
            this->z = 0;
    }

    if (this->inside_key('W') || this->inside_key(1062))
        dy -= .05f;
    if (this->inside_key('S') || this->inside_key(1067))
        dy += .05f;
    if (this->inside_key('A') || this->inside_key(1060))
        dx -= .05f;
    if (this->inside_key('D') || this->inside_key(1042))
        dx += .05f;
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
    this->timerT->globaltime += this->updatetime;
    this->searchkeys();
    if ((this->levelnomber > this->maxlevels) || this->FFall)
        this->freefall();
//    if (this->levelnomber == 0)
//        this->freefall();
    if (this->dead) {
                this->rx = 0;
                if (!this->menuopened)
                    this->timetorestart -= this->updatetime;
                if (this->timetorestart <= 0) {
                    this->life++;
                    this->restart();
                }
        }
    else {
        if (!this->menuopened)
            this->TIME += this->updatetime;
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
    if (this->levelnomber == 0)
        return;

    if (! this->mousedetected) {
        this->mouseX = ev->x();
        this->mouseY = ev->y();
        this->mousedetected = true;
    }
    QPoint NP(ev->x(), ev->y());
//    qDebug() << (this->mouseX - ev->x()) / 100 * this->lat << (this->mouseY - ev->y()) / 100 * this->lat;
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

void GLPainter::switchmode() {
    this->fullscreen = !this->fullscreen;
    setWindowState(this->fullscreen ? Qt::WindowFullScreen : Qt::WindowNoState);
    if (this->fullscreen)
        this->setCursor(QCursor(Qt::BlankCursor));
    else
        this->setCursor(QCursor(Qt::ArrowCursor));

}

void GLPainter::levelclear() {
    this->sx = this->sy = 0;
    this->Hpanel.clear();
    this->Mpanel.clear();
    this->Fpanel.clear();
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
            fscanf(inp, "%f %f %f %f %c %d %d %f %d %f %f %f\n", &p.x, &p.y, &p.z, &p.r, &p.direction, &p.interval, &p.rest, &p.dist, &p.pause, &p.stratchX, &p.stratchY, &p.stratchZ);
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
    br.setColor(QColor("black"));
    p.setBrush(br);
    int a = 0;
    int b = 0;
    for (int i = 0; i < mes.size(); i++) {
        a = std::max(a, p.fontMetrics().width(mes[i]));
        b = std::max(b, p.fontMetrics().height());
    }
    qDebug() << a << b;
    int dx = (w - a) / 2;
    int dy = (h - b * mes.size()) / 2;
    qDebug() << dx << dy;
//    dy = 0;
//    p.drawText(40, 40, "ASDD);
    for (int i = 0; i < mes.size(); i++)
        p.drawText(dx, dy + b * (i), mes[i]);
    p.end();
    return *menu;
}

void GLPainter::loadstaticTEX() {
    this->PIXwin = QPixmap("../Textures/win.jpg");
    this->PIXhole = QPixmap("../Textures/hole.png");
    this->PIXfireball = QPixmap("../Textures/fireball.jpg");
    QVector <QString> mes (10);
    mes[0] = "WASD   :: move";
    mes[1] = "arrows :: rotate camera";
    mes[2] = "Space  :: jump";
    mes[3] = "Ctrl   :: duck";
    mes[4] = "Esc    :: pause";
    mes[5] = "Z      :: fullscreen";
    mes[6] = "Reach finish...";
    mes[7] = "<Press ENTER to Start>";
    mes[8] = "         or";
    mes[9] = "<Press Esc to exit>";
    this->PIXmenu = this->genpix(1024, 1024, 40, mes);

    mes.resize(3);
    mes[0] = "You won!";
    mes[1] = "Thank you for playing Walkers!";
    mes[2] = "                    buy danpol";
    this->PIXwin = this->genpix(1024, 1024, 40, mes);

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
        glVertex2f (this->dw + 200, -this->dh + this->height() - 100);
        glVertex2f (this->dw + 200, -this->dh + this->height());
      glEnd();
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);      
      renderText(this->dw + 5,this->dh + 25, "Level: " + QString::number(this->levelnomber) + "/" + QString::number(this->maxlevels));
      renderText(this->dw + 5,this->dh + 45, "Extra lifes taken: " + QString::number(this->life));
      renderText(this->dw + 5,this->dh + 65, "Time: " + QString::number(this->timerT->globaltime / 1000) + "s.");
      }
      else {
       glColor4f(std::min((GLfloat) this->timetorestart / this->restime + 0.05, 1.0d), 0.0f, 0.0f, 0.8f);
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
    this->drawNOTHING(-50, -100, -50, 100, 0, 100, this->PIXmenu);
}