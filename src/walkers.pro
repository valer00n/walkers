#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T22:46:07
#
#-------------------------------------------------

QT       += core gui opengl

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
    ghost.cpp

HEADERS  += \
    drawgl.h \
    timer.h \
    smdloader.h \
    matrix.h \
    ghost.h

OTHER_FILES += \
    TODO.txt \
    ../Levels/8 \
    ../Levels/7 \
    ../Levels/6 \
    ../Levels/5 \
    ../Levels/4 \
    ../Levels/3 \
    ../Levels/2 \
    ../Levels/1 \
    ../Levels/9 \
    ../Levels/10 \
    ../Levels/11 \
    ../HowTo.txt \
    ../Levels/12 \
    ../Levels/13 \
    ../Param/param.walk \
    ../Param/results.walk \
    ../Param/Best/13 \
    ../Param/Best/12 \
    ../Param/Best/11 \
    ../Param/Best/10 \
    ../Param/Best/9 \
    ../Param/Best/8 \
    ../Param/Best/7 \
    ../Param/Best/6 \
    ../Param/Best/5 \
    ../Param/Best/4 \
    ../Param/Best/3 \
    ../Param/Best/2 \
    ../Param/Best/1

FORMS +=
