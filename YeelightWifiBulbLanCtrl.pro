#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T15:55:24
#
#-------------------------------------------------

QT       += core gui  widgets

TARGET = YeelightWifiBulbLanCtrl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bulb_t.cpp

HEADERS  += \
    mainwindow.h \
    bulb_t.h

FORMS    += mainwindow.ui

QT += network
RC_FILE = app.rc
