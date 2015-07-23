#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T11:57:15
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phoneNumber
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    json.cpp

HEADERS  += dialog.h \
    json.h

FORMS    += dialog.ui
