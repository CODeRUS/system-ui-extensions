#ifndef TOOLREBOOT_H
#define TOOLREBOOT_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include <gq/GConfItem>

class MToolReboot : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolReboot(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    MImageWidget *m_toggleicon;
    QImage icon_power;
    QImage icon_power_unloaded;
    QTimer *m_timer;
    int counter;

    void reqReboot();
    GConfItem *poskey;
    GConfItem *statuskey;
    GConfItem *service;


private slots:
    void onTimer();
    void onGConf();
    void onIndexChanged();
    void onStatusChanged();

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);
};

#endif // TOOLREBOOT_H
