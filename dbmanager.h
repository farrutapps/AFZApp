#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <iostream>
#include <QObject>
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
    DbManager();

 //   void setpath(QString path);
    bool select_query(QString sql_query, vector <QString> &column_names, vector < vector <QString> > &output);
    bool select_single_query(QString sql_query, QString column_name, vector < QString > &output);
    bool count_lines(QString table, int &result);
    bool insert_query(QString sql_query);


private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DBMANAGER_H
