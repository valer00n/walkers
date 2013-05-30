#include "ghost.h"

Ghost::Ghost()
{
    this->history.clear();
}

void Ghost::load(QString path){
    this->clear();
    std::ifstream in;
    in.open(path.toStdString().c_str());
    int n;
    in >> n;
    this->history.resize(n);
    for (int i = 0; i < n; i++) {
        Hevent ev;
        int player;
        in >> ev.time >> ev.x >> ev.y >> ev.z >> ev.ry >> player >> ev.sceneindex;
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
        out << ev.time << " " << ev.x << " " << ev.y << " " << ev.z << " " << ev.ry << " " << (int) ev.player << " " << ev.sceneindex << "\n";
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
void Ghost::pushHevent(int time, float x, float y, float z, float ry, Hstatus player, int sceneindex) {
    Hevent ev;
    ev.time = time;
    ev.x = x;
    ev.y = y;
    ev.z = z;
    ev.ry = ry;
    ev.player = player;
    ev.sceneindex = sceneindex;
    this->pushHevent(ev);
}

void Ghost::clear() {
    this->history.clear();
}
