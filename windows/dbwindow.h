#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QUrl>
#include "classes/dbmanager.h"
#include "classes/question.h"
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
    explicit DbWindow(QWidget *parent = 0, DbManager * dbManager= 0 );
    ~DbWindow();

    void setupTable();
    void setupCombo();
    void deleteSurvey(QString survey_id);
    void evaluateSurvey(int survey_id, int surveytype_id);

signals:


public slots:
    void on_ActionButton_clicked();
    void readDatabase();
    void on_FindPathButton_clicked(bool path_is_set);
    void saveToDatabase();


private:
    Ui::DbWindow *ui;
    DbManager *dbMan;
    FileManager *fMan;
    DataInputPopup *newPopup;
    QUrl file;
    CalcWindow *newCalcWindow;
//    FileManager *f_man;
//    vector <questiondata> questions;

};

#endif // DBWINDOW_H
