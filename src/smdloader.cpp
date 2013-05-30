#include "smdloader.h"
#include <fstream>
#include <string>
#include <QGLWidget>


typedef struct {
    Mat mat;
} mat;

typedef struct {
    Vertex vert;
} vert;

void SMDloader::setalpha(GLfloat alpha) {
    this->alpha = alpha;
}

void SMDloader::setstay(bool stay) {
    this->stay = stay;
}

GLint SMDloader::getanimationlength() {
    return this->animation.skeleton.size();
}

GLfloat SMDloader::getalpha() {
    return this->alpha;
}


void SMDloader::setpatent(QGLWidget *parent) {
    this->parent = parent;
}

bool SMDloader::getstay() {
    return this->stay;
}

void SMDloader::loadmodel(QString name) {
    std::ifstream inp;
    inp.open(QString(this->path + "/" + name).toStdString().c_str());
    std::string s;
    std::getline(inp, s);

    inp >> s;
    if (s != "nodes") {
        qDebug() << "nodes not found!";
        qDebug() << name;
        return;
    }
    inp >> s;
    bool ok;
    QString::fromStdString(s).toInt(&ok);
    while (ok) {
        int a = QString::fromStdString(s).toInt();
        this->model.nodes.resize(std::max(this->model.nodes.size(), a + 1));
        char c;
        inp >> c;
        while (c != '"')
            inp >> c;
        inp >> c;
        while (c != '"')
            inp >> c;
        inp >> s;
        this->model.nodes[a] = QString::fromStdString(s).toInt();
        inp >> s;
        QString::fromStdString(s).toInt(&ok);
    }

//    qDebug() << QString::fromStdString(s);
    inp >> s;
    if (s != "skeleton") {
        qDebug() << "nodes not found!";
        qDebug() << name;
        return;
    }
    inp >> s;
    while (s != "end") {
        inp >> s;
        inp >> s;
        QVector <node> skel;
        QString::fromStdString(s).toInt(&ok);
        while (ok) {
            int a = QString::fromStdString(s).toInt();
            skel.resize(std::max(this->model.nodes.size(), a + 1));
            inp >> skel[a].x >> skel[a].y >> skel[a].z >> skel[a].rotx >> skel[a].roty >> skel[a].rotz;
            inp >> s;
            QString::fromStdString(s).toInt(&ok);
        }

        this->model.skeleton.push_back(skel);

    }


    inp >> s;
    if (s != "triangles") {
        qDebug() << "Triangles not found!";
        qDebug() << name;
        return;
    }
    inp >> s;
    while (s != "end") {
        triangle ntr;
        ntr.PIX = QPixmap(this->path + "/" + QString::fromStdString(s));
        for (int i = 0; i < 3; i++)
            inp >> ntr.nodes[i].anc >> ntr.nodes[i].x >> ntr.nodes[i].y >> ntr.nodes[i].z >> ntr.nodes[i].nx >> ntr.nodes[i].ny >> ntr.nodes[i].nz >> ntr.nodes[i].s >> ntr.nodes[i].t;
        this->model.triangles.push_back(ntr);
        inp >> s;
    }

    inp.close();

    //-----------------------------------------------
    int sceneindex = 0;
    QVector <vert> skel(this->model.nodes.size());
    QVector <mat> absolute(this->model.nodes.size());
    for (int i = 0; i < this->model.nodes.size(); i++) {
        Vertex ver;
        ver[0] = ver[1] = ver[2] = 0;
        Mat tmp1, tmp2, tmp3;
        XRot(-this->model.skeleton[sceneindex][i].rotx, tmp1);
        YRot(-this->model.skeleton[sceneindex][i].roty, tmp2);
        ZRot(-this->model.skeleton[sceneindex][i].rotz, tmp3);
        ConcatMatrix(tmp2, tmp1);
        ConcatMatrix(tmp3, tmp1);
        tmp1[3][0] = this->model.skeleton[sceneindex][i].x;
        tmp1[3][1] = this->model.skeleton[sceneindex][i].y;
        tmp1[3][2] = this->model.skeleton[sceneindex][i].z;
        if (this->model.nodes[i] != -1)
            ConcatMatrix(absolute[this->model.nodes[i]].mat, tmp1);
        else {
//            tmp1[3][0] = tmp1[3][1] = tmp1[3][2] = 0;
        }
        CopyMat(tmp1, absolute[i].mat);
        ApplyMatrix(skel[i].vert, absolute[i].mat);
    }



    for (int i = 0; i < this->model.triangles.size(); i++)
        for (int j = 0; j < 3; j++) {
            Vertex v;
            v[0] = this->model.triangles[i].nodes[j].x;
            v[1] = this->model.triangles[i].nodes[j].y;
            v[2] = this->model.triangles[i].nodes[j].z;
            InvApplyMatrix(v, absolute[this->model.triangles[i].nodes[j].anc].mat);
            this->model.triangles[i].nodes[j].x = v[0];
            this->model.triangles[i].nodes[j].y = v[1];
            this->model.triangles[i].nodes[j].z = v[2];
        }

}

