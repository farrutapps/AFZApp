#include "windows/dbwindow.h"
#include "ui_dbwindow.h"

DbWindow::DbWindow(QWidget *parent, DbManager *db_manager) :
    QWidget(parent),
    ui(new Ui::DbWindow), db_man(db_manager)
{
    ui->setupUi(this);
    SetupTable();
    SetupCombo();
    ReadDatabase();

    connect (db_man,SIGNAL(database_changed()),this,SLOT(ReadDatabase()));
}

DbWindow::~DbWindow()
{
    delete ui;
}

void DbWindow::SetupTable(){
    ui->DbTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DbTable->setRowCount(10);
    ui->DbTable->setColumnCount(5);

    ui->DbTable->setDragEnabled(false);
    ui->DbTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

void DbWindow::ReadDatabase(){
    //setheaders
    ui->DbTable->clear();
    QStringList TableHeaders;
    TableHeaders.append("Seminar");
    TableHeaders.append("Ort");
    TableHeaders.append("Datum");
    TableHeaders.append("Feedbacks");
    TableHeaders.append("Datenbank ID");

    ui->DbTable->setHorizontalHeaderLabels(TableHeaders);
    ui->DbTable->horizontalHeader()->setStretchLastSection(false);
    ui->DbTable->setRowHidden(4,true);

    vector <vector <QString> > surveydata;
    vector <QString> column_names;

    column_names.push_back("surveytype_name");
    column_names.push_back("survey_name");
    column_names.push_back("survey_date");
    column_names.push_back("survey_datasize");
    column_names.push_back("survey_id");

    db_man->select_query("SELECT survey_name, survey_date, survey_datasize, survey_id, surveytype_name  "
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id",column_names,surveydata);


    if (!surveydata.empty()){

       // go through inner vectors
        for (int i=0; i<surveydata[0].size();++i){
            //go through outer vector
            for (int j=0; j<surveydata.size();++j){
                QTableWidgetItem *newItem = new QTableWidgetItem(surveydata[j][i]);
                ui->DbTable->setItem(j, i, newItem);
            }
        }
    }

    else {
        cout << "Error reading database. Maybe empty." <<endl;
    }
}
    
void DbWindow::SetupCombo(){
    ui->ActionCombo->addItem("Ausgewählten Eintrag löschen");
}

void DbWindow::on_ActionButton_clicked(){

    QString survey_id = ui->DbTable->selectedItems().at(4)->text();

    switch(ui->ActionCombo->currentIndex()){
        case 0:
        QMessageBox msgBox;
        msgBox.setText("Ausgewählten Eintrag wirklich löschen?");
        msgBox.setInformativeText("Daten werden aus der Datenbank entfernt.");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Cancel){return;}
        if (ret == QMessageBox::Ok){DeleteSurvey(survey_id);}
        break;
    }


}

void DbWindow::DeleteSurvey(QString survey_id){

    db_man->delete_query("DELETE FROM surveys WHERE survey_id="+ survey_id);

    vector <QString> q_ids;
    vector <QString> sq_ids;
    vector <QString> d_ids;

    db_man->blockSignals(true);

    db_man->select_single_query("SELECT question_id FROM questions WHERE survey_id ="+survey_id, "question_id",q_ids);
    db_man->delete_query("DELETE FROM questions WHERE survey_id="+survey_id);

    for (int i=0; i<q_ids.size();++i){
        db_man->select_single_query("SELECT subquestion_id FROM subquestions WHERE question_id ="+q_ids[i], "subquestion_id",sq_ids);
        db_man->delete_query("DELETE FROM subquestions WHERE question_id="+q_ids[i]);

        for (int j=0; j<sq_ids.size();++j){
           db_man->delete_query("DELETE FROM data WHERE subquestion_id="+sq_ids[j]);
        }
    }
    db_man->blockSignals(false);
    ReadDatabase();
}

