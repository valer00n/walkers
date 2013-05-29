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
    matrix.cpp

HEADERS  += \
    drawgl.h \
    timer.h \
    smdloader.h \
    matrix.h

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
    ../Param/results.walk

FORMS +=
