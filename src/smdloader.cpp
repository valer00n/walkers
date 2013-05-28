#include "smdloader.h"
#include <fstream>
#include <string>
#include <QGLWidget>

void SMDloader::load(QString path) {
    std::ifstream inp;
    inp.open(path.toStdString().c_str());
    std::string s;
    std::getline(inp, s);

    inp >> s;
    if (s != "nodes") {
        qDebug() << "nodes not found!";
        return;
    }
    inp >> s;
    bool ok;
    QString::fromStdString(s).toInt(&ok);
    while (ok) {
        int a = QString::fromStdString(s).toInt();
        this->model.nodes.resize(std::max(this->model.nodes.size(), a + 1));
        inp >> s;
        inp >> s;
        this->model.nodes[a] = QString::fromStdString(s).toInt();
        inp >> s;
        QString::fromStdString(s).toInt(&ok);
    }

    inp >> s;
    if (s != "skeleton") {
        qDebug() << "nodes not found!";
        return;
    }
    inp >> s;
    inp >> s;
    QString::fromStdString(s).toInt(&ok);
    while (ok) {
        int a = QString::fromStdString(s).toInt();
        int b;
        this->model.skeleton.resize(std::max(this->model.nodes.size(), a + 1));
        inp >> s;
        b = QString::fromStdString(s).toInt();
        this->model.skeleton[a].x = b;
        inp >> s;
        b = QString::fromStdString(s).toInt();
        this->model.skeleton[a].y = b;
        inp >> s;
        b = QString::fromStdString(s).toInt();
        this->model.skeleton[a].z = b;
        inp >> s;
        b = QString::fromStdString(s).toInt();
        this->model.skeleton[a].rotx = b;
        inp >> s;
        b = QString::fromStdString(s).toInt();
        this->model.skeleton[a].roty = b;
        inp >> s;
        b = QString::fromStdString(s).toInt();
        this->model.skeleton[a].rotz = b;

        inp >> s;
        QString::fromStdString(s).toInt(&ok);
    }

    inp >> s;
    inp >> s;
    while (s != "end") {
        triangle ntr;
        ntr.PIX = QPixmap(QString::fromStdString(s));
        for (int i = 0; i < 3; i++)
            inp >> ntr.nodes[i].anc >> ntr.nodes[i].x >> ntr.nodes[i].y >> ntr.nodes[i].z >> ntr.nodes[i].nx >> ntr.nodes[i].ny >> ntr.nodes[i].nz >> ntr.nodes[i].s >> ntr.nodes[i].t;
        this->model.triangles.push_back(ntr);
        inp >> s;
    }

}

void SMDloader::draw() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        for (int i = 0; i < this->model.triangles.size(); i++) {
            GLuint s = this->parent->bindTexture(this->model.triangles[i].PIX, GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, s);
            for (int j = 0; j < 3; j++) {
//                glTexCoord2f(this->model.triangles[i].nodes[j].s, this->model.triangles[i].nodes[j].t);
                glVertex3f(this->model.triangles[i].nodes[j].x, this->model.triangles[i].nodes[j].y, this->model.triangles[i].nodes[j].z);
            }

        }
    glEnd();
}

SMDloader::SMDloader(QGLWidget *par) {
    this->parent = par;
}
