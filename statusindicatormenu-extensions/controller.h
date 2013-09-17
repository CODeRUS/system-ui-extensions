#ifndef EXTENSIONSCONTROLLER_H
#define EXTENSIONSCONTROLLER_H

#include <MLayout>
#include <MLinearLayoutPolicy>

#include "plugin.h"

#include "MWidgetBrightness.h"
#include "MWidgetAvialability.h"
#include "MWidgetTools.h"

class MStatusIndicatorMenuInterface;

class ExtensionsController : public MWidget
{
    Q_OBJECT
//    Q_CLASSINFO("D-Bus Interface", "org.system-ui-extensions.controller")

public:
    explicit ExtensionsController(ExtensionsPlugin *extensionsPlugin, QGraphicsItem *parent = NULL);
    virtual ~ExtensionsController();

signals:
    void pressed();
    void released();

private:
    MLayout *m_layout;
    MLinearLayoutPolicy *m_mainLayout;

    ExtensionsPlugin *m_extensionsPlugin;
    MWidget *spacing1;

    MWidgetBrightness *m_brightnessWidget;
    MWidgetAvialability *m_avialabilityWidget;
    MWidgetTools *m_togglesWidget;

public slots:
    Q_SCRIPTABLE void setBrightnessVisibility(bool isVisible);
    Q_SCRIPTABLE void setAvialabilityVisibility(bool isVisible);
    Q_SCRIPTABLE void setToolsVisibility(bool isVisible);

};

#endif // EXTENSIONSCONTROLLER_H
