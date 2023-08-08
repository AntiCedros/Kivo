#include "database.h"

Database::Database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QFile databaseFile(QCoreApplication::applicationDirPath() + "/Kivo.db");
    db.setDatabaseName(databaseFile.fileName());
    if (!databaseFile.exists()) {
        db.open();
        QFile databaseDump(":/Kivo.sql");
        databaseDump.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&databaseDump);
        while (!in.atEnd()) {
            QString query = "";
            QString line;
            do {
                line = in.readLine();
                query.append(line);
            } while (!line.endsWith(';'));

            QSqlQuery sqlQuery(query);
            if (!sqlQuery.exec()) {
                qCritical() << "Error during initial database creation; last query was: "
                            << sqlQuery.lastQuery();
            }
        }
    } else {
        db.open();
    }
}

Database::~Database() {
    db.close();
}

bool Database::addIngredient(QString name) {
    QSqlQuery query;
    query.prepare("INSERT INTO Ingredients (IngredientName) VALUES (:name)");
    query.bindValue(":name", name);
    return query.exec();
}

bool Database::addRecipe(QString name) {
    QSqlQuery query;
    query.prepare("INSERT INTO Recipes (RecipeName) VALUES (:name)");
    query.bindValue(":name", name);
    return query.exec();
}

QString* Database::getIngredient(QString name) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Ingredients WHERE IngredientName=(:name)");
    query.bindValue(":name", name);
    query.exec();
    if (query.first()) {
        QString* ingredient = new QString[]{
            query.value(0).toString(),
            query.value(1).toString()
        };
        return ingredient;
    } else {
        QString* noIngredient = new QString[]{
            "-1"
        };
        return noIngredient;
    }
}

QString* Database::getRecipe(QString name) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Recipes WHERE RecipeName=(:name)");
    query.bindValue(":name", name);
    query.exec();
    if (query.first()) {
        QString* recipe = new QString[]{
            query.value(0).toString(),
            query.value(1).toString()
        };
        return recipe;
    } else {
        QString* noRecipe = new QString[]{
            "-1"
        };
        return noRecipe;
    }
}
