#include "datainputpopup.h"
#include "ui_DataInputPopup.h"


DataInputPopup::DataInputPopup(QWidget *parent, DbManager *database_manager) :
    QWidget(parent),
    ui(new Ui::DataInputPopup),
    db_man(database_manager)
{
    ui->setupUi(this);
    ui->OkButton->setEnabled(false);
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    ui->HeaderLabel->setFont(font);

    SetupCombo();


}

DataInputPopup::~DataInputPopup()
{
    delete ui;
}

void DataInputPopup::SetupCombo(){


    db_man->select_single_query("SELECT surveytype_name FROM surveytypes", "surveytype_name", Surveytypes);


    for(int i =0; i<Surveytypes.size();++i){
    ui->SurveyTypeBox->addItem(Surveytypes[i]);
    }

    ui->SurveyTypeBox->addItem("-- Bitte Seminartyp auswählen --");
    ui->SurveyTypeBox->setCurrentIndex(Surveytypes.size());
}

int DataInputPopup::GetSurveyType(){
    return ui->SurveyTypeBox->currentIndex();
}

QString DataInputPopup::GetLocation(){
    return ui->LocationInput->toPlainText();
}

QString DataInputPopup::GetDate(){
    QDate date= ui->CalendarWidget->selectedDate();
    return QString::number(date.month())+"-" + QString::number(date.day()) + "-" + QString::number(date.year());

}

void DataInputPopup::on_OkButton_clicked(){
    emit ok_clicked();
}

void DataInputPopup::on_CancelButton_clicked(){
    close();
}

void DataInputPopup::on_SurveyTypeBox_currentIndexChanged(int index){
    if (index!=Surveytypes.size() && ui->LocationInput->toPlainText()!="")
        ui->OkButton->setEnabled(true);

    else ui->OkButton->setEnabled(false);
}


void DataInputPopup::on_LocationInput_textChanged(){
    on_SurveyTypeBox_currentIndexChanged(ui->SurveyTypeBox->currentIndex());
}
