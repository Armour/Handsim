#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T21:22:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bash.cpp \
    reginfo.cpp \
    mccode.cpp \
    memory.cpp \
    mmu.cpp

HEADERS  += mainwindow.h \
    bash.h \
    reginfo.h \
    mccode.h \
    memory.h \
    mmu.h

FORMS    += mainwindow.ui
