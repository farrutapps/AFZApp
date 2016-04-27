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
    model/dbmanager.cpp \
    model/filemanager.cpp \
    view/dbwindow.cpp \
    view/flexiblesurvey.cpp \
    view/mainwindow.cpp \
    view/calcwindow.cpp \
    view/datainputpopup.cpp \
    view/preferenceswindow.cpp \
    model/question.cpp \
    model/survey.cpp \
    model/import.cpp

HEADERS  += model/dbmanager.h \
    model/filemanager.h \
    view/dbwindow.h \
    view/flexiblesurvey.h \
    view/mainwindow.h \
    view/calcwindow.h \
    view/datainputpopup.h \
    view/preferenceswindow.h \
    model/question.h \
    model/survey.h \
    model/constants.h \
    model/import.h

FORMS    += view/mainwindow.ui \
   view/flexiblesurvey.ui \
    view/dbwindow.ui \
    view/calcwindow.ui \
    view/datainputpopup.ui \
    view/preferenceswindow.ui
