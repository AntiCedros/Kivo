#include "kivocmd.h"

KivoCMD::KivoCMD(QObject* parent) : QObject(parent) {
    app = QCoreApplication::instance();
}

void KivoCMD::run() {
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"s", "show-recipe"},
            app->translate("cmd", "Prints the recipe with title <T>"),
            app->translate("cmd", "T")},
        {"show-ingredient",
            app->translate("cmd", "Prints the ingredient with name <N>"),
            app->translate("cmd", "N")},
        {"create-recipe",
            app->translate("cmd", "Creates new recipe with title <T>"),
            app->translate("cmd", "T")},
        {"create-ingredient",
            app->translate("cmd", "Creates new ingredient with name <N>"),
            app->translate("cmd", "N")},
    });

    parser.process(app->arguments());

    QTextStream out(stdout);
    if (parser.isSet("create-ingredient")) {
        if (Database::addIngredient(parser.value("create-ingredient"))) {
            out << app->translate("cmd/create-ingredient", "Ingredient creation successful")
                << Qt::endl;
        } else {
            qWarning() << app->translate("cmd/create-ingredient", "Ingredient creation failed");
        }
    }
    if (parser.isSet("create-recipe")) {
        if (Database::addRecipe(parser.value("create-recipe"))) {
            out << app->translate("cmd/create-recipe", "Recipe creation successful")
                << Qt::endl;
        } else {
            qWarning() << app->translate("cmd/create-recipe", "Recipe creation failed");
        }
    }
    if (parser.isSet("show-ingredient")) {
        QString* ingredient = Database::getIngredient(parser.value("show-ingredient"));
        if (!ingredient[0].contains("-1")) {
            out << app->translate("cmd/show-ingredient", "Showing ingredient '")
                << parser.value("show-ingredient")
                << app->translate("cmd/show-ingredient", "':")
                << Qt::endl;
            out << app->translate("cmd/show-ingredient", "    ID:   \t")
                << ingredient[0]
                << Qt::endl;
            out << app->translate("cmd/show-ingredient", "    Title:\t")
                << ingredient[1]
                << Qt::endl;
        } else {
            out << app->translate("cmd/show-ingredient", "Ingredient with name '")
                << parser.value("show-ingredient")
                << app->translate("cmd/show-ingredient", "' not found")
                << Qt::endl;
        }
    }
    if (parser.isSet("show-recipe")) {
        QString* recipe = Database::getRecipe(parser.value("show-recipe"));
        if (!recipe[0].contains("-1")) {
            out << app->translate("cmd/show-recipe", "Showing recipe '")
                << parser.value("show-recipe")
                << app->translate("cmd/show-recipe", "':")
                << Qt::endl;
            out << app->translate("cmd/show-recipe", "    ID:   \t")
                << recipe[0]
                << Qt::endl;
            out << app->translate("cmd/show-recipe", "    Title:\t")
                << recipe[1]
                << Qt::endl;
        } else {
            out << app->translate("cmd/show-recipe", "Recipe with title '")
                << parser.value("show-recipe")
                << app->translate("cmd/show-recipe", "' not found")
                << Qt::endl;
        }
    }

    quit();
}

void KivoCMD::quit() {
    emit finished();
}

void KivoCMD::aboutToQuitApp() {

}
