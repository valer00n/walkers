#include "ghost.h"

Ghost::Ghost()
{
    this->history.clear();
}

void Ghost::load(QString path){
    this->clear();
    std::ifstream in;
    in.open(path.toStdString().c_str());
    if (! in.is_open())
    {
        std::ofstream out;
        out.open(path.toStdString().c_str());
        out <<  "0";
        out.close();
        in.open(path.toStdString().c_str());
    }
    int n;
    in >> n;
    this->history.resize(n);
    for (int i = 0; i < n; i++) {
        Hevent ev;
        int player;
        in >> ev.time >> ev.x >> ev.y >> ev.z >> ev.ry >> player >> ev.sceneindex >> ev.levelnumber;
        switch (player) {
            case 0:
                ev.player = Hstay;
            break;
            case 1:
                ev.player = Hwalk;
            break;
            case 2:
                ev.player = Hjump;
            break;
            case 3:
                ev.player = Hcrouch;
            break;
            case 4:
                ev.player = Hdead;
            break;
        }
        this->history[i] = ev;
    }
    in.close();
}
void Ghost::save(QString path){
    std::ofstream out;
    out.open(path.toStdString().c_str());
    out << this->gethistorylength() << "\n";
    for (int i = 0; i < this->gethistorylength(); i++) {
        Hevent ev = this->getHevent(i);
        out << ev.time << " " << ev.x << " " << ev.y << " " << ev.z << " " << ev.ry << " " << (int) ev.player << " " << ev.sceneindex << " " << ev.levelnumber << "\n";
    }
    out.close();

}

Hevent Ghost::getHevent(int Heventindex){
    if (Heventindex >= this->history.size())
        qDebug() << "Invalid Hevent number";
    return this->history[Heventindex];
}
int Ghost::gethistorylength(){
    return this->history.size();
}
void Ghost::pushHevent(Hevent ev){
    this->history.push_back(ev);
}
void Ghost::pushHevent(int time, float x, float y, float z, float ry, Hstatus player, int sceneindex, int levelnumber) {
    Hevent ev;
    ev.time = time;
    ev.x = x;
    ev.y = y;
    ev.z = z;
    ev.ry = ry;
    ev.player = player;
    ev.sceneindex = sceneindex;
    ev.levelnumber = levelnumber;
    this->pushHevent(ev);
}

void Ghost::clear() {
    this->history.clear();
}

QByteArray getByte(Hevent ev) {
    QString res;
    res = "0 ";
    res  += QString::number(ev.time);
    res += " ";
    res += QString::number(ev.x);
    res += " ";
    res += QString::number(ev.y);
    res += " ";
    res += QString::number(ev.z);
    res += " ";
    res += QString::number(ev.ry);
    res += " ";
    res += QString::number((int) ev.player);
    res += " ";
    res += QString::number(ev.sceneindex);
    res += " ";
    res += QString::number(ev.levelnumber);
    res += " ";
    res += "\0";
    return res.toLocal8Bit();
}

Hevent getEvent(QByteArray bit) {
    Hevent res;
    QString inp = QString::fromLocal8Bit(bit);
    QString p;
    int i = 2;
    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.time = p.toInt();
    i++;
    p = "";

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.x = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.y = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.z = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.ry = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    int player = p.toInt();
    i++;
    p = "";

    switch (player) {
        case 0:
            res.player = Hstay;
        break;
        case 1:
            res.player = Hwalk;
        break;
        case 2:
            res.player = Hjump;
        break;
        case 3:
            res.player = Hcrouch;
        break;
        case 4:
            res.player = Hdead;
        break;
    }

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.sceneindex = p.toInt();
    i++;
    p = "";

    while (inp[i] != ' ') {
        i++;
        p += inp[i];
    }
    res.levelnumber = p.toInt();
    i++;
    p = "";

    return res;
}
