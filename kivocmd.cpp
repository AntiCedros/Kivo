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
        {"show-ingredient", app->translate("cmd", "Prints the ingredient with <name>"), app->translate("cmd", "name")},
        {"create-recipe", app->translate("cmd", "Creates new recipe with <name>"), app->translate("cmd", "name")},
        {"create-ingredient", app->translate("cmd", "Creates new ingredient with <name>"), app->translate("cmd", "name")},
    });

    parser.process(app->arguments());

    QTextStream out(stdout);
    if (parser.isSet("create-ingredient")) {
        if (Database::addIngredient(parser.value("create-ingredient"))) {
            out << app->translate("cmd/create-ingredient", "Ingredient creation successful") << Qt::endl;
        } else {
            qWarning() << app->translate("cmd/create-ingredient", "Ingredient creation failed");
        }
    }
    if (parser.isSet("create-recipe")) {
        if (Database::addRecipe(parser.value("create-recipe"))) {
            out << app->translate("cmd/create-recipe", "Recipe creation successful") << Qt::endl;
        } else {
            qWarning() << app->translate("cmd/create-recipe", "Recipe creation failed");
        }
    }
    if (parser.isSet("show-ingredient")) {
        out << app->translate("cmd/show-ingredient", "Showing recipe '") + parser.value("show-ingredient") + app->translate("cmd/show-ingredient", "'") << Qt::endl;
    }
    if (parser.isSet("show-recipe")) {
        out << app->translate("cmd/show-recipe", "Showing recipe '") + parser.value("show-recipe") + app->translate("cmd/show-recipe", "'") << Qt::endl;
    }

    quit();
}

void KivoCMD::quit() { emit finished(); }

void KivoCMD::aboutToQuitApp() {}
