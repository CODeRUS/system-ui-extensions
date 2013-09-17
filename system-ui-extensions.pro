TEMPLATE = subdirs

SUBDIRS =   statusindicatormenu-extensions \
	    settings \
            extensions_daemon

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/conffiles \
    qtc_packaging/debian_harmattan/preinst \
    qtc_packaging/debian_harmattan/postinst \
    qtc_packaging/debian_harmattan/postrm \
    qtc_packaging/debian_harmattan/prerm \
    qtc_packaging/debian_harmattan/changelog
