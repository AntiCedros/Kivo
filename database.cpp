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
                qCritical() << "Error during initial database creation; last query was: " << sqlQuery.lastQuery();
            }
        }
    } else {
        db.open();
    }
}

Database::~Database() { db.close(); }

bool Database::addIngredient(QString name) {
    QSqlQuery query;
    query.prepare("INSERT INTO Ingredients (IngredientName) VALUES (:name)");
    query.bindValue(":name", name);
    return query.exec();
}
