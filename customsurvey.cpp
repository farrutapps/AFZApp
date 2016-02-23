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
    db_man= new DbManager("users/Sebastian/Documents/CPP/AFZ/Feedbacker/database/feedbacker.db");
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



   /* filename = QFileDialog::getOpenFileUrl(this,
        tr("Open Image"), "/Users/Sebastian", tr("Image Files (*.png *.jpg *.bmp)"));
*/
    QUrl StartDir("/Users/Sebastian");

    file = QFileDialog::getOpenFileUrl(this, tr("here we go"), StartDir,tr("CSV Files (*.csv)") );

    ui->DirectoryTextBox->appendPlainText(file.path());

    f_man = new FileManager(file.path(),ui->SurveyTypeBox->currentIndex());

  //  cout << "CSV SCCESSFULLY LOADED" << endl;


   // ReadCsv(file.path().toStdString());

}

void CustomSurvey::ReadCsv(string filepath){

    cout << "START READING CSV..." << endl;


    ifstream file;
    file.open(filepath.c_str());

   if(!file.is_open()){
   cout << "file could not be opened! error"<< endl;
   assert(0);
   }

    string value;


    vector <string> dataset;

    string delimiter = "\r\n";      // \r for mac. \r\n for windows csv
    string token1;
    string token2;

    while (getline(file,value,';'))
    {
        // check if row delimiter is part of value. if yes, eliminate it and jump to next line.


        if (value.find(delimiter) != std::string::npos) {
        token1 = value.substr(0, value.find(delimiter));
        token2 = value.substr(value.find(delimiter)+delimiter.size(),value.size());

        token1.push_back('"');


        dataset.push_back(token1);
        datamatrix.push_back(dataset);
        dataset.clear();
        dataset.push_back(token2);
        }
        else dataset.push_back(value);

    }
    if (datamatrix.empty()){
        cout << "ERROR. READING CSV FAILED. STOP." << endl << "Check .csv dialect. "
                                                              "line breakers could be different.  maybe: \r\n " << endl;
    }
    cout << "...CSV SUCESSFULLY READ!" << endl;

   // ExtractHeaders();
   // ExtractNumbers();


    cout << "DATA SUCCESSFULLY READ - ready to go!" << endl;
    }

void CustomSurvey::ExtractHeaders(){
    // extracts headers from datamatrix and puts them into one single array

 cout << "START BUILDING HEADERS" << endl;

    for (int i=0; i<datamatrix[0].size();++i){

        if(datamatrix[0][i]=="")
        {

            fb_headers.push_back(datamatrix[1][i]);

        }
        else{
            if (datamatrix[1][i]=="locker")   {    //workaround for "locker" problem
                fb_headers.push_back(datamatrix[1][i]);
            }
            else{
            fb_headers.push_back(datamatrix[0][i]);

            }
        }
    }
    cout << "HEADERS SUCCESSFULLY BUILT" << endl;


}

void CustomSurvey::ExtractNumbers(){
// extracts number-strings from datamatrix and converts them to doubles. returns a new matrix.

    fb_values.resize(datamatrix.size()-2,vector <double>(datamatrix[2].size()));

    // go through datasets
    for(int i=0; i<fb_values.size();++i){

        //go through questions
        for (int j=0; j<fb_values[2].size();++j){
            fb_values[i][j]=atoi(datamatrix[i+2][j].c_str());
        }
    }
}


void CustomSurvey::on_GoButton_clicked(){

    DisplayStatistics();

}

void CustomSurvey::on_ClearButton_clicked(){
    ui->ShowWindow->moveCursor(QTextCursor::End);
    ui->ShowWindow->clear();
    samples.clear();
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

void CustomSurvey::SortSamples(){
    // sorts samples according to their questiontypes from 0 to the highest type

    int n = samples.size();
    questiondata temp;

    for(int i=0; i< n; i++)
    {
        for(int j=i; j< n-1; j++)
        {
        if(samples[i].read_question_type() > samples[j+1].read_question_type() ){
            temp= samples[i];
            samples[i]= samples[j+1];
            samples[j+1]= temp;
            }
        }
    }
}

void CustomSurvey::ReadDataToSamples(){

    int m = datamatrix[0].size();

    samples.resize(m);
    QString result;
    int id=0;

    for(int i=0; i<m;++i){
        samples[i].write_question(QString::fromStdString(datamatrix[0][i]));
        samples[i].write_subquestion(QString::fromStdString(datamatrix[1][i]));
        samples[i].write_data_fromStdString(datamatrix,i);

            if(samples[i].read_question()!="")
            ++id;

            samples[i].write_ID(id);

    for (int i=0; i<m;++i){

        switch(ui->SurveyTypeBox->currentIndex()){
            case 0: // DA, Trainingsseminar
                samples[i].write_questiontype(questiontypes_DA_TS[i]);
                break;

            case 1: // BAN, Trainingsseminar
                samples[i].write_questiontype(questiontypes_BAN_TS[i]);
                break;

            case 2: //DA, Feedbackseminar
                samples[i].write_questiontype(questiontypes_DA_FBS[i]);
                break;
            case 3: // BAN, Feedbackseminar
                samples[i].write_questiontype(questiontypes_BAN_FBS[i]);
                break;

            default: cout << "ERROR: Survey Type not implemented!!" << endl;
        }
    }

    }

    cout << "DATA READ INTO SAMPLES" << endl;

    /*

    samples.resize(fb_headers.size());
    QString result;

    for (int i=0; i<fb_headers.size();++i){   //-2 because i want to hide the last (two) questions

        samples[i].write_question(QString::fromStdString(fb_headers[i]));
        samples[i].write_data(fb_values, i);

        switch(ui->SurveyTypeBox->currentIndex()){
            case 0: // DA, Trainingsseminar
                samples[i].write_questiontype(questiontypes_DA_TS[i]);
                break;

            case 1: // BAN, Trainingsseminar
                samples[i].write_questiontype(questiontypes_BAN_TS[i]);
                break;

            case 2: //DA, Feedbackseminar
                samples[i].write_questiontype(questiontypes_DA_FBS[i]);
                break;
            case 3: // BAN, Feedbackseminar
                samples[i].write_questiontype(questiontypes_BAN_FBS[i]);
                break;

            default: cout << "ERROR: Survey Type not implemented!!" << endl;
        }
    }
    */
}

void CustomSurvey::DisplayStatistics(){

    QString introduction = "<i>Falls nicht anders angegeben, wurden die Mittelwerte der Antworten ermittelt. Möchgliche Antworten waren: 1,2,3,4. Für die Wanderausstellungen giltet: 1 bedeutet volle Zusstimmung, 4 gar keine Zustimmung <\i>" ;
    ui->ShowWindow->append(introduction);
    ui->ShowWindow->append("");

    vector <questiondata> questions = f_man->get_questions();

    for (int i=0; i<samples.size();++i){
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

void CustomSurvey::MergeSamples(){
 /*   questiondata temp;
    int id_in_work=0;
    bool found=0;
    int start_index=0;
    int end_index=0;

    for(int i=0; i<samples.size();++i){

        if(!found)
        {
            if(samples[i].read_ID()==samples[i+1].read_ID()){
                found=1;
                start_index=i;
            }
        }
       else {
            if(samples[i].read_ID()!=samples[i+1].read_ID()){
                found=0;
                end_index=i;

                for(int j=start_index; j<end_index; ++j){
                    temp.push_back_datamatrix(samples[j]);
                }
                samples.erase(start_index,end_index);

                temp.write_question(samples[start_index].read_question);
                temp
                samples.push_back(temp);

            }
        }

    }
*/
}
