#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T22:46:07
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = walkers
TEMPLATE = app

LIBS += -L/usr/local/lib

unix: !macx: LIBS += -lGLU

SOURCES += \
    main.cpp \
    drawgl.cpp \
    timer.cpp \
    smdloader.cpp \
    matrix.cpp \
    ghost.cpp \
    settings.cpp \
    socket.cpp \
    server.cpp \
    server_socket.cpp \
    game_server.cpp

HEADERS  += \
    drawgl.h \
    timer.h \
    smdloader.h \
    matrix.h \
    ghost.h \
    settings.h \
    socket.h \
    server.h \
    server_socket.h \
    game_server.h

OTHER_FILES += \
    TODO.txt \
    ../Levels/8.lvl \
    ../Levels/7.lvl \
    ../Levels/6.lvl \
    ../Levels/5.lvl \
    ../Levels/4.lvl \
    ../Levels/3.lvl \
    ../Levels/2.lvl \
    ../Levels/9.lvl \
    ../Levels/10.lvl \
    ../Levels/11.lvl \
    ../Levels/12.lvl \
    ../Levels/13.lvl \
    ../Levels/1.lvl \
    walkers.pro.user


FORMS += \
    settings.ui \
    game_server.ui
