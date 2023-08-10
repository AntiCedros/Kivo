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
    //! Database class constructor
    /*!
      Checks for existance of database file.
      If it exists, opens it; if not, creates and populates an new one, then opens it.
     */
    Database();

    //! Database class destructor
    ~Database();

    //! Writes new ingredient of given \a name to the database.
    /*!
      \param name QString with the ingredient's name in unlocalized form.
      \return Success as bool
     */
    static bool addIngredient(QString name);

    //! Writes new recipe of given \a title to the database.
    /*!
      \param title QString with the recipe's title in unlocalized form.
      \return Success as bool
     */
    static bool addRecipe(QString title);

    //! Reads an ingredient of given \a name from the database.
    /*!
      \param name QString with the ingredient's name in unlocalized form.
      \return Pointer to QString array with values for all columns
     */
    static QString* getIngredient(QString name);

    //! Reads a recipe of given \a title from the database.
    /*!
      \param title QString with the recipe's title in unlocalized form.
      \return Pointer to QString array with values for all columns
     */
    static QString* getRecipe(QString title);

private:
    //! Database variable.
    /*! A QSqlDatabase containing all recipe and ingredient information. */
    QSqlDatabase db;
};

#endif // DATABASE_H
