#include "brightnesswidget.h"

#include <MLocale>

MBrightnessWidgetSettings::MBrightnessWidgetSettings(QGraphicsItem *parent):
    MWidget(parent)
{
    MLocale locale;
    locale.installTrCatalog("settings");
    MLocale::setDefault(locale);

    setMaximumHeight(70);
    setMinimumHeight(70);
    setMaximumWidth(468);
    setMinimumWidth(468);

    MLabel *label = new MLabel(qtTrId("qtn_sett_main_brightness"), this);
    label->setColor(QColor(255,255,255));
    QFont font = label->font();
    font.setPixelSize(22);
    label->setFont(font);
    label->setPos(-5,-12);

    s_pix_brightnessbar = QPixmap(1,1);
    s_pix_brightnessbar.fill(QColor(GConfItem("/apps/system-ui-extensions/brightness/red").value().toInt(),
                    GConfItem("/apps/system-ui-extensions/brightness/green").value().toInt(),
                    GConfItem("/apps/system-ui-extensions/brightness/blue").value().toInt()));

    s_brightnessbar = new MImageWidget(&s_pix_brightnessbar, this);
    s_brightnessbar->setAspectRatioMode(Qt::IgnoreAspectRatio);
    s_brightnessbar->setGeometry(QRectF(0,26,468,24));

    QImage *icon_background = new QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-background.png");
    MImageWidget *alpha = new MImageWidget(icon_background, this);
    alpha->setGeometry(QRectF(0,26,468,24));
}

void MBrightnessWidgetSettings::setBarWidth(int width)
{
    int val = width / 78;
    int off = width % 78;

    rr = 0;
    gg = 0;
    bb = 255;

    switch (val)
    {
    case 0:
        rr = 0;
        gg = 99 + off*2;
        bb = 255;
        break;
    case 1:
        rr = 0;
        gg = 255;
        bb = 255 - off*2;
        break;
    case 2:
        rr = 99 + off*2;
        gg = 255;
        bb = 0;
        break;
    case 3:
        rr = 255;
        gg = 255 - off*2;
        bb = 0;
        break;
    case 4:
        rr = 255;
        gg = 0;
        bb = 99 + off*2;
        break;
    default:
        rr = 255;
        gg = 99 + off*2;
        bb = 255;
        break;
    }

    s_pix_brightnessbar.fill(QColor(rr,gg,bb));
    s_brightnessbar->setPixmap(s_pix_brightnessbar);
}

void MBrightnessWidgetSettings::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    setBarWidth(ev->pos().x());
    ev->accept();
}

void MBrightnessWidgetSettings::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    setBarWidth(ev->pos().x());
    ev->accept();
}

void MBrightnessWidgetSettings::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    GConfItem("/apps/system-ui-extensions/brightness/red").set(rr);
    GConfItem("/apps/system-ui-extensions/brightness/green").set(gg);
    GConfItem("/apps/system-ui-extensions/brightness/blue").set(bb);
    event->accept();
}

void MBrightnessWidgetSettings::hide()
{
    setVisible(false);
}

void MBrightnessWidgetSettings::show()
{
    setVisible(true);
}

