#ifndef TOOLCELLULAR_H
#define TOOLCELLULAR_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <CellularQt/radioaccess.h>
#include <CellularQt/SystemControl>

class MToolCellular : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);

public:
    explicit MToolCellular(QGraphicsItem *parent = 0);

    void hide();
    void show();

    int index;
    bool status;

private:
    Cellular::RadioAccess *m_radio;
    MImageWidget *m_toggleicon;

    QImage icon_2g;
    QImage icon_3g;
    QImage icon_dual;

    int m_nextmode;
    GConfItem *poskey;
    GConfItem *statuskey;


private slots:
    void onModeChanged(int mode);
    void onIndexChanged();
    void onStatusChanged();

signals:
    void pressed();
    void released();
    void setIndex(int index);
    void setStatus(bool isActive, int index);
};

#endif // TOOLCELLULAR_H
