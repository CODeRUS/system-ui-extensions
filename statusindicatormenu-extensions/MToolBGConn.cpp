#include "MToolBGConn.h"
#include <MFeedback>

MToolBGConn::MToolBGConn(QGraphicsItem *parent):
    MWidget(parent),
    m_GConfItem(new GConfItem("/system/osso/connectivity/network_type/restricted_mode")),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/bgconn/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/bgconn/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_bg_on =  QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-background-on.png");
    icon_bg_off = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-background-off.png");

    m_toggleicon = new MImageWidget(&icon_bg_on, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

//    connect(m_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));

    onGConfChanged();

//    connect(poskey,
//            SIGNAL(valueChanged()),
//            SLOT(onIndexChanged()));
//    connect(statuskey,
//            SIGNAL(valueChanged()),
//            SLOT(onStatusChanged()));

    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolBGConn::hide()
{
    disconnect(m_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
}

void MToolBGConn::show()
{
    connect(m_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
    onGConfChanged();
}

void MToolBGConn::onGConfChanged()
{
    if (m_GConfItem->value().toBool())
        m_toggleicon->setImage(icon_bg_off);
    else
        m_toggleicon->setImage(icon_bg_on);
}

void MToolBGConn::onIndexChanged()
{
    index = poskey->value().toInt();
    emit setIndex(index);
}

void MToolBGConn::onStatusChanged()
{
    status = statuskey->value().toBool();
    emit setStatus(status, poskey->value().toInt());
    setVisible(status);
}

void MToolBGConn::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
}

void MToolBGConn::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
        m_GConfItem->set(!m_GConfItem->value().toBool());
}

