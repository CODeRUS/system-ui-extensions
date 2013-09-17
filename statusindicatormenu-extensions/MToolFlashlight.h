#ifndef TOOLFLASHLIGHT_H
#define TOOLFLASHLIGHT_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>

#include <cstdio>
#include <cstring>

#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#define V4L2_CTRL_CLASS_FLASH           0x009c0000
#define V4L2_CID_FLASH_CLASS_BASE       (V4L2_CTRL_CLASS_FLASH | 0x900)
#define V4L2_CID_FLASH_TORCH_INTENSITY  (V4L2_CID_FLASH_CLASS_BASE + 8)
#define V4L2_CID_FLASH_LED_MODE         (V4L2_CID_FLASH_CLASS_BASE + 1)

enum v4l2_flash_led_mode {
    V4L2_FLASH_LED_MODE_NONE,
    V4L2_FLASH_LED_MODE_FLASH,
    V4L2_FLASH_LED_MODE_TORCH
};

class MToolFlashlight : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolFlashlight(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    MImageWidget *m_toggleicon;

    QImage icon_flash_on;
    QImage icon_flash_off;

    bool flash_active;

    void setFlashActive(bool active);
    GConfItem *poskey;
    GConfItem *statuskey;

    int fd;
    v4l2_control mode_ctrl;

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);

private slots:
    void onIndexChanged();
    void onStatusChanged();
};

#endif // TOOLFLASHLIGHT_H
