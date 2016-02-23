#include "customsurvey.h"
#include "ui_customsurvey.h"
#include <QFileDialog>
#include <questiondata.h>
#include <fstream>

using namespace std;

CustomSurvey::CustomSurvey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomSurvey)
{
    ui->setupUi(this);
    db_man= new DbManager("/Users/Sebastian/Documents/CPP/AFZ/Feedbacker/database/fb_database.db");
    BuildCombo();
    ui->ShowWindow->setReadOnly(true);


    // 0 - ignore
    // 1 - average value
    // 2 - share of non zeros // do you agree with
    // 3 - gender
    // 4 - age
    // 5 - School type
    // 6 - text
/*
   int question_types_DA_TS[] =  {0,0,0,0,0,0,0,0,0,1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,6,6,6,4,3,5,0,0}; //fill here according to survey
   int question_types_DA_FBS[]={0};
   int question_types_BAN_TS[]=  {0};
   int question_types_BAN_FBS[]={0};
*/
    /*
   for (int i =0; i<sizeof(question_types_DA_TS)/sizeof(int);++i)
       questiontypes_DA_TS.push_back(question_types_DA_TS[i]);


  for (int i =0; i<sizeof(question_types_DA_FBS)/sizeof(int);++i)
       questiontypes_DA_FBS.push_back(question_types_DA_FBS[i]);

  for (int i =0; i<sizeof(question_types_BAN_TS)/sizeof(int);++i)
       questiontypes_BAN_TS.push_back(question_types_BAN_TS[i]);

  for (int i =0; i<sizeof(question_types_BAN_FBS)/sizeof(int);++i)
       questiontypes_BAN_FBS.push_back(question_types_BAN_FBS[i]);
*/
}

CustomSurvey::~CustomSurvey()
{
    delete ui;
}

void CustomSurvey::on_DirectoryButton_clicked(){

    QUrl StartDir("/Users/Sebastian");

    file = QFileDialog::getOpenFileUrl(this, tr("here we go"), StartDir,tr("CSV Files (*.csv)") );

    ui->DirectoryTextBox->appendPlainText(file.path());

    cout << "INITIATE FILEMANAGER" << endl;

    f_man = new FileManager(file.path(),ui->SurveyTypeBox->currentIndex());

     questions = f_man->get_questions();

}

void CustomSurvey::on_GoButton_clicked(){

    cout << "START DISPLAYING STATISTICS " << endl;

    DisplayStatistics();

}

void CustomSurvey::on_ClearButton_clicked(){
    ui->ShowWindow->moveCursor(QTextCursor::End);
    ui->ShowWindow->clear();
  //  samples.clear();                          // TODO: CLEAR SAMPLES
    fb_values.clear();
    fb_headers.clear();
    datamatrix.clear();
    ui->DirectoryTextBox->clear();


}

void CustomSurvey::BuildCombo(){

    vector <QString> Surveytypes;

    db_man->select_single_query("SELECT name FROM surveytypes", "name", Surveytypes);

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

    cout << "filepath: " << filepath.toStdString() << endl;

     ofstream myfile;
     myfile.open (filepath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();

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
        else {
            cout << "QUESTION IGNORED" << endl;
        }

    }

    ui->ShowWindow->append("<b>Teilnehmende insgesamt:</b>");
    int size = questions[0].read_data().size();
    ui->ShowWindow->append(QString::number(size));
    ui->ShowWindow->moveCursor(QTextCursor::Start);
}

