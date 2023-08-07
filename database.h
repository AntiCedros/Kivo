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

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
