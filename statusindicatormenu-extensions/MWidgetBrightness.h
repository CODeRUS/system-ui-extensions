#ifndef WIDGETBRIGHTNESS_H
#define WIDGETBRIGHTNESS_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QSizeF>

#include <MLabel>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <QTime>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusObjectPath>
#include <QDBusMessage>

class MWidgetBrightness : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);
    void enterDisplayEvent();

public:
    explicit MWidgetBrightness(QGraphicsItem *parent = 0);
    virtual ~MWidgetBrightness();
    void hide();
    void show();

private:
    MImageWidget *backgroundbar;
    MImageWidget *brightnessbar;
    MImageWidget *alpha0;
    GConfItem *m_brightnessGConfItem;

    GConfItem *m_bar_red;
    GConfItem *m_bar_green;
    GConfItem *m_bar_blue;

    void setBarWidthMove(int width);
    void setBarWidthPress(int width);

    QTime interval;
    QPixmap pix_brightnessbar;

private slots:
    void onValueChanged();

public slots:
    Q_SCRIPTABLE void setColor(int red, int green, int blue);

};

#endif // BRIGHTNESSWIDGET_H
