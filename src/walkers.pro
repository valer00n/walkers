#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T22:46:07
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = walkers
TEMPLATE = app

LIBS += -L/usr/local/lib -lGLU

SOURCES += \
    mainwindow.cpp \
    main.cpp

HEADERS  += \
    mainwindow.h

OTHER_FILES += \
    TODO.txt

FORMS +=
