#include "MToolPSM.h"
#include <MFeedback>

MToolPSM::MToolPSM(QGraphicsItem *parent):
    MWidget(parent),
    m_autopsm_GConfItem(new GConfItem("/system/osso/dsm/energymanagement/enable_power_saving")),
    m_forcepsm_GConfItem(new GConfItem("/system/osso/dsm/energymanagement/force_power_saving")),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/psm/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/psm/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_psm_on =  QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-powersave-on.png");
    icon_psm_off = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-powersave-off.png");
    icon_psm_auto = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-powersave-auto.png");

    m_toggleicon = new MImageWidget(&icon_psm_off, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    percentage = new MLabel(this);
    QFont font = percentage->font();
    font.setPixelSize(20);
    percentage->setFont(font);
    percentage->setColor(QColor(255,255,255));
    percentage->setPos(11,13);
    percentage->setVisible(false);

    battery = new MeeGo::QmBattery(this);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));
    MFeedback* feedback3 = new MFeedback("priority2_grab", this);
    connect(this, SIGNAL(longpressed()), feedback3, SLOT(play()));

//    connect(m_autopsm_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
//    connect(m_forcepsm_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));

    pressTime = new QTimer(this);
    pressTime->setSingleShot(true);
    pressTime->setInterval(800);
    connect(pressTime,
            SIGNAL(timeout()),
            SLOT(longPress()));

    onGConfChanged();
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolPSM::hide()
{
    disconnect(m_autopsm_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
    disconnect(m_forcepsm_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
}

void MToolPSM::show()
{

    connect(m_autopsm_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
    connect(m_forcepsm_GConfItem, SIGNAL(valueChanged()), this, SLOT(onGConfChanged()));
    onGConfChanged();

    int pct = battery->getRemainingCapacityPct();

    if (pct < 100)
    {
        if (pct > 9)
            percentage->setText(QString("%1").arg(pct));
        else
            percentage->setText(QString("0%1").arg(pct));
        percentage->setVisible(true);
    }
    else
    {
        percentage->setVisible(false);
    }
}

void MToolPSM::onGConfChanged()
{
   bool forcePSM = m_forcepsm_GConfItem->value().toBool();
   bool autoPSM = m_autopsm_GConfItem->value().toBool();

   if (forcePSM)
   {
       nextState = 0;
       m_toggleicon->setImage(icon_psm_on);
   }
   else if (autoPSM)
   {
       nextState = 2;
       m_toggleicon->setImage(icon_psm_auto);
   }
   else
   {
       nextState = 1;
       m_toggleicon->setImage(icon_psm_off);
   }
}

void MToolPSM::setPsmState(int state)
{
    switch (state)
    {
    case 0: m_forcepsm_GConfItem->set(false);
            m_autopsm_GConfItem->set(false);
            break;
    case 1: m_forcepsm_GConfItem->set(false);
            m_autopsm_GConfItem->set(true);
            break;
    case 2: m_forcepsm_GConfItem->set(true);
            m_autopsm_GConfItem->set(false);
            break;
    }
}

void MToolPSM::longPress()
{
    longPressed = true;
    emit longpressed();
}

void MToolPSM::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
    pressTime->start();

    longPressed = false;
}

void MToolPSM::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        if (!longPressed)
        {
            emit released();
            setPsmState(nextState);
            pressTime->stop();
        }
        else
            system(QString("qdbus com.nokia.DuiControlPanel / com.nokia.DuiControlPanelIf.appletPage Battery").toAscii());
    }
}

void MToolPSM::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolPSM::onStatusChanged()
{

        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}
