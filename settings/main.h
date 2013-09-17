#ifndef MAIN_H
#define MAIN_H

#include <DcpAppletIf>
#include <QObject>
class DcpWidget;
class MAction;

class StatusMenuExtensionsApplet : public QObject, public DcpAppletIf
{
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

public:
    virtual void init();
    virtual DcpWidget* constructWidget(int widgetId);

    virtual DcpWidget* pageMain();
/*  Applet can have more 'pages'. Each page must be a DcpWidget subclass
    virtual DcpWidget* page1();
    virtual DcpWidget* page2();
*/
    virtual QString title() const;
    virtual QVector<MAction *> viewMenuItems();
    virtual DcpBrief* constructBrief(int);
};

#endif // MAIN_H
