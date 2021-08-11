#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <Qmenu>
#include <QAction>
#include <QTimer>

class SystemTray : public QObject
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = nullptr);
public slots:
    void showOnTray();
    void alertOnTray(int instanceId, QByteArray msg);

signals:
        int loadWindow();

private:
    QSystemTrayIcon *trayIcon;
    QIcon normalIcon;
    QIcon alertIcon;
    QMenu *trayMenu;
    QTimer *alertTimer;
    int cnt = 0;
private slots:
    void alert();
};

#endif // SYSTEMTRAY_H
