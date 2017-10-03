TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sha512.cpp
LIBS += -lws2_32

HEADERS += \
    sha512.h
