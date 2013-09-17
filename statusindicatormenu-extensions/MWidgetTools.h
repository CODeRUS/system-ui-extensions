#ifndef WIDGETTOOLS_H
#define WIDGETTOOLS_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>

#include <MFlowLayoutPolicy>
#include <MLayout>
#include <QGraphicsSceneMouseEvent>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusObjectPath>
#include <QDBusMessage>

#include <gq/GConfItem>

#include "MToolBluetooth.h"
#include "MToolCellular.h"
#include "MToolFlashlight.h"
#include "MToolPSM.h"
#include "MToolRadio.h"
#include "MToolBrightness.h"
#include "MToolUSB.h"
#include "MToolReboot.h"
#include "MToolBGConn.h"
#include "MToolGLOL.h"

class MWidgetTools : public MWidget
{

   Q_OBJECT
//    Q_CLASSINFO("D-Bus Interface", "org.system-ui-extensions.tools")

public:
    explicit MWidgetTools(QGraphicsItem *parent = 0);
    virtual ~MWidgetTools();

private:
    MFlowLayoutPolicy *m_mainLayout;
    MLayout *m_layout;

    MToolBluetooth *bluetooth;
    MToolCellular *cellular;
    MToolFlashlight *flashlight;
    MToolRadio *radio;
    MToolPSM *psm;
    MToolBrightness *brightness;
    MToolUSB *usb;
    MToolReboot *reboot;
    MToolBGConn *bgconn;
    MToolGLOL *glol;

    QList<QGraphicsLayoutItem*> m_items;
    QList<bool> m_visible;

    void refreshLayout();

public slots:
    Q_SCRIPTABLE void onSetStatus(bool status, int index);
    Q_SCRIPTABLE void switchItems(int s_index1, int s_index2);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

};

#endif // WIDGETTOOLS_H
