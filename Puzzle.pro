#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T18:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puzzle
TEMPLATE = app


SOURCES += main.cpp\
    puzzlesizewidget.cpp \
    puzzlepiece.cpp \
    gamelogic.cpp \
    setupdialog.cpp

HEADERS  += \
    puzzlesizewidget.h \
    puzzlepiece.h \
    gamelogic.h \
    setupdialog.h

FORMS    += \
    setupdialog.ui

RESOURCES += \
    res.qrc

