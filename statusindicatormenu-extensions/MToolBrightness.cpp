#include "MToolBrightness.h"
#include <MFeedback>

MToolBrightness::MToolBrightness(QGraphicsItem *parent):
    MWidget(parent),
    m_brightnessGConfItem(new GConfItem("/system/osso/dsm/display/display_brightness")),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/brightness/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/brightness/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_brightness_min = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-brightness-min.png");
    icon_brightness_med = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-brightness-med.png");
    icon_brightness_max = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-brightness-max.png");

    m_toggleicon = new MImageWidget(&icon_brightness_med, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

//    connect(m_brightnessGConfItem, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));

    onValueChanged();
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolBrightness::hide()
{
    disconnect(m_brightnessGConfItem, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void MToolBrightness::show()
{
    connect(m_brightnessGConfItem, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
}

void MToolBrightness::onValueChanged()
{
    switch (m_brightnessGConfItem->value().toInt())
    {
    case 1: m_toggleicon->setImage(icon_brightness_min);
            nextValue = 3;
            break;
    case 2:
    case 3:
    case 4: m_toggleicon->setImage(icon_brightness_med);
            nextValue = 5;
            break;
    case 5: m_toggleicon->setImage(icon_brightness_max);
            nextValue = 1;
            break;
    }
}

void MToolBrightness::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolBrightness::onStatusChanged()
{

        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}

void MToolBrightness::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
}

void MToolBrightness::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        m_brightnessGConfItem->set(nextValue);
    }
}

