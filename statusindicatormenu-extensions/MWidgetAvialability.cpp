#include "MWidgetAvialability.h"
#include "AccountWrapper.h"

MWidgetAvialability::MWidgetAvialability(QGraphicsItem *parent):
    MWidget(parent)
{
    m_layout = new MLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setMaximumWidth(480);

    m_mainLayout = new MFlowLayoutPolicy(m_layout);
    m_mainLayout->setContentsMargins(10,0,0,0);
    m_mainLayout->setSpacing(12);
    m_mainLayout->setVerticalSpacing(16);

    registerDBusObject();
    Tp::registerTypes();

    const QDBusConnection &bus = QDBusConnection::sessionBus();
    accountFactory =        Tp::AccountFactory::create(bus,
         Tp::Features() << Tp::Account::FeatureCore
                        << Tp::Account::FeatureAvatar
                        << Tp::Account::FeatureCapabilities
                        << Tp::Account::FeatureProfile
                        << Tp::Account::FeatureProtocolInfo);
    connectionFactory =     Tp::ConnectionFactory::create(bus,
         Tp::Features() << Tp::Connection::FeatureConnected
                        << Tp::Connection::FeatureCore
                        << Tp::Connection::FeatureRoster
                        << Tp::Connection::FeatureSimplePresence
                        << Tp::Connection::FeatureRosterGroups);
    channelFactory =        Tp::ChannelFactory::create(bus);
    contactFactory =        Tp::ContactFactory::create(
         Tp::Features() << Tp::Contact::FeatureAlias
                        << Tp::Contact::FeatureAvatarToken
                        << Tp::Contact::FeatureAvatarData
                        << Tp::Contact::FeatureSimplePresence
                        << Tp::Contact::FeatureInfo
                        << Tp::Contact::FeatureLocation
                        << Tp::Contact::FeatureCapabilities);
    mAM =                   Tp::AccountManager::create(bus,
                                                       accountFactory,
                                                       connectionFactory,
                                                       channelFactory,
                                                       contactFactory);

    connect(mAM->becomeReady(Tp::AccountManager::FeatureCore),
                SIGNAL(finished(Tp::PendingOperation*)),
                SLOT(onReadyLoad(Tp::PendingOperation*)));
}

void MWidgetAvialability::onReadyLoad(Tp::PendingOperation *op)
{
    Q_UNUSED(op);

    mAccSet = mAM->validAccounts();

    foreach (Tp::AccountPtr account, mAccSet->accounts())
        if (!account->cmName().count(QRegExp("ring|mmscm")))
        {
            connect(account->becomeReady(),
                    SIGNAL(finished(Tp::PendingOperation*)),
                    SLOT(onAccountReady(Tp::PendingOperation*)));
        }

    connect(mAM.data(),
            SIGNAL(newAccount(Tp::AccountPtr)),
            SLOT(onNewAccount(Tp::AccountPtr)));
}

void MWidgetAvialability::onNewAccount(Tp::AccountPtr newaccount)
{
    connect(newaccount->becomeReady(),
            SIGNAL(finished(Tp::PendingOperation*)),
            SLOT(onAccountReady(Tp::PendingOperation*)));
}

void MWidgetAvialability::onAccountReady(Tp::PendingOperation *op)
{
    Tp::AccountPtr account = Tp::AccountPtr::staticCast(op->object());
    AccountWrapper *wrapper = new AccountWrapper(this, account);
    m_mainLayout->addItem(wrapper);

    connect(wrapper,
            SIGNAL(accountRemoved(QGraphicsLayoutItem*, bool)),
            SLOT(onAccountRemoved(QGraphicsLayoutItem*, bool)));

    wrapper->init_state();
}

void MWidgetAvialability::onAccountRemoved(QGraphicsLayoutItem *item, bool value)
{
    if (value)
        m_mainLayout->addItem(item);
    else
        m_mainLayout->removeItem(item);
}


void MWidgetAvialability::hide()
{
    setVisible(false);
}

void MWidgetAvialability::show()
{
    setVisible(true);
}
