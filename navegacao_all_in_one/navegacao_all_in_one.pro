QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
           Navegar.cpp

HEADERS += \
    Navegar.h \
    minhaMatriz.h
