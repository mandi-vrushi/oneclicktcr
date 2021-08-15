#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QApplication>
#include <QQmlContext>
#include <QWindow>
#include <QSystemTrayIcon>
#include <QQmlApplicationEngine>
#include <QMenu>
#include <QAction>
#include <QTimer>

#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QFileDialog>
#include <QPainter>
#include <QSerialPort>
#include <QSerialPortInfo>

class SystemTray : public QObject
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = nullptr);
    Q_INVOKABLE void print(QString url);

public slots:
    void showOnTray();
    void alertOnTray();
    void unloadWindow(QWindow *window);

private:
    QQmlApplicationEngine *mEngine;
    QSystemTrayIcon *trayIcon;
    QIcon normalIcon;
    QIcon alertIcon;
    QMenu *trayMenu;
    QTimer *alertTimer;
    QWindow *mainWindow;
    int cnt = 0;
private slots:
    void alert();
    void loadWindow(QUrl url);
    void notifyUser();

};

#endif // SYSTEMTRAY_H
