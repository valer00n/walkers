#include "settings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings w(&a);
//    QTranslator t;
//    t.load("../Textures/walkers_ru");

//    a.installTranslator(&t);
    w.show();

    return a.exec();
}
