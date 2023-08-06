#include <QCoreApplication>
#include <QLocale>
#include <QTimer>
#include <QTranslator>
#include "kivocmd.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setApplicationName("Kivo");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationName("AntiCedros");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Kivo_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    KivoCMD kivoCMD;

    QObject::connect(&kivoCMD, SIGNAL(finished()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(aboutToQuit()), &kivoCMD, SLOT(aboutToQuitApp()));

    QTimer::singleShot(10, &kivoCMD, SLOT(run()));

    return app.exec();
}
