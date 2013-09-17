#ifndef TOOLBGCONN_H
#define TOOLBGCONN_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <QTimer>

class MToolBGConn : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolBGConn(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    MImageWidget *m_toggleicon;
    GConfItem *m_GConfItem;

    QImage icon_bg_on;
    QImage icon_bg_off;

    GConfItem *poskey;
    GConfItem *statuskey;

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);

private slots:
    void onGConfChanged();
    void onIndexChanged();
    void onStatusChanged();
};

#endif // TOOLBGCONN_H
