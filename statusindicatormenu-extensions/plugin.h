#ifndef EXTENSIONSPLUGIN_H
#define EXTENSIONSPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <MLibrary>
#include <MStatusIndicatorMenuExtensionInterface>
#include <MApplicationExtensionInterface>
#include <QGraphicsWidget>

class ExtensionsController;

class ExtensionsPlugin : public QObject, public MStatusIndicatorMenuExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(MStatusIndicatorMenuExtensionInterface MApplicationExtensionInterface)

public:
    explicit ExtensionsPlugin(QObject *parent = 0);
    MStatusIndicatorMenuInterface *statusIndicatorMenuInterface() const;
    virtual void setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface);
    virtual bool initialize(const QString &interface);
    virtual QGraphicsWidget *widget();

private:
    MStatusIndicatorMenuInterface *statusIndicatorMenu;
    ExtensionsController *m_extensionsController;
};

#endif // EXTENSIONSPLUGIN_H
