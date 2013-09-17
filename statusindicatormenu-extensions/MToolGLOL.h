#ifndef TOOLGLOL_H
#define TOOLGLOL_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <QTimer>
#include <QtDBus/QDBusConnection>
#include <gq/GConfItem>

#include "PropertyAdaptor.h"

class MToolGLOL : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolGLOL(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    MImageWidget *m_toggleicon;

    QImage icon_glol_portait;
    QImage icon_glol_landscape;
    QImage icon_glol_auto;

    QTimer *pressTime;
    bool longPressed;

    QDBusConnection bus;
    PropertyAdaptor *adaptor;
    int currentstate;

    GConfItem *poskey;
    GConfItem *statuskey;

    void setGLOLState();

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);

private slots:
    void longPress();
    void onIndexChanged();
    void onStatusChanged();

};

#endif // TOOLGLOL_H
