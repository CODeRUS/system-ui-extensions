#include "MWidgetTools.h"
#include <QGraphicsLinearLayout>

#define IT_OBJECT_NAME "/tools"
#define IT_SERVICE_NAME "org.system-ui-extensions.tools"

MWidgetTools::MWidgetTools(QGraphicsItem *parent):
    MWidget(parent)
{
    QDBusConnection::sessionBus().registerObject(IT_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);
    QDBusConnection::sessionBus().registerService(IT_SERVICE_NAME);

    for (int i=0; i<10; i++)
    {
        m_items.append(new MWidget());
        m_visible.append(true);
    }

    bluetooth = new MToolBluetooth();
    cellular = new MToolCellular();
    flashlight = new MToolFlashlight();
    radio = new MToolRadio();
    psm = new MToolPSM();
    brightness = new MToolBrightness();
    usb = new MToolUSB();
    reboot = new MToolReboot();
    bgconn = new MToolBGConn();
    glol = new MToolGLOL();

    m_layout = new MLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setMaximumWidth(480);

    m_mainLayout = new MFlowLayoutPolicy(m_layout);
    m_mainLayout->setContentsMargins(10,0,0,0);
    m_mainLayout->setSpacing(12);
    m_mainLayout->setVerticalSpacing(16);

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
}

MWidgetTools::~MWidgetTools()
{
    QDBusConnection::sessionBus().unregisterService(IT_SERVICE_NAME);
    QDBusConnection::sessionBus().unregisterObject(IT_OBJECT_NAME);
}

void MWidgetTools::refreshLayout()
{
    for (int i=m_mainLayout->count()-1; i>-1; i--)
        m_mainLayout->removeAt(i);

    for (int i=0; i<10; i++)
    {
        if (m_visible.at(i))
            m_mainLayout->addItem(m_items.at(i));
    }
}

void MWidgetTools::onSetStatus(bool status, int index)
{
    m_visible[index] = status;
    refreshLayout();
}

void MWidgetTools::switchItems(int s_index1, int s_index2)
{
    QGraphicsLayoutItem *item1 = m_mainLayout->itemAt(s_index1);
    QGraphicsLayoutItem *item2 = m_mainLayout->itemAt(s_index2);

    m_items[s_index2] = item1;
    m_items[s_index1] = item2;

    refreshLayout();
}

void MWidgetTools::enterDisplayEvent()
{
    bluetooth->show();
    cellular->show();
    flashlight->show();
    psm->show();
    radio->show();
    brightness->show();
    usb->show();
    reboot->show();
    bgconn->show();
    glol->show();
}

void MWidgetTools::exitDisplayEvent()
{
    bluetooth->hide();
    cellular->hide();
    flashlight->hide();
    psm->hide();
    radio->hide();
    brightness->hide();
    usb->hide();
    reboot->hide();
    bgconn->hide();
    glol->hide();
}
