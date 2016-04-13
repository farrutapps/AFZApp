#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QUrl>
#include "classes/dbmanager.h"
#include "classes/questiondata.h"
#include "classes/filemanager.h"
#include "windows/calcwindow.h"
#include "windows/datainputpopup.h"

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
    void EvaluateSurvey(int survey_id, int surveytype_id);

signals:


public slots:
    void on_ActionButton_clicked();
    void ReadDatabase();
    void on_FindPathButton_clicked(bool path_is_set);
    void SaveToDatabase();


private:
    Ui::DbWindow *ui;
    DbManager *db_man;
    FileManager *f_man;
    DataInputPopup *NewPopup;
    QUrl file;
    CalcWindow * NewCalcWindow;
//    FileManager *f_man;
//    vector <questiondata> questions;

};

#endif // DBWINDOW_H
