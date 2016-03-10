#include "windows/dbwindow.h"
#include "windows/datainputpopup.h"

#include "ui_dbwindow.h"
#include "classes/filemanager.h"
#include "QFileDialog"

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
    ui->ActionCombo->addItem("Umfrage Auswerten");
    ui->ActionCombo->addItem("Ausgewählten Eintrag löschen");
}

void DbWindow::on_ActionButton_clicked(){

    QString survey_id = ui->DbTable->selectedItems().at(4)->text();

    switch(ui->ActionCombo->currentIndex()){

        case 0:
            // FUNCTION: READ DATA FROM DB TO QUESTIONS
            NewCalcWindow = new CalcWindow(0, db_man,f_man);
            NewCalcWindow->show();

        break;



        case 1:
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

}

void DbWindow::on_FindPathButton_clicked(){


    QUrl StartDir("~/Documents");

    file = QFileDialog::getOpenFileUrl(this, "Bitte Datenbank auswählen", StartDir,tr("CSV Files (*.csv)") );

    ui->NewSurveyPath->appendPlainText(file.path());

    // OPEN DATA INPUT WINDOW
    NewPopup = new DataInputPopup(0,db_man);
    connect (NewPopup, SIGNAL(ok_clicked()),this, SLOT(SaveToDatabase()));
    NewPopup->show();

    // READ FILE AND SAVE TO DATABASE


}

void DbWindow::SaveToDatabase(){

    f_man = new FileManager(file.path(),NewPopup->GetSurveyType(),db_man);
    f_man->QuestionsToDb(NewPopup->GetLocation(),NewPopup->GetDate());
    NewPopup->close();

}
