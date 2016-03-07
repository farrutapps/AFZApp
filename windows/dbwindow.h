#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "classes/dbmanager.h"

namespace Ui {
class DbWindow;
}

class DbWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DbWindow(QWidget *parent = 0, DbManager * db_manager= 0 );
    ~DbWindow();

    void SetupTable();
    void SetupCombo();
    void DeleteSurvey(QString survey_id);


public slots:
    void on_ActionButton_clicked();
    void ReadDatabase();
private:
    Ui::DbWindow *ui;
    DbManager *db_man;

};

#endif // DBWINDOW_H
