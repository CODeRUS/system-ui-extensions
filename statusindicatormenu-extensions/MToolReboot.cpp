#include "MToolReboot.h"
#include <MFeedback>
#include <QProcess>

MToolReboot::MToolReboot(QGraphicsItem *parent):
    MWidget(parent),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/reboot/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/reboot/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_power_unloaded =  QImage("/usr/share/themes/blanco/meegotouch/icons/c.png");
    icon_power =  QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-power.png");

    m_toggleicon = new MImageWidget(&icon_power_unloaded, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    connect(m_timer,
            SIGNAL(timeout()),
            SLOT(onTimer()));

    service = new GConfItem("/apps/system-ui-extensions/daemon/service");
//    connect(service,
//            SIGNAL(valueChanged()),
//            SLOT(onGConf()));
    onGConf();
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolReboot::hide()
{
    disconnect(service,
            SIGNAL(valueChanged()), this,
            SLOT(onGConf()));
}

void MToolReboot::show()
{
    connect(service,
            SIGNAL(valueChanged()),
            SLOT(onGConf()));
    onGConf();
}

void MToolReboot::onGConf()
{
    if (GConfItem("/apps/system-ui-extensions/daemon/service").value().toBool())
        m_toggleicon->setImage(icon_power);
    else
        m_toggleicon->setImage(icon_power_unloaded);
}

void MToolReboot::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolReboot::onTimer()
{
    emit pressed();
    if (counter == 2)
        reqReboot();
    else
        counter+=1;
}

void MToolReboot::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();

    counter = 0;

    if (GConfItem("/apps/system-ui-extensions/daemon/service").value().toBool())
        m_timer->start();
}

void MToolReboot::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        counter = 0;
        m_timer->stop();
    }
}

void MToolReboot::reqReboot()
{

    MFeedback* feedback3 = new MFeedback("priority2_grab", this);
    feedback3->play();
    GConfItem("/apps/system-ui-extensions/daemon/reboot").set(true);
}

void MToolReboot::onStatusChanged()
{
        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}
