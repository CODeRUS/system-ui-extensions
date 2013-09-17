#ifndef TOOLBRIGHTNESS_H
#define TOOLBRIGHTNESS_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>

class MToolBrightness : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolBrightness(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    GConfItem *m_brightnessGConfItem;
    MImageWidget *m_toggleicon;

    QImage icon_brightness_min;
    QImage icon_brightness_med;
    QImage icon_brightness_max;

    int nextValue;
    GConfItem *poskey;
    GConfItem *statuskey;


private slots:
    void onValueChanged();
    void onIndexChanged();
    void onStatusChanged();

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);
};

#endif // TOOLBRIGHTNESS_H
