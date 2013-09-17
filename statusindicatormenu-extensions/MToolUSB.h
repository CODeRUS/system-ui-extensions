#ifndef TOOLUSB_H
#define TOOLUSB_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>

class MToolUSB : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolUSB(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    GConfItem *m_usbmode_GConfItem;
    GConfItem *m_devmode_GConfItem;
    MImageWidget *m_toggleicon;

    QImage icon_usb_ask;
    QImage icon_usb_sync;
    QImage icon_usb_mass;
    QImage icon_usb_sdk;
    QImage icon_usb_charging;

    QString nextValue;

    GConfItem *poskey;
    GConfItem *statuskey;

private slots:
    void onUsbValueChanged();
    void onIndexChanged();
    void onStatusChanged();

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);
};

#endif // TOOLUSB_H
