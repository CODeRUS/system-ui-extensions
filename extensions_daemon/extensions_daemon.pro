QT       += core dbus
QT      -= gui

TARGET = extensionsDaemon
CONFIG   += console link_pkgconfig
PKGCONFIG += gq-gconf

TEMPLATE = app

SOURCES += main.cpp \
    myclass.cpp

target.path = /opt/system-ui-extensions/bin

autorun.files = extensionsDaemon.conf
autorun.path = /etc/init/apps

INSTALLS += target autorun

HEADERS += \
    myclass.h
