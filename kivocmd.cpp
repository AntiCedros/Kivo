#include "kivocmd.h"

KivoCMD::KivoCMD(QObject *parent)
    : QObject(parent)
{
    app = QCoreApplication::instance();
}

void KivoCMD::run()
{
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"s", "show-recipe"},
         app->translate("cmd", "Prints the recipe with <title>"),
         app->translate("cmd", "title")},
    });

    parser.process(app->arguments());

    if (parser.isSet("s")) {
        QTextStream out(stdout);
        out << app->translate("cmd", "Showing recipe '") + parser.value("s") + "'" << endl;
    }

    quit();
}

void KivoCMD::quit()
{
    emit finished();
}

void KivoCMD::aboutToQuitApp() {}
