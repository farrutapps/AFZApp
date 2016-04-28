#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <iostream>
#include <QWidget>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>

using namespace std;

class DbManager
{


public:
    DbManager(const QString& path);


    bool selectQuery(QString sqlQuery, vector <QString> &columnNames, vector < vector <QString> > &output);
    bool selectSingleQuery(QString sqlQuery, QString columnName, vector < QString > &output);
    bool selectSingleQuery(QString sqlQuery, QString columnName, vector < int > &output);
    bool countLines(QString table, int &result);
    bool insertQuery(QString sqlQuery);
    bool insertQuery(QString sqlQuery, QString idName, int &idOfInsert);
    bool deleteQuery(QString sqlQuery);



private:
    QSqlDatabase mDb;

signals:


public slots:

};

#endif // DBMANAGER_H
