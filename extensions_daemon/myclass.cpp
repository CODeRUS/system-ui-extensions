#include <QFile>
#include "myclass.h"

MGConfController::MGConfController(QObject *parent) :
    QObject(parent),
    m_GConf_daemon(new GConfItem("/apps/system-ui-extensions/daemon/service")),
    m_GConf_reboot(new GConfItem("/apps/system-ui-extensions/daemon/reboot")),
    m_GConf_restore(new GConfItem("/apps/system-ui-extensions/daemon/restore")),
    m_GConf_remove(new GConfItem("/apps/system-ui-extensions/daemon/remove"))
{
    qDebug() << "GConf Controller Created;";

    m_GConf_daemon->set(true);

    m_GConf_reboot->set(false);
    connect(m_GConf_reboot,
            SIGNAL(valueChanged()),
            SLOT(doReboot()));

    m_GConf_restore->set("");
    connect(m_GConf_restore,
            SIGNAL(valueChanged()),
            SLOT(doRestore()));

    m_GConf_remove->set("");
    connect(m_GConf_remove,
            SIGNAL(valueChanged()),
            SLOT(doRemove()));
}

void MGConfController::doReboot()
{
    qDebug() << "GConf_reboot Value Changed;";
    if (m_GConf_reboot->value().toBool())
    {
        qDebug() << "reqReboot active!";
        m_GConf_reboot->blockSignals(true);
        m_GConf_reboot->set(false);
        m_GConf_daemon->set(false);
        m_GConf_reboot->blockSignals(false);
        QDBusInterface interface("com.nokia.dsme",
                                 "/com/nokia/dsme/request",
                                 "com.nokia.dsme.request",
                                 QDBusConnection::systemBus());
        interface.call("req_reboot");
    }
}

void MGConfController::doRestore()
{
    QString extension = m_GConf_restore->value().toString();
    QString template_path=QString("/usr/share/meegotouch/applicationextensions/statusindicatormenu-%1.desktop").arg(extension);
    QString template_data=QString("\"[Desktop Entry]\nType=X-MeeGoApplicationExtension\nName=Status Indicator Menu Applet\n\n[X-MeeGoApplicationExtension]\nInterface=com.meego.core.MStatusIndicatorMenuExtensionInterface/1.0\nExtension=libstatusindicatormenu-%1.so\"").arg(extension);
    system(QString("busybox echo %1 > %2").arg(template_data).arg(template_path).toAscii());

    m_GConf_restore->blockSignals(true);
    m_GConf_restore->set("");
    m_GConf_restore->blockSignals(false);
}

void MGConfController::doRemove()
{
    QString extension = m_GConf_remove->value().toString();
    QString filename = QString("/usr/share/meegotouch/applicationextensions/statusindicatormenu-%1.desktop").arg(extension);
    if (QFile(filename).exists())
        QFile(filename).remove();

    m_GConf_remove->blockSignals(true);
    m_GConf_remove->set("");
    m_GConf_remove->blockSignals(false);
}
