#include "MToolRadio.h"
#include <MFeedback>

MToolRadio::MToolRadio(QGraphicsItem *parent):
    MWidget(parent),
    m_radio(new Cellular::SystemControl(this)),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/radio/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/radio/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_radio_off = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-gsm-off.png");
    icon_radio_on =  QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-gsm-on.png");

    m_toggleicon = new MImageWidget(&icon_radio_on, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

//    connect(m_radio,
//            SIGNAL(powerChanged(bool)),
//            SLOT(onPowerChanged(bool)));
    onPowerChanged(m_radio->power());
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolRadio::hide()
{
    disconnect(m_radio,
            SIGNAL(powerChanged(bool)),
               this,
            SLOT(onPowerChanged(bool)));
}

void MToolRadio::show()
{
    connect(m_radio,
            SIGNAL(powerChanged(bool)),
            SLOT(onPowerChanged(bool)));
    onPowerChanged(m_radio->power());
}

void MToolRadio::onPowerChanged(bool mode)
{
    if (mode)
        m_toggleicon->setImage(icon_radio_on);
    else
        m_toggleicon->setImage(icon_radio_off);
}

void MToolRadio::onIndexChanged()
{

        index = poskey->value().toInt();

}

void MToolRadio::onStatusChanged()
{

        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}

void MToolRadio::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
}

void MToolRadio::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        m_radio->setPower(!m_radio->power());
    }
}
