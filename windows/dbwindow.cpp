#include "windows/dbwindow.h"
#include "windows/datainputpopup.h"

#include "ui_dbwindow.h"
#include "classes/filemanager.h"
#include "QFileDialog"

DbWindow::DbWindow(QWidget *parent, DbManager *dbManager) :
    QWidget(parent),
    ui(new Ui::DbWindow), dbMan(dbManager)
{
    ui->setupUi(this);
    setupTable();
    setupCombo();
    readDatabase();

    connect (dbMan,SIGNAL(databaseChanged()),this,SLOT(readDatabase()));
    connect (ui->DbTable, SIGNAL(cellDoubleClicked(int,int)),this,SLOT(on_ActionButton_clicked()));

}

DbWindow::~DbWindow()
{
    delete ui;
}

void DbWindow::setupTable(){
    ui->DbTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DbTable->setRowCount(50);
    ui->DbTable->setColumnCount(4);

    ui->DbTable->setDragEnabled(false);
    ui->DbTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void DbWindow::readDatabase(){
    //setheaders
    ui->DbTable->clear();
    QStringList TableHeaders;
    TableHeaders.append("Seminar");
    TableHeaders.append("Ort");
    TableHeaders.append("Datum [J M T]");
    TableHeaders.append("Feedbacks");


    ui->DbTable->setHorizontalHeaderLabels(TableHeaders);
    ui->DbTable->horizontalHeader()->setStretchLastSection(false);


    vector <vector <QString> > surveydata;
    vector <QString> column_names;

    column_names.push_back("surveytype_name");
    column_names.push_back("survey_name");
    column_names.push_back("survey_date");
    column_names.push_back("survey_datasize");
    column_names.push_back("survey_id");

    dbMan->selectQuery("SELECT survey_name, survey_date, survey_datasize, survey_id, surveytype_name  "
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id",column_names,surveydata);



    if (!surveydata.empty()){
        int sd_size_inner=surveydata.size();

    // go through outer vectors, columns
        for (int i=0; i<surveydata.size()-1;++i){

            //go through inner vector, rows
            for (int j=0; j<surveydata[0].size();++j){



                QTableWidgetItem *newItem = new QTableWidgetItem(surveydata[i][j]);

                //write survey_id behind the first cell
                if (i==0)
                   newItem->setData(Qt::UserRole,surveydata[sd_size_inner-1][j]);

                ui->DbTable->setItem(j, i, newItem);
            }
        }

    ui->DbTable->sortByColumn(2);
    }


    else {
        cout << "Error reading database. Maybe empty." <<endl;
    }

}
    
void DbWindow::setupCombo(){

    ui->ActionCombo->addItem("Umfrage Auswerten");
    ui->ActionCombo->addItem("Ausgewählten Eintrag löschen");
}

void DbWindow::on_ActionButton_clicked(){

    QString survey_id = ui->DbTable->selectedItems().at(0)->data(Qt::UserRole).toString();
    vector<QString> surveytype_id;
    dbMan->selectSingleQuery("SELECT surveytype_id FROM surveys WHERE survey_id = "+survey_id,"surveytype_id",surveytype_id );

    switch(ui->ActionCombo->currentIndex()){

        case 0:
            evaluateSurvey(survey_id.toInt(), surveytype_id[0].toInt());
        break;

        case 1:
            QMessageBox msgBox;
            msgBox.setText("Ausgewählten Eintrag wirklich löschen?");
            msgBox.setInformativeText("Daten werden aus der Datenbank entfernt.");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();

            if (ret == QMessageBox::Cancel){return;}
            if (ret == QMessageBox::Ok){deleteSurvey(survey_id);}
            break;
    }


}

void DbWindow::deleteSurvey(QString survey_id){

    dbMan->deleteQuery("DELETE FROM surveys WHERE survey_id="+ survey_id);

}

void DbWindow::on_FindPathButton_clicked(bool path_is_set=0){

    if(!path_is_set)
    {QUrl StartDir("~/Documents");
        file = QFileDialog::getOpenFileUrl(this, "Bitte Datenbank auswählen", StartDir,tr("CSV Files (*.csv)") );
        ui->NewSurveyPath->appendPlainText(file.path());
    }

    // OPEN DATA INPUT WINDOW
    newPopup = new DataInputPopup(0,dbMan);
    connect (newPopup, SIGNAL(ok_clicked()),this, SLOT(saveToDatabase()));
    newPopup->show();

    // As soon as user clicks ok in the popup window, DbWindow::SaveToDatabase() is called.


}

void DbWindow::saveToDatabase(){

    fMan = new FileManager(file.path(),newPopup->getSurveyType(),dbMan);

    if(fMan->isReady()){

        fMan->questionsToDb(newPopup->getLocation(),newPopup->getDate());
        newPopup->close();
        readDatabase();
    }

    else {
        newPopup->close();
        on_FindPathButton_clicked(true);

    }
    delete fMan;

}

void DbWindow::evaluateSurvey(int survey_id, int surveytype_id){
    fMan=new FileManager(survey_id,surveytype_id,dbMan);

    newCalcWindow = new CalcWindow(0, dbMan,fMan);
    newCalcWindow->show();
}

