#include "AccountWrapper.h"
#include <MFeedback>

AccountWrapper::AccountWrapper(QGraphicsItem *parent, Tp::AccountPtr account):
    MWidget(parent),
    m_account(account)
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);

    MFeedback* feedback1 = new MFeedback("priority2_static_press", this);
    connect(this, SIGNAL(pressed()), feedback1, SLOT(play()));
    MFeedback* feedback2 = new MFeedback("priority2_static_release", this);
    connect(this, SIGNAL(released()), feedback2, SLOT(play()));
    MFeedback* feedback3 = new MFeedback("priority2_grab", this);
    connect(this, SIGNAL(longpressed()), feedback3, SLOT(play()));

    m_iconService = new MImageWidget("icon-m-service-icq", this);
    m_iconService->setAspectRatioMode(Qt::KeepAspectRatio);
    m_iconService->setMaximumSize(64,64);
    m_iconService->setMinimumSize(64,64);
    m_iconService->setPos(0,0);

    m_iconPresence = new MImageWidget("icon-m-common-presence-unknown", this);
    m_iconPresence->setAspectRatioMode(Qt::KeepAspectRatio);
    m_iconPresence->setMaximumSize(24,24);
    m_iconPresence->setPos(40, 0);
    currentIconId = presenceToIconId(m_account->currentPresence());
    requestedIconId = presenceToIconId(m_account->requestedPresence());

    if (m_account->currentPresence().type() == Tp::ConnectionPresenceTypeOffline)
        nextPresence = Tp::Presence(Tp::ConnectionPresenceTypeAvailable, "", "");
    else
        nextPresence = Tp::Presence(Tp::ConnectionPresenceTypeOffline, "", "");

    m_iconPresence->setImage(currentIconId);

    isFakePresence = false;

    m_account->setConnectsAutomatically(false);

    QString serviceName = m_account->serviceName();
    Accounts::Manager *manager = new Accounts::Manager();
    Accounts::Service *service = manager->service(serviceName);
    QString serviceIconId = service->iconName();

    m_iconService->setImage(serviceIconId);

    connect(m_account.data(),
            SIGNAL(changingPresence(bool)),
            SLOT(onChangingPresence(bool)));

    connect(m_account.data(),
            SIGNAL(currentPresenceChanged(Tp::Presence)),
            SLOT(onCurrentPresenceChanged(Tp::Presence)));

    connect(m_account.data(),
            SIGNAL(requestedPresenceChanged(Tp::Presence)),
            SLOT(onRequestedPresenceChanged(Tp::Presence)));

    connect(m_account.data(),
            SIGNAL(removed()),
            SLOT(onRemoved()));

    connect(m_account.data(),
            SIGNAL(stateChanged(bool)),
            SLOT(onStateChanged(bool)));

    presenceFaker = new QTimer(this);
    connect(presenceFaker, SIGNAL(timeout()), this, SLOT(fakerupdate()));

    pressTime = new QTimer(this);
    pressTime->setSingleShot(true);
    pressTime->setInterval(800);
    connect(pressTime, SIGNAL(timeout()), this, SLOT(openPresence()));
}

void AccountWrapper::openPresence()
{
    emit longpressed();
    longPressed = true;
}

void AccountWrapper::init_state()
{
    if (!m_account->isEnabled())
        emit accountRemoved(this, false);
}

void AccountWrapper::fakerupdate()
{
    isFakePresence = !isFakePresence;
    if (isFakePresence)
        m_iconPresence->setImage(requestedIconId);
    else
        m_iconPresence->setImage(currentIconId);

    if (fakeTime.elapsed() > 60000)
    {
        m_iconPresence->setImage(currentIconId);
        presenceFaker->stop();
    }
}

void AccountWrapper::onChangingPresence(bool value)
{
    if (value)
        presenceFaker->start(750);
    else
        presenceFaker->stop();
    fakeTime.start();
    fakeTime.restart();
}

void AccountWrapper::onCurrentPresenceChanged(const Tp::Presence &presence)
{
    currentIconId = presenceToIconId(presence);
    m_iconPresence->setImage(currentIconId);

    if (presence.type() == Tp::ConnectionPresenceTypeOffline)
        nextPresence = Tp::Presence(Tp::ConnectionPresenceTypeAvailable, "", "");
    else
        nextPresence = Tp::Presence(Tp::ConnectionPresenceTypeOffline, "", "");
}

void AccountWrapper::onRequestedPresenceChanged(const Tp::Presence &presence)
{
    requestedIconId = presenceToIconId(presence);
}

void AccountWrapper::onRemoved()
{
    emit accountRemoved(this, false);
}

void AccountWrapper::onStateChanged(bool value)
{
    emit accountRemoved(this, value);
}

QString AccountWrapper::presenceToIconId(Tp::Presence presence)
{
    switch (presence.type())
    {
    case Tp::ConnectionPresenceTypeOffline:     return "icon-m-common-presence-offline";
    case Tp::ConnectionPresenceTypeAvailable:   return "icon-m-common-presence-online";
    case Tp::ConnectionPresenceTypeAway:        return "icon-m-common-presence-away";
    case Tp::ConnectionPresenceTypeBusy:        return "icon-m-common-presence-busy";
    case Tp::ConnectionPresenceTypeHidden:      return "icon-m-common-presence-unknown";
    default:                                    return "icon-m-common-presence-away";
    }
}

void AccountWrapper::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    Q_UNUSED(ev);

    pressTime->start();
    emit pressed();
    longPressed = false;
}

void AccountWrapper::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if (m_iconService->geometry().contains(ev->pos()))
    {
        if (!longPressed)
        {
            emit released();
            m_account->setRequestedPresence(nextPresence);
            pressTime->stop();
        }
        else
        {
            system(QString("qdbus com.nokia.Presence-ui / com.nokia.PresenceUiInterface.showPresenceUi").toAscii());
        }
    }
}

void AccountWrapper::hide()
{
    setVisible(false);
}

void AccountWrapper::show()
{
    setVisible(true);
}

