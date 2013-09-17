#ifndef MYCLASS_H
#define MYCLASS_H

#include <gq/GConfItem>
#include <QObject>

#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>

#include <QDebug>

class MGConfController : public QObject
{
    Q_OBJECT

public:
    explicit MGConfController(QObject *parent = 0);

private:
    GConfItem *m_GConf_daemon;
    GConfItem *m_GConf_reboot;
    GConfItem *m_GConf_restore;
    GConfItem *m_GConf_remove;
    GConfItem *m_GConf_refresh;
    
private slots:
    void doReboot();
    void doRestore();
    void doRemove();
    
};

#endif // MYCLASS_H