void SMDloader::loadanimation(QString name) {
    std::ifstream inp;
    inp.open(QString(this->path + "/" + name).toStdString().c_str());
    std::string s;
    std::getline(inp, s);

    inp >> s;
    if (s != "nodes") {
        qDebug() << "nodes not found!";
        qDebug() << name;
        return;
    }
    inp >> s;
    bool ok;
    QString::fromStdString(s).toInt(&ok);
    while (ok) {
        int a = QString::fromStdString(s).toInt();
        this->animation.nodes.resize(std::max(this->animation.nodes.size(), a + 1));
        char c;
        inp >> c;
        while (c != '"')
            inp >> c;
        inp >> c;
        while (c != '"')
            inp >> c;
        inp >> s;
        this->animation.nodes[a] = QString::fromStdString(s).toInt();
        if (this->animation.nodes[a] > a)
            qDebug() << "!";
        inp >> s;
        QString::fromStdString(s).toInt(&ok);
    }

//    qDebug() << QString::fromStdString(s);
    inp >> s;
    if (s != "skeleton") {
        qDebug() << "nodes not found!";
        return;
    }
    inp >> s;
    while (s != "end") {
        inp >> s;
        inp >> s;
        QVector <node> skel;
        QString::fromStdString(s).toInt(&ok);
        while (ok) {
            int a = QString::fromStdString(s).toInt();
            skel.resize(std::max(this->animation.nodes.size(), a + 1));
            inp >> skel[a].x >> skel[a].y >> skel[a].z >> skel[a].rotx >> skel[a].roty >> skel[a].rotz;
            inp >> s;
            QString::fromStdString(s).toInt(&ok);
        }

        this->animation.skeleton.push_back(skel);

    }

   inp.close();
}



