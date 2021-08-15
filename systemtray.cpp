#include "systemtray.h"


SystemTray::SystemTray(QObject *parent) : QObject(parent),
    trayIcon(new QSystemTrayIcon()),
    normalIcon(QIcon(QString(":/images/OCwhite.png"))),
    alertIcon(QIcon(QString(":/images/OC_green.png"))),
    trayMenu(new QMenu()),
    mEngine(new QQmlApplicationEngine()),
    alertTimer(new QTimer())
{
    mEngine->rootContext()->setContextProperty("trayIcon", this);

    connect(this->mEngine, &QQmlApplicationEngine::objectCreated, [=](QObject *obj, const QUrl url){
        obj->setObjectName(url.toString());
    });
    if(qApp->allWindows().isEmpty()){
        loadWindow(QUrl(QString("qrc:/main.qml")));
    }
}

void SystemTray::print(QString url)
{
    QList<QSerialPortInfo> serialPorts;
    serialPorts = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo portInfo:serialPorts){
        qInfo() << portInfo.portName() << portInfo.description() << portInfo.productIdentifier();
    }
    QString filename = QFileDialog::getOpenFileName(0,"Open File",QString(),"PNG File(*.png)");
    QPrinter printer;
    QPrintDialog  *dlg  = new QPrintDialog(&printer, 0);
    if (dlg->exec() == QDialog::Accepted) {
        QImage  img(filename);
        QPainter painter(&printer);
        painter.drawImage(QPoint(0,0), img);
        painter.end();

    }
}

void SystemTray::showOnTray()
{
    QAction *quitAction = new QAction(QObject::tr("&Quit"), this);
    QAction *openMainAction = new QAction(QObject::tr("&One Click TCR"), this);
    QAction *openSettingsAction = new QAction(QObject::tr("&Settings"), this);

    connect(quitAction, &QAction::triggered, parent(), &QApplication::quit );
    connect(this->alertTimer, &QTimer::timeout,this, &SystemTray::alert, Qt::QueuedConnection );
    connect(openMainAction, &QAction::triggered, this, [=](){
        loadWindow(QUrl(QString("qrc:/main.qml")));}, Qt::QueuedConnection);
    connect(openSettingsAction, &QAction::triggered, this, [=](){
        loadWindow(QUrl(QString("qrc:/second.qml")));}, Qt::QueuedConnection);

    trayMenu->addAction(openMainAction);
    trayMenu->addAction(openSettingsAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(normalIcon);
    trayIcon->show();

}

void SystemTray::alertOnTray()
{
    alertTimer->start(350);
}

void SystemTray::unloadWindow(QWindow *window)
{
    foreach(QWindow *win, qApp->allWindows()){
        if(win->objectName() == window->objectName()){
            win->deleteLater();
        }
    }
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
        loadWindow(QUrl(QString("qrc:/main.qml")));
        notifyUser();
    }
}

void SystemTray::loadWindow(QUrl url)
{
    bool isLoaded = false;
    foreach(QWindow *win, qApp->allWindows()){
        if(win->objectName() == url.toString()){
            isLoaded = true;
            switch (win->visibility()) {
            case QWindow::Hidden:
                win->show();
                break;
            case QWindow::Minimized:
                win->showNormal();
                break;
            default:
                win->raise();

            }
        }
    }
    if (!isLoaded) {
        mEngine->load(url);
    }
    qInfo() << qApp->allWindows();


}

void SystemTray::notifyUser()
{
    trayIcon->setIcon(normalIcon);
    trayIcon->showMessage("Vëmendje!!!", "Aplikacioni eshte duke u egzekutuar.\nPërdorni ikonën ne TaskBar", alertIcon, 15000);
}


