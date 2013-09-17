#include "MToolGLOL.h"
#include <MFeedback>

#define SERVICE_NAME "com.system-ui-extensions.glol"

MToolGLOL::MToolGLOL(QGraphicsItem *parent):
    MWidget(parent),
    bus(QDBusConnection::sessionBus()),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/glol/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/glol/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_glol_portait =   QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-glol-portait.png");
    icon_glol_landscape = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-glol-landscape.png");
    icon_glol_auto =      QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-glol-auto.png");

    m_toggleicon = new MImageWidget(&icon_glol_auto, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    adaptor = new PropertyAdaptor(this);

    bus.registerObject(adaptor->objectPath(), this);
    bus.registerService(SERVICE_NAME);

    currentstate = 0;
    adaptor->setValue("auto");

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

    pressTime = new QTimer(this);
    pressTime->setSingleShot(true);
    pressTime->setInterval(800);
    connect(pressTime,
            SIGNAL(timeout()),
            SLOT(longPress()));

    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolGLOL::hide()
{
}

void MToolGLOL::show()
{
}

void MToolGLOL::setGLOLState()
{
    ++currentstate;

    switch (currentstate)
    {
    case 1:
        adaptor->setValue("top");
        m_toggleicon->setImage(icon_glol_landscape);
        break;
    case 2:
        adaptor->setValue("left");
        m_toggleicon->setImage(icon_glol_portait);
        break;
    case 3:
        adaptor->setValue("auto");
        m_toggleicon->setImage(icon_glol_auto);
        currentstate=0;
        break;
    }
}

void MToolGLOL::longPress()
{
    longPressed = true;
    emit released();
}

void MToolGLOL::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
//    pressTime->start();

//    longPressed = false;
}

void MToolGLOL::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
//        if (!longPressed)
//        {
            emit released();
            setGLOLState();
//            pressTime->stop();
//        }
//        else
//            system(QString("qdbus com.nokia.DuiControlPanel / com.nokia.DuiControlPanelIf.appletPage Battery").toAscii());
    }
}

void MToolGLOL::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolGLOL::onStatusChanged()
{

        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}
