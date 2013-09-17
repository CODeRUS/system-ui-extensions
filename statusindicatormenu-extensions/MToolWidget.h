#ifndef MTOOLWIDGETPROTO_H
#define MTOOLWIDGETPROTO_H

#include <MImageWidget>
#include <gq/GConfItem>

class MToolWidgetPrototype: public MImageWidget
{
    Q_OBJECT

public:
    explicit MToolWidgetPrototype(QString widget_name, QGraphicsItem *parent): MImageWidget(parent)
    {
        setMaximumSize(64,64);
        setMinimumSize(64,64);
        setAspectRatioMode(Qt::KeepAspectRatio);

        widget = widget_name;
        init();
    }

    int index;
    bool status;

    virtual void init();
    virtual void hide();
    virtual void show();

private:
    void settings_init()
    {
        if (widget != "")
        {
            index_key = new GConfItem(QString("/apps/system-ui-extensions/tools/%1/index").arg(widget));
            status_key = new GConfItem(QString("/apps/system-ui-extensions/tools/%1/working").arg(widget));

            index = index_key->value().toInt();
            status = status_key->value().toBool();
        }
    }

    void setIndex(int index_new)
    {
        index = index_new;
        index_key->set(index);
    }

    void setStatus(bool status_new)
    {
        status = status_new;
        status_key->set(status);
    }

    QString widget;
    GConfItem *index_key;
    GConfItem *status_key;

    QList<QString> images;

};

#endif // MTOOLWIDGET_H
