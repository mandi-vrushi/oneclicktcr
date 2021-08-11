#include "systemtray.h"

SystemTray::SystemTray(QObject *parent) : QObject(parent),
    trayIcon(new QSystemTrayIcon()),
    normalIcon(QIcon(QString(":/images/OCwhite.png"))),
    alertIcon(QIcon(QString(":/svg/cash-register-alert.svg"))),
    trayMenu(new QMenu())
{

}

void SystemTray::showOnTray()
{
    QAction *quitAction = new QAction(QObject::tr("&Quit"), this);
    QAction *openMainAction = new QAction(QObject::tr("Open &Main"), this);
    QAction *openSecondAction = new QAction(QObject::tr("Open &Second"), this);

    QObject::connect(quitAction, SIGNAL(triggered()), parent(), SLOT(quit()));
    QObject::connect(openMainAction, SIGNAL( triggered()), SLOT(alertOnTray()), Qt::QueuedConnection);
    QObject::connect(openSecondAction, SIGNAL(triggered()), SLOT(alertOnTray()), Qt::QueuedConnection);

    trayMenu->addAction(openMainAction);
    trayMenu->addAction(openSecondAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(normalIcon);
    trayIcon->show();

}

void SystemTray::alertOnTray(int instanceId, QByteArray msg)
{
    qInfo()<< "slot called from" << instanceId;
    qInfo()<< msg;
    alertTimer = new QTimer(this);
    connect(alertTimer, &QTimer::timeout, this, &SystemTray::alert, Qt::QueuedConnection );
    alertTimer->start(350);
}

void SystemTray::alert()
{
    switch (cnt % 2){
    case 0:
        trayIcon->setIcon(alertIcon);
        break;
    default:
        trayIcon->setIcon(normalIcon);
    }
    cnt++;
    if (cnt > 6) {
        cnt = 0;
        alertTimer->stop();
        trayIcon->setIcon(normalIcon);
        trayIcon->showMessage("Vëmendje!!!", "Aplikacioni eshte duke u egzekutuar.\nPërdorni ikonën ne TaskBar", alertIcon, 15000);
    }
}
