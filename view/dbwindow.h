#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QUrl>
#include "model/dbmanager.h"
#include "model/question.h"
#include "controller/controller.h"
#include "view/calcwindow.h"

#include "view/datainputpopup.h"

namespace Ui {
class DbWindow;
}

class DbWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DbWindow(QWidget *parent = 0);
    ~DbWindow();

    void setupTable();
    void setupCombo();
    void deleteSurvey(QString surveyId);
    void evaluateSurvey(int survey_id, int surveytype_id);




signals:


public slots:
    void on_ActionButton_clicked();
    void updateTableContent();
    void on_FindPathButton_clicked(bool path_is_set);
    void saveToDatabase();



private:
    Ui::DbWindow *ui;


    DataInputPopup *newPopup;
    QUrl selectedFile;
    CalcWindow *newCalcWindow;
//    FileManager *f_man;
//    vector <questiondata> questions;

};

#endif // DBWINDOW_H
