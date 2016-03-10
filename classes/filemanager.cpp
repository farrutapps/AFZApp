#include "classes/filemanager.h"
#include "classes/questiondata.h"
#include "classes/dbmanager.h"
#include "windows/dbwindow.h"

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

if(CsvToDatamatrix())
    DatamatrixToQuestions();

}

bool FileManager::CsvToDatamatrix(){
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

void FileManager::DatamatrixToQuestions(){

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

void FileManager::QuestionsToDb(QString Location, QString Date){
    cout << "START WRITING SURVEY TO DATABASE!" << endl;

    // INSERT SURVEY
    int survey_id=0;
    int question_id=0;
    int subquestion_id=0;
    vector <int> temp_data;

    db_man->insert_query("INSERT INTO surveys(surveytype_id, survey_name, survey_date, survey_datasize) VALUES (" + QString::number(surveytype_id) + ",'" +
                         Location +"', '02/24/2015', "+ QString::number(questions[0].read_data().size()) + ") RETURNING survey_id","survey_id",survey_id);


    // INSERT QUESTIONS WITH SUBQUESTIONS
    for (int i=0; i<questions.size();++i){

        if (questions[i].read_question() != ""){

            db_man->insert_query("INSERT INTO questions(survey_id, question_name, question_type) VALUES(" + QString::number(survey_id) +", '"+ questions[i].read_question()+"'," + QString::number(questions[i].read_question_type()) + ") RETURNING question_id", "question_id", question_id);
        }

        db_man->insert_query("INSERT INTO subquestions(question_id, subquestion_name) VALUES (" + QString::number(question_id) +", '"+ questions[i].read_subquestion()+"') RETURNING subquestion_id","subquestion_id",subquestion_id); //

         // NOW INSERT DATA CONNECTED TO SUBQUESTIONS


        temp_data.clear();
        temp_data=questions[i].read_data();
        for (int j=0; j<temp_data.size(); ++j){

            db_man->insert_query("INSERT INTO data(subquestion_id, answer) VALUES(" + QString::number(subquestion_id) + ", " + QString::number(temp_data[j]) +")");
        }

    }

    questions.clear();
    datamatrix.clear();

}

vector <questiondata> FileManager::get_questions(){
    return questions;
}

void FileManager::QuestionsToTextFile(QString filepath, QString text){
    cout << "filepath: " << filepath.toStdString() << endl;

     ofstream myfile;
     myfile.open (filepath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();
}

void FileManager::DbToQuestions(int survey_id){
    vector < vector <QString> > survey_data;
    vector <QString> column_names;
    column_names.push_back("surveytype_name");
    column_names.push_back("survey_name");
    column_names.push_back("survey_date");

    db_man->select_query("SELECT surveytype_name, survey_name, survey_date"
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id"
                         "WHERE survey_id = "+ QString::number(survey_id),column_names,survey_data);

    questions.clear();

    vector < vector <QString> > question_data;
    vector < QString > q_column_names;
    q_column_names.push_back("question_id");
    q_column_names.push_back("question_name");

    db_man->select_query("SELECT question_id, question_name, question_type FROM questions WHERE survey_id="+QString::number(survey_id),q_column_names, question_data);

    vector <vector <QString> > subquestion_names;
    vector <QString> sq_col_names;
    sq_col_names.push_back("subquestion_id");
    sq_col_names.push_back("subquestion_name");



    for (int i=0; i<question_data[0].size();++i){
        questions[i].write_question(question_data[1][i]);
        questions[i].write_surveytype(question_data[2][i]);
        db_man->select_query("SELECT subquestion_id, subquestion_name FROM subquestions WHERE question_id ="+question_data[0][i],sq_col_names,subquestion_names);

        for(int j=0; j<subquestion_data[0].size){
            questions
        }
    }



}





















