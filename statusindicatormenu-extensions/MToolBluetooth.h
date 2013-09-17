#ifndef TOOLBLUETOOTH_H
#define TOOLBLUETOOTH_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <QBluetoothLocalDevice>
#include <QTime>
#include <QTimer>

using namespace QtMobility;

class MToolBluetooth : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolBluetooth(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    QBluetoothLocalDevice *m_btLocalDevice;
    QBluetoothLocalDevice::HostMode m_mode;
    QBluetoothLocalDevice::HostMode m_nextmode;
    MImageWidget *m_toggleicon;
    QTimer *longAction;
    bool longPressed;

    QGraphicsSceneMouseEvent *myevent;

    QImage icon_active;
    QImage icon_inactive;
    QImage icon_discoverable;

    GConfItem *poskey;
    GConfItem *statuskey;


private slots:
    void onBluetoothStateChanged(QBluetoothLocalDevice::HostMode *mode);
    void LongPress();
    void onIndexChanged();
    void onStatusChanged();

signals:
    void pressed();
    void longpressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);
};



#endif // TOOLBLUETOOTH_H
