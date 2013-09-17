#include "toolswidget.h"

MToolsWidgetSettings::MToolsWidgetSettings(QGraphicsItem *parent):
    MWidget(parent)
{
    m_layout = new MLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setMaximumWidth(480);

    m_mainLayout = new MFlowLayoutPolicy(m_layout);
    m_mainLayout->setContentsMargins(12,0,0,0);
    m_mainLayout->setSpacing(12);
    m_mainLayout->setVerticalSpacing(16);

    QPixmap *pixmap = new QPixmap(64,64);
    pixmap->fill(QColor(127,127,127));
    selection = new MImageWidget(pixmap, this);
    selection->setVisible(false);

    bluetooth = new MImageWidgetEx("bluetooth", "icon-extensions-bluetooth-on", this);
    cellular = new MImageWidgetEx("cellular", "icon-extensions-cellular-3g", this);
    flashlight = new MImageWidgetEx("flashlight", "icon-extensions-flashlight-on", this);
    radio = new MImageWidgetEx("radio", "icon-extensions-gsm-on", this);
    psm = new MImageWidgetEx("psm", "icon-extensions-powersave-on", this);
    brightness = new MImageWidgetEx("brightness", "icon-extensions-brightness-med", this);
    usb = new MImageWidgetEx("usb", "icon-extensions-usb-ask", this);
    reboot = new MImageWidgetEx("reboot", "icon-extensions-power", this);
    bgconn = new MImageWidgetEx("bgconn", "icon-extensions-background-on", this);
    glol = new MImageWidgetEx("glol", "icon-extensions-glol-auto", this);

    m_items[bluetooth->index] = bluetooth;
    m_items[cellular->index] = cellular;
    m_items[flashlight->index] = flashlight;
    m_items[radio->index] = radio;
    m_items[psm->index] = psm;
    m_items[brightness->index] = brightness;
    m_items[usb->index] = usb;
    m_items[reboot->index] = reboot;
    m_items[bgconn->index] = bgconn;
    m_items[glol->index] = glol;

    m_visible[bluetooth->index] = bluetooth->status;
    m_visible[cellular->index] = cellular->status;
    m_visible[flashlight->index] = flashlight->status;
    m_visible[radio->index] = radio->status;
    m_visible[psm->index] = psm->status;
    m_visible[brightness->index] = brightness->status;
    m_visible[usb->index] = usb->status;
    m_visible[reboot->index] = reboot->status;
    m_visible[bgconn->index] = bgconn->status;
    m_visible[glol->index] = glol->status;

    refreshLayout();

    newIndex = -1;

    connect(bluetooth, SIGNAL(released()), SLOT(onStartMoving()));
    connect(cellular, SIGNAL(released()), SLOT(onStartMoving()));
    connect(flashlight, SIGNAL(released()), SLOT(onStartMoving()));
    connect(radio, SIGNAL(released()), SLOT(onStartMoving()));
    connect(psm, SIGNAL(released()), SLOT(onStartMoving()));
    connect(brightness, SIGNAL(released()), SLOT(onStartMoving()));
    connect(usb, SIGNAL(released()), SLOT(onStartMoving()));
    connect(reboot, SIGNAL(released()), SLOT(onStartMoving()));
    connect(bgconn, SIGNAL(released()), SLOT(onStartMoving()));
    connect(glol, SIGNAL(released()), SLOT(onStartMoving()));
}

void MToolsWidgetSettings::exitDisplayEvent()
{
    newIndex = -1;
}

void MToolsWidgetSettings::onStartMoving()
{
    MImageWidgetEx *item = qobject_cast<MImageWidgetEx*>(sender());

    if (newIndex == -1)
    {
        selection->setGeometry(QRectF(item->geometry().x(), item->geometry().y(),64,64));
        selection->setVisible(true);

        newIndex = m_mainLayout->indexOf(item);

    }
    else
    {
        selection->setVisible(false);
        if (newIndex != m_mainLayout->indexOf(item))
        {
            MImageWidgetEx *olditem = (MImageWidgetEx*) m_mainLayout->itemAt(newIndex);
            int oldIndex = newIndex;
            newIndex = m_mainLayout->indexOf(item);

            QDBusInterface interface("org.system-ui-extensions.tools",
                                     "/tools",
                                     "local.MWidgetTools",
                                     QDBusConnection::sessionBus());
            interface.call("switchItems", oldIndex, newIndex);

            m_items[oldIndex] = item;
            m_items[newIndex] = olditem;

            refreshLayout();
        }
        newIndex = -1;
    }
}

void MToolsWidgetSettings::refreshLayout()
{
    for (int i=m_mainLayout->count()-1; i>-1; i--)
        m_mainLayout->removeAt(i);

    for (int i=0; i<10; i++)
    {
        if (m_visible.at(i))
            m_mainLayout->addItem(m_items.at(i));
    }
}


void MToolsWidgetSettings::onEndMoving()
{

}

void MToolsWidgetSettings::hide()
{
    setVisible(false);
}

void MToolsWidgetSettings::show()
{
    setVisible(true);
}


