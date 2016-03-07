#include "classes/filemanager.h"
#include "classes/questiondata.h"
#include "classes/dbmanager.h"


/**
 * TODO:
 *
 * SEE TEXT FILE
 *
 * */

FileManager::FileManager(){}

FileManager::FileManager(QString path, int stype_id, DbManager *database_man) : file_path(path), surveytype_id(stype_id), db_man(database_man)
{

ReadSurveytypes();

if(ReadCsv())
    ReadDataToQuestions();

}

bool FileManager::ReadCsv(){
    bool success = false;

    cout << "START READING CSV" << endl;

    ifstream file;
    file.open(file_path.toStdString().c_str());

    if(!file.is_open()){
        cout << "WARNING: file has not been opened!"<< endl;
        success = false;
    }

    else {success = true;}

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

    if (success==true && datamatrix.empty()){
        cout << "ERROR. READING CSV FAILED. " << endl << "Check .csv dialect. "
                                                              "line breakers could be different.  maybe: \r\n " << endl;
    success = false;
    }


    return success;
}

void FileManager::ReadDataToQuestions(){

    cout << "START READING DATA TO QUESTION OBJECTS" << endl;
// fills CSV Data from vector < vector <...> > datamatrix to questiondata objects.

    int m = datamatrix[0].size();


    int id=0;

    for(int i=0; i<m;++i){


        if(question_types[surveytype_id][i].toInt()!=0){

            questiondata *temp_question = new questiondata;

            temp_question->write_questiontype(question_types[surveytype_id][i].toInt());
            temp_question->write_question(QString::fromStdString(datamatrix[0][i]));
            temp_question->write_subquestion(QString::fromStdString(datamatrix[1][i]));
            temp_question->write_data_fromStdString(datamatrix,i);

            if(temp_question->read_question()!="")
                ++id;

                temp_question->write_ID(id);      // a question and its subquestions share the same id

                questions.push_back(*temp_question);
                delete temp_question;
            }

        }

}

void FileManager::ReadSurveytypes(){
    cout << "START READING SURVEYTYPES FROM DB" << endl;

    int surveytypes_size =0;
    db_man->count_lines("surveytypes",surveytypes_size);
    question_types.resize(surveytypes_size);

    for (int i=0; i<surveytypes_size; ++i){
        db_man->select_single_query("SELECT qtype FROM qtypes WHERE surveytype_id = " + QString::number(i),"qtype",question_types[i] );
    }


}

void FileManager::WriteSurveyToDb(QString Location){
    cout << "START WRITING SURVEY TO DATABASE!" << endl;

    // INSERT SURVEY
    db_man->insert_query("INSERT INTO surveys VALUES (NULL," + QString::number(surveytype_id) + ",'" + Location +"', '02/24/2015', "+ QString::number(questions[0].read_data().size()) +")");

    vector <QString> temp_survey_id;
    db_man->select_single_query("SELECT last_insert_rowid() FROM surveys", "last_insert_rowid()",temp_survey_id);

    vector <QString> temp_mainquestion_id;
    vector <QString> temp_subquestion_id;
    vector <int> temp_data;


    // INSERT QUESTIONS WITH SUBQUESTIONS
    for (int i=0; i<questions.size();++i){

        if (questions[i].read_question() != ""){

            db_man->insert_query("INSERT INTO questions VALUES(NULL, "+ temp_survey_id[0] +", '"+ questions[i].read_question()+"'," + QString::number(questions[i].read_question_type()) + ")");

            temp_mainquestion_id.clear();
            db_man->select_single_query("SELECT last_insert_rowid() FROM questions", "last_insert_rowid()",temp_mainquestion_id);
        }


        db_man->insert_query("INSERT INTO subquestions VALUES (NULL, " + temp_mainquestion_id[0] +", '"+ questions[i].read_subquestion()+"')"); //

         // NOW INSERT DATA CONNECTED TO SUBQUESTIONS
        temp_subquestion_id.clear();
        db_man->select_single_query("SELECT last_insert_rowid() FROM subquestions", "last_insert_rowid()",temp_subquestion_id);

        temp_data.clear();
        temp_data=questions[i].read_data();
        for (int j=0; j<temp_data.size(); ++j){

            db_man->insert_query("INSERT INTO data VALUES(NULL, " + temp_subquestion_id[0] + ", " + QString::number(temp_data[j]) +")");
        }

    }

}

vector <questiondata> FileManager::get_questions(){
    return questions;
}

void FileManager::saveToTextFile(QString filepath, QString text){
    cout << "filepath: " << filepath.toStdString() << endl;

     ofstream myfile;
     myfile.open (filepath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();
}
