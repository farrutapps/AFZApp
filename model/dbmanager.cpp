#include "classes/dbmanager.h"

DbManager::DbManager(const QString& path, QWidget *parent) : QWidget(parent)
{
    mDb = QSqlDatabase::addDatabase("QPSQL");
        mDb.setHostName("localhost");
        mDb.setDatabaseName("postgres");
        mDb.setUserName("postgres");
        mDb.setPassword("database");
        mDb.setPort(5432);

    if (!mDb.open()){
        cout << "Error: connection with database failed" << endl;
    }
    else{
        cout << "database connection ok!" << endl;
    }


}


bool DbManager::selectQuery(QString sqlQuery, vector <QString> &columnNames, vector < vector <QString> > &output){
    // can output one column

    bool success = false;
    QSqlQuery query;

    query.prepare(sqlQuery);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success){
        cout << "select query error: " << query.lastError().text().toStdString() << endl;
    }

    vector <int> ids;
    vector <QString> table_column;
    for (int i=0; i<columnNames.size();++i){
         ids.push_back(query.record().indexOf(columnNames[i]));
    }

    int ids_size=ids.size();
    output.resize(ids_size);

    while (query.next()){
        for (int i=0; i<ids_size;++i){
            output[i].push_back(query.value(ids[i]).toString());
        }
    }

return success;
}

bool DbManager::selectSingleQuery(QString sql_query, QString columnName, vector <QString>  &output){
    // can output one column

    bool success = false;
    QSqlQuery query;

    query.prepare(sql_query);

    success = query.exec();

    if (!success){
        cout << "select_single_query error: " << query.lastError().text().toStdString() << endl;
    }

    int  id_column=query.record().indexOf(columnName);


    while (query.next()){
        output.push_back(query.value(id_column).toString());
    }

return success;
}

bool DbManager::selectSingleQuery(QString sqlQuery, QString columnName, vector <int>  &output){
    // can output one column

    bool success = false;
    QSqlQuery query;

    query.prepare(sqlQuery);

    success = query.exec();

    if (!success){
        cout << "select_single_query error: " << query.lastError().text().toStdString() << endl;
    }

    int  idColumn=query.record().indexOf(columnName);


    while (query.next()){
        output.push_back(query.value(idColumn).toInt());
    }

return success;
}

bool DbManager::insertQuery(QString sqlQuery){
    bool success=false;
    QSqlQuery query;

    query.prepare(sqlQuery);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success)
        cout << "insert query error:" << query.lastError().text().toStdString()<< endl;


    return success;
}
bool DbManager::insertQuery(QString sqlQuery, QString idName, int &idOfInsert){
    bool success=false;
    QSqlQuery query;

    query.prepare(sqlQuery);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success)
        cout << "insert query error:" << query.lastError().text().toStdString()<< endl;

    while (query.next()){
        idOfInsert=query.value(idName).toInt();
    }


    return success;
}

bool DbManager::countLines(QString table, int &result){
    bool success = false;
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM " + table);

    success = query.exec();

    if (!success){
        cout << "count_query error: " << query.lastError().text().toStdString() << endl;
    }

    int  idColumn=query.record().indexOf("count");


    while (query.next()){
        result=query.value(idColumn).toInt();
    }

return success;
}

bool DbManager::deleteQuery(QString sqlQuery){
    bool success = false;
    QSqlQuery query;

    query.prepare(sqlQuery);

    success = query.exec();
    cout << query.executedQuery().toStdString() << endl;

    if (!success){
        cout << "delete error: " << query.lastError().text().toStdString() << endl;
    }


    databaseChanged();
    return success;
}
