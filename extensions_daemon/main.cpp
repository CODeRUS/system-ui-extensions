#include <QtCore/QCoreApplication>

#include <stdio.h>
#include <signal.h>
#include <gq/GConfItem>

#include "myclass.h"

static void handleSignal(int signal)
{
    printf(QString("Killed with signal: %1\n").arg(signal).toAscii());
    GConfItem("/apps/system-ui-extensions/tools/reboot/last_signal_killed").set(signal);
    QCoreApplication::instance()->exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGINT, handleSignal);
    signal(SIGHUP, handleSignal);
    signal(SIGTERM, handleSignal);
    signal(SIGKILL, handleSignal);
    signal(SIGUSR1, handleSignal);
    signal(SIGUSR2, handleSignal);

    new MGConfController();

    return a.exec();
}
