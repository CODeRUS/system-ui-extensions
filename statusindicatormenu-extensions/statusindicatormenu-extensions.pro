TEMPLATE      = lib
QT += dbus network
CONFIG       += plugin gui meegotouch link_pkgconfig iodata cellular-qt dbus mobility

MOBILITY += connectivity

TARGET        = statusindicatormenu-extensions

PKGCONFIG += gq-gconf \
             accounts-qt \
	     contextprovider-1.0

LIBS += -ltelepathy-qt4
LIBS += -lcellular-qt
LIBS += -lcreds
LIBS += -lX11

INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/cellular-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/telepathy-1.0
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/accounts-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/meegotouch
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/system-ui/statusindicatormenu
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/contextprovider

HEADERS += \
    MToolBGConn.h \
    MToolBluetooth.h \
    MToolBrightness.h \
    MToolCellular.h \
    MToolFlashlight.h \
    MToolPSM.h \
    MToolRadio.h \
    MToolReboot.h \
    MToolUSB.h \
    MWidgetTools.h \
    plugin.h \
    controller.h \
    MWidgetAvialability.h \
    MWidgetBrightness.h \
    PropertyAdaptor.h \
    AccountWrapper.h \
    MToolGLOL.h \
    MToolWidget.h

SOURCES += \
    MToolBGConn.cpp \
    MToolBluetooth.cpp \
    MToolBrightness.cpp \
    MToolCellular.cpp \
    MToolFlashlight.cpp \
    MToolPSM.cpp \
    MToolRadio.cpp \
    MToolReboot.cpp \
    MToolUSB.cpp \
    MWidgetTools.cpp \
    plugin.cpp \
    controller.cpp \
    MWidgetBrightness.cpp \
    MWidgetAvialability.cpp \
    AccountWrapper.cpp \
    PropertyAdaptor.cpp \
    MToolGLOL.cpp

target.path = /usr/lib/meegotouch/applicationextensions

png.files = icons/icon-extensions-background.png \
            icons/icon-extensions-power.png \
            icons/icon-extensions-power-unloaded.png \
            icons/icon-extensions-glol-portait.png \
            icons/icon-extensions-glol-landscape.png \
            icons/icon-extensions-glol-auto.png \
            icons/icon-extensions-background-off.png \
            icons/icon-extensions-background-on.png \
            icons/icon-extensions-bluetooth-off.png \
            icons/icon-extensions-bluetooth-on.png \
            icons/icon-extensions-bluetooth-visible.png \
            icons/icon-extensions-brightness-max.png \
            icons/icon-extensions-brightness-med.png \
            icons/icon-extensions-brightness-min.png \
            icons/icon-extensions-cellular-2g.png \
            icons/icon-extensions-cellular-3g.png \
            icons/icon-extensions-cellular-dual.png \
            icons/icon-extensions-flashlight-off.png \
            icons/icon-extensions-flashlight-on.png \
            icons/icon-extensions-gsm-off.png \
            icons/icon-extensions-gsm-on.png \
            icons/icon-extensions-powersave-off.png \
            icons/icon-extensions-powersave-on.png \
            icons/icon-extensions-powersave-auto.png \
            icons/icon-extensions-usb-ask.png \
            icons/icon-extensions-usb-mass.png \
            icons/icon-extensions-usb-sdk.png \
            icons/icon-extensions-usb-sync.png \
            icons/icon-extensions-usb-charging.png
png.path = /usr/share/themes/blanco/meegotouch/icons

contextfiles.path += /usr/share/contextkit/providers
contextfiles.files = com.system-ui-extensions.glol.context

INSTALLS += target png contextfiles

OTHER_FILES += \
    com.system-ui-extensions.glol.context
