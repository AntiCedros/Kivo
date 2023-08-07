#include "kivocmd.h"

KivoCMD::KivoCMD(QObject* parent)
    : QObject(parent) {
    app = QCoreApplication::instance();
}

void KivoCMD::run() {
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"s", "show-recipe"}, app->translate("cmd", "Prints the recipe with <title>"), app->translate("cmd", "title")},
        {"create-ingredient", app->translate("cmd", "Creates new ingredient with <name>"), app->translate("cmd", "name")},
    });

    parser.process(app->arguments());

    QTextStream out(stdout);
    if (parser.isSet("s")) {
        out << app->translate("cmd", "Showing recipe ") + "'" + parser.value("s") + "'" << Qt::endl;
    }
    if (parser.isSet("create-ingredient")) {
        if (Database::addIngredient(parser.value("create-ingredient"))) {
            out << app->translate("cmd", "Ingredient creation successful") << Qt::endl;
        } else {
            qWarning() << app->translate("cmd", "Ingredient creation failed");
        }
    }

    quit();
}

void KivoCMD::quit() { emit finished(); }

void KivoCMD::aboutToQuitApp() {}
