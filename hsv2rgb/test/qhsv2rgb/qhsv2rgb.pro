#-------------------------------------------------
#
# Project created by QtCreator 2013-12-25T11:49:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qhsv2rgb
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    ../../src/hsv2rgb.c

HEADERS  += dialog.h \
    ../../src/hsv2rgb.h

FORMS    += dialog.ui

INCLUDEPATH += ../../src
