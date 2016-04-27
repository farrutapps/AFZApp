#include "view/dbwindow.h"
#include "view/datainputpopup.h"

#include "ui_dbwindow.h"
#include "model/filemanager.h"
#include "QFileDialog"
#include "model/import.h"

DbWindow::DbWindow(QWidget *parent, DbManager *dbManager) :
    QWidget(parent),
    ui(new Ui::DbWindow), dbMan(dbManager)
{
    ui->setupUi(this);
    setupTable();
    updateTableContent();
    
    setupCombo();
    

    connect (dbMan,SIGNAL(databaseChanged()),this,SLOT(updateTableContent()));
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

//SUBSTITUTET
void DbWindow::updateTableContent(){


    //setheaders
    ui->DbTable->clear();
    QStringList TableHeaders;
    TableHeaders.append("Seminar");
    TableHeaders.append("Ort");
    TableHeaders.append("Datum [J M T]");
    TableHeaders.append("Anzahl TN");


    ui->DbTable->setHorizontalHeaderLabels(TableHeaders);
    ui->DbTable->horizontalHeader()->setStretchLastSection(false); 

    int numberOfSurveys;
    if (fMan->surveysFromDbToModel(numberOfSurveys)){

        vector<QString> surveyFacts;

            //go through inner vector, rows
            for (int j=0; j<numberOfSurveys;++j){

                surveyFacts.clear();
                fMan->getSurveyFacts(surveyFacts,j);

                // -1 in order to write surveyID behind first cell
                for(int i=0; i<surveyFacts.size()-1; ++i){
                QTableWidgetItem *newItem = new QTableWidgetItem(surveyFacts[i]);

                //write survey_id behind the first cell
                if (i==0)
                   newItem->setData(Qt::UserRole,surveyFacts.back());

                ui->DbTable->setItem(j, i, newItem);
                }


    ui->DbTable->sortByColumn(2);
            }


    }
}

void DbWindow::setupCombo(){

    ui->ActionCombo->addItem("Umfrage Auswerten");
    ui->ActionCombo->addItem("Ausgewählten Eintrag löschen");
}

void DbWindow::on_ActionButton_clicked(){

    int surveyId = ui->DbTable->selectedItems().at(0)->data(Qt::UserRole).toInt();


    switch(ui->ActionCombo->currentIndex()){

        case 0:
            fMan->newCalculation(surveyId);
        
        break;

        case 1:
            QMessageBox msgBox;
            msgBox.setText("Ausgewählten Eintrag wirklich löschen?");
            msgBox.setInformativeText("Daten werden aus der Datenbank entfernt.");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();

            if (ret == QMessageBox::Cancel){return;}
            if (ret == QMessageBox::Ok){deleteSurvey(QString::number(surveyId));}
            break;
    }


}

void DbWindow::deleteSurvey(QString survey_id){

    dbMan->deleteQuery("DELETE FROM surveys WHERE survey_id="+ survey_id);

}

void DbWindow::on_FindPathButton_clicked(bool path_is_set){


    if(!path_is_set)
    {QUrl StartDir("~/Documents");
         selectedFile = QFileDialog::getOpenFileUrl(this, "Bitte Datenbank auswählen", StartDir,"CSV Files (*.csv)" );

    }

    // OPEN DATA INPUT WINDOW
    newPopup = new DataInputPopup(0,dbMan);
    connect (newPopup, SIGNAL(ok_clicked()),this, SLOT(newImport()));
    newPopup->show();

    // As soon as user clicks ok in the popup window, DbWindow::SaveToDatabase() is called.
}


void DbWindow::newImport(){

    if (fMan->newImport(newPopup->getLocation(),newPopup->getDate(),newPopup->getSurveyType(),selectedFile.path())){
        newPopup->close();
        updateTableContent();
    }

    else {
        newPopup->close();
        on_FindPathButton_clicked(true);
    }
}



