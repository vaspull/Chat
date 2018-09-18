TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sha512.cpp \
    applink.c
LIBS += -lws2_32

HEADERS += \
    sha512.h

win32: LIBS += -LC:/OpenSSL-Win32-1-0-2o/lib/ -llibeay32
win32: LIBS += -LC:/OpenSSL-Win32-1-0-2o/lib/ -lssleay32
INCLUDEPATH += C:/OpenSSL-Win32-1-0-2o/include
DEPENDPATH += C:/OpenSSL-Win32-1-0-2o/include
