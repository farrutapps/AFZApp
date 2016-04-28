#include "datainputpopup.h"
#include "ui_DataInputPopup.h"




DataInputPopup::DataInputPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataInputPopup)

{
    ui->setupUi(this);
    ui->OkButton->setEnabled(false);
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    ui->HeaderLabel->setFont(font);

    setupCombo();


}

DataInputPopup::~DataInputPopup()
{
    delete ui;
}

void DataInputPopup::setupCombo(){

    Controller::getSurveyTypes(surveyTypes);



    for(int i =0; i<surveyTypes.size();++i){
    ui->SurveyTypeBox->addItem(surveyTypes[i]);
    }

    ui->SurveyTypeBox->addItem("-- Bitte Seminartyp auswählen --");
    ui->SurveyTypeBox->setCurrentIndex(surveyTypes.size());
}

int DataInputPopup::getSurveyType(){
    return ui->SurveyTypeBox->currentIndex();
}

QString DataInputPopup::getLocation(){
    return ui->LocationInput->toPlainText();
}

QString DataInputPopup::getDate(){
    QDate date= ui->CalendarWidget->selectedDate();
    return QString::number(date.month())+"-" + QString::number(date.day()) + "-" + QString::number(date.year());

}

void DataInputPopup::on_OkButton_clicked(){
    emit okClicked();
}

void DataInputPopup::on_CancelButton_clicked(){
    close();
}

void DataInputPopup::on_SurveyTypeBox_currentIndexChanged(int index){
    if (index!=surveyTypes.size() && ui->LocationInput->toPlainText()!="")
        ui->OkButton->setEnabled(true);

    else ui->OkButton->setEnabled(false);
}


void DataInputPopup::on_LocationInput_textChanged(){
    on_SurveyTypeBox_currentIndexChanged(ui->SurveyTypeBox->currentIndex());
}