void SMDloader::draw(int sceneindex) {
//    glBegin(GL_LINES);
//        glColor3f(.0f, 1.0f, 1.0f);
//        glVertex3f(.0f, .0f, .0f);
//        glVertex3f(100.0f, .0f, .0f);
//        glColor3f(.0f, 1.0f, .0f);
//        glVertex3f(.0f, .0f, .0f);
//        glVertex3f(.0f, 100.0f, .0f);
//        glColor3f(.0f, .0f, 1.0f);
//        glVertex3f(.0f, .0f, .0f);
//        glVertex3f(.0f, .0f, 100.0f);
//    glEnd();


    QVector <vert> skel(this->model.nodes.size());
    QVector <mat> absolute(this->model.nodes.size());
    for (int i = 0; i < this->animation.nodes.size(); i++) {
        Vertex ver;
        ver[0] = ver[1] = ver[2] = 0;
        Mat tmp1, tmp2, tmp3;
        XRot(-this->animation.skeleton[sceneindex][i].rotx, tmp1);
        YRot(-this->animation.skeleton[sceneindex][i].roty, tmp2);
        ZRot(-this->animation.skeleton[sceneindex][i].rotz, tmp3);
        ConcatMatrix(tmp2, tmp1);
        ConcatMatrix(tmp3, tmp1);
        tmp1[3][0] = this->animation.skeleton[sceneindex][i].x;
        tmp1[3][1] = this->animation.skeleton[sceneindex][i].y;
        tmp1[3][2] = this->animation.skeleton[sceneindex][i].z;
        if (this->animation.nodes[i] != -1)
            ConcatMatrix(absolute[this->animation.nodes[i]].mat, tmp1);
        else {
            if (this->stay)
               tmp1[3][0] = tmp1[3][1] = tmp1[3][2] = 0;
        }
        CopyMat(tmp1, absolute[i].mat);
        ApplyMatrix(skel[i].vert, absolute[i].mat);
    }

    GLuint s;
//    for (int i = 0; i < this->animation.nodes.size(); i++) {
//        glPointSize(3.0f);
//        glColor3f(1.0f, 1.0f, 1.0f);
//        glBegin(GL_POINTS);
//            glVertex3f(skel[i].vert[0], skel[i].vert[1], skel[i].vert[2]);
//        glEnd();
//        if (this->animation.nodes[i] != -1) {
//            glColor3f(1.0f, .0f, .0f);
//            glLineWidth(2.0f);
//            glBegin(GL_LINES);
//                glVertex3f(skel[i].vert[0], skel[i].vert[1], skel[i].vert[2]);
//                glVertex3f(skel[this->animation.nodes[i]].vert[0], skel[this->animation.nodes[i]].vert[1], skel[this->animation.nodes[i]].vert[2]);
//            glEnd();
//        }
//    }
    glEnable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, this->alpha);
    for (int i = 0; i < this->model.triangles.size(); i++) {
        s = this->parent->bindTexture(this->model.triangles[i].PIX, GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, s);
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++) {
            Vertex v;
            v[0] = this->model.triangles[i].nodes[j].x;
            v[1] = this->model.triangles[i].nodes[j].y;
            v[2] = this->model.triangles[i].nodes[j].z;
            ApplyMatrix(v, absolute[this->model.triangles[i].nodes[j].anc].mat);
            glTexCoord2f(this->model.triangles[i].nodes[j].s, this->model.triangles[i].nodes[j].t);
            glVertex3f(v[0], v[1], v[2]);
        }
        glEnd();
    }

    glDisable(GL_BLEND);

}

SMDloader::SMDloader(QGLWidget *par) {
    this->parent = par;
    this->alpha = 1.0f;
}

void SMDloader::draw_skeleton(int sceneindex) {
    QVector <vert> skel(this->model.nodes.size());
    QVector <mat> absolute(this->model.nodes.size());
    for (int i = 0; i < this->animation.nodes.size(); i++) {
        Vertex ver;
        ver[0] = ver[1] = ver[2] = 0;
        Mat tmp1, tmp2, tmp3;
        XRot(-this->animation.skeleton[sceneindex][i].rotx, tmp1);
        YRot(-this->animation.skeleton[sceneindex][i].roty, tmp2);
        ZRot(-this->animation.skeleton[sceneindex][i].rotz, tmp3);
        ConcatMatrix(tmp2, tmp1);
        ConcatMatrix(tmp3, tmp1);
        tmp1[3][0] = this->animation.skeleton[sceneindex][i].x;
        tmp1[3][1] = this->animation.skeleton[sceneindex][i].y;
        tmp1[3][2] = this->animation.skeleton[sceneindex][i].z;
        if (this->animation.nodes[i] != -1)
            ConcatMatrix(absolute[this->animation.nodes[i]].mat, tmp1);
        else {
            if (this->stay)
               tmp1[3][0] = tmp1[3][1] = tmp1[3][2] = 0;
        }
        CopyMat(tmp1, absolute[i].mat);
        ApplyMatrix(skel[i].vert, absolute[i].mat);
    }

    for (int i = 0; i < this->animation.nodes.size(); i++) {
        glPointSize(3.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
            glVertex3f(skel[i].vert[0], skel[i].vert[1], skel[i].vert[2]);
        glEnd();
        if (this->animation.nodes[i] != -1) {
            glColor3f(1.0f, .0f, .0f);
            glLineWidth(2.0f);
            glBegin(GL_LINES);
                glVertex3f(skel[i].vert[0], skel[i].vert[1], skel[i].vert[2]);
                glVertex3f(skel[this->animation.nodes[i]].vert[0], skel[this->animation.nodes[i]].vert[1], skel[this->animation.nodes[i]].vert[2]);
            glEnd();
        }
    }


}

void SMDloader::setpath(QString s) {
    this->path = s;
}
