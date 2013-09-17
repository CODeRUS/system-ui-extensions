#ifndef TOOLPSM_H
#define TOOLPSM_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <qmsystem2/qmbattery.h>
#include <QTimer>
#include <MLabel>
#include <qmsystem2/qmbattery.h>

class MToolPSM : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolPSM(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    MImageWidget *m_toggleicon;
    GConfItem *m_autopsm_GConfItem;
    GConfItem *m_forcepsm_GConfItem;
    MeeGo::QmBattery *battery;

    QImage icon_psm_on;
    QImage icon_psm_off;
    QImage icon_psm_auto;
    MLabel *percentage;

    QTimer *pressTime;
    bool longPressed;

    int nextState;

    void setPsmState(int state);
    GConfItem *poskey;
    GConfItem *statuskey;

    MeeGo::QmBattery *m_battery;

signals:
    void pressed();
    void released();
    void longpressed();
    void setIndex(int index);
    void setStatus(bool isActive, int index);

private slots:
    void onGConfChanged();
    void longPress();
    void onIndexChanged();
    void onStatusChanged();
};

#endif // TOOLPSM_H
