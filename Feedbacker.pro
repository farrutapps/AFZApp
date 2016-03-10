#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T10:51:07
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Feedbacker
TEMPLATE = app


SOURCES += main.cpp\
    classes/dbmanager.cpp \
    classes/filemanager.cpp \
    classes/questiondata.cpp \
    windows/dbwindow.cpp \
    windows/flexiblesurvey.cpp \
    windows/mainwindow.cpp \
    windows/calcwindow.cpp \
    windows/datainputpopup.cpp

HEADERS  += classes/dbmanager.h \
    classes/filemanager.h \
    classes/questiondata.h \
    windows/dbwindow.h \
    windows/flexiblesurvey.h \
    windows/mainwindow.h \
    windows/calcwindow.h \
    windows/datainputpopup.h

FORMS    += windows/mainwindow.ui \
   windows/flexiblesurvey.ui \
    windows/dbwindow.ui \
    windows/calcwindow.ui \
    windows/datainputpopup.ui
