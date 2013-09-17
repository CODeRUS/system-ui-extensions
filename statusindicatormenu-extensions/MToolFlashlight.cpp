#include "MToolFlashlight.h"
#include <MFeedback>

MToolFlashlight::MToolFlashlight(QGraphicsItem *parent):
    MWidget(parent),
    poskey(new GConfItem("/apps/system-ui-extensions/tools/flashlight/index")),
    statuskey(new GConfItem("/apps/system-ui-extensions/tools/flashlight/working"))
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    icon_flash_on =  QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-flashlight-on.png");
    icon_flash_off = QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-flashlight-off.png");

    m_toggleicon = new MImageWidget(&icon_flash_off, this);
    m_toggleicon->setAspectRatioMode(Qt::KeepAspectRatio);
    m_toggleicon->setMaximumSize(64,64);
    m_toggleicon->setMinimumSize(64,64);

    fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);

    flash_active = false;

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));

    connect(poskey,
            SIGNAL(valueChanged()),
            SLOT(onIndexChanged()));
    connect(statuskey,
            SIGNAL(valueChanged()),
            SLOT(onStatusChanged()));
    index = poskey->value().toInt();
    status = statuskey->value().toBool();
}

void MToolFlashlight::hide()
{
}

void MToolFlashlight::show()
{
    if (fd == -1)
        fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);

    if (fd != -1)
    {
        mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
        mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
        ioctl(fd, VIDIOC_G_CTRL, &mode_ctrl);
        if (mode_ctrl.value != V4L2_FLASH_LED_MODE_NONE)
        {
            flash_active = true;
            m_toggleicon->setImage(icon_flash_on);
        }
        else
        {
            flash_active = false;
            m_toggleicon->setImage(icon_flash_off);
        }
    }
}

void MToolFlashlight::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    emit pressed();
}

void MToolFlashlight::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    emit released();
    if (m_toggleicon->geometry().contains(ev->pos()))
    {
        if (fd != -1)
        {
            if (flash_active)
            {
                mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
                mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
                if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) != -1)
                {
                    m_toggleicon->setImage(icon_flash_off);
                    flash_active = !flash_active;
                }
            }
            else
            {
                mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
                mode_ctrl.value = V4L2_FLASH_LED_MODE_TORCH;
                if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) != -1)
                {
                    m_toggleicon->setImage(icon_flash_on);
                    flash_active = !flash_active;
                }
            }
        }
    }
}

void MToolFlashlight::onIndexChanged()
{

        index = poskey->value().toInt();
        emit setIndex(index);

}

void MToolFlashlight::onStatusChanged()
{

        status = statuskey->value().toBool();
        emit setStatus(status, poskey->value().toInt());
        setVisible(status);

}
