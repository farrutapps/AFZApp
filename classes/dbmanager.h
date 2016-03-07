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

class DbManager : public QWidget
{
    Q_OBJECT

public:
    explicit DbManager(const QString& path, QWidget *parent = 0);


    bool select_query(QString sql_query, vector <QString> &column_names, vector < vector <QString> > &output);
    bool select_single_query(QString sql_query, QString column_name, vector < QString > &output);
    bool count_lines(QString table, int &result);
    bool insert_query(QString sql_query);
    bool delete_query(QString sql_query);
    bool enable_foreign_keys();


private:
    QSqlDatabase m_db;

signals:
    void database_changed();

public slots:

};

#endif // DBMANAGER_H
