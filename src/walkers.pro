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
    ../Param/Best/13.bst \
    ../Param/Best/12.bst \
    ../Param/Best/11.bst \
    ../Param/Best/10.bst \
    ../Param/Best/9.bst \
    ../Param/Best/8.bst \
    ../Param/Best/7.bst \
    ../Param/Best/6.bst \
    ../Param/Best/5.bst \
    ../Param/Best/4.bst \
    ../Param/Best/3.bst \
    ../Param/Best/2.bst \
    ../Param/Best/1.bst

FORMS +=
