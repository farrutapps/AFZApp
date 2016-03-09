#include "classes/dbmanager.h"

DbManager::DbManager(const QString& path, QWidget *parent) : QWidget(parent)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
        m_db.setHostName("localhost");
        m_db.setDatabaseName("postgres");
        m_db.setUserName("postgres");
        m_db.setPassword("database");
        m_db.setPort(5432);

    if (!m_db.open()){
        cout << "Error: connection with database failed" << endl;
    }
    else{
        cout << "database connection ok!" << endl;
    }


}


bool DbManager::select_query(QString sql_query,vector <QString> &column_names,vector < vector <QString> > &output){
    // can output one column

    bool success = false;
    QSqlQuery query;

    query.prepare(sql_query);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success){
        cout << "print error: " << query.lastError().text().toStdString() << endl;
    }

    vector <int> ids;
    vector <QString> table_line;
    for (int i=0; i<column_names.size();++i){
         ids.push_back(query.record().indexOf(column_names[i]));
    }

    while (query.next()){
        for (int i=0; i<ids.size();++i){
            table_line.push_back(query.value(ids[i]).toString());
        }

        output.push_back(table_line);
        table_line.clear();
    }

return success;
}

bool DbManager::select_single_query(QString sql_query,QString column_name,vector <QString>  &output){
    // can output one column

    bool success = false;
    QSqlQuery query;

    query.prepare(sql_query);

    success = query.exec();

    if (!success){
        cout << "select_single_query error: " << query.lastError().text().toStdString() << endl;
    }

    int  id_column=query.record().indexOf(column_name);


    while (query.next()){
        output.push_back(query.value(id_column).toString());
    }

return success;
}

bool DbManager::insert_query(QString sql_query){
    bool success=false;
    QSqlQuery query;

    query.prepare(sql_query);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success)
        cout << "insert query error:" << query.lastError().text().toStdString()<< endl;

    emit database_changed();
    return success;
}
bool DbManager::insert_query(QString sql_query, QString id_name, int &id_of_insert){
    bool success=false;
    QSqlQuery query;

    query.prepare(sql_query);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success)
        cout << "insert query error:" << query.lastError().text().toStdString()<< endl;

    while (query.next()){
        id_of_insert=query.value(id_name).toInt();
    }

    emit database_changed();
    return success;
}

bool DbManager::count_lines(QString table, int &result){
    bool success = false;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM " + table);

    success = query.exec();

    if (!success){
        cout << "count_query error: " << query.lastError().text().toStdString() << endl;
    }

    int  id_column=query.record().indexOf("count");


    while (query.next()){
        result=query.value(id_column).toInt();
    }

return success;
}

bool DbManager::delete_query(QString sql_query){
    bool success = false;
    QSqlQuery query;

    query.prepare(sql_query);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success){
        cout << "delete error: " << query.lastError().text().toStdString() << endl;
    }


    emit database_changed();
    return success;
}
