//#include "drawgl.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    GLPainter w(20.0);
//    w.setWindowTitle("Walkers");
//    w.show();
    
//    return a.exec();
//}

#include "settings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings w;
    w.show();

    return a.exec();
}
