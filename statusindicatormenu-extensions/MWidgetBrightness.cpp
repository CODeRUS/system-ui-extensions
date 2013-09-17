#include <MLocale>
#include <QBitmap>
#include <QPaintEngine>
#include <QGraphicsLinearLayout>

#include "MWidgetBrightness.h"
#include "controller.h"

#define IB_OBJECT_NAME "/brightness"
#define IB_SERVICE_NAME "org.system-ui-extensions.brightness"

MWidgetBrightness::MWidgetBrightness(QGraphicsItem *parent):
    MWidget(parent)
{
    QDBusConnection::sessionBus().registerObject(IB_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);
    QDBusConnection::sessionBus().registerService(IB_SERVICE_NAME);

    MLocale locale;
    locale.installTrCatalog("settings");
    MLocale::setDefault(locale);

    setMaximumHeight(70);
    setMinimumHeight(70);

    MLabel *label = new MLabel(qtTrId("qtn_sett_main_brightness"), this);
    label->setColor(QColor(255,255,255));
    QFont font = label->font();
    font.setPixelSize(22);
    label->setFont(font);
    label->setPos(-5,-12);

    QPixmap *pix_background = new QPixmap(468,24);
    pix_background->fill(QColor(50,50,50));
    backgroundbar = new MImageWidget(pix_background, this);
    backgroundbar->setAspectRatioMode(Qt::IgnoreAspectRatio);
//    backgroundbar->setMaximumHeight(24);
//    backgroundbar->setMinimumHeight(24);
//    backgroundbar->setMinimumWidth(468);
//    backgroundbar->setMaximumWidth(468);
    backgroundbar->setGeometry(QRectF(0,26,468,24));

    m_bar_red = new GConfItem("/apps/system-ui-extensions/brightness/red");
    m_bar_green = new GConfItem("/apps/system-ui-extensions/brightness/green");
    m_bar_blue = new GConfItem("/apps/system-ui-extensions/brightness/blue");
//    connect(m_bar_red, SIGNAL(valueChanged()), SLOT(onRGBChanged()));
//    connect(m_bar_green, SIGNAL(valueChanged()), SLOT(onRGBChanged()));
//    connect(m_bar_blue, SIGNAL(valueChanged()), SLOT(onRGBChanged()));

    pix_brightnessbar = QPixmap(1,1);
    brightnessbar = new MImageWidget(&pix_brightnessbar, this);
    brightnessbar->setAspectRatioMode(Qt::IgnoreAspectRatio);
    brightnessbar->setMaximumHeight(24);
    brightnessbar->setMinimumHeight(24);
    brightnessbar->setMinimumWidth(0);
    brightnessbar->setMaximumWidth(468);
    brightnessbar->setPos(0,26);
//    enterDisplayEvent();

    QImage *icon_background = new QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-background.png");
    MImageWidget *alpha1 = new MImageWidget(icon_background, this);
    alpha1->setPos(0,26);
    MImageWidget *alpha2 = new MImageWidget(icon_background, this);
    alpha2->setPos(467,26),
    alpha0 = new MImageWidget(icon_background, this);
    alpha0->setPos(-1,26);

    m_brightnessGConfItem = new GConfItem("/system/osso/dsm/display/display_brightness");
    connect(m_brightnessGConfItem, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));

    onValueChanged();
}

MWidgetBrightness::~MWidgetBrightness()
{
    QDBusConnection::sessionBus().unregisterService(IB_SERVICE_NAME);
    QDBusConnection::sessionBus().unregisterObject(IB_OBJECT_NAME);
}

void MWidgetBrightness::setBarWidthMove(int width)
{
    interval.restart();
    m_brightnessGConfItem->blockSignals(true);

    if (width < 50) {
        m_brightnessGConfItem->set(1);
        brightnessbar->setGeometry(QRectF(0,26,0,24));
    } else if ((width > 60) && (width < 97)) {
        m_brightnessGConfItem->set(2);
        brightnessbar->setGeometry(QRectF(0,26,117,24));
        alpha0->setPos(116,26);
    } else if ((width > 137) && (width < 214)) {
        m_brightnessGConfItem->set(3);
        brightnessbar->setGeometry(QRectF(0,26,234,24));
        alpha0->setPos(233,26);
    } else if ((width > 254) && (width < 331)) {
        m_brightnessGConfItem->set(4);
        brightnessbar->setGeometry(QRectF(0,26,351,24));
        alpha0->setPos(350,26);
    } else if (width > 371) {
        m_brightnessGConfItem->set(5);
        brightnessbar->setGeometry(QRectF(0,26,468,24));
    }

    m_brightnessGConfItem->blockSignals(false);
}

void MWidgetBrightness::setBarWidthPress(int width)
{
    m_brightnessGConfItem->blockSignals(true);
    alpha0->setPos(-1,26);
    if (width < 50) {
        m_brightnessGConfItem->set(1);
        brightnessbar->setGeometry(QRectF(0,26,0,24));
    } else if ((width > 49) && (width < 117)) {
        m_brightnessGConfItem->set(2);
        brightnessbar->setGeometry(QRectF(0,26,117,24));      
        alpha0->setPos(116,26);
    } else if ((width > 116) && (width < 234)) {
        m_brightnessGConfItem->set(3);
        brightnessbar->setGeometry(QRectF(0,26,234,24));     
        alpha0->setPos(233,26);
    } else if ((width > 233) && (width < 351)) {
        m_brightnessGConfItem->set(4);
        brightnessbar->setGeometry(QRectF(0,26,351,24));
        alpha0->setPos(350,26);
    } else if (width > 350) {
        m_brightnessGConfItem->set(5);
        brightnessbar->setGeometry(QRectF(0,26,468,24));
    }

    m_brightnessGConfItem->blockSignals(false);
}

void MWidgetBrightness::onValueChanged()
{
    int width = 470 * (m_brightnessGConfItem->value().toInt()-1) / 4;
    brightnessbar->setGeometry(QRectF(0,26,width,24));
}

void MWidgetBrightness::setColor(int red, int green, int blue)
{
    pix_brightnessbar.fill(QColor(red, green, blue));
    brightnessbar->setPixmap(pix_brightnessbar);
}

void MWidgetBrightness::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    interval.start();
    setBarWidthPress(ev->pos().x());
}

void MWidgetBrightness::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    if (interval.elapsed() > 100)
        setBarWidthMove(ev->pos().x());
}

void MWidgetBrightness::enterDisplayEvent()
{
    setColor(m_bar_red->value().toInt(),
             m_bar_green->value().toInt(),
             m_bar_blue->value().toInt());
}

void MWidgetBrightness::hide()
{
//    setVisible(false);
}

void MWidgetBrightness::show()
{
//    setVisible(true);
}
