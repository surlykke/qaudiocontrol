#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T18:16:57
#
#-------------------------------------------------

QT       += core gui widgets dbus

TARGET = qaudiocontrol
TEMPLATE = app

SOURCES += main.cpp\
    mixer.cpp \
    paproxy.cpp \
    deviceview.cpp \
    device_proxy.cpp

HEADERS  += \
    mixer.h \
    paproxy.h \
    deviceview.h \
    device_proxy.h \
    dbus_types.h


FORMS    += \
    mixer.ui \
    test.ui \
    deviceview.ui
