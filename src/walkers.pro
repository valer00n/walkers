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
    ../Results/results.walk \
    ../Results/Best/13.bst \
    ../Results/Best/12.bst \
    ../Results/Best/11.bst \
    ../Results/Best/10.bst \
    ../Results/Best/9.bst \
    ../Results/Best/8.bst \
    ../Results/Best/7.bst \
    ../Results/Best/6.bst \
    ../Results/Best/5.bst \
    ../Results/Best/4.bst \
    ../Results/Best/3.bst \
    ../Results/Best/2.bst \
    ../Results/Best/1.bst

FORMS +=
