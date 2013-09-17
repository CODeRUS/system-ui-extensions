#include "MImageWidgetEx.h"
#include <MFeedback>

MImageWidgetEx::MImageWidgetEx(QString gconfname, const QString &id, QGraphicsItem *parent):
    MWidget(parent),
    poskeyname(QString("/apps/system-ui-extensions/tools/%1/index").arg(gconfname)),
    statuskeyname(QString("/apps/system-ui-extensions/tools/%1/working").arg(gconfname))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play())); 
    MFeedback* feedback3 = new MFeedback("priority2_grab", this);
    connect(this, SIGNAL(longpressed()), feedback3, SLOT(play()));

    index = GConfItem(poskeyname).value().toInt();
    status = GConfItem(statuskeyname).value().toBool();

    QImage *icon = new QImage(QString("/usr/share/themes/blanco/meegotouch/icons/%1.png").arg(id));
    image = new MImageWidget(icon, this);
    image->setAspectRatioMode(Qt::KeepAspectRatio);
    image->setMinimumSize(64,64);
    image->setMaximumSize(64,64);

    QPixmap *alphagray = new QPixmap(64,64);
    alphagray->fill(QColor(0,0,0,127));
    grayed = new MImageWidget(alphagray, this);
    grayed->setGeometry(QRectF(0,0,64,64));
    grayed->setVisible(!status);

    connect(image,
            SIGNAL(geometryChanged()),
            SLOT(onGeometryChanged()));

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(500);
    connect(m_timer,
            SIGNAL(timeout()),
            SLOT(longpress()));
}

void MImageWidgetEx::longpress()
{
    emit longpressed();
    setGrayed(!isGrayed());
}

void MImageWidgetEx::setGrayed(bool isGrayed)
{
    grayed->setVisible(isGrayed);
    status = !isGrayed;
    GConfItem(statuskeyname).set(status);

    QDBusInterface interface("org.system-ui-extensions.tools",
                             "/tools",
                             "local.MWidgetTools",
                             QDBusConnection::sessionBus());
    interface.call("onSetStatus", status, index);
}

bool MImageWidgetEx::isGrayed()
{
    return grayed->isVisible();
}

void MImageWidgetEx::setIndex(int i_index)
{
    GConfItem(poskeyname).set(i_index);
    index = i_index;
}

void MImageWidgetEx::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void MImageWidgetEx::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed();
    m_timer->start();
    event->accept();
}

void MImageWidgetEx::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void MImageWidgetEx::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_timer->isActive())
    {
        m_timer->stop();
        emit released();
    }
    event->accept();
}

void MImageWidgetEx::cancelEvent(MCancelEvent *event)
{
    Q_UNUSED(event);
}
