#ifndef BRIGHTNESSWIDGET_H
#define BRIGHTNESSWIDGET_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>

#include <MLabel>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>

class MBrightnessWidgetSettings : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    explicit MBrightnessWidgetSettings(QGraphicsItem *parent = 0);

    void hide();
    void show();

private:
    MImageWidget *s_backgroundbar;
    MImageWidget *s_brightnessbar;
    GConfItem *s_brightnessGConfItem;

    QPixmap s_pix_brightnessbar;
    int rr;
    int gg;
    int bb;

    void setBarWidth(int width);


private slots:
    void onValueChanged();

};

#endif // BRIGHTNESSWIDGET_H
