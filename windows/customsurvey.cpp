#include "customsurvey.h"

#include "ui_customsurvey.h"
#include <QFileDialog>
#include <QInputDialog>
#include <classes/questiondata.h>
#include <fstream>
#include <windows/dbwindow.h>

using namespace std;

CustomSurvey::CustomSurvey(QWidget *parent, DbManager *db_manager) :
    QWidget(parent),
    ui(new Ui::CustomSurvey), db_man(db_manager)
{
    ui->setupUi(this);



    BuildCombo();
    ui->ShowWindow->setReadOnly(true);

}

CustomSurvey::~CustomSurvey()
{
    delete ui;
}

void CustomSurvey::on_DirectoryButton_clicked(){
  //  on_ClearButton_clicked();

    QUrl StartDir("/Users/Sebastian/Documents");

    file = QFileDialog::getOpenFileUrl(this, tr("here we go"), StartDir,tr("CSV Files (*.csv)") );

    ui->DirectoryTextBox->appendPlainText(file.path());

    cout << "INITIATE FILEMANAGER" << endl;

    f_man = new FileManager(file.path(),ui->SurveyTypeBox->currentIndex(),db_man);

     questions = f_man->get_questions();

}

void CustomSurvey::on_GoButton_clicked(){

    cout << "START DISPLAYING STATISTICS " << endl;

    DisplayStatistics();

}

void CustomSurvey::on_ClearButton_clicked(){

    ui->ShowWindow->moveCursor(QTextCursor::End);
    ui->ShowWindow->clear();
    ui->DirectoryTextBox->clear();
    delete f_man;
    questions.clear();
}

void CustomSurvey::BuildCombo(){

    vector <QString> Surveytypes;

    db_man->select_single_query("SELECT surveytype_name FROM surveytypes", "surveytype_name", Surveytypes);

    for(int i =0; i<Surveytypes.size();++i){
    ui->SurveyTypeBox->addItem(Surveytypes[i]);
    }

}

void CustomSurvey::on_WriteFile_Button_clicked(){

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);

    QList<QUrl> directory;
    if (dialog.exec())
        directory = dialog.selectedUrls();

    QString text = ui->ShowWindow->toPlainText();

    QString filename = file.fileName();
    filename.chop(4);
    filename+="_Statistik.txt";

    QString filepath=directory[0].path();
    filepath=filepath+"/"+filename;

    f_man->saveToTextFile(filepath,text);

}

void CustomSurvey::DisplayStatistics(){

    QString introduction = "<i>Falls nicht anders angegeben, wurden die Mittelwerte der Antworten ermittelt. Möchgliche Antworten waren: 1,2,3,4. Für die Wanderausstellungen giltet: 1 bedeutet volle Zusstimmung, 4 gar keine Zustimmung <\i>" ;
    ui->ShowWindow->append(introduction);
    ui->ShowWindow->append("");

    for (int i=0; i<questions.size();++i){
     // display statistical results, if question type is not unknown and is not a text question.
        if(questions[i].read_question_type()!=0 && questions[i].read_question_type()!=6  ){

            QString MainQuestion="<b>"+questions[i].read_question()+"</b>";
            QString SubQuestion=questions[i].read_subquestion();

            if(questions[i].read_question()!="")
            ui->ShowWindow->append(MainQuestion);

            if(questions[i].read_subquestion()!="")
                ui->ShowWindow->append(SubQuestion);

            ui->ShowWindow->append(questions[i].read_stat_val_string());
            ui->ShowWindow->append("");
        }
    }

    ui->ShowWindow->append("<b>Teilnehmende insgesamt:</b>");
    int size = questions[0].read_data().size();
    ui->ShowWindow->append(QString::number(size));
    ui->ShowWindow->moveCursor(QTextCursor::Start);
}

void CustomSurvey::on_ToDbButton_clicked(){
 //

    QInputDialog *dialog = new QInputDialog(this);
    dialog->setOkButtonText("Speichern");
    dialog->setCancelButtonText("Abbrechen");
    QString Ort = QInputDialog::getText(this, "Seminarort", "Bitte den Ort des Seminares eingeben!");

    f_man->WriteSurveyToDb(Ort);
}
