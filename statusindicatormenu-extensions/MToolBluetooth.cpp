#include "MToolBluetooth.h"
#include <gq/GConfItem>
#include <MFeedback>

MToolBluetooth::MToolBluetooth(QGraphicsItem *parent):
    MWidget(parent),
    m_btLocalDevice(new QBluetoothLocalDevice(this)),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/bluetooth/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/bluetooth/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_active = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-bluetooth-on.png");
    icon_inactive = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-bluetooth-off.png");
    icon_discoverable = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-bluetooth-visible.png");

    m_toggleicon = new MImageWidget(&icon_inactive, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));
    MFeedback* feedback3 = new MFeedback("priority2_grab", this);
    connect(this, SIGNAL(longpressed()), feedback3, SLOT(play()));

    longAction = new QTimer(this);
    longAction->setSingleShot(true);
    longAction->setInterval(800);
    connect(longAction, SIGNAL(timeout()), this, SLOT(LongPress()));

//    connect(m_btLocalDevice,
//            SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
//            SLOT(onBluetoothStateChanged(QBluetoothLocalDevice::HostMode)));

    onBluetoothStateChanged(m_btLocalDevice->hostMode());
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));

    index = poskey->value().toInt();
    status = statuskey->value().toBool();

    if (m_btLocalDevice->isValid())
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/device").set("valid");
    else
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/device").set("invalid");
}

void MToolBluetooth::hide()
{
    disconnect(m_btLocalDevice,
            SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
               this,
            SLOT(onBluetoothStateChanged(QBluetoothLocalDevice::HostMode)));
}

void MToolBluetooth::show()
{
    connect(m_btLocalDevice,
            SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
            SLOT(onBluetoothStateChanged(QBluetoothLocalDevice::HostMode)));
    onBluetoothStateChanged(m_btLocalDevice->hostMode());
}

void MToolBluetooth::LongPress()
{
    longPressed = true;
    emit longpressed();
}

void MToolBluetooth::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolBluetooth::onStatusChanged()
{
     status = statuskey->value().toBool();
     emit setStatus(status, poskey->value().toInt());
     setVisible(status);
}

void MToolBluetooth::onBluetoothStateChanged(QBluetoothLocalDevice::HostMode *mode)
{
    m_mode = mode;
    switch (m_mode) {
    case QBluetoothLocalDevice::HostPoweredOff:
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/mode").set("PoweredOff");
        m_toggleicon->setImage(icon_inactive);
        if (GConfItem("/system/osso/connectivity/BT/visible").value().toBool())
        {
            GConfItem("/apps/system-ui-extensions/tools/bluetooth/nextmode").set("Discoverable");
            m_nextmode = QBluetoothLocalDevice::HostDiscoverable;
        }
        else
        {
            GConfItem("/apps/system-ui-extensions/tools/bluetooth/nextmode").set("Connectable");
            m_nextmode = QBluetoothLocalDevice::HostConnectable;
        }
        break;
    case QBluetoothLocalDevice::HostDiscoverable:
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/mode").set("Discoverable");
        m_toggleicon->setImage(icon_discoverable);
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/nextmode").set("PoweredOff");
        m_nextmode = QBluetoothLocalDevice::HostPoweredOff;
        break;
    case QBluetoothLocalDevice::HostDiscoverableLimitedInquiry:
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/mode").set("DiscoverableLimited");
        m_toggleicon->setImage(icon_discoverable);
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/nextmode").set("PoweredOff");
        m_nextmode = QBluetoothLocalDevice::HostPoweredOff;
        break;
    case QBluetoothLocalDevice::HostConnectable:
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/mode").set("Connectable");
        m_toggleicon->setImage(icon_active);
        GConfItem("/apps/system-ui-extensions/tools/bluetooth/nextmode").set("PoweredOff");
        m_nextmode = QBluetoothLocalDevice::HostPoweredOff;
        break;
    }
}

void MToolBluetooth::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    emit pressed();
    longAction->start();
    longPressed = false;


    ev->accept();
}

void MToolBluetooth::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        if (!longPressed)
        {
            emit released();
            m_btLocalDevice->setHostMode(m_nextmode);
            longAction->stop();
        }
        else
            system(QString("qdbus com.nokia.DuiControlPanel / com.nokia.DuiControlPanelIf.appletPage Bluetooth").toAscii());
    }

    ev->accept();
}
