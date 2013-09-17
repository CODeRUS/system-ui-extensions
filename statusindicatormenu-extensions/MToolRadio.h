#ifndef TOOLRADIO_H
#define TOOLRADIO_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <CellularQt/SystemControl>

class MToolRadio : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolRadio(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    Cellular::SystemControl *m_radio;
    MImageWidget *m_toggleicon;

    QImage icon_radio_off;
    QImage icon_radio_on;

    int m_nextmode;
    GConfItem *poskey;
    GConfItem *statuskey;


private slots:
    void onPowerChanged(bool mode);
    void onIndexChanged();
    void onStatusChanged();

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);
};

#endif // TOOLRADIO_H
