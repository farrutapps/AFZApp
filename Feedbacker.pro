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
        mainwindow.cpp \
    customsurvey.cpp \
    flexiblesurvey.cpp \
    questiondata.cpp \
    dbmanager.cpp \
    filemanager.cpp

HEADERS  += mainwindow.h \
    customsurvey.h \
    flexiblesurvey.h \
    questiondata.h \
    dbmanager.h \
    filemanager.h

FORMS    += mainwindow.ui \
    customsurvey.ui \
    flexiblesurvey.ui
