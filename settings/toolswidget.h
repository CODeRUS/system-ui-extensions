#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>

#include <MFlowLayoutPolicy>
#include <MLayout>
#include <QGraphicsSceneMouseEvent>

#include <stdio.h>
#include <QDebug>

#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>

#include "MImageWidgetEx.h"

class MToolsWidgetSettings : public MWidget
{
    Q_OBJECT

public:
    explicit MToolsWidgetSettings(QGraphicsItem *parent = 0);

    MFlowLayoutPolicy *m_mainLayout;
    MLayout *m_layout;

    QList<MImageWidgetEx*> items;

    MImageWidgetEx *bluetooth;
    MImageWidgetEx *cellular;
    MImageWidgetEx *flashlight;
    MImageWidgetEx *radio;
    MImageWidgetEx *psm;
    MImageWidgetEx *brightness;
    MImageWidgetEx *usb;
    MImageWidgetEx *reboot;
    MImageWidgetEx *bgconn;
    MImageWidgetEx *glol;

    MImageWidget *selection;

public slots:
    void hide();
    void show();
    void onEndMoving();
    void onStartMoving();

private:
    int newIndex;

    QList<QGraphicsLayoutItem*> m_items;
    QList<bool> m_visible;

    void refreshLayout();

protected:
    void exitDisplayEvent();
};


#endif // TOOLSWIDGET_H
