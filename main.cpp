//#include <QApplication>
#include  <singleapplication/singleapplication.h>
#include <QSettings>
#include <QQuickStyle>
#include <QIcon>
#include <QTranslator>
#include "systemtray.h"
#include "windowloader.h"
#include <QDebug>



int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    SingleApplication app(argc, argv, false, SingleApplication::Mode::System | SingleApplication::Mode::SecondaryNotification, 100);
    QCoreApplication::setOrganizationName("Click");
    QCoreApplication::setOrganizationDomain("click.al");
    QCoreApplication::setApplicationName("One Click TCR");
    QCoreApplication::setApplicationVersion("0.1.0");

    QSettings settings;

    app.setQuitOnLastWindowClosed(false);
    QQuickStyle::setStyle("Material");


    SystemTray *sysTray = new SystemTray(&app);
    QObject::connect(&app, &SingleApplication::instanceStarted, sysTray, &SystemTray::alertOnTray , Qt::QueuedConnection);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "OneClickTCR_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }


    QIcon appIcon = QIcon(QString(":/images/AppIcon.png"));
    app.setWindowIcon(appIcon);

    sysTray->showOnTray();
    QPrinter *printer = new QPrinter();
    QPrintDialog printDialog(printer);
    printDialog.open();
    return app.exec();
}
