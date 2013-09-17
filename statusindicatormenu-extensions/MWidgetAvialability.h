#ifndef AVIALABILITYWIDGET_H
#define AVIALABILITYWIDGET_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>

#include <QGraphicsLayoutItem>
#include <QGraphicsSceneMouseEvent>

#include <MFlowLayoutPolicy>

#include <TelepathyQt4/Constants>
#include <TelepathyQt4/Contact>
#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/ContactManager>
#include <TelepathyQt4/ContactFactory>
#include <TelepathyQt4/ChannelFactory>
#include <TelepathyQt4/ConnectionFactory>
#include <TelepathyQt4/AccountFactory>
#include <TelepathyQt4/PendingAccount>
#include <TelepathyQt4/PendingContactInfo>
#include <TelepathyQt4/PendingOperation>
#include <TelepathyQt4/PendingReady>
#include <TelepathyQt4/PendingStringList>
#include <TelepathyQt4/Account>
#include <TelepathyQt4/AccountSet>
#include <TelepathyQt4/Types>

#include <QtDBus>
#include <QDBusMessage>
#include <QDBusConnection>

class MWidgetAvialability : public MWidget
{
    Q_OBJECT

public:
    explicit MWidgetAvialability(QGraphicsItem *parent = 0);

    void hide();
    void show();

    MLayout *m_layout;
    MFlowLayoutPolicy *m_mainLayout;

private:
    Tp::AccountManagerPtr mAM;
    Tp::AccountPtr mAcc;
    Tp::ConnectionPtr mConnection;
    Tp::AccountSetPtr mAccSet;
    Tp::AccountFactoryPtr accountFactory;
    Tp::ConnectionFactoryPtr connectionFactory;
    Tp::ChannelFactoryPtr channelFactory;
    Tp::ContactFactoryPtr contactFactory;

private slots:
    void onReadyLoad(Tp::PendingOperation *op);
    void onAccountReady(Tp::PendingOperation *op);
    void onNewAccount(Tp::AccountPtr newaccount);
    void onAccountRemoved(QGraphicsLayoutItem *item, bool value);
};

#endif // AVIALABILITYWIDGET_H
