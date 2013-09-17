#include "MToolCellular.h"
#include <MFeedback>

MToolCellular::MToolCellular(QGraphicsItem *parent):
    MWidget(parent),
    m_radio(new Cellular::RadioAccess(this)),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/cellular/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/cellular/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_2g =   QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-cellular-2g.png");
    icon_3g =   QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-cellular-3g.png");
    icon_dual = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-cellular-dual.png");

    m_toggleicon = new MImageWidget(&icon_2g, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));


//    connect(m_radio,
//            SIGNAL(modeChanged(int)),
//            SLOT(onModeChanged(int)));

    onModeChanged(m_radio->mode());
    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolCellular::hide()
{
    disconnect(m_radio,
            SIGNAL(modeChanged(int)),
               this,
               SLOT(onModeChanged(int)));
}

void MToolCellular::show()
{
    connect(m_radio,
         SIGNAL(modeChanged(int)),
         SLOT(onModeChanged(int)));

    onModeChanged(m_radio->mode());
}

void MToolCellular::onModeChanged(int mode)
{
    switch (mode)
    {
        case Cellular::RadioAccess::DualMode:
            m_nextmode = Cellular::RadioAccess::OnlyTwoG;
            m_toggleicon->setImage(icon_dual);
            break;
        case Cellular::RadioAccess::OnlyTwoG:
            m_nextmode = Cellular::RadioAccess::OnlyThreeG;
            m_toggleicon->setImage(icon_2g);
            break;
        case Cellular::RadioAccess::OnlyThreeG:
            m_nextmode = Cellular::RadioAccess::DualMode;
            m_toggleicon->setImage(icon_3g);
            break;
        default:
            m_nextmode = Cellular::RadioAccess::OnlyTwoG;
            m_toggleicon->setImage(icon_dual);
            break;
    }
}

void MToolCellular::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolCellular::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
}

void MToolCellular::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        m_radio->setMode((Cellular::RadioAccess::Mode)m_nextmode);
    }
}

void MToolCellular::onStatusChanged()
{

        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}
