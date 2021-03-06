#include "ghost.h"

Ghost::Ghost()
{
    this->history.clear();
}

bool operator < (Hevent a, Hevent b) {
    if (a.time != b.time)
        return (a.time < b.time);
    if (a.x != b.x)
        return (a.x < b.x);
    if (a.y != b.y)
        return (a.y < b.y);
    if (a.z != b.z)
        return (a.z < b.z);
    if (a.ry != b.ry)
        return (a.ry < b.ry);
    if (a.sceneindex != b.sceneindex)
        return (a.sceneindex < b.sceneindex);
    if (a.player != b.player)
        return (a.player < b.player);
    if (a.levelnumber != b.levelnumber)
        return (a.levelnumber < b.levelnumber);
    return true;
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
    if ((Heventindex >= this->history.size()) || (Heventindex < 0)) {
        qDebug() << "Invalid Hevent number";
        Hevent ev;
        ev.levelnumber = -1;
        ev.player = Hstay;
        ev.ry = ev.sceneindex = ev.time = ev.x = ev.y = ev.z = 0;
        return ev;
    }
    else
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
    if (this->history.size() != 0)
        qDebug() << "Something strange in Ghost::clear()";
}

QString getByte(Hevent ev) {
    QString res;
    res = "";
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
    return res;
}

Hevent getEvent(QString inp) {
    Hevent res;
    QString p;
    p = "";
    int i = 0;
    while (inp[i] != ' ') {
        p += inp[i];
        i++;
    }
    res.time = p.toInt();
    i++;
    p = "";

    while (inp[i] != ' ') {
        p += inp[i];
        i++;
    }
    res.x = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        p += inp[i];
        i++;
    }
    res.y = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        p += inp[i];
        i++;
    }
    res.z = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        p += inp[i];
        i++;
    }
    res.ry = p.toDouble();
    i++;
    p = "";

    while (inp[i] != ' ') {
        p += inp[i];
        i++;
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
        p += inp[i];
        i++;
    }
    res.sceneindex = p.toInt();
    i++;
    p = "";

    while (inp[i] != ' ') {
        p += inp[i];
        i++;
    }
    res.levelnumber = p.toInt();
    i++;
    p = "";

    return res;
}
