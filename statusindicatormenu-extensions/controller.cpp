#include "controller.h"
#include <MLinearLayoutPolicy>

#define IC_OBJECT_NAME "/controller"
#define IC_SERVICE_NAME "org.system-ui-extensions.controller"

ExtensionsController::ExtensionsController(ExtensionsPlugin *extensionsPlugin, QGraphicsItem *parent) :
    MWidget(parent),
    m_extensionsPlugin(extensionsPlugin)
{
    QDBusConnection::sessionBus().registerObject(IC_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);
    QDBusConnection::sessionBus().registerService(IC_SERVICE_NAME);

    setObjectName("StatusIndicatorMenuExtensionContentItem");

    m_layout = new MLayout(this);
    m_mainLayout = new MLinearLayoutPolicy(m_layout, Qt::Vertical);
    m_mainLayout->setSpacing(6);

    MImageWidget *test = new MImageWidget("icon-m-service-icq", this);
    test->setMaximumSize(64,64);
    test->setMinimumSize(64,64);
    test->setAspectRatioMode(Qt::KeepAspectRatio);
    m_mainLayout->addItem(test);
}

ExtensionsController::~ExtensionsController()
{
    QDBusConnection::sessionBus().unregisterService(IC_SERVICE_NAME);
    QDBusConnection::sessionBus().unregisterObject(IC_OBJECT_NAME);
}

void ExtensionsController::setBrightnessVisibility(bool isVisible)
{

}

void ExtensionsController::setAvialabilityVisibility(bool isVisible)
{

}

void ExtensionsController::setToolsVisibility(bool isVisible)
{

}
