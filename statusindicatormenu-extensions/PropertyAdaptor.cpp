#include <QtCore/QRegExp>
#include <QtCore/QDebug>
#include <QtDBus/QDBusMessage>

#include "PropertyAdaptor.h"

PropertyAdaptor::PropertyAdaptor(QObject *parent) :
    QDBusAbstractAdaptor(parent)
{

}

QString PropertyAdaptor::objectPath() const
{
    return QString("/org/maemo/contextkit/") +
            QString("Screen.TopEdge").replace(".", "/").replace(QRegExp("[^A-Za-z0-9_/]"), "_");
}

void PropertyAdaptor::setValue(QString value)
{
    m_value = value;

    if (value == "auto")
    {
        m_timestamp = 0;
    }
    else
    {
        m_timestamp = Q_INT64_C(-1);
    }

    emit ValueChanged(QVariantList() << m_value, m_timestamp);
}

void PropertyAdaptor::Subscribe(const QDBusMessage& msg, QVariantList& values, quint64& timestamp)
{
    Q_UNUSED(msg);
    values << m_value;
    timestamp = m_timestamp;
}

void PropertyAdaptor::Unsubscribe(const QDBusMessage& msg)
{
    Q_UNUSED(msg);
}
