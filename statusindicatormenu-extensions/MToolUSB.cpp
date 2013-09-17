#include "MToolUSB.h"
#include <MFeedback>

MToolUSB::MToolUSB(QGraphicsItem *parent):
    MWidget(parent),
    m_usbmode_GConfItem(new GConfItem("/Meego/System/UsbMode")),
    m_devmode_GConfItem(new GConfItem("/Meego/System/DeveloperMode")),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/usb/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/usb/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_usb_ask =      QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-usb-ask.png");
    icon_usb_sync =     QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-usb-sync.png");
    icon_usb_mass =     QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-usb-mass.png");
    icon_usb_sdk =      QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-usb-sdk.png");
    icon_usb_charging = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-usb-charging.png");

    m_toggleicon = new MImageWidget(&icon_usb_ask, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

//    connect(m_usbmode_GConfItem, SIGNAL(valueChanged()), this, SLOT(onUsbValueChanged()));
    onUsbValueChanged();
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolUSB::hide()
{
    disconnect(m_usbmode_GConfItem, SIGNAL(valueChanged()), this, SLOT(onUsbValueChanged()));
}

void MToolUSB::show()
{
    connect(m_usbmode_GConfItem, SIGNAL(valueChanged()), this, SLOT(onUsbValueChanged()));
    onUsbValueChanged();
}

void MToolUSB::onUsbValueChanged()
{
    QString value = m_usbmode_GConfItem->value().toString();

    if (value == "mass_storage")
    {
        m_toggleicon->setImage(icon_usb_mass);
        nextValue = "ovi_suite";
    }
    else if (value == "ovi_suite")
    {
        m_toggleicon->setImage(icon_usb_sync);
        if (m_devmode_GConfItem->value().toBool())
            nextValue = "windows_network";
        else
            nextValue = "charging_only";
    }
    else if (value == "windows_network")
    {
        m_toggleicon->setImage(icon_usb_sdk);
        nextValue = "charging_only";
    }
    else if (value == "charging_only")
    {
        m_toggleicon->setImage(icon_usb_charging);
        nextValue = "ask";
    }
    else if (value == "ask")
    {
        m_toggleicon->setImage(icon_usb_ask);
        nextValue = "mass_storage";
    }
}

void MToolUSB::onIndexChanged()
{
    index = poskey->value().toInt();
    emit setIndex(index);
}

void MToolUSB::onStatusChanged()
{
    status = statuskey->value().toBool();
    emit setStatus(status, poskey->value().toInt());
    setVisible(status);
}

void MToolUSB::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
}

void MToolUSB::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
        m_usbmode_GConfItem->set(nextValue);
}
