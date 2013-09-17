#ifndef PROPERTYADAPTOR_H
#define PROPERTYADAPTOR_H

#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusConnection>

class PropertyAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.maemo.contextkit.Property")

public:
    explicit PropertyAdaptor(QObject* parent);
    QString objectPath() const;

signals:
    void ValueChanged(const QVariantList &values, const quint64& timestamp);

public slots:
    void Subscribe(const QDBusMessage& msg, QVariantList& values, quint64& timestamp);
    void Unsubscribe(const QDBusMessage& msg);
    void setValue(QString value);

private:
    QVariant m_value;
    quint64 m_timestamp;

};

#endif // PROPERTYADAPTOR_H
