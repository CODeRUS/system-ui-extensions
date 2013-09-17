#include "plugin.h"
#include "controller.h"

Q_EXPORT_PLUGIN2(extensions, ExtensionsPlugin)

ExtensionsPlugin::ExtensionsPlugin(QObject *parent) :
    statusIndicatorMenu(0),
    m_extensionsController(0)
{
    Q_UNUSED(parent)
}

void ExtensionsPlugin::setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface)
{
    statusIndicatorMenu = &menuInterface;
}

MStatusIndicatorMenuInterface *ExtensionsPlugin::statusIndicatorMenuInterface() const
{
    return statusIndicatorMenu;
}

bool ExtensionsPlugin::initialize(const QString &)
{
    m_extensionsController = new ExtensionsController(this);

    return true;
}

QGraphicsWidget *ExtensionsPlugin::widget()
{
    return m_extensionsController;
}

M_LIBRARY
