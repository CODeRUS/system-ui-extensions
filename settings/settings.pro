CONFIG += plugin gui meegotouch-boostable meegotouch debug

QT += core dbus
CONFIG += console link_pkgconfig

PKGCONFIG += duicontrolpanel meegotouch-controlpanel

INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/duicontrolpanel

TEMPLATE = lib
TARGET = statusmenuextensionsapplet

settingsdesktop.path = /usr/lib/duicontrolpanel
settingsdesktop.files = statusmenuextensions.desktop

target.path = /usr/lib/duicontrolpanel/applets
INSTALLS += target settingsdesktop

SOURCES += \
    main.cpp \
    settingsui.cpp \
    toolswidget.cpp \
    MImageWidgetEx.cpp \
    brief.cpp \
    brightnesswidget.cpp
HEADERS += \
    settingsui.h \
    toolswidget.h \
    MImageWidgetEx.h \
    main.h \
    brief.h \
    brightnesswidget.h

OTHER_FILES += \
    statusmenuextensions.desktop
