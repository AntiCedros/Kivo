#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

using namespace std;

class Database {
public:
    Database();
    ~Database();
    static bool addIngredient(QString name);
    static bool addRecipe(QString name);
    static QString* getIngredient(QString name);
    static QString* getRecipe(QString name);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
