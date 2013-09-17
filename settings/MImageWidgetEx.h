#ifndef MIMAGEWIDGETEX_H
#define MIMAGEWIDGETEX_H

#include <MImageWidget>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <gq/GConfItem>

#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>

class MImageWidgetEx : public MWidget
{
    Q_OBJECT
public:
    explicit MImageWidgetEx(QString gconfname, const QString &id = "", QGraphicsItem *parent = 0);
    void setGrayed(bool isGrayed);
    bool isGrayed();
    void setIndex(int index);
    int index;
    bool status;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void cancelEvent(MCancelEvent *event);

signals:
    void pressed();
    void released();
    void longpressed();

private:
    QTimer *m_timer;
    MImageWidget *image;
    MImageWidget *grayed;
    QString poskeyname;
    QString statuskeyname;

private slots:
    void longpress();

};


#endif // MIMAGEWIDGETEX_H
