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
    windows/customsurvey.cpp \
    windows/dbwindow.cpp \
    windows/flexiblesurvey.cpp \
    windows/mainwindow.cpp

HEADERS  += classes/dbmanager.h \
    classes/filemanager.h \
    classes/questiondata.h \
    windows/customsurvey.h \
    windows/dbwindow.h \
    windows/flexiblesurvey.h \
    windows/mainwindow.h

FORMS    += windows/mainwindow.ui \
    windows/customsurvey.ui \
   windows/flexiblesurvey.ui \
    windows/dbwindow.ui
